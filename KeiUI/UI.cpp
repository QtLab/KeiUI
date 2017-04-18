#include "UI.h"

namespace KeiUI{

	UI::UI(Rect rect) : rect(rect) {
		this->color = Color::rgb(255, 255, 255);
		this->scale = 1.0f;
		this->rotation = 1.0f;
	}

	UI::~UI(){
		Utility::Release(this->texture);
	}

	void UI::draw(const Canvas* canvas){

	}

	Rect UI::getRect(){
		return this->rect;
	}

	D3DCOLOR UI::getColor(){
		return this->color;
	}

	float UI::getScale(){
		return this->scale;
	}

	float UI::getRotation(){
		return this->rotation;
	}

	void UI::setColor(int r, int g, int b){
		this->color = Color::rgb(r, g, b);
	}

	IDirect3DTexture9* UI::getTexture(){
		return this->texture;
	}

	void UI::setRect(Rect rect){
		this->rect = rect;
	}

	void UI::setScale(float scale){
		this->scale = scale;
	}

	void UI::setRotation(float rotation){
		this->rotation = rotation;
	}

	void UI::setTexture(IDirect3DTexture9* texture){
		this->texture = texture;
	}

};
