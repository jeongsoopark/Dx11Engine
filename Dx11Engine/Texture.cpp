#include "Texture.h"



Texture::Texture()
{
	mTexture = 0;
	mWidth = 0;
	mHeight = 0;
}


Texture::~Texture()
{
	if (mTexture)
	{
		mTexture->Release();
		mTexture = 0;
	}
}

bool Texture::Init(ID3D11Device * _device, LPCSTR _fileName)
{
	HRESULT res; 

	res = D3DX11CreateShaderResourceViewFromFile(_device, _fileName, NULL, NULL, &mTexture, NULL);
	if (FAILED(res))
	{
		return false;
	}

	ID3D11Resource* resource = 0;
	mTexture->GetResource(&resource);

	ID3D11Texture2D* texture2D = 0;
	res = resource->QueryInterface(&texture2D);

	if (SUCCEEDED(res))
	{
		D3D11_TEXTURE2D_DESC desc; 
		texture2D->GetDesc(&desc);
		mWidth = desc.Width;
		mHeight = desc.Height;
	}

	texture2D->Release();
	resource->Release();
	return true;
}

int Texture::GetWidth()
{
	return mWidth;
}

int Texture::GetHeight()
{
	return mHeight;
}

ID3D11ShaderResourceView * Texture::GetTexture()
{
	return mTexture;
}
