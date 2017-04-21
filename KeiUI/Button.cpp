#include "Button.h"

namespace KeiUI{
	Button::Button(string name, Rect rect) : UI(name, rect) {

	}

	Button::~Button(){

	}

	void Button::update(Input* input){

	}

	void Button::draw(Canvas* canvas){
		UI::draw(canvas);
	}

}