#include <AEEngine.h>
#include <imgui/imgui.h>
#include <functional>
#include <string>

#include "Level 1.h"

#include "../Pong/Player.h"
#include "../Pong/Ball.h"
#include "../Framework/event.hh"
#include "../Framework/event_handlers.hh"
#include "../Pong/InputEventManager.h"
#include "../Pong/CollisionEventManager.h"

int mode = 0;

Player *player1;
Player *player2;
Ball* ball;
InputEventManager &EventManager = InputEventManager::instance();

OnMoveEvent onMoveEvent;
OnMoveUpdateEvent UpdateMoveEvent;

const static int PLAYER_START_POS =350;


bool ShowFrameworkMenu();

void Level_1_Load()
{
}

void Level_1_Init()
{
    player1 = new Player();
    player2 = new Player();
    ball = new Ball();
    player1->posComponent->setPosition(-PLAYER_START_POS, 0);
    player2->posComponent->setPosition(PLAYER_START_POS, 0);
    EventManager.registerEventHandler(player1->eventOnMoveChange);
    EventManager.registerEventHandler(player1->eventOnMoveUpdate);

}


void Level_1_Update()
{
    

    player1->Update();
    player2->Update();
    ball ->Update();

    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();


}

void Level_1_Render()
{
    player1->Draw();
    ball->Draw();
    player2->Draw();

    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();
}

void Level_1_Free()
{
    delete(player1);
    delete(player2);

}

void Level_1_Unload()
{
    AEInputKeyPressed('R');
    AEInputKeyTriggered('R');
}


bool AEInputKeyChange(const char key, Action* ActionType)
{
    if (AEInputKeyTriggered(key))
    {
        ActionType->IsActionHappening = true;
        return true;

    }
    else if (ActionType->IsActionHappening && !AEInputKeyPressed(key))
    {
        ActionType->IsActionHappening = false;
        return true;
    }
    return false;
}
void KeyboardInput()
{
    //std::cout << AEInputKeyTriggered('W');
    if (AEInputKeyChange('W', onMoveEvent.MovingUp)) EventManager.notifyEvent(&onMoveEvent);
    if (AEInputKeyChange('S', onMoveEvent.MovingDown)) EventManager.notifyEvent(&onMoveEvent);

    if (AEInputKeyPressed('W') || AEInputKeyPressed('S')) EventManager.notifyEvent(&UpdateMoveEvent);
    
    //if (AEInputKeyPressed('S')||AEInputKeyPressed('W')) EventManager.notifyEvent()
    if (AEInputKeyTriggered('R'))
        AESetGameStateNext(AE_GS_RESTART);
    if (AEInputKeyTriggered('Q') && AEInputKeyPressed(AE_KEY_CTRL))
        AESetGameStateNext(AE_GS_QUIT);
}

bool ShowFrameworkMenu()
{
    bool isGuiActive = false;
    mode = 0;

    // show File options 
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode")) {

            if (ImGui::MenuItem("Restart", "1"))
                mode = 1;

            ImGui::EndMenu();
        }

        auto mSize = ImGui::GetWindowHeight();
        AEVec2 mouseVP = AEGetMouseData().position + AEVec2((float)AEGetSysWindowWidth() / 2.0f, (float)AEGetSysWindowHeight() / 2.0f);
        auto inMenu = mouseVP.y >= (AEGetSysWindowHeight() - mSize);
        isGuiActive = ImGui::IsAnyItemActive() || ImGui::IsAnyItemHovered() || inMenu;

        ImGui::EndMainMenuBar();
    }

    if (mode == 1) {
        AESetGameStateNext(AE_GS_RESTART);
    }

    return isGuiActive;
}

