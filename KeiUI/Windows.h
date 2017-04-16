#ifndef _Windows_H_
#define _Windows_H_

#include "Direct2D1.h"

class Windows : public Direct2D1{
private:
	static float refreshLast;

protected:
	static float refreshTime;

	int x, y;
	int width, height;
	string name;

public:

	Windows(string name, HINSTANCE hInstance = 0);
	~Windows();

	static void messageBox(HWND hWnd, string content, string title, UINT uType);

	virtual bool main(int width, int height);
	virtual bool load() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void draw() = 0;
	virtual void recover() = 0;

	virtual LRESULT events(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	static LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void setWindowCenter();

};

#endif