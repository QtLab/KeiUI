#include "Form1.h"
#include "Window.h"

namespace KeiUI{

	Form1::Form1(string name, Window* window) : Form(name, window) {
		this->panel = new Panel(L"panel", Clip(50, 50, 300, 300));
		this->button1 = new Button(L"btn1", Clip(10, 10, 120, 120));
		this->button2 = new Button(L"btn2", Clip(130, 130, 100, 35));

		this->textbox = new Textbox(L"textbox", Clip(20, 15, 80, 20));
	}

	Form1::~Form1(){
		Utility::Delete(this->textbox);

		Utility::Delete(this->button2);
		Utility::Delete(this->button1);
		Utility::Delete(this->panel);
	}

	bool Form1::load(){
		this->panel->setColor(Color(67, 238, 156));
		this->panel->setFocur(true);
		this->add(this->panel);

		this->button1->setTexture(L"Resource/1.png", L"Resource/2.png");
		this->button1->setText(L"");
		this->button1->setEvent(Event((UI*)this, (Function)(&Form1::button1ClickEvent), Event::MouseLeftClickEvent));
		this->panel->add(this->button1);

		this->button2->setTexture(L"Resource/UI/button-default.png", L"Resource/UI/button-focus.png");
		this->button2->setStretch(true);
		this->button2->setEvent(Event((UI*)this, (Function)(&Form1::button2ClickEvent), Event::MouseRightClickEvent));
		this->panel->add(this->button2);

		this->panel->setEvent(Event((UI*)this, (Function)(&Form1::panelMoveEvent), Event::MouseLeftDragEvent));
		this->panel->setEvent(Event((UI*)this, (Function)(&Form1::panelClickEvent), Event::MouseRightClickEvent));

		this->textbox->setColor(Color(255, 0, 255));
		this->textbox->setEvent(Event((UI*)this, (Function)(&Form1::textboxClickEvent), Event::MouseLeftClickEvent));
		this->add(this->textbox);

		return UI::loadChildren();
	}

	void Form1::update(Input* input){
		UI::update(input);


		if(this->panel->getFocur()){
			if(input->keyDown(Input::Key::A)){
				this->panel->setX(this->panel->getX() - 10);
			}

			if(input->keyDown(Input::Key::D)){
				this->panel->setX(this->panel->getX() + 10);
			}
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

	void Form1::button1ClickEvent(Input* input){
		Window::messageBox(nullptr, L"Event Test", this->button1->getName(), MB_ICONSTOP);
	}

	void Form1::button2ClickEvent(Input* input){
		this->window->setMinimize();
		Window::messageBox(nullptr, L"Event Test", this->button2->getName(), MB_ICONSTOP);
	}

	void Form1::panelClickEvent(Input* input){
		this->textbox->setColor(Color(255, 0, 255));
		this->textbox->setFocur(false);
		this->panel->setFocur(true);
	}

	void Form1::textboxClickEvent(Input* input){
		this->textbox->setColor(Color(100, 0, 255));
		this->textbox->setFocur(true);
		this->panel->setFocur(false);
	}
};