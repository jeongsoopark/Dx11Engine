#include "Shader.h"



VertexShader::VertexShader()
{
}


VertexShader::~VertexShader()
{
}

bool VertexShader::Initialize(ComPtr<ID3D11Device>& device, std::wstring shaderPath)
{
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), mpShaderBlob.GetAddressOf());
	if (FAILED(hr))
	{
		std::wstring errMsg = L"Failed to load shader";
		errMsg += shaderPath;
		ErrLogger::Log(hr, errMsg);
		return false;
	}

	hr = device->CreateVertexShader(mpShaderBlob->GetBufferPointer(), mpShaderBlob->GetBufferSize(), NULL, mpShader.GetAddressOf());

	if (FAILED(hr))
	{
		std::wstring errMsg = L"Failed to create vertex shader";
		errMsg += shaderPath;
		ErrLogger::Log(hr, errMsg);
		return false;
	}


	return false;
}


ID3D11VertexShader* VertexShader::GetShader()
{
	return mpShader.Get();
}

ID3D10Blob* VertexShader::GetShaderBlob()
{
	return mpShaderBlob.Get();
}
