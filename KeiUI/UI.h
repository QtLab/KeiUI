#ifndef _UI_H_
#define _UI_H_

#include "Canvas.h"
#include "Input.h"
#include "Array.h"
#include "Event.h"

namespace KeiUI{

	class Event;

	class UI{
	private:
		string name;
		int depth;
		Rect rect;	// Coordinate information
		float rotation;

		UI* controlParent;
		Array<int, UI*> controlList;

		Array<int, Event> eventList;	// Event

	public:
		UI(string name, Rect rect);
		~UI();

		virtual bool load();
		virtual void update(Input* input);
		virtual void render();
		virtual void draw(Canvas* canvas);
		virtual void recover();

		// Children
		void updateChildren(Input* input);
		void drawChildren(Canvas* canvas);

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

		void setEvent(Event event);	// Event

	protected:
		Rect getParentRect();

		void callEvent(Input* input);	// Event
	};

};

#endif _UI_H_