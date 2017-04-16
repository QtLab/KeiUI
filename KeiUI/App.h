#ifndef _App_H_
#define _App_H_

#include "Windows.h"

class App : public Windows{
private:
	IDirect3DVertexBuffer9* buffer;
	IDirect3DTexture9* texture;

public:
	App(string name, HINSTANCE hInstance = 0);

	virtual bool load();
	virtual void update();
	virtual void render();
	virtual void draw();
	virtual void recover();
};

#endif