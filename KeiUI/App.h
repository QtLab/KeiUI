#ifndef _App_H_
#define _App_H_

#include "Windows.h"

class App : public Windows{
private:
	ID3DXMesh* object[4];
	D3DMATERIAL9 matreial[4];
	D3DLIGHT9 spotLight;
	D3DXMATRIX worldMatrix[4];

public:
	App(string name, HINSTANCE hInstance = 0);

	virtual bool load();
	virtual void update();
	virtual void render();
	virtual void recover();
};

#endif