#include "LevelCamera.h"

#include "UI.h"
#include "Input.h"
#include "Ray.h"
#include "Graphics.h"
#include "OctreeQuery.h"
#include "Octree.h"
#include "Scene.h"
#include "Log.h"
#include "ValueAnimation.h"

LevelCamera::LevelCamera(Context *context) :Object(context)
{

}


void LevelCamera::VerticalTranslate(float amount)
{
    float currentRot = _cameraNode->GetRotation().YawAngle();
    Quaternion distilledRot;
    distilledRot.FromAngleAxis(currentRot, Vector3(0,1,0));
    Vector3 rotated = distilledRot.RotationMatrix() * Vector3(0,0,amount);

    float initialLength = _centerPosition->GetWorldPosition().Length();

    Vector3 futurePos = _centerPosition->GetWorldPosition();
    futurePos += rotated;

    if(futurePos.Length() < initialLength)
    {
        _cameraNode->Translate(rotated, TS_WORLD);
        _centerPosition->Translate(rotated);
    }
    else
    {
        if(initialLength < _mapDimension*DIMENSION_COEF)
        {
            _cameraNode->Translate(rotated, TS_WORLD);
            _centerPosition->Translate(rotated);
        }
    }
}

void LevelCamera::HorizontalTranslate(float amount)
{
    float currentRot = _cameraNode->GetRotation().YawAngle();
    Quaternion distilledRot;
    distilledRot.FromAngleAxis(currentRot, Vector3(0,1,0));
    Vector3 rotated = distilledRot.RotationMatrix() * Vector3(amount,0,0);

    float initialLength = _centerPosition->GetWorldPosition().Length();

    Vector3 futurePos = _centerPosition->GetWorldPosition();
    futurePos += rotated;

    if(futurePos.Length() < initialLength)
    {
        _cameraNode->Translate(rotated, TS_WORLD);
        _centerPosition->Translate(rotated);
    }
    else
    {
        if(initialLength < _mapDimension*DIMENSION_COEF)
        {
            _cameraNode->Translate(rotated, TS_WORLD);
            _centerPosition->Translate(rotated);
        }
    }
}

void LevelCamera::Update()
{
    UI* ui = GetSubsystem<UI>();
    Input* input = GetSubsystem<Input>();
    Graphics *graphics = GetSubsystem<Graphics>();

    if (ui->GetFocusElement())
        return;

    if(input->GetMousePosition().y_ < BORDER_OFFSET)
        VerticalTranslate(CAMERA_VELOCITY);
    if(input->GetMousePosition().y_ >  graphics->GetHeight() - BORDER_OFFSET)
        VerticalTranslate(-CAMERA_VELOCITY);
    if(input->GetMousePosition().x_ < BORDER_OFFSET)
        HorizontalTranslate(-CAMERA_VELOCITY);
    if(input->GetMousePosition().x_ >  graphics->GetWidth() - BORDER_OFFSET)
        HorizontalTranslate(CAMERA_VELOCITY);
    if (input->GetMouseButtonDown(MOUSEB_RIGHT))
    {
        IntVector2 mouseMove = input->GetMouseMove();
        _yaw += MOUSE_SENSITIVITY * mouseMove.x_;
        _pitch += MOUSE_SENSITIVITY * mouseMove.y_;

        Vector3 centerPos = _centerPosition->GetPosition();
        _cameraNode->RotateAround(centerPos, Quaternion(_yaw, Vector3(0,1,0)), TS_WORLD);
        if(abs((int)_pitch) < 20 )
        {
            if(_cameraNode->GetRotation().PitchAngle() < 65 &&  _pitch < 0)
                _cameraNode->RotateAround(centerPos, Quaternion(_pitch, _cameraNode->GetDirection().CrossProduct(Vector3(0,1,0))), TS_WORLD);
            if(_cameraNode->GetRotation().PitchAngle() > 30 && _pitch > 0)
                _cameraNode->RotateAround(centerPos, Quaternion(_pitch, _cameraNode->GetDirection().CrossProduct(Vector3(0,1,0))), TS_WORLD);
        }

        _yaw = 0;
        _pitch = 0;
    }
    int wheelMove = input->GetMouseMoveWheel();
    if( wheelMove != 0 && abs((int)wheelMove) < 2)
    {
        Camera *camera = _cameraNode->GetComponent<Camera>();
        float oldZoom = camera->GetZoom();
        if(oldZoom > 0.5f && wheelMove < 0)
            camera->SetZoom(oldZoom + wheelMove*WHEEL_SENSITIVITY);
        if(oldZoom < 4 && wheelMove > 0)
            camera->SetZoom(oldZoom + wheelMove*WHEEL_SENSITIVITY);
    }
}

void LevelCamera::MoveTo(Vector3 target)
{
    Vector3 pos = _cameraNode->GetPosition();
    _cameraNode->SetPosition(target + _initialOffset);
    _cameraNode->LookAt(target);
    _centerPosition->SetPosition(target);

}


void LevelCamera::Setup(Node *cameraNode, Node *centerNode, Scene *scene, Vector3 heroOffset, int mapDimension)
{
    _sceneNode = scene;
    _cameraNode = cameraNode;
    _centerPosition = centerNode;

    cameraNode->LookAt(_centerPosition->GetPosition());
    _initialOffset = heroOffset;
    _mapDimension = mapDimension;
}
