#pragma once

#include "Object.h"
#include "Node.h"
#include "Scene.h"
#include "Context.h"
#include "Vector3.h"
#include "Drawable.h"
#include "NavigationMesh.h"
#include "Terrain.h"
#include "NavigationMesh.h"

using namespace Urho3D;

class Hero : public Object
{
    OBJECT(Hero);
public:
    Hero(Context *context);
    void Setup(Scene *scene, Node *heroNode, Node *cameraNode, Node *terrainNode);
    void CalculatePath();
    void Update(float deltaTime);
    Vector3 GetFuturePos(Node *node, Vector3 delta);
private:
    bool Raycast(float maxDist, Vector3& hit, Drawable*& hitDrawable);
    SharedPtr<Scene> _scene;
    SharedPtr<Node> _heroNode;
    SharedPtr<Node> _cameraNode;
    PODVector<Vector3> _path;
    SharedPtr<Terrain> _terrain;
    SharedPtr<NavigationMesh> _navMesh;
};
