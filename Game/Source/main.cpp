#include "Framework.h"
#include "Game.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	{
		fw::FWCore core;


		core.Init(2000, 1000);

		Game game(core);
		core.Run(&game);

		core.Shutdown();
	}

	return 0;
}