#pragma once

#include "Mesh.h"

using namespace DirectX;

class Model
{
public:
	bool Initialize(const std::string & filepath, ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* texture, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void Draw(const XMMATRIX& worldMatrix, const XMMATRIX& viewProjectionMatrix);

private:
	bool LoadModel(const std::string& filepath);
	void ProcessNode(aiNode* node, const aiScene * scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene * scene);

	std::vector<Mesh> meshes;

	ID3D11Device * device = nullptr;
	ID3D11DeviceContext * deviceContext = nullptr;
	ConstantBuffer<CB_VS_vertexshader> * cb_vs_vertexshader = nullptr;
	ID3D11ShaderResourceView * texture = nullptr;
};
