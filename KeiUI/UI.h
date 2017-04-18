#ifndef _UI_H_
#define _UI_H_

#include "Utility.h"
#include "Color.h"
#include "Canvas.h"
#include "Rect.h"

namespace KeiUI{

	class UI{
	private:
		Rect rect;
		D3DCOLOR color;
		float scale, rotation;
		IDirect3DTexture9* texture;

	public:
		UI(Rect rect);
		~UI();

		void draw(const Canvas* canvas);

		Rect getRect();
		D3DCOLOR getColor();
		float getScale();
		float getRotation();
		IDirect3DTexture9* getTexture();

		void setRect(Rect rect);
		void setColor(int r, int g, int b);
		void setScale(float scale);
		void setRotation(float rotation);
		void setTexture(IDirect3DTexture9* texture);
	};

};

#endif _UI_H_