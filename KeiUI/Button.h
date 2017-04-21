#ifndef _Button_H_
#define _Button_H_

#include "UI.h"

namespace KeiUI{

	class Button : public UI{

	public:
		Button(string name, Rect rect);
		~Button();

		virtual void update(Input* input);
		virtual void draw(Canvas* canvas);
	};

};

#endif _Button_H_