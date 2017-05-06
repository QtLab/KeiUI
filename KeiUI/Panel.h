#ifndef _Panel_H_
#define _Panel_H_

#include "UI.h"

namespace KeiUI{

	class Panel : public UI{
	public:
		Panel(string name, Rect rect);

		virtual void update(Input* input);
		virtual void draw(Canvas* canvas);
	};

};

#endif _Panel_H_