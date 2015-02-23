#pragma once

#include "AbstractSceneManager.h"
#include "Scene.h"
#include "Node.h"
#include "Context.h"
#include "LevelConfigReader.h"
#include "List.h"
#include "NavigationMesh.h"
#include "Drawable.h"
#include "OctreeQuery.h"
#include "Octree.h"
#include "Quaternion.h"
#include "Terrain.h"
#include "ResourceCache.h"

#include "LevelCamera.h"
#include "Hero.h"

const int MAX_PLACEMENT_TRY_COUNT = 20;

class LevelSceneManager : public AbstractSceneManager {

public:
    typedef std::map<String, int>::iterator buildingsIterator;
    OBJECT(LevelSceneManager);
    LevelSceneManager(Context *context);
    void Setup(MainApp *app);
    void OnUpdate(float deltaTime);
    void Shutdown();
private:
    void GoToHeroButtonHandle(StringHash eventType, VariantMap& eventData);
    SharedPtr<MainApp> _mainApp;
    SharedPtr<Scene> _scene;
    SharedPtr<Node> _robotNode;
    SharedPtr<LevelConfigReader> _configReader;
    SharedPtr<Node> _terrainNode;
    List<Vector3> _buildingsCoords;
    List<Vector3> _garbageCoords;
    SharedPtr<LevelCamera> _levelCamera;
    SharedPtr<Hero> _hero;
    Vector3 _initialCameraOffset;
    void PlaceBuildings(int mapDimension, ResourceCache* cache, Terrain *terrain, std::map<String, int> buildings);
    void PlaceGarbage(int mapDimension, ResourceCache* cache, Terrain *terrain, std::map<String, int> garbage);
};

