#pragma once
#pragma comment(lib, "D3DCompiler.lib")

#include "../ErrLogger.h"
#include <d3d11.h>
#include <wrl/client.h>>
#include <d3dcompiler.h>


using namespace Microsoft::WRL;
class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	bool Initialize(ComPtr<ID3D11Device> &device, std::wstring shaderPath);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetShaderBlob();

private:
	ComPtr<ID3D11VertexShader> mpShader = nullptr;
	ComPtr<ID3D10Blob> mpShaderBlob = nullptr;

};

