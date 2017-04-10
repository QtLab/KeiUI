#ifndef _DXContext_H_
#define _DXContext_H_

#include <Windows.h>
#include <d3dx9.h>
#include "Utility.h"

class DXContext{
protected:
	HWND hWnd;
	IDirect3DDevice9* device; 
	D3DPRESENT_PARAMETERS config;

public:
	DXContext();
	~DXContext();

	bool init(HWND hWnd, string name, int width, int height);

};

#endif