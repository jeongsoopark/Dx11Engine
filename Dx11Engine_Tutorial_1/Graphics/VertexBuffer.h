#pragma once
#include <wrl/client.h>
#include <d3d11.h>
using namespace Microsoft::WRL;
using namespace std;

template<class T>
class VertexBuffer
{
public:
	VertexBuffer() {};
	~VertexBuffer() {};


private:
	ComPtr<ID3D11Buffer> buffer;
	std::unique_ptr<UINT> stride;
	UINT bufferSize;

public:
	ID3D11Buffer* GetBuffer() const
	{
		return buffer.Get();
	}
	ID3D11Buffer* const* GetAddressOf() const
	{
		return buffer.GetAddressOf();
	}

	UINT BufferSize() const
	{
		return bufferSize;
	}

	const UINT Stride() const 
	{
		return *stride.get();
	}
	const UINT * StridePtr() const
	{
		return stride.get();
	 }

	HRESULT Initialize(ID3D11Device *device, T* data, UINT numberVertices)
	{
		bufferSize = numberVertices;
		stride = std::make_unique<UINT>(sizeof(T));

		D3D11_BUFFER_DESC vbDesc;
		ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));

		vbDesc.Usage = D3D11_USAGE_DEFAULT;
		vbDesc.ByteWidth = sizeof(T)* numberVertices;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vbData;
		ZeroMemory(&vbData, sizeof(D3D11_SUBRESOURCE_DATA));
		vbData.pSysMem = data;

		return device->CreateBuffer(&vbDesc, &vbData, buffer.GetAddressOf());
	}
};
