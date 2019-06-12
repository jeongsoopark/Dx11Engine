#pragma once
#include "WindowContainer.h"

class Engine : WindowContainer
{
public:
	Engine();
	~Engine();


	bool Initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height);
	bool ProcessMessages();


};

