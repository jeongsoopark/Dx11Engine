#pragma once
#include "../ErrLogger.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DXGI.lib")
#include <vector>
#include <wrl/client.h>
using namespace Microsoft::WRL;

class AdapterData
{
public:
	AdapterData(IDXGIAdapter* pAdapter);
	IDXGIAdapter* mpAdapter = nullptr;
	DXGI_ADAPTER_DESC mDesc;
};



class AdapterReader
{
public:
	AdapterReader();
	~AdapterReader();
	static std::vector<AdapterData> GetAdapterData();

private:
	//static so that another window would shares the Adapter list.
	static std::vector<AdapterData> mAdapters;
};

