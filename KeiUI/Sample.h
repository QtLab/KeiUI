#ifndef _Sample_H_
#define _Sample_H_

#include "DXWindow.h"

class Sample : public DXWindow{
public:
	Sample(string name, HINSTANCE hInstance = 0);
	virtual void render();
};

#endif