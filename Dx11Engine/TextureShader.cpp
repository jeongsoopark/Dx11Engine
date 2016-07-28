#include "TextureShader.h"


TextureShader::TextureShader(ID3D11Device* _device, HWND _hwnd, LPCSTR _shaderFileName, LPCSTR _vsFuncName, LPCTSTR _psFuncName) :
    Shader(_device, _hwnd, _shaderFileName, _vsFuncName, _psFuncName)
{
    mIsInit = InitSamplerState(_device);
}



TextureShader::TextureShader()
{
}


TextureShader::~TextureShader()
{
	if (mSamplerState)
	{
		mSamplerState->Release();
		mSamplerState = 0;
	}
}

bool TextureShader::Init(ID3D11Device* _device, HWND _hwnd, LPCSTR _shaderFileName, LPCSTR _vertexFuncName, LPCSTR _pixelFuncName)
{
	if (!Shader::Init(_device, _hwnd, _shaderFileName, _vertexFuncName, _pixelFuncName))
	{
		return false;
	}
	return true;
}

bool TextureShader::InitSamplerState(ID3D11Device * _device)
{
	D3D11_SAMPLER_DESC samplerDesc;
	HRESULT res;

	//setting sampler description
	samplerDesc.Filter = D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//create sampler state
	res = _device->CreateSamplerState(&samplerDesc, &mSamplerState);
	if (FAILED(res))
	{
		return false;
	}
	return true;
}

void TextureShader::Begin(ID3D11DeviceContext* _deviceContext, int _indexCount)
{
	_deviceContext->PSSetSamplers(0, 1, &mSamplerState);
	Shader::Begin(_deviceContext, _indexCount);
}

void TextureShader::End(ID3D11DeviceContext* _deviceContext)
{
	_deviceContext->PSSetSamplers(0, 0, NULL);
	Shader::End(_deviceContext);
}

