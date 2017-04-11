#include "Windows.h"

float Windows::refreshLast = 0;
float Windows::refreshTime = 0;

Windows::Windows(string name, HINSTANCE hInstance) : DirectX9(0), name(name) {

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

Windows::~Windows(){

}

bool Windows::main(int width, int height){
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

	// Initialize Graphic
	if(!this->init(this->name, this->width, this->height)){
		return false;
	}

	if(!this->load()){
		Windows::messageBox(this->hWnd, L"载入资源失败！", name, MB_ICONSTOP);
		return false;
	}

	// Message loop
	MSG msg = {0};

	while(WM_QUIT != msg.message){

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}else{
			float refreshNow = (float)timeGetTime();
			Windows::refreshTime = refreshNow - Windows::refreshLast;

			if(this->device){
				// action
				this->update();

				// draw
				this->device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
				this->device->BeginScene();

				this->render();

				this->device->EndScene();
				this->device->Present(0, 0, 0, 0);
			}else{
				Windows::messageBox(this->hWnd, L"图形驱动发生错误！", name, MB_ICONSTOP);
				PostQuitMessage(0);
			}

			Windows::refreshLast = refreshNow;
		}
	}

	this->recover();
	return true;
}

LRESULT Windows::events(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
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

LRESULT CALLBACK Windows::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	if(message == WM_CREATE){
		LPCREATESTRUCT pData = (LPCREATESTRUCT)lParam;
		Windows* pThis = (Windows*)pData->lpCreateParams;

		SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);
		return DefWindowProc(hWnd, message, wParam, lParam);

	}else{
		Windows* pThis = (Windows*)GetWindowLong(hWnd, GWL_USERDATA);
		
		if(pThis){
			return pThis->events(hWnd, message, wParam, lParam);
		}else{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
}

void Windows::messageBox(HWND hWnd, string content, string title, UINT uType){
	MessageBoxW(hWnd, content.c_str(), title.c_str(), uType);
}

void Windows::setWindowCenter(){
	this->x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (this->width / 2);
	this->y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (this->height / 2);
}