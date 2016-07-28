#include "VertexBuffer.h"



VertexBuffer::VertexBuffer()
{
	mVertices = 0;
	mShader = 0;
	mVertexBuffer = 0;
	mIndexBuffer = 0;
	mVertexCount = 0;
	mIndexCount = 0;
}


VertexBuffer::~VertexBuffer()
{
	if (mVertices)
	{
		delete[] mVertices;
		mVertices = nullptr;
	}
	if (mVertexBuffer)
	{
		mVertexBuffer->Release();
		mVertexBuffer = 0;
	}
	if (mIndexBuffer)
	{
		mIndexBuffer->Release();
		mIndexBuffer = 0;
	}
}

bool VertexBuffer::Init(ID3D11Device * _device, Shader * _shader, float _size, bool _writable)
{
	ULONG* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT res;
	mShader = _shader;

	mVertexCount = 4;
	mIndexCount = 6;

	mVertices = new VertexType[mVertexCount];
	indices = new ULONG[mIndexCount];

	float halfSize = _size / 2.0f;

	mVertices[0].position = D3DXVECTOR3(-halfSize, -halfSize, 0.0f);
	mVertices[0].uv = D3DXVECTOR2(0.0f, 1.0f);
	mVertices[1].position = D3DXVECTOR3(-halfSize, halfSize, 0.0f);
	mVertices[1].uv = D3DXVECTOR2(0.0f, 0.0f);
	mVertices[2].position = D3DXVECTOR3(halfSize, halfSize, 0.0f);
	mVertices[2].uv = D3DXVECTOR2(1.0f, 0.0f);
	mVertices[3].position = D3DXVECTOR3(halfSize, -halfSize, 0.0f);
	mVertices[3].uv = D3DXVECTOR2(1.0f, 1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	vertexBufferDesc.Usage = _writable ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = _writable ? D3D11_CPU_ACCESS_WRITE : 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = mVertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	res = _device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer);
	if (FAILED(res))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(ULONG) * mIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	res = _device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer);
	if (FAILED(res))
	{
		return false;
	}

	//release
	delete[] indices;
	indices = nullptr;

	return true;
}

void VertexBuffer::Render(ID3D11DeviceContext * _deviceContext)
{
	UINT stride;
	UINT offset;

	stride = sizeof(VertexType);
	offset = 0;

	mShader->Begin(_deviceContext, mIndexCount);

	_deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	_deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    mShader->End(_deviceContext);

}

VertexBuffer::VertexType * VertexBuffer::GetVertices()
{
	return nullptr;
}

ID3D11Buffer * VertexBuffer::GetVertexBuffer()
{
	return nullptr;
}

int VertexBuffer::GetIndexcount()
{
	return 0;
}
