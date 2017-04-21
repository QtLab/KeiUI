#include "Button.h"
#include "Window.h"

namespace KeiUI{
	Button::Button(string name, Rect rect) : UI(name, rect) {

	}

	Button::~Button(){

	}

	void Button::update(Input* input){
		if(input->mouseDown(this->getParentRect())){
			Window::messageBox(nullptr, L"���������˰�", L"����", MB_ICONSTOP);
		}
	}

	void Button::draw(Canvas* canvas){
		UI::draw(canvas);
	}

}