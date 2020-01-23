#pragma once
#include <d3d11.h>
#include "ConstantBufferTypes.h"
#include <wrl/client.h>
#include "../ErrLogger.h"

using namespace Microsoft::WRL;


template<class T>
class ConstantBuffer
{
private:
	ConstantBuffer(const ConstantBuffer<T>& rhs);

	ComPtr<ID3D11Buffer> buffer;
	ID3D11DeviceContext* deviceContext = nullptr;
	UINT bufferSize;


public:
	ConstantBuffer() {};
	~ConstantBuffer() {};

	T data;
	ID3D11Buffer* Get() const 
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* GetAddressOf() const 
	{
		return buffer.GetAddressOf();
	}

	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	{
		this->deviceContext = deviceContext;
		D3D11_BUFFER_DESC cbDesc;
		ZeroMemory(&cbDesc, sizeof(cbDesc));
		cbDesc.Usage = D3D11_USAGE_DYNAMIC;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbDesc.MiscFlags = 0;
		cbDesc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
		cbDesc.StructureByteStride = 0;
		return device->CreateBuffer(&cbDesc, 0, buffer.GetAddressOf());
	}
	
	bool ApplyChanges()
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		HRESULT hr = deviceContext->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(hr))
		{
			ErrLogger::Log(hr, "Failed to map for constant buffer ");
			return false;
		}
		CopyMemory(mappedResource.pData, &data, sizeof(T));
		deviceContext->Unmap(buffer.Get(), 0);

		return true;
	}
};
