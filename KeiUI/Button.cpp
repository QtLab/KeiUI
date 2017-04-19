#include "Button.h"

namespace KeiUI{
	Button::Button(string name, Rect rect) : UI(name, rect) {

	}

	Button::~Button(){

	}

	void Button::draw(Canvas* canvas){

		// Draw self
		Rect parent;
		if(this->getParent() != nullptr){
			parent = this->getParent()->getRect();
		}

		Rect rect(parent + this->getRect());
		canvas->drawRect(rect, 0.5f, this->getTexture());

		// Draw children
		for(int i = 0; i < this->controlList.size(); i++){
			this->controlList.get(i)->draw(canvas);
		}

	}
}