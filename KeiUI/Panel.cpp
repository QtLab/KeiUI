#include "Panel.h"

namespace KeiUI{
	Panel::Panel(string name, Clip rect) : UI(name, rect){

	}

	Panel::~Panel(){

	}

	void Panel::update(Input* input){
		UI::update(input);
	}

	void Panel::draw(Canvas* canvas){
		UI::draw(canvas);
	}
};
