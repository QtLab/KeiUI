#include "Panel.h"
#include "Window.h"
#include "Event.h"

namespace KeiUI{

	Panel::Panel(string name, Rect rect) : UI(name, rect) {
		this->button = new Button(L"btn1", Rect(10, 10, 120, 120));
	}

	Panel::~Panel(){
		Utility::Delete(this->button);
	}

	bool Panel::load(){
		this->button->setTexture(L"Resource/1.png");
		typedef void (UI::*Function)();
		this->button->setEvent((UI*)this, (Function)&Panel::buttonClickEvent);

		this->add(button);

		return true;
	}

	void Panel::update(Input* input){
		UI::update(input);
	}

	void Panel::draw(Canvas* canvas){
		UI::draw(canvas);
	}

	void Panel::recover(){

	}

	void Panel::buttonClickEvent(){
		Window::messageBox(nullptr, L"Event Test", this->button->getName(), MB_ICONSTOP);
	}
};