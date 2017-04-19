#ifndef _Canvas_H_
#define _Canvas_H_

#include "Utility.h"
#include "Rect.h"
#include "Color.h"

namespace KeiUI{

	class Canvas{
	protected:
		IDirect3DDevice9* device;
		ID3DXSprite* sprite;

	public:
		Canvas(IDirect3DDevice9* device, ID3DXSprite* sprite);
		~Canvas();

		void drawRect(Rect rect, float depth, IDirect3DTexture9* texture, D3DCOLOR color = Color::rgb(255, 255, 255), float scale = 1.0f, float rotation = 0.0f) const;

	private:
		IDirect3DTexture9* nullTexture(int width, int height) const;
	};

};

#endif _Canvas_H_