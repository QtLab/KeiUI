#ifndef _Clip_H_
#define _Clip_H_

#include <Windows.h>

namespace KeiUI{

	class Clip{
		friend RECT operator*(const Clip& left, const float& right);	// Used to stretching the resolution when drawing the font

	private:
		int x, y;
		int width, height;

	public:
		Clip(int x = 0, int y = 0, int width = 0, int height = 0);

		RECT toRECT();

		int getX() const;
		int getY() const;
		int getWidth() const;
		int getHeight() const;

		void setX(int x);
		void setY(int y);
		void setWidth(int width);
		void setHeight(int height);

		bool empty();
	};

};


#endif _Clip_H_