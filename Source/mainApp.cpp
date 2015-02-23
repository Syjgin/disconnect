#include "mainApp.h"
#include "MainMenuSceneManager.h"
#include "LevelSceneManager.h"

#include "Input.h"
#include "CoreEvents.h"
#include "Engine.h"


DEFINE_APPLICATION_MAIN(MainApp)

MainApp::MainApp(Context* context): Application(context)
{
}


void MainApp::Start()
{
    Urho3D::Application::Start();
    GetSubsystem<Input>()->SetMouseVisible(true);
    _currentSceneManager = new MainMenuSceneManager(context_);
    _currentSceneManager->Setup(this);
    HandleEvents();
}

void MainApp::HandleUpdate(StringHash eventType, VariantMap &eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    _currentSceneManager->OnUpdate(timeStep);
    if(_currentSceneManager->IsFinished())
    {
        _currentSceneManager->Shutdown();
        AbstractSceneManager::SceneManagerState nextState = _currentSceneManager->NextState;
        //delete _currentSceneManager;
        switch (nextState) {
        case AbstractSceneManager::SceneManagerState::mainMenu:
            _currentSceneManager = new MainMenuSceneManager(context_);
            break;
        case AbstractSceneManager::SceneManagerState::level:
            _currentSceneManager = new LevelSceneManager(context_);

            break;
        default:
            break;
        }
        if(_currentSceneManager)
            _currentSceneManager->Setup(this);
    }
}

void MainApp::Exit()
{
    engine_->Exit();
}

void MainApp::Setup()
{
    Urho3D::Application::Setup();
    engineParameters_["FullScreen"]  = false;
}

void MainApp::Stop()
{
    Urho3D::Application::Stop();
}

void MainApp::HandleEvents()
{
    SubscribeToEvent(E_UPDATE, HANDLER(MainApp, HandleUpdate));
}
