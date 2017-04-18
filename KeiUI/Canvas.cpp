#include "Canvas.h"

namespace KeiUI{
	Canvas::Canvas(ID3DXSprite* sprite) : sprite(sprite){

	}

	Canvas::~Canvas(){

	}

	void Canvas::drawRect(Rect rectangle, float depth){
		/*
		D3DXMATRIX positionMatrix, scaleMatrix, rotateMatrix, finalMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, rectangle.getRotation());
		D3DXMatrixScaling(&scaleMatrix, rectangle.getScale(), rectangle.getScale(), 0.0f);
		D3DXMatrixTranslation(&positionMatrix, rectangle.getX(), rectangle.getY(), depth);

		finalMatrix = scaleMatrix * rotateMatrix * positionMatrix;
		this->sprite->SetTransform(&finalMatrix);

		this->sprite->Draw(rectangle.getTexture(), nullptr, nullptr, nullptr, rectangle.getColor());
		*/
	}

}