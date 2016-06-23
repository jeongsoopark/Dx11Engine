#include "Graphics.h"



Graphics::Graphics()
{
	mDxManager = nullptr;
}


Graphics::~Graphics()
{
	if (mDxManager)
	{
		delete mDxManager;
		mDxManager = nullptr;
	}
}

bool Graphics::InitDX(HWND _hwnd)
{
	mDxManager = new DxManager();
	if (!mDxManager->Init(SCREEN_WIDTH, SCREEN_HEIGHT, bVSync, _hwnd, bFULL_SCREEN))
	{
		return false;
	}
	return true;
}

void Graphics::Init()
{
}

void Graphics::BeginScene(float _r, float _g, float _b, float _a)
{
	mDxManager->BeginScene(_r, _g, _b, _a);
}

void Graphics::EndScene()
{
	mDxManager->EndScene();
}

void Graphics::EnableAlphaBlending(bool _enable)
{
	mDxManager->EnableAlphaBlending(_enable);
}

void Graphics::EnableZBuffer(bool _enable)
{
	mDxManager->EnableZBuffer(_enable);
}

DxManager * Graphics::GetDXManager()
{
	return mDxManager;
}

HWND Graphics::GetHwnd()
{
	return mHwnd;
}

void Graphics::SetHwnd(HWND _hwnd)
{
	mHwnd = _hwnd;
}

ID3D11Device * Graphics::GetDevice()
{
	return mDxManager->GetDevice();
}

ID3D11DeviceContext * Graphics::GetDeviceContext()
{
	return mDxManager->GetDeviceContext();
}
