#include "Graphics.h"



Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	if (!InitializeDirectX(hwnd, width, height))
	{
		return false;
	}

	if (!InitializeShaders())
	{
		return false;
	}

	return true;
}

void Graphics::RenderFrame()
{
	float backColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), backColor);
	mSwapChain->Present(1, NULL);
}

void Graphics::ClearFrame(float * bgColor)
{
	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
	mSwapChain->Present(1, NULL);
}

bool Graphics::InitializeDirectX(HWND hwnd, int width, int height)
{
	std::vector<AdapterData> adapters = AdapterReader::GetAdapterData();

	if (adapters.size() < 1)
	{
		ErrLogger::Log("No IDXGI adapter found");
		return false;
	}

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	SwapChainDesc.BufferDesc.Width = width;
	SwapChainDesc.BufferDesc.Height = height;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;

	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.OutputWindow = hwnd;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	//Createing Swapchain
	HRESULT hr = D3D11CreateDeviceAndSwapChain(adapters[0].mpAdapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		NULL,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		this->mSwapChain.GetAddressOf(),
		this->mDevice.GetAddressOf(),
		NULL,
		this->mDeviceContext.GetAddressOf()
	);

	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create swapchain");
		return false;
	}

	//RenderTargetview Creation

	//get back buffer from swapchain
	ComPtr<ID3D11Resource> backBuffer;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to get buffer from SwapChain");
		return false;
	}

	D3D11_RENDER_TARGET_BLEND_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));

	hr = mDevice->CreateRenderTargetView(backBuffer.Get(), NULL, this->mRenderTargetView.GetAddressOf());
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create render target view from back buffer from SwapChain");
		return false;
	}

	mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), NULL);


	//D3d11_view
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Width = width;
	viewport.Height = height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	mDeviceContext->RSSetViewports(1, &viewport);
	return true;
}

bool Graphics::InitializeShaders()
{
	std::wstring shaderFolder = L"D:\\Github\\Dx11Engine\\Dx11Engine_Tutorial_1\\";
#pragma region DetermineShaderFolder
	if (IsDebuggerPresent())
	{
#if 0
	#ifdef _WIN64
		shaderFolder = L"..\\x64\\Debug\\";
	#else
		shaderFolder = L"..\\x86\\Debug\\";
	#endif
#else
	#ifdef _WIN64
		shaderFolder = L"..\\x64\\Release\\";
	#else
		shaderFolder = L"..\\x86\\Release\\";
	#endif
#endif
	}


	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT nElements = ARRAYSIZE(layout);

	if (!mVertexShader.Initialize(mDevice, shaderFolder + L"vertexshader.cso", layout, nElements))
	{
		return false;
	}

	if (!mPixelShader.Initialize(mDevice, shaderFolder + L"pixelshader.cso"))
	{
		return false;
	}



	return true;
}
