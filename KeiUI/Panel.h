#ifndef _Panel_H_
#define _Panel_H_

#include "UI.h"
#include "Button.h"

namespace KeiUI{

	class Panel : public UI {
	private:
		Button* button;

	public:
		Panel(string name, Rect rect);
		~Panel();

		virtual bool load();
		virtual void update(Input* input);
		virtual void draw(Canvas* canvas);
		virtual void recover();

	private:
		void buttonClickEvent();
	};

};

#endif _Panel_H_