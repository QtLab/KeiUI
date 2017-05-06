#ifndef _Form_H_
#define _Form_H_

#include "UI.h"
#include "Window.h"

namespace KeiUI{

	class Form : public UI {
	protected:
		Window* window;

	public:
		Form(string name, Window* window);
		~Form();

		virtual bool load() = 0;
		virtual void update(Input* input) = 0;
		virtual void render() = 0;
		virtual void draw(Canvas* canvas) = 0;
		virtual void recover() = 0;
	};

};

#endif _Form_H_