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
		Rect rect;
		D3DCOLOR color;
		float scale, rotation;
		IDirect3DTexture9* texture;

		UI* controlParent;
		Array<int, UI*> controlList;

	public:
		UI(string name, Rect rect);
		~UI();

		virtual void draw(const Canvas* canvas);

		void add(UI* children);
		void remove(string name);

		string getName();
		Rect getRect();
		D3DCOLOR getColor();
		float getScale();
		float getRotation();
		IDirect3DTexture9* getTexture();
		UI* getParent();

		void setName(string name);
		void setRect(Rect rect);
		void setColor(int r, int g, int b);
		void setScale(float scale);
		void setRotation(float rotation);
		void setTexture(IDirect3DTexture9* texture);
		void setParent(UI* parent);
	};

};

#endif _UI_H_