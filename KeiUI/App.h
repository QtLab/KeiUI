#ifndef _App_H_
#define _App_H_

#include "Window.h"
#include "UI.h"

namespace KeiUI{

	class App : public Window{
	private:
		UI* uiTest;

	public:
		App(string name, HINSTANCE hInstance = 0);
		~App();

		virtual bool load();
		virtual void update();
		virtual void render();
		virtual void draw(Canvas* canvas);
		virtual void recover();
	};

};

#endif _App_H_