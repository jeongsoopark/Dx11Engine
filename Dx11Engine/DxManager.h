#pragma once
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>


class DxManager
{
public:
    DxManager();
    ~DxManager();

    bool Init(int width, int height, bool vsync, HWND hwnd, bool fullscreen);
    void BeginScene(float r, float g, float b, float a);
    void EndScene();

    void EnableAlphaBlending(bool en);
    void EnableZBuffer(bool en);

    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetDeviceContext();

private:
    bool initSwapChain(HWND hwnd, bool fullscreen, int width, int height, UINT numerator, UINT denominator);
    bool initDepthBuffer(int width, int height);
	bool initZbuffer();
    bool initDepthStencilBuffer();
    bool initStencilView();
    bool initRasterizerState();
    void initViewport(int width, int height);
    bool initAlphaBlending();

    IDXGISwapChain* mSwapChain;
    ID3D11Device* mDevice;
    ID3D11DeviceContext* mDeviceContext;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11DepthStencilView* mDepthStencilView;
	ID3D11RasterizerState* mRasterizerState;

	ID3D11BlendState* mAlphaBlendStateEnabled;
	ID3D11BlendState* mAlphaBlendStateDisabled;

	ID3D11DepthStencilState* mDepthStencilStateEnabled;
	ID3D11DepthStencilState* mDepthStencilStateDisabled;

    bool mVsync;
    int mGPUMemory;
    char mGPUDescription[256];
};

