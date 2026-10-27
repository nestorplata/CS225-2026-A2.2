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
//Objects
Player *player1;
Player *player2;
Ball* ball;

//Managers
InputEventManager InputManager;
CollisionEventManager CollisionManager;

//PlayerInputEvents
OnChangeEvent onMoveEvent;
UpdateOnEvent UpdateMoveEvent;

//AI Events
SetLoopFunctionEvent SetFollowEvent;

//Collision Events
OnCollisionEvent PlayerBallcollisionEvent;

//EventHandlers
EventHandler<Player, OnChangeEvent>* handlerEventOnPlayerMoveChange;
EventHandler<Player, UpdateOnEvent>* handlerEventOnPlayerMoveUpdate;
EventHandler<Player, SetLoopFunctionEvent>* handlerEventOnCPUFollowSet;




const static int PLAYER_START_POS =350;


bool ShowFrameworkMenu();

namespace CheckIfEvent
{

    bool CheckCollision(Player* player, Ball* ball, AEContact* pResult)
    {
        player->simplePos = AEVec2(player->posComponent->getX(), player->posComponent->getY());
        ball->simplePos = AEVec2(ball->posComponent->getX(), ball->posComponent->getY());

        return   AEStaticRectToStaticCircle(&player->simplePos,
            player->width, player->height,
            &ball->simplePos,
            ball->Radius,
            pResult);


    }

    void CheckAllCollisions()
    {

        if (CheckCollision(player1, ball, PlayerBallcollisionEvent.pResult))
        {
            PlayerBallcollisionEvent.ptr_object = player1;

            CollisionManager.notifyEvent(&PlayerBallcollisionEvent);
            SetFollowEvent.SetEntityToFollow(ball);
            InputManager.notifyEvent(&SetFollowEvent);
            InputManager.
        }

        if (CheckCollision(player2, ball, PlayerBallcollisionEvent.pResult))
        {
            PlayerBallcollisionEvent.ptr_object = player2;
            CollisionManager.notifyEvent(&PlayerBallcollisionEvent);
            SetFollowEvent.SetEntityToFollow(nullptr);
            InputManager.notifyEvent(&SetFollowEvent);

        }
    }


}

using namespace CheckIfEvent;
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

    handlerEventOnPlayerMoveChange = new EventHandler<Player, OnChangeEvent>(player1, &Player::OnMovementChange);
    handlerEventOnPlayerMoveUpdate = new EventHandler<Player, UpdateOnEvent>(player1, &Player::OnMovementUpdate);
    handlerEventOnCPUFollowSet = new EventHandler<Player, SetLoopFunctionEvent>(player2, &Player::OnFollowEvent);

    InputManager = InputEventManager();
    CollisionManager = CollisionEventManager();

    
    InputManager.SetBehaviour(KeyboardInput);
    CollisionManager.SetBehaviour(CheckAllCollisions);
    

    InputManager.registerEventHandler(handlerEventOnPlayerMoveChange);
    InputManager.registerEventHandler(handlerEventOnPlayerMoveUpdate);
    InputManager.registerEventHandler(handlerEventOnCPUFollowSet);

    CollisionManager.registerEventHandler(ball->EventHandlerOnCollisionRect);

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

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    bool guiActive = ShowFrameworkMenu();

    CollisionManager.update();
    InputManager.update();
    
    player1->Update();
    ball->Update();
    player2->Update();


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
    delete(handlerEventOnPlayerMoveChange);
    delete(handlerEventOnPlayerMoveUpdate);
    delete(handlerEventOnCPUFollowSet);

}

void Level_1_Unload()
{
    AEInputKeyPressed('R');
    AEInputKeyTriggered('R');
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

