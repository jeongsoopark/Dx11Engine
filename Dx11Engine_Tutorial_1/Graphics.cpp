#include "Graphics.h"



Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	if (!IntializeDirectX(hwnd, width, height))
	{
		return false;
	}
	return false;
}

bool Graphics::IntializeDirectX(HWND hwnd, int width, int height)
{
	std::vector<AdapterData> adapters = AdapterReader::GetAdapterData();
	return true;
}
