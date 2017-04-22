#ifndef _UI_H_
#define _UI_H_

#include "Canvas.h"
#include "Input.h"
#include "Array.h"

namespace KeiUI{

	class UI{
	private:
		string name;
		int depth;
		Rect rect;	// Coordinate information
		float rotation;

		UI* controlParent;

		UI* object;
		typedef void (UI::*Function)();
		Function function;

	protected:
		Array<int, UI*> controlList;

	public:
		UI(string name, Rect rect);
		~UI();

		virtual void update(Input* input);
		virtual void draw(Canvas* canvas);

		void add(UI* children);
		void remove(string name);

		// Get
		string getName();
		int getDepth();

		Rect getRect();	// Coordinate information
		int getX();
		int getY();
		int getWidth();
		int getHeight();
		string getTexture();
		Color getColor();
		int getScale();

		float getRotation();
		UI* getParent();

		// Set
		void setName(string name);
		void setDepth(int depth);

		void setRect(Rect rect);	// Coordinate information
		void setX(int x);
		void setY(int y);
		void setWidth(int width);
		void setHeight(int height);
		void setTexture(string texture);
		void setColor(Color color);
		void setScale(float scale);

		void setRotation(float rotation);
		void setParent(UI* parent);

		void setEvent(UI* object, Function function);
		void clickEvent();

	protected:
		Rect getParentRect();

	};

};

#endif _UI_H_