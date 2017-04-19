#ifndef _Rectangle_H_
#define _Rectangle_H_

namespace KeiUI{

	class Rect{
		friend Rect operator+(const Rect& left,const Rect& right);

	private:
		int x, y;
		int width, height;

	public:
		Rect(int x, int y, int width, int height);
		Rect(Rect &rect);
		Rect();
		~Rect();

		int getX() const;
		int getY() const;
		int getWidth() const;
		int getHeight() const;

		void setX(int x);
		void setY(int y);
		void setWidth(int width);
		void setHeight(int height);

	};

};

#endif _Rectangle_H_