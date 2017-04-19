#include "Canvas.h"

namespace KeiUI{
	Canvas::Canvas(IDirect3DDevice9* device, ID3DXSprite* sprite)
		: device(device), sprite(sprite), tmpTexture(nullptr) 
	{

	}

	Canvas::~Canvas(){
		Utility::Release(this->tmpTexture);
	}

	void Canvas::drawRect(Rect rect, float depth, IDirect3DTexture9* texture, D3DCOLOR color, float scale, float rotation){
		D3DXMATRIX positionMatrix, scaleMatrix, rotateMatrix, finalMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, rotation);
		D3DXMatrixScaling(&scaleMatrix, scale, scale, 0.0f);
		D3DXMatrixTranslation(&positionMatrix, rect.getX(), rect.getY(), depth);

		finalMatrix = scaleMatrix * rotateMatrix * positionMatrix;
		this->sprite->SetTransform(&finalMatrix);

		if(color != NULL && texture == nullptr){
			texture = this->nullTexture(rect.getWidth(), rect.getHeight());
		}

		this->sprite->Draw(texture, nullptr, nullptr, nullptr, color);
	}

	IDirect3DTexture9* Canvas::nullTexture(int width, int height){

		D3DXCreateTexture(this->device, width, height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &(this->tmpTexture));

		D3DLOCKED_RECT lockedRect;
		this->tmpTexture->LockRect(0, &lockedRect, NULL, 0);
		
		BYTE* pixels= (BYTE*)lockedRect.pBits;
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				int index = i * 4 + j * lockedRect.Pitch;
				pixels[index] = 255;
				pixels[index + 1] = 255;
				pixels[index + 2] = 255;
				pixels[index + 3] = 255;
			}
		}
		
		this->tmpTexture->UnlockRect(0);

		return this->tmpTexture;
	}

}