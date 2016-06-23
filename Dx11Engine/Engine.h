#pragma once

#include "Graphics.h"

class Engine
{
public:
	~Engine();
	bool InitGraphics(HWND _hwnd);
	bool Init(HINSTANCE _hinstance, HWND _hwnd);

	void Run();
	void Release();

	Graphics* GetGraphics();
	static Engine* GetEngine();

private:
	Engine();
	void Update();
	void Render();

	Graphics* mGraphics;
	static Engine* mInstance;

};

