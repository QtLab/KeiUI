#ifndef _DirectX9_H_
#define _DirectX9_H_

#include <Windows.h>
#include <d3dx9.h>
#include "Utility.h"

class DirectX9{
public:
	struct ColorVertex{
		float x, y, z;
		float normalX, normalY, normalZ;
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL;

		ColorVertex(float x, float y, float z, float normalX, float normalY, float normalZ) 
			: x(x), y(y), z(z), normalX(normalX), normalY(normalY), normalZ(normalZ){

		}
	};

protected:
	HWND hWnd;
	IDirect3DDevice9* device; 
	D3DPRESENT_PARAMETERS config;

public:
	DirectX9(HWND hWnd);
	~DirectX9();

	bool init(string name, int width, int height);

protected:
	D3DMATERIAL9 initMaterial(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXCOLOR emissive, float power);
	D3DLIGHT9 initDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 initPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	D3DLIGHT9 initSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);

};

#endif