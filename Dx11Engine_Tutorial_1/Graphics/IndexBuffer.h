#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

using namespace Microsoft::WRL;

class IndexBuffer
{
public:
	IndexBuffer() {};
	~IndexBuffer() {};

private:
	ComPtr<ID3D11Buffer> buffer;
	UINT bufferSize;

public:
	ID3D11Buffer* Get() const
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

	HRESULT Initialize(ID3D11Device* device, DWORD * data, UINT numIndices)
	{
		D3D11_BUFFER_DESC ibDesc;
		ZeroMemory(&ibDesc, sizeof(D3D11_BUFFER_DESC));
		ibDesc.Usage = D3D11_USAGE_DEFAULT;
		ibDesc.ByteWidth = sizeof(DWORD)* numIndices;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA ibData;
		ZeroMemory(&ibData, sizeof(D3D11_SUBRESOURCE_DATA));
		ibData.pSysMem = data;

		return device->CreateBuffer(&ibDesc, &ibData, buffer.GetAddressOf());
	}
};
