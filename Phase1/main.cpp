#pragma once
#include <d3d9.h>
#include <Windows.h>

#define WIDTH 320
#define HEIGHT 640
#define TITLE "GAME"

class Game
{
private:
	//Các thuộc tính quy định chiều dài và rộng của cửa sổ Game
	int m_Width;
	int m_Height;
	//Quy định cửa sổ sẽ hiển thị window hoặc full màn hình.
	bool m_Iswindow;

	//HINSTANCE là 1 biến để đại diện cho game của chúng ta khi được hệ điều hành chạy.
	HINSTANCE m_HandleInstance;
	//Mỗi game sẽ có thể chứa nhiều cửa sổ, mỗi cửa sổ cần có 1 định danh riêng. Định danh đó chính là HWND.
	HWND m_HandleWindow;
	//LPDIRECT3D9 là một Direct3D Object. Biến này cần thiết cho việc khởi tạo Device để thao tác vẽ trong Game.
	LPDIRECT3D9 m_lpDirect3D;
	// LPDIRECT3DDEVICE9 dùng để lưu thông tin của Device sử dụng thao tác vẽ trong chương trình.
	LPDIRECT3DDEVICE9 m_lpDirect3DDevice;

	//Đây là hàm callback dùng để lắng nghe các sự kiện của cửa sổ Game khi người dùng tương tác.
	static LRESULT CALLBACK WndProcedure(HWND hWnd,
		UINT message, WPARAM wParam, LPARAM lParam);
public:
	// Hàm tạo của GameObject.
	Game(int scr_Widht, int scr_Height, bool isWindow);

	//Khởi tạo các thuộc tính cần thiết cho cửa sổ.
	bool initHandleWindow();
	//Khởi tạo môi trường DirectX
	bool initDirectX3DEnvironment();
	//Khởi tạo Direct Device
	bool initDirectX3DDevice();

	//Nơi để đặt tất cả các hàm khởi tạo cần thiết trước lúc chương trình chạy.
	void GameInit();
	//Cập nhật game
	void GameRun();
	//Giải phóng các tài nguyên khi thoát chương trình
	void GameExit();
};
//Ta khởi tạo các giá trị ban đầu cho ứng dụng.
Game::Game(int scr_Widht, int scr_Height, bool isWindow)
{
	this->m_Width = scr_Widht;
	this->m_Height = scr_Height;
	this->m_Iswindow = isWindow;
	this->m_HandleInstance = 0;
	this->m_HandleWindow = 0;
	this->m_lpDirect3D = 0;
	this->m_lpDirect3DDevice = 0;

}

//Ở class này sẽ khởi tạo các thuộc tính cần thiết cho cửa sổ. Giúp cửa sổ hiển thị và đăng ký các sự kiện khi người dùng thao tác với cửa sổ.
bool Game::initHandleWindow()
{
	WNDCLASSEX WndcEx;
	ZeroMemory(&WndcEx, sizeof(WndcEx));
	WndcEx.cbSize = sizeof(WNDCLASSEX);
	WndcEx.hInstance = this->m_HandleInstance;
	WndcEx.lpfnWndProc = (WNDPROC)WndProcedure;
	WndcEx.lpszClassName = "Game";
	if (!RegisterClassEx(&WndcEx))
	{
		return false;
	}
	this->m_HandleWindow = CreateWindow(
		"Game", // đặt trung với WndcEx.lpszClassName
		TITLE, // TITLE của cửa sổ 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // style của cửa sổ
		100, // tọa độ x khi cửa sổ xuất hiện
		100, // tọa độ y khi cửa sổ xuất hiện
		this->m_Width, // chiều dài cửa sổ
		this->m_Height, // chiều cao cửa sổ
		0, // handle window parent của của sổ hiện tại. Để là 0
		0, // handle đến Menu. Để là 0
		this->m_HandleInstance, // Handle Instance của ứng dụng
		0); // giữ nguyên theo default là 0
	if (!this->m_HandleWindow) // Kiểm tra tạo thành công.
	{
		return false;
	}
	ShowWindow(m_HandleWindow, SW_SHOW); // show cửa sổ lên màn hình
	UpdateWindow(m_HandleWindow); // Update cửa sổ theo thời gian
	return true;
}

//Hàm này tác dụng khởi tạo đối tượng Direct3D. Ta sẽ cần đối tượng này để làm việc với DirectX ở các bài viết sau.
bool Game::initDirectX3DEnvironment()
{
	this->m_lpDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_lpDirect3D) {
		return true;
	}
	return false;
}


//Ở hàm này chúng ta cần dùng D3DPRESENT_PARAMETERS để thao tác tạo Direct3D Device. Direct3D Device này sẽ dùng cho việc vẽ các Object Game lên màn hình sau này.
bool Game::initDirectX3DDevice()
{
	D3DPRESENT_PARAMETERS d3dpp; // khai báo biến
	ZeroMemory(&d3dpp, sizeof(d3dpp)); // Khởi tạo vùng nhớ
	d3dpp.BackBufferCount = 1; // Số lượng Back buffer
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Chọn UNKNOW, DirectX sẽ tự chọn 1 định dạng phù hợp cho Device
	d3dpp.BackBufferHeight = HEIGHT; // chiều cao cảu BackBuffer
	d3dpp.BackBufferWidth = WIDTH; // Chiều dài của BackBuffer
	d3dpp.Windowed = true; // Window ở dạng cửa sổ, không phải full màn hình
	d3dpp.hDeviceWindow = this->m_HandleWindow; // Gán HandleWindow cho Device
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Phương thức swap của Buffer
	m_lpDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT, // Chọn DEFAULT ADAPTER
		D3DDEVTYPE_HAL, // 
		m_HandleWindow, // Handle Window của của sổ
		D3DCREATE_HARDWARE_VERTEXPROCESSING, // Hard ware vertex processing
		&d3dpp,
		&m_lpDirect3DDevice); // Hàm tạo Device
	if (FAILED(m_lpDirect3DDevice))
	{
		return false;
	}
	return true;
}

//Hàm này sẽ gọi các hàm khởi tạo ở trên
void Game::GameInit()
{
	initHandleWindow();
	initDirectX3DEnvironment();
	initDirectX3DDevice();
}


//Ở hàm này chúng ta sẽ thực hiện toàn bộ Update của Game. Sẽ sử dụng dòng while để duy trì cửa sổ luôn hoạt động trong quá trình chạy Game.
void Game::GameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Tạo một Mesage để lắng nghe các sự kiện của cửa sổ
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) // Lấy message và truyền vào biến msg đã khai báo
		{
			if (msg.message == WM_QUIT) // Kiểm tra nếu msg yêu cầu QUIT ứng dụng thì ứng dụng sẽ thoát
				break;
			TranslateMessage(&msg); // xử lý input và chuyển vào msg
			DispatchMessage(&msg); // gửi message đến hàm WndProceduce để xử lý
		}
		else
		{
			// Begin Draw something in Game
			m_lpDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0); // Clear cửa sổ 1 lần trước khi vẽ lên
			if (m_lpDirect3DDevice->BeginScene())
			{

				// Game Render Here
				m_lpDirect3DDevice->EndScene();
			}
			m_lpDirect3DDevice->Present(0, 0, 0, 0); // Thể hiện tất cả những gì đã vẽ lên màn hình
		}
	}
}

//Giải phóng vùng nhớ khi thoát game
void Game::GameExit()
{
	if (this->m_lpDirect3D) {
		this->m_lpDirect3D->Release();
		this->m_lpDirect3D = NULL;
	}
	if (this->m_lpDirect3DDevice) {
		this->m_lpDirect3DDevice->Release();
		this->m_lpDirect3DDevice = NULL;
	}
}

//Hàm nhận các sự kiện của cửa sổ và xử lý ở đây. Ví dụ khi nhận sự kiện WM_DESTROY thì cửa sổ sẽ đóng xuống.

LRESULT CALLBACK Game::WndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstace,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	Game mygame(WIDTH, HEIGHT, false);
	mygame.GameInit();
	mygame.GameRun();
	mygame.GameExit();
	return 0;
}