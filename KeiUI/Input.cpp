#include "Input.h"
#include <Windows.h>

namespace KeiUI{

	Input::Input(Rect rect, Canvas* canvas) : rect(rect), canvas(canvas), ui(Rect()){

	}

	bool Input::mouseDown(Rect ui){
		// Cache
		this->ui = ui;	

		if(this->isArea()){
			if(GetAsyncKeyState(VK_LBUTTON)){
				return this->pixelDetection();
			}
		}

		return false;
	}

	bool Input::isArea(){

		float right = rect.getWidth() * rect.getScale();
		float bottom = rect.getHeight() * rect.getScale();

		bool existX = rect.getX() <= this->cursor.getX() && this->cursor.getX() <= rect.getX() + right;
		bool existY = rect.getY() <= this->cursor.getY() && this->cursor.getY() <= rect.getY() + bottom;

		if(existX && existY){
			return true;
		}

		return false;
	}

	bool Input::pixelDetection(){

		int x = (int)((rect.getWidth() * this->cursor.getX()) / (rect.getWidth() * rect.getScale()));
		int y = (int)((rect.getHeight() * this->cursor.getY()) / (rect.getHeight() * rect.getScale()));

		int scaleX = (int)((rect.getWidth() * rect.getX()) / (rect.getWidth() * rect.getScale()));
		int scaleY = (int)((rect.getHeight() * rect.getY()) / (rect.getHeight() * rect.getScale()));

		int pitch = 0;
		BYTE* pixels = this->canvas->getPixel(L"" /*this->ui->getTexture()*/, &pitch);

		if(pixels != nullptr){
			int index = (x - scaleX) * 4 + (y - scaleY) * pitch;
			byte b = pixels[index];
			byte g = pixels[index + 1];
			byte r = pixels[index + 2];
			byte a = pixels[index + 3];

			Utility::Delete(pixels);

			if(a != 0 && (r != 0 || g != 0 || b != 0)){
				return true;
			}
		}

		return false;
	}

	bool Input::setCursorPosition(){

		POINT tmp;
		GetCursorPos(&tmp);	// Get the cursor position

		// Calculate the coordinates on the window
		int cursorX = tmp.x - this->rect.getX();
		int cursorY = tmp.y - this->rect.getY();

		// Judge whether the coordinates are in the window
		bool inWidth = cursorX >= 0 && cursorX <= this->rect.getWidth();
		bool inHeight = cursorY >= 0 && cursorY <= this->rect.getHeight();

		if(!inWidth || !inHeight){
			this->cursor = Rect(cursorX, cursorY);
			return true;
		}

		return false;
	}
};