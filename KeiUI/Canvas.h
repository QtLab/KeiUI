#ifndef _Canvas_H_
#define _Canvas_H_

#include "Utility.h"
#include "Rect.h"

namespace KeiUI{

	class Canvas{
	protected:
		ID3DXSprite* sprite;

	public:
		Canvas(ID3DXSprite* sprite);
		~Canvas();

		void drawRect(Rect rectangle, float depth);
	};

};

#endif _Canvas_H_