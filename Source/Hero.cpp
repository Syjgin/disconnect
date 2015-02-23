#include "Hero.h"
#include "UI.h"
#include "Graphics.h"
#include "OctreeQuery.h"
#include "Octree.h"

#include "LevelCamera.h"


Hero::Hero(Urho3D::Context *context) : Object(context)
{

}

void Hero::Setup(Scene *scene, Node *heroNode, Node *cameraNode, Node *terrainNode)
{
    _scene = scene;
    _cameraNode = cameraNode;
    _heroNode = heroNode;
    _path.Clear();
    _terrain = terrainNode->GetComponent<Terrain>();
    _navMesh = terrainNode->GetComponent<NavigationMesh>();
}

void Hero::CalculatePath()
{
    Vector3 hitPos;
    Drawable* hitDrawable;
    if (Raycast(250.0f, hitPos, hitDrawable))
    {
        Vector3 pathPos = _navMesh->FindNearestPoint(hitPos, Vector3(1.0f, 1.0f, 1.0f));
        _navMesh->FindPath(_path, _heroNode->GetPosition(), pathPos);
    }
}

void Hero::Update(float deltaTime)
{
    if (_path.Size())
    {
        Vector3 nextWaypoint = _path[0]; // NB: currentPath[0] is the next waypoint in order

        // Rotate Jack toward next waypoint to reach and move. Check for not overshooting the target
        float move = 5.0f * deltaTime;
        float distance = (_heroNode->GetPosition() - nextWaypoint).Length();
        if (move > distance)
            move = distance;

        _heroNode->LookAt(nextWaypoint, Vector3::UP);
        Vector3 moveVector = Vector3::FORWARD * move;

        float oldHeight = _terrain->GetHeight(_heroNode->GetPosition());
        moveVector.y_ =  oldHeight - _terrain->GetHeight(GetFuturePos(_heroNode, moveVector));
        _heroNode->Translate(moveVector);
        /*Vector3 oldPos = _heroNode->GetPosition();
        _heroNode->SetPosition(Vector3(oldPos.x_,_terrainNode->GetComponent<Terrain>()->GetHeight(oldPos), oldPos.z_));*/
        if ((_heroNode->GetPosition() - nextWaypoint).Length() < 0.1f)
            _path.Erase(0);
    }
}

Vector3 Hero::GetFuturePos(Node *node, Vector3 delta)
{
    Vector3  addition = (node->GetParent() == node->GetScene()|| !node->GetParent()) ? delta : node->GetParent()->GetWorldTransform().Inverse() * Vector4(delta, 0.0f);
    return node->GetPosition() + addition;
}

bool Hero::Raycast(float maxDist, Vector3 &hit, Drawable *&hitDrawable)
{
    hitDrawable = 0;

    UI* ui = GetSubsystem<UI>();
    IntVector2 pos = ui->GetCursorPosition();
    // Check the cursor is visible and there is no UI element in front of the cursor
    if (ui->GetElementAt(pos, true))
        return false;

    Graphics* graphics = GetSubsystem<Graphics>();
    Camera* camera = _cameraNode->GetComponent<Camera>();
    Ray cameraRay = camera->GetScreenRay((float)pos.x_ / graphics->GetWidth(), (float)pos.y_ / graphics->GetHeight());
    // Pick only geometry objects, not eg. zones or lights, only get the first (closest) hit
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, cameraRay, RAY_TRIANGLE, maxDist, DRAWABLE_GEOMETRY);
    _scene->GetComponent<Octree>()->RaycastSingle(query);
    if (results.Size())
    {
        RayQueryResult& result = results[0];
        hit = result.position_;
        hitDrawable = result.drawable_;
        return true;
    }

    return false;
}
