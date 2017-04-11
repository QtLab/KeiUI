#include "DirectX9.h"
#include <d3dx9.h>
#include "Windows.h"

DirectX9::DirectX9(HWND hWnd) : hWnd(hWnd), device(0) {

}

DirectX9::~DirectX9(){
	this->device->Release();
}

bool DirectX9::init(string name, int width, int height){

	// 1.��ʼ���ӿ�
	IDirect3D9* tmp = nullptr;

	tmp = Direct3DCreate9(D3D_SDK_VERSION);
	
	if(!tmp)
	{
		Windows::messageBox(this->hWnd, L"ͼ�νӿڳ�ʼ��ʧ�ܣ�", name, MB_ICONSTOP);
		return false;
	}

	// 2.ѡ���豸
	D3DCAPS9 caps;
	if(FAILED(tmp->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps))){
		Windows::messageBox(this->hWnd, L"��ȡ��Ⱦ�豸ʧ�ܣ�", name, MB_ICONSTOP);
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
		Windows::messageBox(this->hWnd, L"ͼ���豸��ʼ��ʧ�ܣ�", name, MB_ICONSTOP);
		return false;
	}

	//�ͷ�����ָ��
	tmp->Release();

	return true;
}

D3DMATERIAL9 DirectX9::initMaterial(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXCOLOR emissive, float power){
	D3DMATERIAL9 material;
	material.Ambient = ambient;
	material.Diffuse = diffuse;
	material.Specular = specular;
	material.Emissive = emissive;
	material.Power = power;

	return material;
}

D3DLIGHT9 DirectX9::initDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color){
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
	light.Ambient = (*color) * 0.6f;
	light.Diffuse = (*color);
	light.Specular = (*color) * 0.6f;
	light.Direction = (*direction);

	return light;
}

D3DLIGHT9 DirectX9::initPointLight(D3DXVECTOR3* position, D3DXCOLOR* color){
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHTTYPE::D3DLIGHT_POINT;
	light.Ambient = (*color) * 0.6f;
	light.Diffuse = (*color);
	light.Specular = (*color) * 0.6f;
	light.Position = (*position);
	light.Range = 1000.0f;
	light.Falloff = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

D3DLIGHT9 DirectX9::initSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color){
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHTTYPE::D3DLIGHT_SPOT;
	light.Ambient = (*color) * 0.0f;
	light.Diffuse = (*color);
	light.Specular = (*color) * 0.6f;
	light.Position = (*position);
	light.Direction = (*direction);
	light.Range = 1000.0f;
	light.Falloff = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta = 0.4f;
	light.Phi = 0.9f;

	return light;
}
