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
	if (mAlphaBlendStateEnabled)
	{
		mAlphaBlendStateEnabled->Release();
		mAlphaBlendStateEnabled = 0;
	}
	if (mAlphaBlendStateDisabled)
	{
		mAlphaBlendStateDisabled->Release();
		mAlphaBlendStateDisabled = 0;
	}
	if (mDepthStencilStateEnabled)
	{
		mDepthStencilStateEnabled->Release();
		mDepthStencilStateEnabled = 0;
	}
	if (mDepthStencilStateDisabled)
	{
		mDepthStencilStateDisabled->Release();
		mDepthStencilStateDisabled = 0;
	}
	if (mRasterizerState)
	{
		mRasterizerState->Release();
		mRasterizerState = 0;
	}
	if (mDepthStencilView)
	{
		mDepthStencilView->Release();
		mDepthStencilView = 0;
	}
	if (mDepthStencilBuffer)
	{
		mDepthStencilBuffer->Release();
		mDepthStencilBuffer = 0;
	}
	if (mRenderTargetView)
	{
		mRenderTargetView->Release();
		mRenderTargetView = 0;
	}
	if (mDeviceContext)
	{
		mDeviceContext->Release();
		mDeviceContext = 0;
	}
	if (mDevice)
	{
		mDevice->Release();
		mDevice = 0;
	}
	if (mSwapChain)
	{
		mSwapChain->SetFullscreenState(false, NULL);
	}
}

bool DxManager::Init(int _width, int _height, bool _vsync, HWND _hwnd, bool _fullscreen)
{
	HRESULT res;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	UINT numModes, i, numerator, denominator, stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC* adapterDesc;
	ID3D11Texture2D* backBuffer;
	INT error;

	//vsync setting copy
	mVsync = _vsync;

	//Create directx interface factor
	res = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(res))
	{
		MessageBox(NULL, "CreateDXGIFactory() failed", "Error", MB_OK);
		return false;
	}

	res = factory->EnumAdapters(0, &adapter);
	if (FAILED(res))
	{
		MessageBox(NULL, "EnumAdapters() failed", "Error", MB_OK);
		return false;
	}

	res = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(res))
	{
		MessageBox(NULL, "EnumOutputs() failed", "Error", MB_OK);
		return false;
	}
	
	return false;
}

void DxManager::BeginScene(float r, float g, float b, float a)
{
}

void DxManager::EndScene()
{
}

void DxManager::EnableAlphaBlending(bool en)
{
}

void DxManager::EnableZTest(bool en)
{
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
