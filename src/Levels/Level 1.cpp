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
InputEventManager InputManager;
CollisionEventManager CollisionManager;

OnInputChangeEvent onMoveEvent;
UpdateEvent UpdateMoveEvent;
OnCollisionEvent PlayerBallcollisionEvent;

OnTriggerEvent StartFollowEvent;
OnTriggerEvent DuringFollowEvent;
OnTriggerEvent StopFollowEvent;


OnCollisionEvent OnMoveChange;



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

    player1->eventOnMoveChange = new EventHandler<Player, OnInputChangeEvent>(player1, &Player::OnMovementChange);
    player1->eventOnMoveUpdate = new EventHandler<Player, UpdateEvent>(player1, &Player::OnMovementUpdate);

    player2->eventOnMoveChange = new EventHandler<Player, OnInputChangeEvent>(player2, &Player::OnMovementChange);
    player2->eventOnMoveUpdate = new EventHandler<Player, UpdateEvent>(player2, &Player::OnMovementUpdate);



    InputManager = InputEventManager();
    CollisionManager = CollisionEventManager();


    InputManager.registerEventHandler(player1->eventOnMoveChange);
    InputManager.registerEventHandler(player1->eventOnMoveUpdate);
    CollisionManager.registerEventHandler(ball->EventHandlerOnCollisionRect);

    ball->posComponent;

}

static bool CheckCollision(Player* player, Ball* ball, AEContact* pResult)
{
    player->simplePos = AEVec2(player->posComponent->getX(), player->posComponent->getY());
    ball->simplePos = AEVec2(ball->posComponent->getX(), ball->posComponent->getY());

    return   AEStaticRectToStaticCircle(&player->simplePos,
        player->width, player->height,
        &ball->simplePos,
        ball->Radius, 
        pResult);


}
void Level_1_Update()
{
    
    player1->Update();
    ball->Update();
    if (CheckCollision(player1, ball, PlayerBallcollisionEvent.pResult))
    {
        CollisionManager.notifyEvent(&PlayerBallcollisionEvent);
        CollisionManager.notifyEvent(&OnMoveChange);

    }

    if (CheckCollision(player2, ball, PlayerBallcollisionEvent.pResult))
    {
        CollisionManager.notifyEvent(&PlayerBallcollisionEvent);


    }




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
    delete(ball);

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
    if (AEInputKeyChange('W', onMoveEvent.MovingUp)) InputManager.notifyEvent(&onMoveEvent);
    if (AEInputKeyChange('S', onMoveEvent.MovingDown)) InputManager.notifyEvent(&onMoveEvent);

    if (AEInputKeyPressed('W') || AEInputKeyPressed('S')) InputManager.notifyEvent(&UpdateMoveEvent);
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

