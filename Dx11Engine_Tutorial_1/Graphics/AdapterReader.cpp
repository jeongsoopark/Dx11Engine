#include "AdapterReader.h"

//declare static member variable
std::vector<AdapterData> AdapterReader::mAdapters;

AdapterReader::AdapterReader()
{
}


AdapterReader::~AdapterReader()
{
}

std::vector<AdapterData> AdapterReader::GetAdapterData()
{
	//already initizliaed 
	if (mAdapters.size() > 0)
	{
		return mAdapters;
	}

	ComPtr<IDXGIFactory> pFactory;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Failed to create dxgi factory for adapter enumeration\n");
		exit(-1);
	}

	IDXGIAdapter* pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		mAdapters.push_back(AdapterData(pAdapter));
		index++;
	}

	return mAdapters;
}

AdapterData::AdapterData(IDXGIAdapter * pAdapter)
{
	this->mpAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&(this->mDesc));
	if (FAILED(hr))
	{
		ErrLogger::Log(hr, "Fail to get Description of IDXGIAdapter");
	}
}
