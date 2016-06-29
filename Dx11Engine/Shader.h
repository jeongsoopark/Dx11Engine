#pragma once

#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h >
#include <fstream>
using namespace std;

class Shader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX worldMatrix;
		D3DXMATRIX viewMatrix;
		D3DXMATRIX projectionMatrix;
	};
public:
	Shader(ID3D11Device* _device, HWND _hwnd, LPCSTR _shaderFileName, LPCSTR _vertexFuncName, LPCSTR _pixelFuncName);
	Shader();
	virtual ~Shader();

	virtual void Begin(ID3D11DeviceContext* _deviceContext, int _indexCount);
	virtual void End(ID3D11DeviceContext* _deviceContext);

	bool SetShaderParameters(ID3D11DeviceContext* _deviceContext, ID3D11ShaderResourceView* _texture);
	bool SetShaderParameters(ID3D11DeviceContext* _deviceContext, D3DXMATRIX _world, D3DXMATRIX _view, D3DXMATRIX _projection);

	char* GetName();
	bool isInit();


protected:
	virtual bool Init(ID3D11Device* _device, HWND _hwnd, LPCSTR _shaderFileName, LPCSTR _vertexFuncName, LPCSTR _pixelFuncName);

private:
	bool initShader(ID3D11Device* _device, HWND _hwnd, LPCSTR _vsFileName, LPCSTR _psFileName, LPCSTR _vertexFuncName, LPCSTR _pixelFuncName);
	void OutputShaderError(ID3D10Blob* _msg, HWND _hwnd, LPCSTR _shaderFileName);

	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader* mPixelShader;
	ID3D11InputLayout* mLayout;
	ID3D11Buffer* mMatrixBuffer;
	char* mName;
	bool mIsInit;
	DXGI_MODE_DESC* displayModeList = nullptr;
};

