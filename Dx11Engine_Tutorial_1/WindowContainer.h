#pragma once
#include "RenderWindow.h"
#include "KeyboardClass.h"
#include "MouseClass.h"
#include "Graphics.h"

class WindowContainer
{
public:
	WindowContainer();
	~WindowContainer();

	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


protected:
	RenderWindow mRenderWindow;
	KeyboardClass mKeyboard;
	MouseClass mMouse;
	Graphics mGraphics;
};

