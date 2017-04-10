#ifndef _DXWindow_H_
#define _DXWindow_H_

#include "DXContext.h"

class DXWindow : public DXContext{
protected:
	int x, y;
	int width, height;
	string name;

public:

	DXWindow(string name, HINSTANCE hInstance = 0);
	~DXWindow();

	static void messageBox(HWND hWnd, string content, string title, UINT uType);

	virtual bool main(int width, int height);
	virtual void render() = 0;

	virtual LRESULT events(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	static LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void setWindowCenter();

};

#endif