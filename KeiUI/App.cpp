#include "App.h"

App::App(string name, HINSTANCE hInstance) : Windows(name, hInstance){
	for(int i = 0; i < 4; i++){
		this->object[i] = 0;
	}

}

bool App::load(){

	// create object
	D3DXCreateTeapot(this->device, &(this->object[0]), 0);
	D3DXCreateSphere(this->device, 1.0f, 20, 20, &(this->object[1]), 0);
	D3DXCreateTorus(this->device, 0.5f, 1.0f, 20, 20, &(this->object[2]), 0);
	D3DXCreateCylinder(this->device, 0.5f, 0.5f, 2.0f, 20, 20, &(this->object[3]), 0);

	// set matrix
	D3DXMatrixTranslation(&(this->worldMatrix[0]), 0.0f, 2.0f, 0.0f);
	D3DXMatrixTranslation(&(this->worldMatrix[1]), 0.0f, -2.0f, 0.0f);
	D3DXMatrixTranslation(&(this->worldMatrix[2]), -3.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&(this->worldMatrix[3]), 3.0f, 0.0f, 0.0f);

	D3DXMATRIX x;
	D3DXMatrixRotationX(&x, D3DX_PI * 0.5f);
	(this->worldMatrix)[3] *= x;

	// matreial
	this->matreial[0] = this->initMaterial(
		D3DCOLOR_XRGB(255, 0, 0),
		D3DCOLOR_XRGB(255, 0, 0),
		D3DCOLOR_XRGB(255, 0, 0),
		D3DCOLOR_XRGB(0, 0, 0),
		20.0f
	);

	this->matreial[1] = this->initMaterial(
		D3DCOLOR_XRGB(0, 0, 255),
		D3DCOLOR_XRGB(0, 0, 255),
		D3DCOLOR_XRGB(0, 0, 255),
		D3DCOLOR_XRGB(0, 0, 0),
		20.0f
	);

	this->matreial[2] = this->initMaterial(
		D3DCOLOR_XRGB(0, 255, 0),
		D3DCOLOR_XRGB(0, 255, 0),
		D3DCOLOR_XRGB(0, 255, 0),
		D3DCOLOR_XRGB(0, 0, 0),
		20.0f
	);

	this->matreial[3] = this->initMaterial(
		D3DCOLOR_XRGB(255, 255, 0),
		D3DCOLOR_XRGB(255, 255, 0),
		D3DCOLOR_XRGB(255, 255, 0),
		D3DCOLOR_XRGB(0, 0, 0),
		20.0f
	);

	// light
	D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255);

	this->spotLight = this->initSpotLight(
		&(D3DXVECTOR3(0.0f, 0.0f, -5.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 1.0f)),
		&color
	);

	this->device->SetLight(0, &(this->spotLight));
	this->device->LightEnable(0, true);

	this->device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	this->device->SetRenderState(D3DRS_SPECULARENABLE, true);

	// camera
	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);
	this->device->SetTransform(D3DTS_VIEW, &viewMatrix);

	// projection matrix
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DX_PI * 0.5f,
		(float)(this->width) / (float)(this->height),
		1.0f,
		1000.0f
	);
	this->device->SetTransform(D3DTS_PROJECTION, &projection);

	return true;
}

void App::update(){

	if(GetAsyncKeyState(VK_LEFT) & 0x8000f){
		this->spotLight.Direction.x -= 0.01f;
	}

	if(GetAsyncKeyState(VK_RIGHT) & 0x8000f){
		this->spotLight.Direction.x += 0.01f;
	}

	if(GetAsyncKeyState(VK_DOWN) & 0x8000f){
		this->spotLight.Direction.y -= 0.01f;
	}

	if(GetAsyncKeyState(VK_UP) & 0x8000f){
		this->spotLight.Direction.y += 0.01f;
	}

	this->device->SetLight(0, &(this->spotLight));
	this->device->LightEnable(0, true);

}

void App::render(){
	for(int i = 0; i < 4; i++){
		this->device->SetMaterial(&(this->matreial[i]));
		this->device->SetTransform(D3DTS_WORLD, &(this->worldMatrix[i]));
		this->object[i]->DrawSubset(0);
	}
}

void App::recover(){
	for(int i = 0; i < 4; i++){
		Utility::Release<ID3DXMesh*>(this->object[i]);
	}

}