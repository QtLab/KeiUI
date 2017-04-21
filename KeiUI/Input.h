#ifndef _Input_H_
#define _Input_H_

#include "Rect.h"
#include "Canvas.h"

namespace KeiUI{

	class Input{
	private:
		Rect rect;
		Canvas* canvas;
		Rect ui;
		Rect cursor;

	public:
		Input(Rect rect, Canvas* canvas);

		bool mouseDown(Rect ui);
		bool setCursorPosition();

	private:
		bool isArea();
		bool pixelDetection();
	};

};

#endif _Input_H_