#pragma once

#include <d3d11.h>
#include <D3DX11tex.h>


class Texture
{
public:
	Texture();
	~Texture();

	bool Init(ID3D11Device* _device, LPCSTR _fileName);

	int GetWidth();
	int GetHeight();
	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* mTexture;
	int mWidth;
	int mHeight;

};

