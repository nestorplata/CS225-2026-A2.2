#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"

#include "../Player.h"
int mode = 0;

Player *player1;
Player *player2;

bool ShowFrameworkMenu();

void Level_1_Load()
{
}

void Level_1_Init()
{
    player1 = new Player();
    AEGfxTriStart();
    player1->posComponent->setPosition(200, 0);
        AEGfxTriAdd(0, 0, AEGFX, 0, 0, 
                100, 0, 5, 0, 0,
                100, 100, 2, 0, 0 );
}


void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();


}

void Level_1_Render()
{
    for (auto tri : AEGfxGetAllocatedTrilist())
    {
        AEGfxTriDraw(tri);
    }
   
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();
}

void Level_1_Free()
{

}

void Level_1_Unload()
{
    delete(player1);
}

void KeyboardInput()
{
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

