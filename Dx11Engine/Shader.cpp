#include "Shader.h"



Shader::Shader(ID3D11Device * _device, HWND _hwnd, LPCSTR _shaderFileName, LPCSTR _vertexFuncName, LPCSTR _pixelFuncName)
{
	mVertexShader = 0;
	mPixelShader = 0;
	mLayout = 0;
	mMatrixBuffer = 0;
	mIsInit = Init(_device, _hwnd, _shaderFileName, _vertexFuncName, _pixelFuncName);
}

Shader::Shader()
{
	mVertexShader = 0;
	mPixelShader = 0;
	mLayout = 0;
	mMatrixBuffer = 0;
	mIsInit = false;
}


Shader::~Shader()
{
	if (mMatrixBuffer)
	{
		mMatrixBuffer->Release();
		mMatrixBuffer = 0;
	}
	if (mLayout)
	{
		mLayout->Release();
		mLayout = 0;
	}
	if (mVertexShader)
	{
		mVertexShader->Release();
		mVertexShader = 0;
	}
	if (mPixelShader)
	{
		mPixelShader->Release();
		mPixelShader = 0;
	}
	if (mName)
	{
		delete [] mName;
		mName = nullptr;
	}
}

void Shader::Begin(ID3D11DeviceContext * _ieviceContext, int _indexCount)
{
}

void Shader::End(ID3D11DeviceContext * _deviceContext)
{
}

bool Shader::SetShaderParameters(ID3D11DeviceContext * _deviceContext, ID3D11ShaderResourceView * _texture)
{
	return false;
}

bool Shader::SetShaderParameters(ID3D11DeviceContext * _deviceContext, D3DXMATRIX _world, D3DXMATRIX _view, D3DXMATRIX _projection)
{
	return false;
}

char * Shader::GetName()
{
	return nullptr;
}

bool Shader::isInit()
{
	return false;
}

bool Shader::Init(ID3D11Device * _device, HWND _hwnd, LPCSTR _shaderFileName, LPCSTR _vertexFuncName, LPCSTR _pixelFuncName)
{
	bool res = false;
	UINT strLength = strlen(_shaderFileName);
	mName = new char[strLength];
	memcpy(mName, _shaderFileName, strLength);

	char vsFileName[100];
	strcpy_s(vsFileName, _shaderFileName);
	strcpy_s(vsFileName, ".vs\0");
	char psFileName[100];
	strcpy_s(psFileName, _shaderFileName);
	strcpy_s(psFileName, ".ps\0");


	return true;
}

bool Shader::initShader(ID3D11Device * _device, HWND _hwnd, LPCSTR _shaderFileName, LPCSTR _vertexFuncName, LPCSTR _pixelFuncName)
{
	return false;
}

void Shader::OutputShaderError(ID3D10Blob * _msg, HWND _hwnd, LPCSTR _shaderFileName)
{
}
