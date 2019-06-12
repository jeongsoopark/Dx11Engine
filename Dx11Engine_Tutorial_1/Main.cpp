//Tutorial 1 Solution 2018-09-07 

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")

#include <Windows.h>
#include "Engine.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Engine engine;
	engine.Initialize(hInstance, "my windows", "myclass", 800, 600);

	while (engine.ProcessMessages())
	{

	}


	return 0;
}