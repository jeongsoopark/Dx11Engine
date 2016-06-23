#include "Engine.h"

Engine* Engine::mInstance = NULL;

Engine::Engine()
{
	mGraphics = nullptr;
}

Engine::~Engine()
{
	if (mGraphics)
	{
		delete mGraphics;
		mGraphics = nullptr;
	}
}

bool Engine::InitGraphics(HWND _hwnd)
{
	mGraphics = new Graphics();
	return mGraphics->InitDX(_hwnd);
}

bool Engine::Init(HINSTANCE _hinstance, HWND _hwnd)
{
	mGraphics->Init();
	return false;
}

void Engine::Update()
{
}

void Engine::Render()
{
	mGraphics->BeginScene(1.0, 0.0, 0.0, 1.0);
	mGraphics->EndScene();
}


void Engine::Run()
{
	Update();
	Render();
}

void Engine::Release()
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

Graphics * Engine::GetGraphics()
{
	return mGraphics;
}

Engine * Engine::GetEngine()
{
	if (mInstance == nullptr)
	{
		mInstance = new Engine();
	}
	return mInstance;
}
