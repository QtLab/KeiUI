#ifndef _Button_H_
#define _Button_H_

#include "UI.h"

namespace KeiUI{

	class Button : public UI{
	private:
		string defaultTexture, hoverTexture;

	public:
		Button(string name, Rect rect);
		~Button();

		virtual void update(Input* input);
		virtual void draw(Canvas* canvas);

		void setTexture(string defaultTexture, string hoverTexture);

	private:
		void moveOverEvent(Input* input);
		void moveOutEvent(Input* input);
	};

};

#endif _Button_H_