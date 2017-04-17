#include "DirectX11.h"
#include "Window.h"

namespace KeiUI{

	DirectX11::DirectX11()
		: device(nullptr), context(nullptr), swapChain(nullptr), backBufferTarget(nullptr), depthBufferTarget(nullptr)
	{

	}

	DirectX11::~DirectX11(){
		Utility::Release(this->depthBufferTarget);
		Utility::Release(this->backBufferTarget);
		Utility::Release(this->swapChain);
		Utility::Release(this->context);
		Utility::Release(this->device);
	}

	bool DirectX11::init(string name, int width, int height){

		// 1.�����豸�������ģ�Ӳ������֧��d3d11��ȫ������
		D3D_FEATURE_LEVEL features[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3
		};

		D3D_FEATURE_LEVEL featureLevel;
		HRESULT hr = D3D11CreateDevice(
			NULL, D3D_DRIVER_TYPE_HARDWARE,
			0, 0, features, 3, D3D11_SDK_VERSION,
			&(this->device), &featureLevel, &(this->context)
		);

		if(FAILED(hr)){
			Window::messageBox(this->hWnd, L"ͼ�νӿڳ�ʼ��ʧ�ܣ�", name, MB_ICONSTOP);
			return false;
		}

		// ���4x�����ȼ���֧��d3d11��Ӳ��ȫ��֧��4�ز���
		UINT msaa4xQuality(0);
		this->device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaa4xQuality);

		// 2.������������������������
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {0};
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;	// ˢ��Ƶ��
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferCount = 1;	// �󻺳�������
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.Flags = 0;	
		swapChainDesc.OutputWindow = this->hWnd;
		swapChainDesc.SampleDesc.Count = 4;	// ���ز���
		swapChainDesc.SampleDesc.Quality = (msaa4xQuality - 1);
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Windowed = true;

		// ��ȡIDXGIFactory�Դ���������
		IDXGIDevice *dxgiDevice(nullptr);
		this->device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));

		IDXGIAdapter *dxgiAdapter(nullptr);
		dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter));

		IDXGIFactory *dxgiFactory(nullptr);
		dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory));

		hr = dxgiFactory->CreateSwapChain(this->device, &swapChainDesc, &(this->swapChain));
		if(FAILED(hr)){
			Window::messageBox(this->hWnd, L"ͼ�ν���������ʧ�ܣ�", name, MB_ICONSTOP);
			return false;
		}

		dxgiFactory->Release();
		dxgiAdapter->Release();
		dxgiDevice->Release();

		// 3.������ͼ
		ID3D11Texture2D *backBuffer(NULL);
		this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));

		hr = this->device->CreateRenderTargetView(backBuffer, nullptr, &(this->backBufferTarget));
		if(FAILED(hr)){
			Window::messageBox(this->hWnd, L"������ȾĿ��ʧ�ܣ�", name, MB_ICONSTOP);
			return false;
		}

		backBuffer->Release();

		// 4.������Ȼ�������ͼ��Ҫ�ȴ�����Ӧ������
		D3D11_TEXTURE2D_DESC desc = {0};
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;	// ����Ҫ����ӳ��
		desc.ArraySize = 1;	// û����������
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.MiscFlags = 0;
		desc.SampleDesc.Count = 4;
		desc.SampleDesc.Quality = (msaa4xQuality - 1);	// ��Ҫ��֮ǰ������ͬ
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;

		ID3D11Texture2D *depthStencilBuffer(nullptr);

		hr = this->device->CreateTexture2D(&desc, nullptr, &depthStencilBuffer);
		if(FAILED(hr)){
			Window::messageBox(this->hWnd, L"������Ȼ�����ʧ�ܣ�", name, MB_ICONSTOP);
			return false;
		}

		hr = this->device->CreateDepthStencilView(depthStencilBuffer, nullptr, &(this->depthBufferTarget));
		if(FAILED(hr)){
			Window::messageBox(this->hWnd, L"�������ģ��ʧ�ܣ�", name, MB_ICONSTOP);
			return false;
		}

		// ����ͼ��������Ӧ�׶�
		this->context->OMSetRenderTargets(1,&(this->backBufferTarget), this->depthBufferTarget);
		depthStencilBuffer->Release();

		// 5.�ӿڴ���������
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