#include "UI.h"

namespace KeiUI{

	UI::UI(string name, Rect rect) 
		: name(name), rect(rect), texture(nullptr), controlParent(nullptr), controlList(Array<int, UI*>()) 
	{
		this->color = Color::rgb(255, 255, 255);
		this->scale = 1.0f;
		this->rotation = 1.0f;
	}

	UI::~UI(){
		for(int i = 0; i < this->controlList.size(); i++){
			Utility::Delete(this->controlList.get(i));
		}

		Utility::Release(this->texture);
	}

	void UI::draw(const Canvas* canvas){
		// Draw self
		Rect parent;
		if(this->getParent() != nullptr){
			parent = this->getParent()->getRect();
		}

		Rect rect(parent + this->getRect());
		canvas->drawRect(rect, 0.5f, this->getTexture(), this->getColor());

		// Draw children
		for(int i = 0; i < this->controlList.size(); i++){
			this->controlList.get(i)->draw(canvas);
		}
	}

	void UI::add(UI* children){
		children->setParent(this);

		int index = this->controlList.size();
		this->controlList.add(index, children);
	}

	void UI::remove(string name){
		for(int i = 0; i < this->controlList.size(); i++){
			string tmp = this->controlList.get(i)->getName();

			if(tmp == name){
				this->controlList.remove(i);
			}
		}
	}

	string UI::getName(){
		return this->name;
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

	UI* UI::getParent(){
		return this->controlParent;
	}

	void UI::setName(string name){
		this->name = name;
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

	void UI::setParent(UI* parent){
		this->controlParent = parent;
	}

};