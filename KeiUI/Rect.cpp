#include "Rect.h"

namespace KeiUI{

	Rect operator*(const Rect& left,const float& right){
		Rect rect(left.getX() * right, left.getY() * right, left.getWidth(), left.getHeight(), left.getTexture(), left.getColor(), left.getScale() * right);
		return rect;
	}

	Rect operator+(const Rect& left,const Rect& right){	// example: parent + this->getRect();
		int x = left.getX() + right.getX();
		int y = left.getY() + right.getY();

		Rect rect(x, y, right.getWidth(), right.getHeight(), right.getTexture(), right.getColor(), right.getScale());
		return rect;
	}

	Rect::Rect(int x, int y, int width, int height, string texture, Color color, float scale) 
		: x(x), y(y), width(width), height(height), texture(texture), color(color), scale(scale)
	{

	}

	Rect::Rect(Rect &rect)
		: x(rect.getX()), y(rect.getY()), width(rect.getWidth()), height(rect.getHeight()), texture(rect.getTexture()), color(rect.getColor()), scale(rect.getScale())
	{

	}

	Rect::~Rect(){

	}

	// get
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

	string Rect::getTexture() const{
		return this->texture;
	}

	Color Rect::getColor() const{
		return this->color;
	}

	float Rect::getScale() const{
		return this->scale;
	}

	// set
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

	void Rect::setTexture(string texture){
		this->texture = texture;
	}

	void Rect::setColor(Color color){
		this->color = color;
	}

	void Rect::setScale(float scale){
		this->scale = scale;
	}

	string Rect::toString(){
		string tmp = L"X";
		tmp.append(Utility::toString(this->getX()));

		tmp.append(L"Y");
		tmp.append(Utility::toString(this->getY()));

		tmp.append(L"WIDTH");
		tmp.append(Utility::toString(this->getWidth()));

		tmp.append(L"HEIGHT");
		tmp.append(Utility::toString(this->getHeight()));

		tmp.append(L"TEXTURE");
		tmp.append(Utility::toString(this->getTexture()));

		tmp.append(L"COLOR");
		tmp.append(Utility::toString(this->getColor().toString()));

		tmp.append(L"SCALE");
		tmp.append(Utility::toString(this->getScale()));

		return tmp;
	}

	bool Rect::empty(){
		if(this->getX() == 0 && this->getY() == 0 && this->getWidth() == 0 && this->getHeight() == 0){
			return true;
		}else{
			return false;
		}
	}
};
