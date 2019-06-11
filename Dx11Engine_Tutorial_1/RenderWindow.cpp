#include "RenderWindow.h"



RenderWindow::RenderWindow()
{
}


RenderWindow::~RenderWindow()
{
}

bool RenderWindow::Initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height)
{
	this->mHInstance = hInstance;
	this->mWidth = width;
	this->mHeight = height;
	this->mWindow_title = windowTitle;
	this->mWindow_class_wide = StringConverter::StringToWideString(this->mWindow_title);
	this->mWindow_class = windowClass;
	this->mWindow_class_wide = StringConverter::StringToWideString(this->mWindow_title);

	this->RegisterWindowsClass();

	return false;
}
