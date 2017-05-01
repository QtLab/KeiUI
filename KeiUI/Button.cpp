#include "Button.h"

namespace KeiUI{
	Button::Button(string name, Rect rect) : UI(name, rect), stretch(false) {
		this->setEvent(Event((UI*)this, (Function)(&Button::moveOverEvent), Event::MouseMoveOverEvent));
		this->setEvent(Event((UI*)this, (Function)(&Button::moveOutEvent), Event::MouseMoveOutEvent));
	}

	Button::~Button(){

	}

	void Button::update(Input* input){
		UI::update(input);
	}

	void Button::draw(Canvas* canvas){
		// Draw self
		Rect rect = this->getParentRect();

		float index = 1.0f - this->getDepth() * 0.001f;
		if(this->stretch){
			canvas->drawStretch(rect, index);
		}else{
			canvas->drawRect(rect, index);
		}
	
		// Draw children
		this->drawChildren(canvas);
	}

	void Button::setTexture(string defaultTexture, string hoverTexture){
		this->defaultTexture = defaultTexture;
		this->hoverTexture = hoverTexture;

		UI::setTexture(this->defaultTexture);
	}

	void Button::setStretch(bool type){
		this->stretch = type;
	}

	void Button::moveOverEvent(Input* input){
		UI::setTexture(this->hoverTexture);
	}

	void Button::moveOutEvent(Input* input){
		UI::setTexture(this->defaultTexture);
	}

}