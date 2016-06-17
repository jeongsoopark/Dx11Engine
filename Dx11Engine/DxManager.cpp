#include "DxManager.h"



DxManager::DxManager()
{

	mSwapChain = 0;
	mDevice =0;
	mDeviceContext =0;
	mRenderTargetView =0;
	mDepthStencilBuffer =0;
	mDepthStencilView =0;
	mRasterizerState =0;
	mAlphaBlendStateEnabled =0;
	mAlphaBlendStateDisabled =0;
	mDepthStencilStateEnabled =0;
	mDepthStencilStateDisabled =0; 
}


DxManager::~DxManager()
{
	if (mSwapChain)
	{
		mSwapChain->SetFullscreenState(false, NULL);
	}

	if (mAlphaBlendStateEnabled)
	{
		mAlphaBlendStateEnabled->Release();
	}
}

bool DxManager::initSwapChain(HWND hwnd, bool fullscreen, int width, int height, UINT numerator, UINT denominator)
{
	return false;
}

bool DxManager::initDepthBuffer(int width, int height)
{
	return false;
}

bool DxManager::initDepthStencilBuffer()
{
	return false;
}

bool DxManager::initStencilView()
{
	return false;
}

bool DxManager::initRasterizerState()
{
	return false;
}

bool DxManager::initViewport(int width, int height)
{
	return false;
}

bool DxManager::initAlphaBlending()
{
	return false;
}
