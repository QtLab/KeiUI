#include "DXContext.h"
#include <d3dx9.h>
#include "DXWindow.h"

DXContext::DXContext() : hWnd(0), device(0) {

}

DXContext::~DXContext(){

}

bool DXContext::init(HWND hWnd, string name, int width, int height){
	this->hWnd = hWnd;

	// 1.��ʼ���ӿ�
	IDirect3D9* tmp = nullptr;

	tmp = Direct3DCreate9(D3D_SDK_VERSION);
	
	if(!tmp)
	{
		DXWindow::messageBox(this->hWnd, L"ͼ�νӿڳ�ʼ��ʧ�ܣ�", name, MB_ICONSTOP);
		return false;
	}

	// 2.ѡ���豸
	D3DCAPS9 caps;
	if(FAILED(tmp->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps))){
		DXWindow::messageBox(this->hWnd, L"��ȡ��Ⱦ�豸ʧ�ܣ�", name, MB_ICONSTOP);
		return false;
	}

	int vp = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT){
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;	// ʹ��Ӳ��
	}else{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	// ʹ�����
	}

	// 3.���ýӿ�
	this->config.BackBufferWidth            = width;
	this->config.BackBufferHeight           = height;
	this->config.BackBufferFormat           = D3DFMT_A8R8G8B8;
	this->config.BackBufferCount            = 1;
	this->config.MultiSampleType            = D3DMULTISAMPLE_8_SAMPLES;	// �����
	this->config.MultiSampleQuality         = 0;
	this->config.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	this->config.hDeviceWindow              = this->hWnd;
	this->config.Windowed                   = true;
	this->config.EnableAutoDepthStencil     = true; 
	this->config.AutoDepthStencilFormat     = D3DFMT_D24S8;
	this->config.Flags                      = 0;
	this->config.FullScreen_RefreshRateInHz = 0;
	this->config.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// D3DPRESENT_INTERVAL_DEFAULT

	// 4.�����ӿ�
	if(FAILED(tmp->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->hWnd, vp, &(this->config), &(this->device)))){
		DXWindow::messageBox(this->hWnd, L"ͼ���豸��ʼ��ʧ�ܣ�", name, MB_ICONSTOP);
		return false;
	}

	//�ͷ�����ָ��
	tmp->Release();

	return true;
}