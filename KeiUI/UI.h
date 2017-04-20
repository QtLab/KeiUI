#ifndef _UI_H_
#define _UI_H_

#include "Color.h"
#include "Canvas.h"
#include "Rect.h"
#include "Array.h"

namespace KeiUI{

	class UI{
	private:
		string name;
		int depth;
		Rect rect;
		Color color;
		float scale, rotation;
		string texture;

		UI* controlParent;

	protected:
		Array<int, UI*> controlList;

	public:
		UI(string name, Rect rect);
		~UI();

		virtual void draw(Canvas* canvas);

		void add(UI* children);
		void remove(string name);

		string getName();
		int getDepth();
		Rect getRect();
		Color getColor();
		float getScale();
		float getRotation();
		string getTexture();
		UI* getParent();

		void setName(string name);
		void setDepth(int depth);
		void setRect(Rect rect);
		void setColor(Color color);
		void setScale(float scale);
		void setRotation(float rotation);
		void setTexture(string texture);
		void setParent(UI* parent);
	};

};

#endif _UI_H_