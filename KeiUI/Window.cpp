#include "Window.h"
#include "Canvas.h"

namespace KeiUI{
	float Window::resolution = 1.0f;

	float Window::refreshLast = 0.0f;
	float Window::refreshTime = 0.0f;

	Window::Window(string name, HINSTANCE hInstance) : name(name){

		// Register window
		WNDCLASSEX wndClass = {0};
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
		wndClass.lpfnWndProc = windowProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = hInstance;
		wndClass.hIcon = NULL;
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = name.c_str();

		RegisterClassEx(&wndClass);
	}

	Window::~Window(){

	}

	bool Window::main(int width, int height){
		this->width = width;
		this->height = height;

		// Create window
		this->hWnd = CreateWindowEx(
			NULL,
			(this->name).c_str(), (this->name).c_str(),
			WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT,
			width, height,
			NULL, NULL,
			0, this
			);

		// Show window
		if(this->hWnd){

			this->setWindowCenter();
			MoveWindow(this->hWnd, this->x, this->y, this->width, this->height, true);

			UpdateWindow(this->hWnd);
			ShowWindow(this->hWnd, SW_SHOW);

		}else{
			return false;
		}

		// Initialize graphic
		if(!this->init(this->name, this->width, this->height)){
			return false;
		}



		if(!this->load()){
			Window::messageBox(this->hWnd, L"载入资源失败！", name, MB_ICONSTOP);
			return false;
		}

		// Initialize canvas
		this->changeResolution(Resolution::ExtremelyLow);	// Default is ExtremelyLow
		Canvas canvas(this->device, this->sprite);

		// Message loop
		MSG msg = {0};

		while(WM_QUIT != msg.message){

			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}else{
				float refreshNow = (float)timeGetTime();
				Window::refreshTime = refreshNow - Window::refreshLast;

				if(this->device){
					// action
					this->update();

					// render
					this->device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(169, 169, 169), 1.0f, 0);
					this->device->BeginScene();

					// 3D
					this->render();

					// 2D
					this->sprite->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
					this->draw(&canvas);
					this->sprite->End();

					this->device->EndScene();
					this->device->Present(0, 0, 0, 0);

				}else{
					Window::messageBox(this->hWnd, L"图形驱动发生错误！", name, MB_ICONSTOP);
					PostQuitMessage(0);
				}

				Window::refreshLast = refreshNow;
			}
		}

		this->recover();
		return true;
	}

	LRESULT Window::events(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
		switch(message){
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}

	LRESULT CALLBACK Window::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
		if(message == WM_CREATE){
			LPCREATESTRUCT pData = (LPCREATESTRUCT)lParam;
			Window* pThis = (Window*)pData->lpCreateParams;

			SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);
			return DefWindowProc(hWnd, message, wParam, lParam);

		}else{
			Window* pThis = (Window*)GetWindowLong(hWnd, GWL_USERDATA);

			if(pThis){
				return pThis->events(hWnd, message, wParam, lParam);
			}else{
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
	}

	void Window::messageBox(HWND hWnd, string content, string title, UINT uType){
		MessageBoxW(hWnd, content.c_str(), title.c_str(), uType);
	}

	void Window::changeResolution(Resolution resolution){
		Window::resolution = (1.0f + resolution * 0.25f);

		// 计算窗口大小
		this->width = (int)(this->width * Window::resolution);
		this->height = (int)(this->height * Window::resolution);

		// 修改接口配置
		this->config.BackBufferWidth = this->width;
		this->config.BackBufferHeight = this->height;

		this->sprite->OnLostDevice();
		this->device->Reset(&(this->config));
		this->sprite->OnResetDevice();

		// 更改窗口大小
		this->setWindowCenter();
		SetWindowPos(
			this->hWnd, nullptr, this->x, this->y,
			this->width, this->height, SWP_NOZORDER | SWP_SHOWWINDOW
		);
	}

	void Window::setWindowCenter(){
		this->x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (this->width / 2);
		this->y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (this->height / 2);
	}

};