#include "Button.h"

namespace KeiUI{
	Button::Button(string name, Rect rect) : UI(name, rect) {
		this->setEvent(Event((UI*)this, (Function)(&Button::moveOverEvent), Event::MouseMoveOverEvent));
		this->setEvent(Event((UI*)this, (Function)(&Button::moveOutEvent), Event::MouseMoveOutEvent));
	}

	Button::~Button(){

	}

	void Button::update(Input* input){
		UI::update(input);
	}

	void Button::draw(Canvas* canvas){
		UI::draw(canvas);
	}

	void Button::setTexture(string defaultTexture, string hoverTexture){
		this->defaultTexture = defaultTexture;
		this->hoverTexture = hoverTexture;

		UI::setTexture(this->defaultTexture);
	}

	void Button::moveOverEvent(Input* input){
		UI::setTexture(this->hoverTexture);
	}

	void Button::moveOutEvent(Input* input){
		UI::setTexture(this->defaultTexture);
	}

}