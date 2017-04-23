#ifndef _Scene1_H_
#define _Scene1_H_

#include "UI.h"
#include "Button.h"

namespace KeiUI{

	class Scene1 : public UI {
	private:
		Button* button;

	public:
		Scene1(string name, Rect rect);
		~Scene1();

		virtual bool load();
		virtual void update(Input* input);
		virtual void render();
		virtual void draw(Canvas* canvas);
		virtual void recover();

	private:
		void buttonMoveEvent(Input* input);
		void buttonClickEvent();
		void panelClickEvent();

	};

};

#endif _Scene1_H_