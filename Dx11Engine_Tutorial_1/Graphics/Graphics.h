#pragma once
#include "AdapterReader.h"
#include "Shader.h"

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

	ComPtr<ID3D11Device> mDevice;
	ComPtr<ID3D11DeviceContext> mDeviceContext;
	ComPtr<IDXGISwapChain> mSwapChain;
	ComPtr<ID3D11RenderTargetView> mRenderTargetView;

	ComPtr<ID3D11InputLayout> mInputLayout;
	ComPtr<ID3D10Blob> mVertexShaderBuffer;

	VertexShader mVertexShader;

};

