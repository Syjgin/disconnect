#pragma once

#include "AbstractSceneManager.h"
#include "Scene.h"
#include "Node.h"
#include "Context.h"

class MainMenuSceneManager : public AbstractSceneManager {

public:
    OBJECT(MainMenuSceneManager);
    MainMenuSceneManager(Context *context);
    void Setup(MainApp *app);
    void OnUpdate(float deltaTime);
private:
    void ExitButtonHandle(StringHash eventType, VariantMap& eventData);
    void NewGameButtonHandle(StringHash eventType, VariantMap& eventData);
    void Shutdown();
    float _cameraRotation;
    SharedPtr<MainApp> _mainApp;
};

