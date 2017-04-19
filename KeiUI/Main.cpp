#include <Windows.h>
#include "App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	KeiUI::App app(L"²âÊÔ´°¿Ú", hInstance);
	app.main(960, 540);

	return 0;
}