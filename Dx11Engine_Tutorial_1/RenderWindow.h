#pragma once
#include "ErrLogger.h"

class WindowContainer;


class RenderWindow
{
public:
	RenderWindow();
	~RenderWindow();
	HWND GetHwnd() { return mHandle; };
	bool Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height);
	bool ProcessMessages();

private:
	void RegisterWindowsClass();
	HWND mHandle = NULL;
	HINSTANCE mHInstance = NULL;
	std::string mWindow_title = "";
	std::wstring mWindow_title_wide = L"";
	std::string mWindow_class = "";
	std::wstring mWindow_class_wide = L"";

	int mWidth = 0;
	int mHeight = 0;

};

