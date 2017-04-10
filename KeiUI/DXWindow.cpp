#include "DXWindow.h"
#include <tchar.h>

DXWindow::DXWindow(string name, HINSTANCE hInstance) : name(name) {

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

DXWindow::~DXWindow(){

}

bool DXWindow::main(int width, int height){
	this->width = width;
	this->height = height;

	// Create window
	HWND hWnd = CreateWindowEx(
		NULL,
		(this->name).c_str(), (this->name).c_str(),
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL, NULL,
		0, this
		);

	// Show window
	if(hWnd){

		this->setWindowCenter();
		MoveWindow(hWnd, this->x, this->y, this->width, this->height, true);

		UpdateWindow(hWnd);
		ShowWindow(hWnd, SW_SHOW);

	}else{
		return false;
	}

	// Initialize DirectX
	if(!init(hWnd, this->name, this->width, this->height)){
		return false;
	}

	// Message loop
	MSG msg = {0};

	while(WM_QUIT != msg.message){

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}else{
			this->render();
		}
	}

	return true;
}

LRESULT DXWindow::events(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
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

LRESULT CALLBACK DXWindow::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	if(message == WM_CREATE){
		LPCREATESTRUCT pData = (LPCREATESTRUCT)lParam;
		DXWindow* pThis = (DXWindow*)pData->lpCreateParams;

		SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);
		return DefWindowProc(hWnd, message, wParam, lParam);

	}else{
		DXWindow* pThis = (DXWindow*)GetWindowLong(hWnd, GWL_USERDATA);
		
		if(pThis){
			return pThis->events(hWnd, message, wParam, lParam);
		}else{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
}

void DXWindow::messageBox(HWND hWnd, string content, string title, UINT uType){
	MessageBoxW(hWnd, content.c_str(), title.c_str(), uType);
}

void DXWindow::setWindowCenter(){
	this->x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (this->width / 2);
	this->y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (this->height / 2);
}