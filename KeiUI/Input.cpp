#include "Input.h"
#include <Windows.h>

namespace KeiUI{

	Input::Input(Rect rect, Canvas* canvas) : rect(rect), canvas(canvas){

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

		float right = ui.getWidth() * ui.getScale();
		float bottom = ui.getHeight() * ui.getScale();

		int x = ui.getX();
		int y = ui.getY();
		int width = ui.getX() + right;
		int height = ui.getY() + bottom;
		int cX = cursor.getX();
		int cY = cursor.getY();

		bool existX = ui.getX() <= this->cursor.getX() && this->cursor.getX() <= ui.getX() + right;
		bool existY = ui.getY() <= this->cursor.getY() && this->cursor.getY() <= ui.getY() + bottom;

		if(existX && existY){
			return true;
		}

		return false;
	}

	bool Input::pixelDetection(){

		int x = (int)((ui.getWidth() * this->cursor.getX()) / (ui.getWidth() * ui.getScale()));
		int y = (int)((ui.getHeight() * this->cursor.getY()) / (ui.getHeight() * ui.getScale()));

		int scaleX = (int)((ui.getWidth() * ui.getX()) / (ui.getWidth() * ui.getScale()));
		int scaleY = (int)((ui.getHeight() * ui.getY()) / (ui.getHeight() * ui.getScale()));

		int pitch = 0;
		BYTE* pixels = nullptr;

		if(this->ui.getTexture() != L""){
			pixels = this->canvas->getPixel(this->ui.getTexture(), &pitch);
		}else{
			pixels = this->canvas->getPixel(this->ui.toString(), &pitch);
		}

		if(pixels != nullptr){
			int index = (x - scaleX) * 4 + (y - scaleY) * pitch;
			byte b = pixels[index];
			byte g = pixels[index + 1];
			byte r = pixels[index + 2];
			byte a = pixels[index + 3];

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

		if(inWidth && inHeight){
			this->cursor = Rect(cursorX, cursorY);
			return true;
		}

		return false;
	}
};