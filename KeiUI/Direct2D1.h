#ifndef _Direct2D1_H_
#define _Direct2D1_H_

#include "DirectX9.h"
#include <D2D1.h>

class Direct2D1 : public DirectX9 {
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* target;
	ID2D1SolidColorBrush* brush;

public:
	Direct2D1();
	~Direct2D1();

	bool init2D(string name);
	void drawRect(int x, int y, int witdh, int height);
};

#endif