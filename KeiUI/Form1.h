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
		Form1(string name, Window* window);
		~Form1();

		virtual bool load();
		virtual void update(Input* input);
		virtual void render();
		virtual void draw(Canvas* canvas);
		virtual void recover();

	private:
		void button1ClickEvent(Input* input);
		void button2ClickEvent(Input* input);
		void panelMoveEvent(Input* input);
		void panelClickEvent(Input* input);

	};

};

#endif _Form1_H_