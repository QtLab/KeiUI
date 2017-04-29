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
		virtual void callEvent(Input* input);

		void setTexture(string defaultTexture, string hoverTexture);

	private:
		void setDrawType(bool defaultType = true);
	};

};

#endif _Button_H_