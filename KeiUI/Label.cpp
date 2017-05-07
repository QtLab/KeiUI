#include "Label.h"

namespace KeiUI{

	Label::Label(string name, Clip rect)
		: UI(name, rect), text(Font(name, Clip()))
	{
		this->wrapsAutomatically = this->horizontalCenter = this->verticalCenter = true;
	}

	Label::~Label(){

	}

	void Label::update(Input* input){
		if(this->text.getText() != L""){
			Rect rect = this->getParentRect();
			this->text.setRect(rect.getClip());

			// Arrangement
			this->type = 0;
			if (this->getWrapsAutomatically()){
				this->type |= DT_WORDBREAK;
			}

			if (this->getHorizontalCenter()){
				this->type |= DT_CENTER;
			}

			if (this->getVerticalCenter()){
				this->type |= DT_VCENTER;
			}
		}
	}

	void Label::draw(Canvas* canvas){
		if(this->text.getText() != L""){
			canvas->drawFont(this->text, this->type);
		}

	}

	void Label::setText(string text){
		this->text.setText(text);
	}

	void Label::appendText(string text){
		this->text.setText(this->text.getText() + text);
	}

	bool Label::getWrapsAutomatically(){
		return this->wrapsAutomatically;
	}

	bool Label::getHorizontalCenter(){
		return this->horizontalCenter;
	}

	bool Label::getVerticalCenter(){
		return this->verticalCenter;
	}

	void Label::setWrapsAutomatically(bool wrapsAutomatically){
		this->wrapsAutomatically = wrapsAutomatically;
	}

	void Label::setHorizontalCenter(bool horizontalCenter){
		this->horizontalCenter = horizontalCenter;
	}

	void Label::setVerticalCenter(bool verticalCenter){
		this->verticalCenter = verticalCenter;
	}

};