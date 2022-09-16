#include "Framework.h"
#include "Game.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    fw::FWCore core;
    

    core.Init(600, 600);
    Game game;
    core.Run(&game);
    core.Shutdown();

    return 0;
}