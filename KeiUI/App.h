#ifndef _App_H_
#define _App_H_

#include "Window.h"
#include "Form1.h"

namespace KeiUI{

	class App : public Window{
	private:
		Form1* form1;

	public:
		App(string name, HINSTANCE hInstance = 0);
		~App();

		virtual bool load();
		virtual void update(Input* input);
		virtual void render();
		virtual void draw(Canvas* canvas);
		virtual void recover();

	protected:
		void bindForm(UI* form);

	};

};

#endif _App_H_