#include "MainMenuSceneManager.h"
#include "ResourceCache.h"
#include "UI.h"
#include "Button.h"
#include "Graphics.h"
#include "CoreEvents.h"
#include "UIEvents.h"
#include "Camera.h"
#include "Renderer.h"
#include "Viewport.h"
#include "Input.h"
#include "mainApp.h"

MainMenuSceneManager::MainMenuSceneManager(Context *context) : AbstractSceneManager(context)
{
    context_ = context;
    _finished = false;
}

void MainMenuSceneManager::Setup(MainApp *app)
{
    _mainApp = app;

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();
    ui->Clear();
    XMLFile *defaultStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    ui->GetRoot()->SetDefaultStyle(defaultStyle);

    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto();
    ui->SetCursor(cursor);

    XMLFile *mainMenuLayout = cache->GetResource<XMLFile>("UI/mainMenu.xml");
    SharedPtr<UIElement> layoutRoot = ui->LoadLayout(mainMenuLayout);
    ui->GetRoot()->AddChild(layoutRoot);
    Button* exitButton = static_cast<Button*>(layoutRoot->GetChild("exit", true));
    if (exitButton)
        SubscribeToEvent(exitButton, E_RELEASED, HANDLER(MainMenuSceneManager, ExitButtonHandle));

    Button* newGameButton = static_cast<Button*>(layoutRoot->GetChild("new", true));
    if (newGameButton)
        SubscribeToEvent(newGameButton, E_RELEASED, HANDLER(MainMenuSceneManager, NewGameButtonHandle));
}

void MainMenuSceneManager::OnUpdate(float deltaTime)
{
}

void MainMenuSceneManager::ExitButtonHandle(StringHash eventType, VariantMap &eventData)
{
    _mainApp->Exit();
}

void MainMenuSceneManager::NewGameButtonHandle(StringHash eventType, VariantMap &eventData)
{
    NextState = SceneManagerState::level;
    _finished = true;
}

void MainMenuSceneManager::Shutdown()
{
}
