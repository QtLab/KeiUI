#include "Button.h"

namespace KeiUI{
	Button::Button(string name, Rect rect) : UI(name, rect) {

	}

	Button::~Button(){

	}

	void Button::update(Input* input){
		UI::update(input);
	}

	void Button::draw(Canvas* canvas){
		UI::draw(canvas);
	}

	void Button::callEvent(Input* input){

		if(input->inArea()){
			this->setDrawType(false);
			UI::callEvent(input);

		}else{
			this->setDrawType(true);
		}

	}

	void Button::setTexture(string defaultTexture, string hoverTexture){
		this->defaultTexture = defaultTexture;
		this->hoverTexture = hoverTexture;

		UI::setTexture(this->defaultTexture);
	}

	void Button::setDrawType(bool defaultType){
		if(defaultType){
			UI::setTexture(this->defaultTexture);
		}else{
			UI::setTexture(this->hoverTexture);
		}
	}
}