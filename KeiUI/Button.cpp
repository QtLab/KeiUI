#include "Button.h"

namespace KeiUI{
	Button::Button(string name, Rect rect) : UI(name, rect) {

	}

	Button::~Button(){

	}

	void Button::draw(const Canvas* canvas){
		Rect parent;
		if(this->getParent() != nullptr){
			parent = this->getParent()->getRect();
		}

		Rect rect(parent + this->getRect());
		canvas->drawRect(rect, 0.5f, this->getTexture());
	}
}