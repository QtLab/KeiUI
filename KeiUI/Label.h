#ifndef _Label_H_
#define _Label_H_

#include "UI.h"
#include "Font.h"

namespace KeiUI{

	class Label : public UI{
	private:
		Font text;
		bool wrapsAutomatically, horizontalCenter, verticalCenter;
		int type;

	public:
		Label(string name, Clip rect);
		~Label();

		virtual void update(Input* input);
		virtual void draw(Canvas* canvas);

		void setText(string text);
		void appendText(string text);

		bool getWrapsAutomatically();
		bool getHorizontalCenter();
		bool getVerticalCenter();

		void setWrapsAutomatically(bool wrapsAutomatically);
		void setHorizontalCenter(bool horizontalCenter);
		void setVerticalCenter(bool verticalCenter);
	};

};

#endif _Label_H_