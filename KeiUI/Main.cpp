#include <Windows.h>
#include "App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	App app(L"���Դ���", hInstance);
	app.main(800, 600);

	return 0;
}