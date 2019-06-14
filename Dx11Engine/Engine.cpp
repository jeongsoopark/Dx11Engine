#include "Engine.h"

Engine* Engine::mInstance = NULL;

Engine::Engine()
{
	mGraphics = nullptr;
	//temp
	vertexBuffer = nullptr;
	textureShader = nullptr;
	texture = nullptr;
	//
}

Engine::~Engine()
{
	if (mGraphics)
	{
		delete mGraphics;
		mGraphics = nullptr;
	}
	//temp
	delete vertexBuffer;
	delete textureShader;
	delete texture;
	//
}

bool Engine::InitGraphics(HWND _hwnd)
{
	mGraphics = new Graphics();
	return mGraphics->InitDX(_hwnd);
}

bool Engine::Init(HINSTANCE _hinstance, HWND _hwnd)
{
	InitGraphics(_hwnd);
	mGraphics->Init();
	//temp
	textureShader = new TextureShader();
	textureShader->Init(mGraphics->GetDevice(), _hwnd, "Shader\\texture", "TextureVertexShader", "TexturePixelShader");

	texture = new Texture();
	texture->Init(mGraphics->GetDevice(), "nvidia.png");

	vertexBuffer = new VertexBuffer();
	vertexBuffer->Init(mGraphics->GetDevice(), textureShader, 256.0, false);
	//
	return true;
}

void Engine::Update()
{
	
}

void Engine::Render()
{
	mGraphics->BeginScene(0.0, 0.0, 0.0, 1.0);

	//temp
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;

	D3DXVECTOR3 position = D3DXVECTOR3(0.0, 0.0, -10.0);
	D3DXVECTOR3 up = D3DXVECTOR3(0.0, 1.0, 0.0);
	D3DXVECTOR3 lookAt = D3DXVECTOR3(0.0, 0.0, 1.0);

	D3DXMatrixLookAtLH(&view, &position, &lookAt, &up);
	D3DXMatrixOrthoLH(&projection, SCREEN_WIDTH, SCREEN_HEIGHT, 0.1f, 1000.0);
	D3DXMatrixIdentity(&world);
	/*
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);
	*/
	textureShader->SetShaderParameters(mGraphics->GetDeviceContext(), texture->GetTexture());
	textureShader->SetShaderParameters(mGraphics->GetDeviceContext(), world, view, projection);
	vertexBuffer->Render(mGraphics->GetDeviceContext());
	//

	mGraphics->EndScene();
}


void Engine::Run()
{
	Update();
	Render();
}

void Engine::Release()
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

Graphics * Engine::GetGraphics()
{
	return mGraphics;
}

Engine * Engine::GetEngine()
{
	if (mInstance == nullptr)
	{
		mInstance = new Engine();
	}
	return mInstance;
}
