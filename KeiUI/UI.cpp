#include "UI.h"
#include "Window.h"

namespace KeiUI{

	UI::UI(string name, Rect rect) 
		: name(name), depth(0), rect(rect), texture(L""), controlParent(nullptr), controlList(Array<int, UI*>()) 
	{
		this->color = Color();
		this->scale = 1.0f;
		this->rotation = 1.0f;
	}

	UI::~UI(){
		for(int i = 0; i < this->controlList.size(); i++){
			Utility::Delete(this->controlList.get(i));
		}
	}

	void UI::draw(Canvas* canvas){

		// Draw self
		Rect rect;
		if(this->getParent() != nullptr){	// ´æÔÚ¸¸UI
			Rect parent = this->getParent()->getRect();
			rect = parent + this->getRect();

		}else{
			rect = this->getRect();
		}

		float index = 1.0f - this->getDepth() * 0.001f;
		if(this->getTexture() == L"" && !(this->getColor().empty())){
			canvas->drawRect(rect, index, this->getColor());
		}else if(this->getTexture() != L""){
			canvas->drawRect(rect, index, this->getColor(), this->getTexture());
		}

		// Draw children
		for(int i = 0; i < this->controlList.size(); i++){
			this->controlList.get(i)->draw(canvas);
		}
	}

	void UI::add(UI* children){
		children->setParent(this);

		int index = this->controlList.size();
		children->setDepth(index);

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

	// get
	string UI::getName(){
		return this->name;
	}

	int UI::getDepth(){
		return this->depth;
	}

	Rect UI::getRect(){
		return this->rect * Window::resolution;
	}

	Color UI::getColor(){
		return this->color;
	}

	float UI::getScale(){
		return this->scale;
	}

	float UI::getRotation(){
		return this->rotation;
	}

	// set
	void UI::setColor(Color color){
		this->color = color;
	}

	string UI::getTexture(){
		return this->texture;
	}

	UI* UI::getParent(){
		return this->controlParent;
	}

	void UI::setName(string name){
		this->name = name;
	}

	void UI::setDepth(int depth){
		this->depth = depth;
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

	void UI::setTexture(string texture){
		this->texture = texture;
	}

	void UI::setParent(UI* parent){
		this->controlParent = parent;
	}

};
