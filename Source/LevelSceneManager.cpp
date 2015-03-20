#include "ResourceCache.h"
#include "UI.h"
#include "Button.h"
#include "Graphics.h"
#include "CoreEvents.h"
#include "UIEvents.h"
#include "Renderer.h"
#include "Viewport.h"
#include "Input.h"
#include "Random.h"
#include "StaticModel.h"
#include "Model.h"
#include "Material.h"
#include "ValueAnimation.h"
#include "Log.h"
#include "CollisionShape.h"

#include <ctime>
#include <iostream>

#include "mainApp.h"
#include "LevelSceneManager.h"

LevelSceneManager::LevelSceneManager(Context *context) : AbstractSceneManager(context)
{
    context_ = context;
    _finished = false;
}

void LevelSceneManager::PlaceBuildings(int mapDimension, ResourceCache* cache, Terrain *terrain, std::map<String, int> buildings)
{
    for(buildingsIterator it = buildings.begin(); it != buildings.end(); it++)
    {
        String modelName =  it->first;
        int buildingCount = it->second;
        for(int i =0; i < buildingCount; i++)
        {
            bool buildingWasPlaced = false;
            int currentTryCount = 0;
            while(!buildingWasPlaced && currentTryCount < MAX_PLACEMENT_TRY_COUNT)
            {
                int xCoord = Random(-mapDimension, mapDimension);
                int zCoord = Random(-mapDimension, mapDimension);
                float yCoord = terrain->GetHeight(Vector3(xCoord, 0, zCoord));
                Vector3 position = Vector3(xCoord, yCoord, zCoord);
                bool wasNearestCoordsFound = false;
                for(auto j=_buildingsCoords.Begin(); j != _buildingsCoords.End(); j++)
                {

                    Vector3 currentVector = Vector3(j->x_, j->y_, j->z_);
                    Vector3 dist = currentVector - position;
                    if(dist.Length() < _configReader->GetMinimalBuildingsDist())
                    {
                        wasNearestCoordsFound = true;
                        break;
                    }
                }
                if(wasNearestCoordsFound)
                {
                    currentTryCount++;
                    break;
                }
                else
                {
                    _buildingsCoords.Push(position);
                    buildingWasPlaced = true;
                    Node* buildingNode = _scene->CreateChild(modelName+i);
                    buildingNode->SetPosition(position);
                    Model * loadedModel = cache->GetResource<Model>("Models/"+modelName+".mdl");
                    CollisionShape *shape = new CollisionShape(context_);
                    shape->SetBox(loadedModel->GetBoundingBox().Size());
                    buildingNode->AddComponent(shape, 100, CreateMode::LOCAL);
                    StaticModel* buildingModel = buildingNode->CreateComponent<StaticModel>();
                    buildingModel->SetModel(loadedModel);
                    buildingModel->SetMaterial(cache->GetResource<Material>("Materials/Building.xml"));
                }
            }

        }
    }
}

void LevelSceneManager::PlaceGarbage(int mapDimension, ResourceCache *cache, Terrain *terrain, std::map<String, int> garbage)
{
    for(buildingsIterator it = garbage.begin(); it != garbage.end(); it++)
    {
        String modelName =  it->first;
        int garbageCount = it->second;
        for(int i =0; i < garbageCount; i++)
        {
            int xCoord = Random(-mapDimension, mapDimension);
            int zCoord = Random(-mapDimension, mapDimension);
            float yCoord = terrain->GetHeight(Vector3(xCoord, 0, zCoord));
            Vector3 position = Vector3(xCoord, yCoord, zCoord);
            _garbageCoords.Push(position);
            Node* garbageNode = _scene->CreateChild(modelName+i);
            garbageNode->SetPosition(position);
            StaticModel* garbageModel = garbageNode->CreateComponent<StaticModel>();
            garbageModel->SetModel(cache->GetResource<Model>("Models/"+modelName+".mdl"));
            garbageModel->SetMaterial(cache->GetResource<Material>("Materials/"+modelName+".xml"));
        }
    }
}

void LevelSceneManager::Setup(MainApp *app)
{
    std::time_t result = std::time(0);
    SetRandomSeed(result);
    _mainApp = app;

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    _scene = new Scene(context_);
    SharedPtr<File> file = cache->GetFile("Scenes/levelScene.xml");
    _scene->LoadXML(*file);

    _terrainNode = _scene->GetChild("terrain");

    Terrain *terrain = _terrainNode->GetComponent<Terrain>();

    if(!_configReader)
    {
        _configReader = new LevelConfigReader(context_);
        _configReader->ReadConfig(cache->GetResource<XMLFile>("Config/LevelConfig.xml"));
    }
    std::map<String, int> buildings = _configReader->GetBuildings();
    std::map<String, int> garbageItems = _configReader->GetGarbage();
    int mapDimension = _configReader->GetMapDimension();
    PlaceBuildings(mapDimension, cache, terrain, buildings);
    PlaceGarbage(mapDimension, cache, terrain, garbageItems);

    NavigationMesh *navigationMesh = _terrainNode->GetComponent<NavigationMesh>();
    navigationMesh->SetPadding(Vector3(0.0f, 10.0f, 0.0f));
    navigationMesh->Build();

    UI* ui = GetSubsystem<UI>();
    ui->Clear();
    XMLFile *defaultStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    ui->GetRoot()->SetDefaultStyle(defaultStyle);

    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto();
    ui->SetCursor(cursor);
    Graphics* graphics = GetSubsystem<Graphics>();
    cursor->SetPosition(graphics->GetWidth() / 2, graphics->GetHeight() / 2);

    XMLFile *uiLayout = cache->GetResource<XMLFile>("UI/levelUI.xml");
    SharedPtr<UIElement> layoutRoot = ui->LoadLayout(uiLayout);
    ui->GetRoot()->AddChild(layoutRoot);

    _robotNode = _scene->GetChild("robot");
    _hero = new Hero(context_);

    Vector3 oldPos = _robotNode->GetPosition();
    float newY = terrain->GetHeight(oldPos);
    _robotNode->SetPosition(Vector3(oldPos.x_, newY + 1, oldPos.z_));

    Node *cameraNode =  _scene->GetChild("camera");
    Node *centerPos =  cameraNode->GetChild("center");
    Camera *camera = cameraNode->GetComponent<Camera>();
    _levelCamera = new LevelCamera(context_);
    Vector3 initialOffset = cameraNode->GetPosition() - _robotNode->GetPosition();
    _levelCamera->Setup(cameraNode, centerPos, _scene, initialOffset, mapDimension);

    _hero->Setup(_scene, _robotNode, cameraNode, _terrainNode);
    Renderer* renderer = GetSubsystem<Renderer>();
    SharedPtr<Viewport> viewport(new Viewport(context_, _scene, camera));
    renderer->SetViewport(0, viewport);
    _initialCameraOffset = cameraNode->GetPosition() - _robotNode->GetPosition();
    Button* robotButton = static_cast<Button*>(layoutRoot->GetChild("findRobot", true));
    if (robotButton)
        SubscribeToEvent(robotButton, E_RELEASED, HANDLER(LevelSceneManager, GoToHeroButtonHandle));
}

void LevelSceneManager::OnUpdate(float deltaTime)
{
    Input* input = GetSubsystem<Input>();
    if (input->GetMouseButtonDown(MOUSEB_LEFT))
    {
        _hero->CalculatePath();
    }
    _hero->Update(deltaTime);
    _levelCamera->Update();
}

void LevelSceneManager::Shutdown()
{
    _scene->Clear();
}

void LevelSceneManager::GoToHeroButtonHandle(StringHash eventType, VariantMap &eventData)
{
    _levelCamera->MoveTo(_robotNode->GetPosition());
}
