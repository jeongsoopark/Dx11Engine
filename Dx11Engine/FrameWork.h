#pragma once
#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
class FrameWork
{
public:
	FrameWork();
	~FrameWork();
	bool Init();
	void Run();

private:
	bool createDxWindow(char* windowName, int x, int y, int width, int height);

	char* mApplicationName;
	HINSTANCE mHIntance;


};


#endif