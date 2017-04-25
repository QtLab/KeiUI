#ifndef _Input_H_
#define _Input_H_

#include "Rect.h"
#include "Canvas.h"
#include "TimeLock.h"

namespace KeiUI{

	class Input{
	public:
		enum Key{
			Num0 = 0x30,
			Num1 = 0x31,
			Num2 = 0x32,
			Num3 = 0x33,
			Num4 = 0x34,
			Num5 = 0x35,
			Num6 = 0x36,
			Num7 = 0x37,
			Num8 = 0x38,
			Num9 = 0x39,
			A = 0x41,
			B = 0x42,
			C = 0x43,
			D = 0x44,
			E = 0x45,
			F = 0x46,
			G = 0x47,
			H = 0x48,
			I = 0x49,
			J = 0x4A,
			K = 0x4B,
			L = 0x4C,
			M = 0x4D,
			N = 0x4E,
			O = 0x4F,
			P = 0x50,
			Q = 0x51,
			R = 0x52,
			S = 0x53,
			T = 0x54,
			U = 0x55,
			V = 0x56,
			W = 0x57,
			X = 0x58,
			Y = 0x59,
			Z = 0x5A
		};

	private:
		Rect rect;
		Canvas* canvas;
		Rect ui;
		Rect cursor;
		Rect last;

		TimeLock timeLock;
		bool isHold;

	public:
		Input(Rect rect, Canvas* canvas);

		bool Input::keyDown(int vKey);
		bool mouseLeftDown(Rect ui);
		bool mouseRightDown(Rect ui);

		bool setCursorPosition();

		int getCursorX();
		int getCursorY();
		int getLastX();
		int getLastY();

	private:
		bool getState(int vKey);

		bool inArea();
		bool pixelDetection();
	};

};

#endif _Input_H_