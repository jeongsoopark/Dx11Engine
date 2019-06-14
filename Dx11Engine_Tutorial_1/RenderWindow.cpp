#include "WindowContainer.h"

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

bool RenderWindow::Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height)
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
		pWindowContainer);

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

LRESULT HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	default:
		{
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);

		}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWindow == nullptr)
		{
			ErrLogger::Log("Critical error : pointer to window container is null during WM_NCCREATE message");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	case WM_CHAR:
	{
		unsigned char letter = static_cast<unsigned char>(wParam);
		return 0;
	}
	case WM_KEYDOWN:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		return 0;
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void RenderWindow::RegisterWindowsClass()
{
	WNDCLASSEX wc; 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
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
	if (PeekMessage(&msg, this->mHandle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//key down message here

	if (msg.message == WM_NULL)
	{
		if (!IsWindow(this->mHandle))
		{
			this->mHandle = NULL;
			UnregisterClass(this->mWindow_class.c_str(), this->mHInstance);
			return false;
		}
	}


	return true;

}

