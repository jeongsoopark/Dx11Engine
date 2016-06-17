#include "FrameWork.h"
#include "Defines.h"

#include <iostream>
using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

FrameWork::FrameWork()
{
}

FrameWork::FrameWork(char* applicationName)
{
	mApplicationName = applicationName;
}


FrameWork::~FrameWork()
{
	if (bFULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}
	UnregisterClass(mApplicationName, mHIntance);
	mHIntance = nullptr;
}

bool FrameWork::Init()
{
	if (!createDxWindow(mApplicationName, WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		return false;
	}
	return true;
}

void FrameWork::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//update loop logic
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// update and rendering loop
		
		}
	}
}


bool FrameWork::createDxWindow(char* windowName, int x, int y, int width, int height)
{
	HWND hwnd;
	WNDCLASSEX wc;
	mApplicationName = windowName;
	mHIntance = GetModuleHandle(NULL);

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= mHIntance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm			= wc.hIcon;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= mApplicationName;
	wc.cbSize			= sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "RegisterClassEx() failed", "Error", MB_OK);
		return false;
	}

	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int screenX = 0;
	int screenY = 0;

	if (bFULL_SCREEN)
{	
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = screenWidth;
		dmScreenSettings.dmPelsHeight = screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		screenX = x;
		screenY = y;
		screenWidth = width;
		screenHeight = height;
	}
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, windowName, windowName, nStyle, x, y, screenWidth, screenHeight, NULL, NULL, mHIntance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "CreateWindowEX() failed", "Error", MB_OK);
		PostQuitMessage(0);
	}
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}






















