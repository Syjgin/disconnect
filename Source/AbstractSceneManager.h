#pragma once

#include "Object.h"

using namespace Urho3D;

class MainApp;

class AbstractSceneManager: public Object {

    OBJECT(AbstractSceneManager);

public:
    enum SceneManagerState {
     mainMenu,
     level
    };

    AbstractSceneManager(Context *context): Object(context) {};
    virtual void Setup(MainApp *app) {};
    virtual void OnUpdate(float deltaTime) {};
    virtual void Shutdown() {};
    bool IsFinished()
    {
        return _finished;
    }
    SceneManagerState NextState;
protected:
    bool _finished;
};

