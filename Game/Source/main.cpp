#include "Framework.h"
#include "Game.h"
//
//typedef float (MathOp)(float x, float y);
//
//float Add(float x, float y) { return x + y; }
//float Multiply(float x, float y) { return x * y; }
//
//float DoMath(float x, float y, MathOp Function) { return Function(x, y); }

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	//Example for global function pointers
	//------------------------------------

	//MathOp* FunctionPointer = Add;

	//float r = FunctionPointer(15, 25); // r = 40

	//FunctionPointer = Multiply;

	//float r2 = FunctionPointer(15, 20); // r2 = 375

	//float r3 = DoMath(15, 25, Add);
	//float r4 = DoMath(15, 25, Multiply);

	{
		fw::FWCore core;


		core.Init(2000, 1000);

		Game game(core);
		core.Run(&game);

		core.Shutdown();
	}

	return 0;
}