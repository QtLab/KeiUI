#ifndef _Button_H_
#define _Button_H_

#include "UI.h"
#include "Label.h"

namespace KeiUI{

	class Button : public UI{
	private:
		string defaultTexture, hoverTexture;
		bool stretch;	// Stretch the display of texture
		
		Label* text;

	public:
		Button(string name, Clip rect);
		~Button();

		virtual bool load();
		virtual void update(Input* input);
		virtual void draw(Canvas* canvas);

		void setTexture(string defaultTexture, string hoverTexture);
		void setStretch(bool type);
		void setText(string text);

	private:
		void moveOverEvent(Input* input);
		void moveOutEvent(Input* input);
	};

};

#endif _Button_H_