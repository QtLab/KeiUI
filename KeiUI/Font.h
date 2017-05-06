#ifndef _Font_H_
#define _Font_H_

#include "Clip.h"
#include "Color.h"

namespace KeiUI{

	class Font{
	private:
		string text;
		Clip rect;
		int size;
		Color color;
		bool bold;

	public:

		Font(string text, Clip rect, int size = 14, Color color = Color(), bool bold = false);

		string getText();
		Clip getRect();
		int getSize();
		Color getColor();
		bool getBold();

		void setText(string text);
		void setRect(Clip rect);
		void setSize(int size);
		void setColor(Color color);
		void setBold(bool bold);

	};

};

#endif _Font_H_