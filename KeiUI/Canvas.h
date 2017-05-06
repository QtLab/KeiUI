#ifndef _Canvas_H_
#define _Canvas_H_

#include "Utility.h"
#include "Array.h"
#include "Rect.h"
#include "Color.h"
#include "Font.h"

namespace KeiUI{

	class Canvas{
	public:
		struct TextureInfo{
			IDirect3DTexture9* texture;
			D3DXIMAGE_INFO info;

			TextureInfo(){}
			TextureInfo(IDirect3DTexture9* texture, D3DXIMAGE_INFO info){
				this->texture = texture;
				this->info = info;
			}

		};

	protected:
		IDirect3DDevice9* device;
		ID3DXSprite* sprite;
		
		IDirect3DTexture9* tmpTexture;
		Array<string, TextureInfo> textureList;

		D3DXFONT_DESC newFont;
		D3DXFONT_DESC oldFont;
		ID3DXFont* font;

	public:
		Canvas(IDirect3DDevice9* device, ID3DXSprite* sprite);
		~Canvas();

		BYTE* getPixel(string name, int* pitch);
		void drawRect(Rect rect, float depth, Clip clip = Clip(), float rotation = 0.0f);
		void drawStretch(Rect rect, float depth);
		void drawFont(Font font);

	private:
		void nullTexture(string name, int width, int height);
		void loadTexture(string source, D3DXIMAGE_INFO* info = nullptr);

	};

};

#endif _Canvas_H_