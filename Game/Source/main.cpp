#include "Framework.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    fw::FWCore core;

    core.Init(1080, 1920);
    core.Run();
    core.Shutdown();

    return 0;
}