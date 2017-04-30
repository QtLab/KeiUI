#ifndef _Rectangle_H_
#define _Rectangle_H_

#include "Utility.h"
#include "Color.h"
#include "Clip.h"

namespace KeiUI{

	class Rect{
		friend Rect operator*(const Rect& left,const float& right);
		friend Rect operator+(const Rect& left,const Rect& right);
		friend bool operator!=(const Rect& left,const Rect& right);

	private:
		Clip clip;
		string texture;
		Color color;
		float scale;

	public:
		Rect(int x = 0, int y = 0, int width = 0, int height = 0, string texture = L"", Color color = Color(), float scale = 1.0f);
		Rect(Rect &rect);
		~Rect();

		int getX() const;
		int getY() const;
		int getWidth() const;
		int getHeight() const;

		string getTexture() const;
		Color getColor() const;
		float getScale() const;

		void setX(int x);
		void setY(int y);
		void setWidth(int width);
		void setHeight(int height);

		void setTexture(string texture);
		void setColor(Color color);
		void setScale(float scale);

		string toString();
		Clip toClip();

		bool empty();

	};

};

#endif _Rectangle_H_