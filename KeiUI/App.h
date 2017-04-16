#ifndef _App_H_
#define _App_H_

#include "Window.h"

namespace KeiUI{

	class App : public Window{
	private:
		// Rectangle rectangle;

	public:
		App(string name, HINSTANCE hInstance = 0);

		virtual bool load();
		virtual void update();
		virtual void render();
		virtual void draw();
		virtual void recover();
	};

};

#endif