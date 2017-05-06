#ifndef _Form1_H_
#define _Form1_H_

#include "Form.h"
#include "Panel.h"
#include "Button.h"

namespace KeiUI{

	class Form1 : public Form {
	private:
		Panel* panel;
		Button* button1;
		Button* button2;

	public:
		Form1(string name);
		~Form1();

		virtual bool load();
		virtual void update(Input* input);
		virtual void render();
		virtual void draw(Canvas* canvas);
		virtual void recover();

	private:
		void panelMoveEvent(Input* input);
		void buttonClickEvent(Input* input);
		void panelClickEvent(Input* input);

	};

};

#endif _Form1_H_