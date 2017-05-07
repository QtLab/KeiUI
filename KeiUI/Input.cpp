#include "Input.h"
#include <Windows.h>
#include "Window.h"

namespace KeiUI{

	string Input::inputTmp = L"";

	Input::Input(Clip rect, Canvas* canvas) : rect(rect), canvas(canvas), timeLock(10), isInput(false){

	}

	string Input::inputText(){
		if(Input::inputTmp != L""){
			string tmp = Input::inputTmp;
			Input::inputTmp = L"";

			return tmp;
		}

		return L"";
	}

	bool Input::keyDown(int vKey){

		if(this->getState(vKey)){
			return true;
		}

		return false;
	}

	bool Input::mouseLeftDown(){

		// Need to set the UI data before using

		if(this->inArea()){
			if(this->getState(VK_LBUTTON)){
				return this->pixelDetection();
			}
		}

		return false;
	}

	bool Input::mouseRightDown(){

		// Need to set the UI data before using

		if(this->inArea()){
			if(this->getState(VK_RBUTTON)){
				return this->pixelDetection();
			}
		}

		return false;
	}

	bool Input::mouseMoveOver(){

		// Need to set the UI data before using

		if(this->inArea()){
			return true;
		}
	}

	bool Input::mouseMoveOut(){

		// Need to set the UI data before using
		
		if(this->leaveArea()){
			return true;
		}
		
		return false;
	}

	void Input::setUI(Rect rectUI){
		this->lastUI = this->rectUI;	// Cache
		this->rectUI = rectUI;	// Need to set the UI data before using
	}

	bool Input::emptyUI(){
		return this->rectUI.empty();
	}

	int Input::getCursorX(){
		return this->rectCursor.getX();
	}

	int Input::getCursorY(){
		return this->rectCursor.getY();
	}
	
	int Input::getLastX(){
		return this->lastCursor.getX();
	}

	int Input::getLastY(){
		return this->lastCursor.getY();
	}

	bool Input::getState(int vKey){

		if((GetAsyncKeyState(vKey) & 0x8000)){
			if(this->timeLock.isTime(Window::refreshTime)){
				return true;
			}
		}

		return false;
	}

	bool Input::inArea(){

		float right = rectUI.getWidth() * rectUI.getScale();
		float bottom = rectUI.getHeight() * rectUI.getScale();

		bool existX = rectUI.getX() <= this->rectCursor.getX() && this->rectCursor.getX() <= rectUI.getX() + right;
		bool existY = rectUI.getY() <= this->rectCursor.getY() && this->rectCursor.getY() <= rectUI.getY() + bottom;

		if(existX && existY){
			return true;
		}

		return false;
	}

	bool Input::leaveArea(){

		float right = rectUI.getWidth() * rectUI.getScale();
		float bottom = rectUI.getHeight() * rectUI.getScale();

		bool lastX = rectUI.getX() <= this->lastCursor.getX() && this->lastCursor.getX() <= rectUI.getX() + right;
		bool lastY = rectUI.getY() <= this->lastCursor.getY() && this->lastCursor.getY() <= rectUI.getY() + bottom;

		if(!(this->inArea()) && lastX && lastY){
			return true;
		}

		return false;

	}

	bool Input::pixelDetection(){

		int x = (int)((rectUI.getWidth() * this->rectCursor.getX()) / (rectUI.getWidth() * rectUI.getScale()));
		int y = (int)((rectUI.getHeight() * this->rectCursor.getY()) / (rectUI.getHeight() * rectUI.getScale()));

		int scaleX = (int)((rectUI.getWidth() * rectUI.getX()) / (rectUI.getWidth() * rectUI.getScale()));
		int scaleY = (int)((rectUI.getHeight() * rectUI.getY()) / (rectUI.getHeight() * rectUI.getScale()));

		int pitch = 0;
		BYTE* pixels = nullptr;

		if(this->rectUI.getTexture() != L""){
			pixels = this->canvas->getPixel(this->rectUI.getTexture(), &pitch);
		}else{
			pixels = this->canvas->getPixel(this->rectUI.toString(), &pitch);
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

		this->rectUI = Rect();	// Clear UI data

		POINT tmp;
		GetCursorPos(&tmp);	// Get the cursor position

		// Calculate the coordinates on the window
		int cursorX = tmp.x - this->rect.getX();
		int cursorY = tmp.y - this->rect.getY();

		// Judge whether the coordinates are in the window
		bool inWidth = cursorX >= 0 && cursorX <= this->rect.getWidth();
		bool inHeight = cursorY >= 0 && cursorY <= this->rect.getHeight();

		if(inWidth && inHeight){
			this->lastCursor = this->rectCursor;
			this->rectCursor = Clip(cursorX, cursorY);
			return true;
		}

		return false;
	}
};