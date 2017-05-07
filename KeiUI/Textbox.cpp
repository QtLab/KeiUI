#include "Textbox.h"

namespace KeiUI{
	Textbox::Textbox(string name, Clip rect) : UI(name, rect) {


		this->text = new Label(name, Clip(0, 0, rect.getWidth(), rect.getHeight()));
	}

	Textbox::~Textbox(){
		Utility::Delete(this->text);
	}

	bool Textbox::load(){

		this->text->setWrapsAutomatically(false);
		this->text->setHorizontalCenter(false);
		this->text->setVerticalCenter(false);

		this->add(this->text);

		return UI::loadChildren();;
	}

	void Textbox::update(Input* input){
		UI::update(input);

		if(this->getFocur()){
			string newInput = input->inputText();
			this->text->appendText(newInput);
		}
	}

	void Textbox::setText(string text){
		this->text->setText(text);
	}
};