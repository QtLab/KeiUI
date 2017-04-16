#include "DirectX11.h"
#include "Window.h"

namespace KeiUI{

	DirectX11::DirectX11() : device(nullptr), context(nullptr), swapChain(nullptr), backBufferTarget(nullptr){

	}

	DirectX11::~DirectX11(){
		Utility::Release(this->backBufferTarget);
		Utility::Release(this->swapChain);
		Utility::Release(this->context);
		Utility::Release(this->device);
	}

	bool DirectX11::init(string name){

		// 计算窗口大小
		RECT rect;
		GetClientRect(this->hWnd, &rect);

		unsigned int width = rect.right - rect.left;
		unsigned int height = rect.bottom - rect.top;

		// 列举的驱动类型和特征级别
		D3D_DRIVER_TYPE driverTypes[] = {
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
			D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};
		unsigned int totalFeatureLevels = ARRAYSIZE(featureLevels);

		// 创建设备和交换链
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = this->hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		unsigned int creationFlags = 0;

		HRESULT result;
		for(unsigned int driver = 0; driver < totalDriverTypes; driver++){
			result = D3D11CreateDeviceAndSwapChain(
				0, driverTypes[driver], 0, creationFlags,
				featureLevels, totalFeatureLevels,
				D3D11_SDK_VERSION, &swapChainDesc, &(this->swapChain),
				&(this->device), &(this->featureLevel), &(this->context)
				);

			if(SUCCEEDED(result)){
				this->driverType = driverTypes[driver];
				break;
			}
		}

		if(FAILED(result)){
			Window::messageBox(this->hWnd, L"图形设备初始化失败！", name, MB_ICONSTOP);
			return false;
		}

		ID3D11Texture2D* backBufferTexture;
		result = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);

		if(FAILED(result)){
			Window::messageBox(this->hWnd, L"获取后台交换链失败！", name, MB_ICONSTOP);
			return false;
		}

		// 创建渲染目标视图
		result = this->device->CreateRenderTargetView(backBufferTexture, 0, &(this->backBufferTarget));
		if(backBufferTexture){
			backBufferTexture->Release();
		}

		if(FAILED(result)){
			Window::messageBox(this->hWnd, L"创建渲染目标视图失败！", name, MB_ICONSTOP);
			return false;
		}

		this->context->OMSetRenderTargets(1, &(this->backBufferTarget), 0);

		// 视口创建和设置
		D3D11_VIEWPORT viewport;
		viewport.Width = static_cast<float>(width);
		viewport.Height = static_cast<float>(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		this->context->RSSetViewports(1, &viewport);
	}

};