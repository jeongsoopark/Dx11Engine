#include "Engine.h"



Engine::Engine()
{
}


Engine::~Engine()
{
}

bool Engine::Initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height)
{
	if (!this->mRenderWindow.Initialize(this, hInstance, windowTitle, windowClass, width, height))
	{
		return false;
	}
	if (!this->mGraphics.Initialize(this->mRenderWindow.GetHwnd(), width, height))
	{
		return false;
	}

	return true;
}

bool Engine::ProcessMessages()
{
	return this->mRenderWindow.ProcessMessages();
}

void Engine::Update()
{
	while (!mKeyboard.IsCharBufferEmpty())
	{
		unsigned char ch = mKeyboard.ReadChar();
		std::string outMsg = "Input char : ";
		outMsg += ch;
		outMsg += "\n";
		OutputDebugString(outMsg.c_str());
	}
	while (!mKeyboard.IsKeyBufferEmpty())
	{
		unsigned char keycode = mKeyboard.ReadKey().GetKeyCode();
		std::string outMsg = "Input keycode : ";
		outMsg += keycode;
		outMsg += "\n";
		OutputDebugString(outMsg.c_str());
	}
	while (!mMouse.IsEventBufferEmpty())
	{
		MouseEvent me = mMouse.GetEvent();
		std::string outMsg = "X: ";
		outMsg += std::to_string(me.GetPosX());
		outMsg += " Y: ";
		outMsg += std::to_string(me.GetPosY());
		OutputDebugString(outMsg.c_str());
	}
}


void Engine::Render()
{
	mGraphics.RenderFrame();
}
