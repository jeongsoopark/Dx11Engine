#include "Model.h"

bool Model::Initialize(const std::string & filepath, ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* texture, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader)
{
	this->device = device;
	this->deviceContext = deviceContext;
	this->texture = texture;
	this->cb_vs_vertexshader = &cb_vs_vertexshader;

	//Textured Square
	try 
	{
		if (!this->LoadModel(filepath))
		{
			return false;
		}
	}
	catch (COMException & exception)
	{
		ErrorLogger::Log(exception);
		return false;
	}

	return true;
}

void Model::SetTexture(ID3D11ShaderResourceView* texture)
{

	this->texture = texture;
}

void Model::Draw(const XMMATRIX& worldMatrix, const XMMATRIX& viewProjectionMatrix)
{
	this->cb_vs_vertexshader->data.mat = worldMatrix*viewProjectionMatrix;
	this->cb_vs_vertexshader->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader->data.mat);
	this->cb_vs_vertexshader->ApplyChanges();

	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader->GetAddressOf());
	this->deviceContext->PSSetShaderResources(0, 1, &(this->texture));

	for (UINT i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw();
	}
}

bool Model::LoadModel(const std::string& filepath)
{
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(filepath,
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded);
	if(pScene == NULL)
		return false;
	this->ProcessNode(pScene->mRootNode, pScene);
	return true;
}

void Model::ProcessNode(aiNode* node, const aiScene * scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(this->ProcessMesh(mesh, scene));;
	}


	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}

}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene * scene)
{

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;
	//for vertices
	for (UINT i = 0 ; i < mesh->mNumVertices; i++)
	{
		Vertex v;
		v.pos.x = mesh->mVertices[i].x;
		v.pos.y = mesh->mVertices[i].y;
		v.pos.z = mesh->mVertices[i].z;
		if (mesh->mTextureCoords[0])
		{
			v.texCoord.x = (float)mesh->mTextureCoords[0][i].x;
			v.texCoord.y = (float)mesh->mTextureCoords[0][i].y;

		}
		vertices.push_back(v);
	}

	//for indices
	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	return Mesh(this->device, this->deviceContext, vertices, indices);
}


