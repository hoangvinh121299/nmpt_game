#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "define.h"
#include "GameObj.h"
#include "Textures.h"

CGame *game;
CGameObj *simon;
CGameObj *ground;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources. In this example, create a brick object and mario object
*/
void LoadResources()
{
	CTextures *textures = CTextures::GetInstance();
	//Simon walking right
	textures->Add(ID_TEX_SIMON_FLIPPED, SIMON_FLIPPED_TEX_PATH, D3DCOLOR_XRGB(255, 0, 255));
	//Simon walking left
	textures->Add(ID_TEX_SIMON, SIMON_TEX_PATH, D3DCOLOR_XRGB(255, 0, 255));
	//add ground 
	textures->Add(ID_TEX_GROUND_INTRO, GROUND_INTRO_TEX_PATH, D3DCOLOR_XRGB(128, 0, 255));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 texSimon_flipped = textures->Get(ID_TEX_SIMON_FLIPPED);
	LPDIRECT3DTEXTURE9 texGround = textures->Get(ID_TEX_GROUND_INTRO);

	//Add simon walking right
	sprites->Add(100, 255, 2, 284, 62, texSimon_flipped);
	sprites->Add(101, 312, 2, 348, 62, texSimon_flipped);
	sprites->Add(102, 373, 2, 406, 62, texSimon_flipped);
	sprites->Add(103, 432, 2, 470, 62, texSimon_flipped);
	//Add simon walking left
	sprites->Add(200, 194, 2, 223, 64, texSimon);
	sprites->Add(201, 132, 2, 169, 64, texSimon);
	sprites->Add(202, 74, 2, 104, 64, texSimon);
	sprites->Add(203, 10, 2, 48, 64, texSimon);
	//Add ground
	sprites->Add(301, 6, 206, 262, 213, texGround);

	LPANIMATION anim;

	anim = new CAnimation(100);
	anim->Add(100);
	anim->Add(101);
	anim->Add(102);
	anim->Add(103);
	animations->Add(ID_ANI_SIMON_WALKING_RIGHT, anim);
	//
	anim = new CAnimation(100);
	anim->Add(200);
	anim->Add(201);
	anim->Add(202);
	anim->Add(203);
	animations->Add(ID_ANI_SIMON_WALKING_LEFT, anim);
	//
	anim = new CAnimation(100);
	anim->Add(301);
	animations->Add(20003, anim);

	simon = new CGameObj();
	simon->AddAnimation(ID_ANI_SIMON_WALKING_RIGHT);
	simon->AddAnimation(ID_ANI_SIMON_WALKING_LEFT);
	simon->SetPosition(10.0f, 200.0f);
	ground = new CGameObj();
	ground->AddAnimation(20003);
	ground->SetPosition(0.0f, 260.0f);
	
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	simon->Update(dt);
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		simon->Render();
		ground->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();
	Run();

	return 0;
}