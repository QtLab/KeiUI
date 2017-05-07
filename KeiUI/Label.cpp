#include "Label.h"

namespace KeiUI{

	Label::Label(string name, Clip rect) : UI(name, rect), text(Font(name, Clip())) {

	}

	Label::~Label(){

	}

	void Label::draw(Canvas* canvas){

		if(this->text.getText() != L""){

			Rect rect = this->getParentRect();

			this->text.setRect(rect.getClip());
			canvas->drawFont(this->text);
		}

	}

	void Label::setText(string text){
		this->text.setText(text);
	}
};