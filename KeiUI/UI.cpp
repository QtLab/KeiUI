#include "UI.h"
#include "Window.h"

namespace KeiUI{
	
	UI::UI(string name, Clip rect) 
		: name(name), depth(0), rect(Rect()), controlParent(nullptr), controlList(Array<int, UI*>()), eventList(Array<int, Event>())
	{
		this->rect.setClip(rect);
		this->rotation = 1.0f;
		this->focus = false;
	}

	UI::~UI(){

	}

	bool UI::load(){
		return this->loadChildren();
	}

	void UI::update(Input* input){

		// Update children
		this->updateChildren(input);

		// Sets the UI data for the current control
		Rect parentRect = this->getParentRect();
		input->setUI(parentRect);

		this->callEvent(input);	// Event
	}

	void UI::draw(Canvas* canvas){
	
		// Draw self
		Rect rect = this->getParentRect();

		float index = 1.0f - this->getDepth() * 0.001f;
		canvas->drawRect(rect, index);

		// Draw children
		this->drawChildren(canvas);
	}

	// Children
	bool UI::loadChildren(){
		for(int i = 0; i < this->controlList.size(); i++){
			if(!(this->controlList.get(i)->load())){
				return false;
			}
		}

		return true;
	}

	void UI::updateChildren(Input* input){
		for(int i = 0; i < this->controlList.size(); i++){
			this->controlList.get(i)->update(input);
		}
	}

	void UI::drawChildren(Canvas* canvas){
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

	Color UI::getColor(){
		return this->getRect().getColor();
	}

	int UI::getScale(){
		return this->getRect().getScale();
	}

	float UI::getRotation(){
		return this->rotation;
	}

	bool UI::getFocur(){
		return this->focus;
	}

	UI* UI::getParent(){
		return this->controlParent;
	}

	// set
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
		this->rect.setX(x / Window::resolution);
	}

	void UI::setY(int y){
		this->rect.setY(y / Window::resolution);
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

	void UI::setColor(Color color){
		this->rect.setColor(color);
	}

	void UI::setScale(float scale){
		this->rect.setScale(scale);
	}

	void UI::setRotation(float rotation){
		this->rotation = rotation;
	}

	void UI::setFocur(bool focur){
		Input::inputTmp = L"";
		this->focus = focur;
	}

	void UI::setParent(UI* parent){
		this->controlParent = parent;
	}

	Rect UI::getParentRect(){
		UI* p = this->getParent();
		Rect rect = this->getRect();

		while(p != nullptr){
			Rect tmp = p->getRect();
			rect = tmp + rect;

			p = p->getParent();
		}

		Utility::Delete(p);
		return rect;
	}

	void UI::setEvent(Event event){
		int index = this->eventList.size();
		this->eventList.add(index, event);
	}

	void UI::callEvent(Input* input){

		for(int i = 0; i < this->eventList.size(); i++){
			Event event = this->eventList.get(i);

			switch(event.getType()){

			case Event::MouseLeftClickEvent:
			case Event::MouseLeftDragEvent:
				if(input->mouseLeftDown()){
					event.callEvent(input);
				}

				break;

			case Event::MouseRightClickEvent:
			case Event::MouseRightDragEvent:
				if(input->mouseRightDown()){
					event.callEvent(input);
				}

				break;

			case Event::MouseMoveOverEvent:
				if(input->mouseMoveOver()){
					event.callEvent(input);
				}

				break;

			case Event::MouseMoveOutEvent:
				if(input->mouseMoveOut()){
					event.callEvent(input);
				}

				break;
			}
		}

	}

};
