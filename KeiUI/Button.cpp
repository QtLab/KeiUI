#include "Button.h"

namespace KeiUI{
	Button::Button(string name, Clip rect) : UI(name, rect), stretch(false) {
		this->setEvent(Event((UI*)this, (Function)(&Button::moveOverEvent), Event::MouseMoveOverEvent));
		this->setEvent(Event((UI*)this, (Function)(&Button::moveOutEvent), Event::MouseMoveOutEvent));

		this->text = new Label(name, Clip(0, 0, rect.getWidth(), rect.getHeight()));
	}

	Button::~Button(){
		Utility::Delete(this->text);
	}

	bool Button::load(){
		this->add(this->text);

		return UI::loadChildren();;
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

	void Button::setText(string text){
		this->text->setText(text);
	}

	void Button::moveOverEvent(Input* input){
		UI::setTexture(this->hoverTexture);
	}

	void Button::moveOutEvent(Input* input){
		UI::setTexture(this->defaultTexture);
	}

}