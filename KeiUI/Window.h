#ifndef _Windows_H_
#define _Windows_H_

#include "DirectX9.h"
#include "Canvas.h"

namespace KeiUI{

	class Window : public DirectX9 {
	public:
		static float resolution;

		enum Resolution{	// �ֱ���
			ExtremelyLow, Low, Middle, High, ExtremelyHigh
		};

	private:
		static float refreshLast;

	protected:
		static float refreshTime;

		int x, y;
		int width, height;
		string name;

	public:

		Window(string name, HINSTANCE hInstance = 0);
		~Window();

		static void messageBox(HWND hWnd, string content, string title, UINT uType);

		virtual bool main(int width, int height);
		virtual bool load() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void draw(Canvas* canvas) = 0;
		virtual void recover() = 0;

		virtual LRESULT events(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	protected:
		static LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		void changeResolution(Resolution resolution);

	private:
		void setWindowCenter();

	};

};

#endif _Windows_H_