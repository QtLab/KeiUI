#ifndef _DirectX11_H_
#define _DirectX11_H_

#include "Utility.h"

#include<d3d11.h>
#include <d3dx11.h>

namespace KeiUI{
	class DirectX11{
	protected:
		HWND hWnd;

		D3D_DRIVER_TYPE driverType;
		D3D_FEATURE_LEVEL featureLevel;

		ID3D11Device* device;
		ID3D11DeviceContext* context;
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* backBufferTarget;
		ID3D11DepthStencilView* depthBufferTarget;

	public:
		DirectX11();
		~DirectX11();

		bool init(string name, int width, int height);

	protected:
	
	};

};

#endif