#pragma once

#include "DxManager.h"
#include "Defines.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool InitDX(HWND hwnd);
	void Init();
	void BeginScene(float _r, float _g, float _b, float _a);
	void EndScene();

	void EnableAlphaBlending(bool _enable);
	void EnableZBuffer(bool _enable);

	DxManager* GetDXManager();
	HWND GetHwnd();
	void SetHwnd(HWND _hwnd);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();


private:
	DxManager* mDxManager;
	HWND mHwnd;

};

