#include "App.h"

App::App(string name, HINSTANCE hInstance) : Windows(name, hInstance){
	this->buffer = nullptr;
	this->texture = nullptr;

}

bool App::load(){

	// vertex buffer
	this->device->CreateVertexBuffer(
		6 * sizeof(DirectX9::Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&(this->buffer),
		0
	);

	Vertex* vertex;
	this->buffer->Lock(0, 0, (void**)&vertex, 0);
	
	vertex[0] = DirectX9::Vertex(-1.0f, -1.0f, 3.0f, 0.0f, 0.0f, -1.0f, 0.0f, 3.0f);
	vertex[1] = DirectX9::Vertex(-1.0f, 1.0f, 3.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertex[2] = DirectX9::Vertex(1.0f, 1.0f, 3.0f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f);

	vertex[3] = DirectX9::Vertex(-1.0f, -1.0f, 3.0f, 0.0f, 0.0f, -1.0f, 0.0f, 3.0f);
	vertex[4] = DirectX9::Vertex(1.0f, 1.0f, 3.0f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f);
	vertex[5] = DirectX9::Vertex(1.0f, -1.0f, 3.0f, 0.0f, 0.0f, -1.0f, 3.0f, 3.0f);

	this->buffer->Unlock();

	// texture
	D3DXCreateTextureFromFile(this->device, L"Resource/1.png", &(this->texture));
	this->device->SetTexture(0, this->texture);

	this->device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	this->device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	this->device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// light
	this->device->SetRenderState(D3DRS_LIGHTING, false);
	
	
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
	if(GetAsyncKeyState('W') & 0x8000f){
		this->device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		this->device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	}

	if(GetAsyncKeyState('B') & 0x8000f){
		this->device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
		this->device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
		this->device->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0x000000ff);
	}

	if(GetAsyncKeyState('C') & 0x8000f){
		this->device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		this->device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	}

	if(GetAsyncKeyState('M') & 0x8000f){
		this->device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		this->device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	}
}

void App::render(){
	this->device->SetStreamSource(0, this->buffer, 0, sizeof(DirectX9::Vertex));
	this->device->SetFVF(DirectX9::Vertex::FVF);
	this->device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

}

void App::draw(){
	this->drawRect(100, 100, 100, 100);
}

void App::recover(){
	Utility::Release<IDirect3DTexture9*>(this->texture);
	Utility::Release<IDirect3DVertexBuffer9*>(this->buffer);
}