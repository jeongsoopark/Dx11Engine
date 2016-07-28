#pragma once

#include "Shader.h"
#include <d3d11.h>
#include <D3DX10math.h>

class VertexBuffer
{
public:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;
	};

	VertexBuffer();
	~VertexBuffer();

	bool Init(ID3D11Device* _device, Shader* _shader, float _size, bool writable = false);
	void Render(ID3D11DeviceContext* _deviceContext);

	VertexType* GetVertices();
	ID3D11Buffer* GetVertexBuffer();
	int GetIndexcount();

private:

	INT mVertexCount;
	INT mIndexCount;
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	VertexType* mVertices;
	Shader* mShader;
};

