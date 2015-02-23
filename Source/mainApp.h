#pragma once

#include "Application.h"
#include "AbstractSceneManager.h"

using namespace Urho3D;

class MainApp : public Application
{
  OBJECT(MainApp);
public:
    MainApp(Context* context);
    virtual void Setup();
    virtual void Start();
    virtual void Stop();

    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void Exit();
private:
  void HandleEvents();

  SharedPtr<AbstractSceneManager> _currentSceneManager;
};
