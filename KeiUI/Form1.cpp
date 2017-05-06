#include "Form1.h"
#include "Window.h"

namespace KeiUI{

	Form1::Form1(string name) : Form(name) {
		this->panel = new Panel(L"panel", Rect(50, 50, 300, 300));
		this->button1 = new Button(L"btn1", Rect(10, 10, 120, 120));
		this->button2 = new Button(L"btn2", Rect(130, 130, 100, 35));
	}

	Form1::~Form1(){
		Utility::Delete(this->button2);
		Utility::Delete(this->button1);
		Utility::Delete(this->panel);
	}

	bool Form1::load(){

		this->panel->setColor(Color(67, 238, 156));
		this->add(this->panel);

		this->button1->setTexture(L"Resource/1.png", L"Resource/2.png");
		this->button1->setEvent(Event((UI*)this, (Function)(&Form1::buttonClickEvent), Event::MouseLeftClickEvent));
		this->panel->add(this->button1);

		this->button2->setTexture(L"Resource/UI/button-default.png", L"Resource/UI/button-focus.png");
		this->button2->setStretch(true);
		this->panel->add(this->button2);

		this->panel->setEvent(Event((UI*)this, (Function)(&Form1::panelMoveEvent), Event::MouseLeftDragEvent));
		this->panel->setEvent(Event((UI*)this, (Function)(&Form1::panelClickEvent), Event::MouseRightClickEvent));

		return true;
	}

	void Form1::update(Input* input){
		UI::update(input);

		if(input->keyDown(Input::Key::A)){
			this->panel->setX(this->panel->getX() - 10);
		}

		if(input->keyDown(Input::Key::D)){
			this->panel->setX(this->panel->getX() + 10);
		}
	}

	void Form1::render(){

	}

	void Form1::draw(Canvas* canvas){
		UI::draw(canvas);
	}

	void Form1::recover(){

	}

	void Form1::panelMoveEvent(Input* input){
		int x = input->getCursorX() - input->getLastX();
		int y = input->getCursorY() - input->getLastY();

		this->panel->setX(this->panel->getX() + x);
		this->panel->setY(this->panel->getY() + y);

	}

	void Form1::buttonClickEvent(Input* input){
		Window::messageBox(nullptr, L"Event Test", this->button1->getName(), MB_ICONSTOP);
	}

	void Form1::panelClickEvent(Input* input){
		Window::messageBox(nullptr, L"Event Test", this->panel->getName(), MB_ICONSTOP);
	}

};