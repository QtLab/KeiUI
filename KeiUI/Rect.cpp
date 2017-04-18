#include "Rect.h"

namespace KeiUI{

	Rect::Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height){

	}

	Rect::~Rect(){

	}

	int Rect::getX(){
		return this->x;
	}

	int Rect::getY(){
		return this->y;
	}

	int Rect::getWidth(){
		return this->width;
	}

	int Rect::getHeight(){
		return this->height;
	}

	void Rect::setX(int x){
		this->x = x;
	}

	void Rect::setY(int y){
		this->y = y;
	}

	void Rect::setWidth(int width){
		this->width = width;
	}

	void Rect::setHeight(int height){
		this->height = height;
	}

};
