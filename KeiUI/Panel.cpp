#include "Panel.h"

namespace KeiUI{
	Panel::Panel(string name, Rect rect) : UI(name, rect){

	}

	void Panel::update(Input* input){
		UI::update(input);
	}

	void Panel::draw(Canvas* canvas){
		UI::draw(canvas);
	}
};
