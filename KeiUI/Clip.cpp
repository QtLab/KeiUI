#include "Clip.h"

namespace KeiUI{

	Clip::Clip(int x, int y, int width, int height): x(x), y(y), width(width), height(height){

	}

	RECT Clip::toRECT(){
		RECT rect;
		rect.left = this->getX();
		rect.right = this->getX() + this->getWidth();
		rect.top = this->getY();
		rect.bottom = this->getY() + this->getHeight();

		return rect;
	}

	// get
	int Clip::getX() const{
		return this->x;
	}

	int Clip::getY() const{
		return this->y;
	}

	int Clip::getWidth() const{
		return this->width;
	}

	int Clip::getHeight() const{
		return this->height;
	}

	// set
	void Clip::setX(int x){
		this->x = x;
	}

	void Clip::setY(int y){
		this->y = y;
	}

	void Clip::setWidth(int width){
		this->width = width;
	}

	void Clip::setHeight(int height){
		this->height = height;
	}

	bool Clip::empty(){
		if(this->getX() == 0 && this->getY() == 0 && this->getWidth() == 0 && this->getHeight() == 0){
			return true;
		}else{
			return false;
		}
	}
};