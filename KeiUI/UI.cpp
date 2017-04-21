#include "UI.h"
#include "Window.h"

namespace KeiUI{

	UI::UI(string name, Rect rect) 
		: name(name), depth(0), rect(rect), controlParent(nullptr), controlList(Array<int, UI*>()) 
	{
		this->color = Color();
		this->rotation = 1.0f;
	}

	UI::~UI(){
		for(int i = 0; i < this->controlList.size(); i++){
			Utility::Delete(this->controlList.get(i));
		}
	}

	void UI::update(Input* input){
		for(int i = 0; i < this->controlList.size(); i++){
			this->controlList.get(i)->update(input);
		}
	}

	void UI::draw(Canvas* canvas){

		// Draw self
		Rect rect;
		if(this->getParent() != nullptr){	// 存在父UI
			Rect parent = this->getParent()->getRect();
			rect = parent + this->getRect();

		}else{
			rect = this->getRect();
		}

		float index = 1.0f - this->getDepth() * 0.001f;
		canvas->drawRect(rect, index, this->getColor());

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

	Rect UI::getRect(){	// Coordinate information
		return this->rect * Window::resolution;
	}

	int UI::getX(){
		return this->getRect().getX();
	}

	int UI::getY(){
		return this->getRect().getY();
	}

	int UI::getWidth(){
		return this->getRect().getWidth();
	}

	int UI::getHeight(){
		return this->getRect().getHeight();
	}

	string UI::getTexture(){
		return this->getRect().getTexture();
	}

	int UI::getScale(){
		return this->getRect().getScale();
	}

	Color UI::getColor(){
		return this->color;
	}

	float UI::getRotation(){
		return this->rotation;
	}

	// set
	void UI::setColor(Color color){
		this->color = color;
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

	void UI::setRect(Rect rect){	// Coordinate information
		this->rect = rect;
	}

	void UI::setX(int x){
		this->rect.setX(x);
	}

	void UI::setY(int y){
		this->rect.setY(y);
	}

	void UI::setWidth(int width){
		this->rect.setWidth(width);
	}

	void UI::setHeight(int height){
		this->rect.setHeight(height);
	}
	
	void UI::setTexture(string texture){
		this->rect.setTexture(texture);
	}

	void UI::setScale(float scale){
		this->rect.setScale(scale);
	}

	void UI::setRotation(float rotation){
		this->rotation = rotation;
	}

	void UI::setParent(UI* parent){
		this->controlParent = parent;
	}

};
