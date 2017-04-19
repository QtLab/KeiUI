#include "Rect.h"

namespace KeiUI{

	Rect operator+(const Rect& left,const Rect& right){
		int x = left.getX() + right.getX();
		int y = left.getY() + right.getY();

		Rect rect(x, y, right.getWidth(), right.getHeight());
		return rect;
	}

	Rect::Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height){

	}

	Rect::Rect(Rect &rect) : x(rect.getX()), y(rect.getY()), width(rect.getWidth()), height(rect.getHeight()){

	}

	Rect::Rect() : x(0), y(0), width(0), height(0){

	}

	Rect::~Rect(){

	}

	int Rect::getX() const{
		return this->x;
	}

	int Rect::getY() const{
		return this->y;
	}

	int Rect::getWidth() const{
		return this->width;
	}

	int Rect::getHeight() const{
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
