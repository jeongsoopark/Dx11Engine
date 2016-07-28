#pragma once
#include "Shader.h"

class TextureShader : public Shader
{
public:
    TextureShader(ID3D11Device* _device, HWND _hwnd, LPCSTR _shaderFileName, LPCSTR _vsFuncName, LPCTSTR _psFuncName);
	TextureShader();
	virtual ~TextureShader();

	void Begin(ID3D11DeviceContext* _deviceContext, int _indexCount);
	void End(ID3D11DeviceContext* _deviceContext);
	bool Init(ID3D11Device* _device, HWND _hwnd, LPCSTR _shaderFileName, LPCSTR _vertexFuncName, LPCSTR _pixelFuncName);

	bool InitSamplerState(ID3D11Device* _device);
private:
	ID3D11SamplerState* mSamplerState;
};

