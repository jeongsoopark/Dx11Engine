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
	IDXGIFactory* factory = nullptr;
	IDXGIAdapter* adapter = nullptr;
	IDXGIOutput* adapterOutput = nullptr;
	UINT numModes, numerator, denominator, stringLength;
	DXGI_MODE_DESC* displayModeList = nullptr;
	DXGI_ADAPTER_DESC adapterDesc;
	ID3D11Texture2D* backBufferPtr = nullptr;

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

	res = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(res))
	{
		MessageBox(NULL, "GetDisplayModeList() failed", "Error", MB_OK);
		return false;
	}

	displayModeList = new DXGI_MODE_DESC[numModes];
	res = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(res))
	{
		MessageBox(NULL, "GetDisplayModeList() failed", "Error", MB_OK);
		return false;
	}

	for (UINT i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (UINT)_width && displayModeList[i].Height == (UINT)_height)
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	if (numerator == 0 && denominator == 0)
	{
		MessageBox(NULL, "invalid denominator and numerator failed", "Error", MB_OK);
		return false;
	}

	res = adapter->GetDesc(&adapterDesc);
	if (numerator == 0 && denominator == 0)
	{
		MessageBox(NULL, "adapter->GetDesc() failed", "Error", MB_OK);
		return false;
	}

	mGPUMemory = (INT)(adapterDesc.DedicatedVideoMemory >> 20);

	delete[] displayModeList;
	displayModeList = NULL;
	adapterOutput->Release();
	adapterOutput = NULL;
	adapter->Release();
	adapter = NULL;
	factory->Release();
	factory = NULL;

	if (!initSwapChain(_hwnd, _fullscreen, _width, _height, numerator, denominator))
	{
		MessageBox(NULL, "initSwapChain() failed", "Error", MB_OK);
		return false;
	}

	res = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferPtr);
	if (FAILED(res))
	{
		MessageBox(NULL, "GetBuffer() - backbufferptr-  failed", "Error", MB_OK);
		return false;
	}
	res = mDevice->CreateRenderTargetView(backBufferPtr, NULL, &mRenderTargetView);
	if (FAILED(res))
	{
		MessageBox(NULL, "CreateRenderTargetView() failed", "Error", MB_OK);
		return false;
	}
	backBufferPtr->Release();
	backBufferPtr = nullptr;

	if (!initDepthBuffer(_width, _height))
	{
		return false;
	}
	if (!initDepthStencilBuffer())
	{
		return false;
	}
	if (!initStencilView())
	{
		return false;
	}
	if (!initStencilView())
	{
		return false;
	}
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	if (!initRasterizerState())
	{
		return false;
	}
	initViewport(_width, _height);

	if (!initAlphaBlending())
	{
		return false;;
	}

	return true;
}

void DxManager::BeginScene(float _r, float _g, float _b, float _a)
{
	float color[4];
	color[0] = _r;
	color[1] = _g;
	color[2] = _b;
	color[3] = _a;

	mDeviceContext->ClearRenderTargetView(mRenderTargetView, color);
	mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}

void DxManager::EndScene()
{
	if (mVsync)
	{
		mSwapChain->Present(1, 0);
	}
	else
	{
		mSwapChain->Present(0, 0);
	}
}

void DxManager::EnableAlphaBlending(bool _enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	if (_enable) 
	{
		mDeviceContext->OMSetBlendState(mAlphaBlendStateEnabled, blendFactor, 0xffffffff);
	}
	else 
	{
		mDeviceContext->OMSetBlendState(mAlphaBlendStateDisabled, blendFactor, 0xffffffff);
	}
}

void DxManager::EnableZBuffer(bool _enable)
{
	if (_enable) 
	{
		mDeviceContext->OMSetDepthStencilState(mDepthStencilStateEnabled, 0);
	}
	else
	{
		mDeviceContext->OMSetDepthStencilState(mDepthStencilStateDisabled, 0);
	}
}

ID3D11Device * DxManager::GetDevice()
{
	return nullptr;
}

ID3D11DeviceContext * DxManager::GetDeviceContext()
{
	return nullptr;
}

bool DxManager::initSwapChain(HWND _hwnd, bool _fullscreen, int _width, int _height, UINT _numerator, UINT _denominator)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT res;
	
	//init swapchaindesc structure
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = _width;
	swapChainDesc.BufferDesc.Height = _height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	if (mVsync)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = _numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = _denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = _hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !_fullscreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &mSwapChain, &mDevice, NULL, &mDeviceContext);
	if (FAILED(res))
	{
		MessageBox(NULL, "D3D11CreateDeviceAndSwapChain() failed", "Error", MB_OK);
		return false;
	}

	return true;
}

bool DxManager::initDepthBuffer(int _width, int _height)
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	HRESULT res; 
	
	ZeroMemory(&depthBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));

	depthBufferDesc.Width = _width;
	depthBufferDesc.Height = _height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1; 
	depthBufferDesc.SampleDesc.Quality = 0; 
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	res = mDevice->CreateTexture2D(&depthBufferDesc, nullptr, &mDepthStencilBuffer);
	if (FAILED(res))
	{
		return false;
	}
	return true;
}

bool DxManager::initZbuffer()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	HRESULT res;

	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = 0xff;
	depthStencilDesc.StencilWriteMask = 0xff;

	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;

	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;


	res = mDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStencilStateDisabled);
	if (FAILED(res))
	{
		return false;
	}
	return true;
}
bool DxManager::initDepthStencilBuffer()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	HRESULT res;

	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = 0xff;
	depthStencilDesc.StencilWriteMask = 0xff;

	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;

	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;


	res = mDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStencilStateEnabled);
	if (FAILED(res))
	{
		return false;
	}
	return true;
}

bool DxManager::initStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilView;
	HRESULT res; 
	ZeroMemory(&depthStencilView, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	depthStencilView.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilView.Texture2D.MipSlice = 0;

	res = mDevice->CreateDepthStencilView(mDepthStencilBuffer, &depthStencilView, &mDepthStencilView);
	if (FAILED(res))
	{
		return false;
	}


	return true;
}

bool DxManager::initRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterDesc;
	HRESULT res;

	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	res = mDevice->CreateRasterizerState(&rasterDesc, &mRasterizerState);
	if (FAILED(res))
	{
		return false;
	}
	mDeviceContext->RSSetState(mRasterizerState);

	return true;
}

void DxManager::initViewport(int _width, int _height)
{
	D3D11_VIEWPORT viewport;

	viewport.Width = _width;
	viewport.Height = _height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	mDeviceContext->RSSetViewports(1, &viewport);
}

bool DxManager::initAlphaBlending()
{
	D3D11_BLEND_DESC blendDesc;
	HRESULT res;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	res = mDevice->CreateBlendState(&blendDesc, &mAlphaBlendStateEnabled);
	if(FAILED(res))
	{	
		return false;
	}
	blendDesc.RenderTarget[0].BlendEnable = false;
	res = mDevice->CreateBlendState(&blendDesc, &mAlphaBlendStateDisabled);
	if(FAILED(res))
	{	
		return false;
	}

	return true;
}
