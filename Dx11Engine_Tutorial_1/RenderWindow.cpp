#include "RenderWindow.h"
#include "windows.h"


RenderWindow::RenderWindow()
{
}


RenderWindow::~RenderWindow()
{
	if (this->mHandle != NULL)
	{
		UnregisterClass(this->mWindow_class.c_str(), this->mHInstance);
		DestroyWindow(mHandle);
	}
}

bool RenderWindow::Initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height)
{
	this->mHInstance = hInstance;
	this->mWidth = width;
	this->mHeight = height;
	this->mWindow_title = windowTitle;
	this->mWindow_title_wide = StringConverter::StringToWideString(this->mWindow_title);
	this->mWindow_class = windowClass;
	this->mWindow_class_wide = StringConverter::StringToWideString(this->mWindow_class);

	//register window class
	this->RegisterWindowsClass();

	this->mHandle = CreateWindowEx(
		0,
		this->mWindow_class.c_str(),
		this->mWindow_title.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0,
		0,
		this->mWidth,
		this->mHeight,
		NULL,
		NULL,
		this->mHInstance,
		nullptr);

	if (this->mHandle == NULL) //in case of failure creating window
	{
		ErrLogger::Log(GetLastError(), "CreateWindowsEX failed");
		return false;
	}

	ShowWindow(this->mHandle, SW_SHOW);
	SetForegroundWindow(this->mHandle);
	SetFocus(this->mHandle);

	return false;
}

void RenderWindow::RegisterWindowsClass()
{
	WNDCLASSEX wc; 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->mHInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->mWindow_class.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);
}


bool RenderWindow::ProcessMessages()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));



}

