#include "Scene1.h"
#include "Window.h"

namespace KeiUI{

	Scene1::Scene1(string name, Rect rect) : UI(name, rect) {
		this->button1 = new Button(L"btn1", Rect(10, 10, 120, 120));
		this->button2 = new Button(L"btn2", Rect(130, 130, 100, 35));
	}

	Scene1::~Scene1(){
		Utility::Delete(this->button2);
		Utility::Delete(this->button1);
	}

	bool Scene1::load(){
		this->button1->setTexture(L"Resource/1.png", L"Resource/2.png");
		this->button1->setEvent(Event((UI*)this, (Function)(&Scene1::buttonClickEvent), Event::MouseLeftClickEvent));
		this->add(button1);

		this->button2->setTexture(L"Resource/UI/button-default.png", L"Resource/UI/button-focus.png");
		this->button2->setStretch(true);
		this->add(button2);

		this->setEvent(Event((UI*)this, (Function)(&Scene1::panelMoveEvent), Event::MouseLeftDragEvent));
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

	void Scene1::panelMoveEvent(Input* input){
		int x = input->getCursorX() - input->getLastX();
		int y = input->getCursorY() - input->getLastY();

		this->setX(this->getX() + x);
		this->setY(this->getY() + y);

	}

	void Scene1::buttonClickEvent(Input* input){
		Window::messageBox(nullptr, L"Event Test", this->button1->getName(), MB_ICONSTOP);
	}

	void Scene1::panelClickEvent(Input* input){
		Window::messageBox(nullptr, L"Event Test", this->getName(), MB_ICONSTOP);
	}

};