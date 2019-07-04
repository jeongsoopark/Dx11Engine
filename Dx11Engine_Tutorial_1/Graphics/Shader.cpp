#include "Shader.h"



VertexShader::VertexShader()
{
}


VertexShader::~VertexShader()
{
}

bool VertexShader::Initialize(ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT nElement)
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

	hr = device->CreateInputLayout(layoutDesc, nElement, mpShaderBlob->GetBufferPointer(), mpShaderBlob->GetBufferSize(), mpInputLayout.GetAddressOf());
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create input layout ");
		return false;
	}


	return true;
}


ID3D11VertexShader* VertexShader::GetShader()
{
	return mpShader.Get();
}

ID3D10Blob* VertexShader::GetShaderBlob()
{
	return mpShaderBlob.Get();
}

ID3D11InputLayout * VertexShader::GetInputLayout()
{
	return mpInputLayout.Get();
}



PixelShader::PixelShader()
{
}


PixelShader::~PixelShader()
{
}




bool PixelShader::Initialize(ComPtr<ID3D11Device>& device, std::wstring shaderPath)
{
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), mpShaderBlob.GetAddressOf());
	if (FAILED(hr))
	{
		std::wstring errMsg = L"Failed to load shader";
		errMsg += shaderPath;
		ErrLogger::Log(hr, errMsg);
		return false;
	}

	hr = device->CreatePixelShader(mpShaderBlob->GetBufferPointer(), mpShaderBlob->GetBufferSize(), NULL, mpShader.GetAddressOf());

	if (FAILED(hr))
	{
		std::wstring errMsg = L"Failed to create pixel shader";
		errMsg += shaderPath;
		ErrLogger::Log(hr, errMsg);
		return false;
	}
	return true;
}


ID3D11PixelShader* PixelShader::GetShader()
{
	return mpShader.Get();
}

ID3D10Blob* PixelShader::GetShaderBlob()
{
	return mpShaderBlob.Get();
}


