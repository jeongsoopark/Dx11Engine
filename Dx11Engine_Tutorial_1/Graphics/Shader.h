#pragma once

#include "../ErrLogger.h"
#include <d3d11.h>
#include <wrl/client.h>>
#include <d3dcompiler.h>


#pragma comment(lib, "D3DCompiler.lib")
using namespace Microsoft::WRL;
class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	bool Initialize(ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT nElement);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetShaderBlob();
	ID3D11InputLayout* GetInputLayout();

private:
	ComPtr<ID3D11VertexShader> mpShader = nullptr;
	ComPtr<ID3D10Blob> mpShaderBlob = nullptr;
	ComPtr<ID3D11InputLayout> mpInputLayout;
};

class PixelShader
{
public:
	PixelShader();
	~PixelShader();

	bool Initialize(ComPtr<ID3D11Device>& device, std::wstring shaderPath);
	ID3D11PixelShader* GetShader();
	ID3D10Blob* GetShaderBlob();

private:
	ComPtr<ID3D11PixelShader> mpShader = nullptr;
	ComPtr<ID3D10Blob> mpShaderBlob = nullptr;


};
