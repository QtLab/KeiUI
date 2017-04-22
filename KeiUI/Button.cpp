#include "Button.h"

namespace KeiUI{
	Button::Button(string name, Rect rect) : UI(name, rect) {

	}

	Button::~Button(){

	}

	void Button::update(Input* input){/*
		if(input->mouseDown(this->getParentRect())){
			// Window::messageBox(nullptr, L"°²À­ºú°¢¿Ë°Í", L"³ÔÖí", MB_ICONSTOP);
		}*/
		UI::update(input);
	}

	void Button::draw(Canvas* canvas){
		UI::draw(canvas);
	}

}