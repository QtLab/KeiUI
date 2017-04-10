#include <Windows.h>
#include "Sample.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	Sample sample(L"²âÊÔ´°¿Ú", hInstance);
	sample.main(800, 600);

	return 0;
}