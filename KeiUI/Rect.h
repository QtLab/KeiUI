#ifndef _Rectangle_H_
#define _Rectangle_H_

namespace KeiUI{

	class Rect{
	private:
		int x, y;
		int width, height;

	public:
		Rect(int x, int y, int width, int height);
		~Rect();

		int getX();
		int getY();
		int getWidth();
		int getHeight();

		void setX(int x);
		void setY(int y);
		void setWidth(int width);
		void setHeight(int height);

	};

};

#endif _Rectangle_H_