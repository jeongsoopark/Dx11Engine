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

	if (!InitializeScene())
	{
		return false;
	}
	return true;
}

void Graphics::RenderFrame()
{
	float backColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), backColor);
	mDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);

	mDeviceContext->RSSetState(mRasterizerState.Get());
	mDeviceContext->OMSetDepthStencilState(mDepthStencilState.Get(), 0);

	mDeviceContext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	mDeviceContext->IASetInputLayout(mVertexShader.GetInputLayout());
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDeviceContext->PSSetSamplers(0, 1, mSamplerState.GetAddressOf());

	//setting constnat buffer
	mConstantBuffer.data.xOffset = 0.5;
	mConstantBuffer.data.yOffset = 0.8;
	if (!mConstantBuffer.ApplyChanges())
	{
		return;
	}

	mDeviceContext->VSSetConstantBuffers(0, 1, mConstantBuffer.GetAddressOf());

	//setting SRV texture
	mDeviceContext->PSSetShaderResources(0, 1, mSRV.GetAddressOf());
	mDeviceContext->VSSetShader(mVertexShader.GetShader(), NULL, 0);
	mDeviceContext->PSSetShader(mPixelShader.GetShader(), NULL, 0);

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	//blue
	mDeviceContext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), mVertexBuffer.StridePtr(), &offset);
	mDeviceContext->DrawIndexed(6, 0, 0);

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

	//create depth stencil buffer and view
	D3D11_TEXTURE2D_DESC DSBufferDesc;
	ZeroMemory(&DSBufferDesc, sizeof(DSBufferDesc));

	DSBufferDesc.Width = width;
	DSBufferDesc.Height = height;
	DSBufferDesc.MipLevels = 1;
	DSBufferDesc.ArraySize = 1;
	DSBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
	DSBufferDesc.SampleDesc.Count = 1;
	DSBufferDesc.SampleDesc.Quality = 0;
	DSBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DSBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DSBufferDesc.CPUAccessFlags = 0;
	DSBufferDesc.MiscFlags = 0;

	hr = mDevice->CreateTexture2D(&DSBufferDesc, NULL, mDepthStencilBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create depth stencil buffer");
		return false;
	}

	hr = mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), NULL, mDepthStencilView.GetAddressOf());
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create depth stencil view");
		return false;
	}


	//D3d11_viewport state
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	mDeviceContext->RSSetViewports(1, &viewport);

	//create depth stencil state
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	mDevice->CreateDepthStencilState(&dsDesc, mDepthStencilState.GetAddressOf());

	//setting RSstate 
	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(rsDesc));
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_NONE;
	hr = mDevice->CreateRasterizerState(&rsDesc, mRasterizerState.GetAddressOf());
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create rasterizer state");
		return false;
	}

	//create sampler state
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = mDevice->CreateSamplerState(&smpDesc, mSamplerState.GetAddressOf());
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create sampler state");
		return false;
	}


	hr = DirectX::CreateWICTextureFromFile(mDevice.Get(), L"Texture\\test.jpg", nullptr, mSRV.GetAddressOf());
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to load texture");
		return false;
	}

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
		{"POSITION",	0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
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

bool Graphics::InitializeScene()
{

	HRESULT hr;
	DWORD indices[] = { 0, 1, 2, 2, 1, 3 };

	hr = mIndexBuffer.Initialize(mDevice.Get(), indices, ARRAYSIZE(indices));
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create index buffer");
		return false;
	}

	Vertex v1[] = {

		Vertex(-0.5f, -0.5f, 0.5f,	0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, 0.5f,	0.0f, 1.0f),
		Vertex(0.5f, -0.5f, 0.5f,	1.0f, 0.0f),
		Vertex(0.5f, 0.5f, 0.5f,	1.0f, 1.0f)
	};

	hr = mVertexBuffer.Initialize(mDevice.Get(), v1, ARRAYSIZE(v1));
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create vertex buffer 1");
		return false;
	}

	hr = mConstantBuffer.Initialize(mDevice.Get(), mDeviceContext.Get());
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to initialize constant buffer ");
		return false;
	}

	return true;
}
