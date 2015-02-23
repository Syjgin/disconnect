#pragma once

#include "Urho3D.h"
#include "Camera.h"
#include "Context.h"
#include "Node.h"
#include "Drawable.h"

using namespace Urho3D;

const float TOUCH_SENSITIVITY = 2.0f;
const float MAX_TARGET_DIFF = 15.0f;
const float MOUSE_SENSITIVITY = 0.5f;
const float WHEEL_SENSITIVITY = 0.5f;
const float BORDER_OFFSET = 5;
const float CAMERA_VELOCITY = 0.5f;

class LevelCamera : public Object {

    OBJECT(LevelCamera);
public:
    LevelCamera(Context *context);
    void Setup(Node *cameraNode, Node *centerNode, Scene *scene, Vector3 heroOffset, int mapDimension);
    void Update();
    void MoveTo(Vector3 target);
private:
    void VerticalTranslate(float amount);
    void HorizontalTranslate(float amount);
    SharedPtr<Node> _cameraNode;
    SharedPtr<Node> _centerPosition;
    SharedPtr<Scene> _sceneNode;
    float _yaw;
    float _pitch;
    Vector3 _initialOffset;
    int _mapDimension;
};

