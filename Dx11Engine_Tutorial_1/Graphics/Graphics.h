#pragma once
#include "AdapterReader.h"
#include "Shader.h"
#include "Vertex.h"

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


	VertexShader mVertexShader;
	PixelShader mPixelShader;

	ComPtr<ID3D11Buffer> mVertexBuffer;

};

