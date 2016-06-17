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
    void EnableZTest(bool en);

    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetDeviceContext();

private:
    bool initSwapChain(HWND hwnd, bool fullscreen, int width, int height, UINT numerator, UINT denominator);
    bool initDepthBuffer(int width, int height);
    bool initDepthStencilBuffer();
    bool initStencilView();
    bool initRasterizerState();
    bool initViewport(int width, int height);
    bool initAlphaBlending();

    bool mVsync;
    int mGPUMemory;
    char* mGPUDescription[256];
    IDXGISwapChain* mSwapChain;
    ID3D11Device* mDevice;
    ID3D11DeviceContext* mDeviceContext;
    :wa

};

