#ifndef _DirectX11_H_
#define _DirectX11_H_

#include "Utility.h"
#include "Rect.h"

namespace KeiUI{
	class DirectX9{
	public:
		struct Vertex{
			float x, y, z;
			float normalX, normalY, normalZ;
			float u, v;
			static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

			Vertex(float x, float y, float z, float normalX, float normalY, float normalZ, float u, float v) 
				: x(x), y(y), z(z), normalX(normalX), normalY(normalY), normalZ(normalZ), u(u), v(v){

			}
		};

	protected:
		HWND hWnd;
		IDirect3DDevice9* device; 
		D3DPRESENT_PARAMETERS config;

		ID3DXSprite* sprite;

	public:
		DirectX9();
		~DirectX9();

		bool init(string name, int width, int height);

	protected:
		D3DMATERIAL9 initMaterial(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXCOLOR emissive, float power);
		D3DLIGHT9 initDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
		D3DLIGHT9 initPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
		D3DLIGHT9 initSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);

	};

};

#endif _DirectX11_H_