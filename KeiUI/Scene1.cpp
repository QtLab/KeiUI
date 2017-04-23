#include "Scene1.h"
#include "Window.h"

namespace KeiUI{

	Scene1::Scene1(string name, Rect rect) : UI(name, rect) {
		this->button = new Button(L"btn1", Rect(10, 10, 120, 120));
	}

	Scene1::~Scene1(){
		Utility::Delete(this->button);
	}

	bool Scene1::load(){
		this->button->setTexture(L"Resource/1.png");
		this->button->setEvent(Event((UI*)this, (Callback)(&Scene1::buttonMoveEvent), Event::MouseLeftDragEvent));
		this->button->setEvent(Event((UI*)this, (Function)(&Scene1::buttonClickEvent), Event::MouseRightClickEvent));

		this->add(button);

		this->setEvent(Event((UI*)this, (Function)(&Scene1::panelClickEvent), Event::MouseRightClickEvent));

		return true;
	}

	void Scene1::update(Input* input){
		UI::update(input);

		if(input->keyDown(Input::Key::A)){
			this->setX(this->getX() - 10);
		}

		if(input->keyDown(Input::Key::D)){
			this->setX(this->getX() + 10);
		}
	}

	void Scene1::render(){

	}

	void Scene1::draw(Canvas* canvas){
		UI::draw(canvas);
	}

	void Scene1::recover(){

	}

	void Scene1::buttonMoveEvent(Input* input){
		string tmp = Utility::toString(input->getCursorX());
		Window::messageBox(nullptr, tmp, this->button->getName(), MB_ICONSTOP);
	}

	void Scene1::buttonClickEvent(){
		Window::messageBox(nullptr, L"Event Test", this->button->getName(), MB_ICONSTOP);
	}

	void Scene1::panelClickEvent(){
		Window::messageBox(nullptr, L"Event Test", this->getName(), MB_ICONSTOP);
	}
};