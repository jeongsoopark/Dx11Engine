#pragma once
#include "AdapterReader.h"
#include "Shader.h"
#include "Vertex.h"
#include <WICTextureLoader.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Initialize(HWND hwnd, int width, int height);
	void RenderFrame();
	void ClearFrame(float* bgColor);

private:
	bool InitializeDirectX(HWND hwnd, int width, int height);
	bool InitializeShaders();
	bool InitializeScene();

	ComPtr<ID3D11Device> mDevice;
	ComPtr<ID3D11DeviceContext> mDeviceContext;
	ComPtr<IDXGISwapChain> mSwapChain;

	ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	ComPtr<ID3D11DepthStencilView> mDepthStencilView;
	ComPtr<ID3D11Texture2D> mDepthStencilBuffer;


	VertexShader mVertexShader;
	PixelShader mPixelShader;

	IndexBuffer mIndexBuffer;
	VertexBuffer<Vertex> mVertexBuffer;
	ConstantBuffer<ConstantBufferVSType> mConstantBuffer;

	ComPtr<ID3D11RasterizerState> mRasterizerState;
	ComPtr<ID3D11DepthStencilState> mDepthStencilState;

	ComPtr<ID3D11SamplerState> mSamplerState;
	ComPtr<ID3D11ShaderResourceView> mSRV;


};

