#include "Framework.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    fw::FWCore core;

    core.Init(600, 600);
    core.Run();
    core.Shutdown();

    return 0;
}