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

void Shader::Begin(ID3D11DeviceContext * _deviceContext, int _indexCount)
{
	_deviceContext->IASetInputLayout(mLayout);

	_deviceContext->VSSetShader(mVertexShader, NULL, 0);
	_deviceContext->PSSetShader(mPixelShader, NULL, 0);

	_deviceContext->DrawIndexed(_indexCount, 0, 0);
}

void Shader::End(ID3D11DeviceContext * _deviceContext)
{
	_deviceContext->IASetInputLayout(NULL);

	_deviceContext->VSSetShader(NULL, NULL, 0);
	_deviceContext->PSSetShader(NULL, NULL, 0);
}

bool Shader::SetShaderParameters(ID3D11DeviceContext * _deviceContext, ID3D11ShaderResourceView * _texture)
{
	_deviceContext->PSSetShaderResources(0, 1, &_texture);
	return true;
}

bool Shader::SetShaderParameters(ID3D11DeviceContext * _deviceContext, D3DXMATRIX _world, D3DXMATRIX _view, D3DXMATRIX _projection)
{
	HRESULT res; 
	D3D11_MAPPED_SUBRESOURCE mappedResource; 
	MatrixBufferType* dataPtr;
	UINT bufferNumber;

	D3DXMatrixTranspose(&_world, &_world);
	D3DXMatrixTranspose(&_view, &_view);
	D3DXMatrixTranspose(&_projection, &_projection);

	res = _deviceContext->Map(mMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(res))
	{
		return false;
	}
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->worldMatrix = _world;
	dataPtr->viewMatrix = _view;
	dataPtr->projectionMatrix = _projection;

	_deviceContext->unmap(mMatrixBuffer, 0);

	return true;
}

char * Shader::GetName()
{
	return nullptr;
}

bool Shader::isInit()
{
	return true;
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

	return initShader(_device, _hwnd, vsFileName, psFileName, _vertexFuncName, _pixelFuncName);
}

bool Shader::initShader(ID3D11Device* _device, HWND _hwnd, LPCSTR _vsFileName, LPCSTR _psFileName, LPCSTR _vsFuncName, LPCSTR _psFuncName)
{
	HRESULT res = NULL; 
	ID3D10Blob* err = nullptr;
	ID3D10Blob* vsBuffer = nullptr;
	ID3D10Blob* psBuffer = nullptr;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	UINT numElements;
	D3D11_BUFFER_DESC  matrixBufferDesc;

	//compile vertex shader 
	res = D3DX11CompileFromFile(_vsFileName, NULL, NULL, _vsFuncName, "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,
		&vsBuffer, &err, NULL);
	if (FAILED(res))
	{
		if (err)
		{
			OutputShaderError(err, _hwnd, _vsFileName);
		}
		else
		{
			MessageBox(_hwnd, _vsFileName, "Vertex shader code error", MB_OK);
		}
		return false;
	}


	//compile pixel shader
	res = D3DX11CompileFromFile(_psFileName, NULL, NULL, _psFuncName, "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,
		&psBuffer, &err, NULL);
	if (FAILED(res))
	{
		if (err)
		{
			OutputShaderError(err, _hwnd, _psFileName);
		}
		else
		{
			MessageBox(_hwnd, _psFileName, "Pixel shader code error", MB_OK);
		}
		return false;
	}


	//create vertex shader
	res = _device->CreateVertexShader(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), NULL, &mVertexShader);
	if (FAILED(res))
	{
		MessageBox(_hwnd, _vsFileName, "Vertex shader creation failed", MB_OK);
		return false;
	}

	//create pixel shader
	res = _device->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), NULL, &mPixelShader);
	if (FAILED(res))
	{
		MessageBox(_hwnd, _psFileName, "Pixel shader creation failed", MB_OK);
		return false;
	}

	//setup shader input layout - position
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	//setup shader input layout - texture
	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
		
	//create input layout 
	res = _device->CreateInputLayout(polygonLayout, numElements, vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), &mLayout);
	if (FAILED(res))
	{
		MessageBox(_hwnd, _psFileName, "Input layout creation failed", MB_OK);
		return false;
	}
	vsBuffer->Release();
	vsBuffer = nullptr;
	psBuffer->Release();
	psBuffer = nullptr;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(matrixBufferDesc);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	res = _device->CreateBuffer(&matrixBufferDesc, NULL, &mMatrixBuffer);
	if (FAILED(res))
	{
		MessageBox(_hwnd, _psFileName, "Matrix buffer creation failed", MB_OK);
		return false;
	}

	return true;
}

void Shader::OutputShaderError(ID3D10Blob * _msg, HWND _hwnd, LPCSTR _shaderFileName)
{
	char* compileErr = (char*)_msg->GetBufferPointer();
	ULONG bufferSize = _msg->GetBufferSize();

	ofstream fout;
	fout.open("shader_err.txt");

	for (UINT i = 0; i < bufferSize; i++)
	{
		fout << compileErr[i];
	}

	fout.close();
	_msg->Release();
	_msg = nullptr;
	
	MessageBox(_hwnd, "Shader compilation error, check shader_err.txt", _shaderFileName, MB_OK);
	return;
}
