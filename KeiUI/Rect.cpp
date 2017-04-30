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

	bool operator!=(const Rect& left,const Rect& right){
		bool x = left.getX() == right.getX();
		bool y = left.getY() == right.getY();

		bool width = left.getWidth() == right.getWidth();
		bool height = left.getHeight() == right.getHeight();

		bool scale = left.getScale() == right.getScale();

		if(x && y && width && height && scale){
			return true;
		}else{
			return false;
		}
	}

	Rect::Rect(int x, int y, int width, int height, string texture, Color color, float scale) 
		: clip(x, y, width, height), texture(texture), color(color), scale(scale)
	{

	}

	Rect::Rect(Rect &rect)
		: clip(rect.getX(), rect.getY(), rect.getWidth(),rect.getHeight()), texture(rect.getTexture()), color(rect.getColor()), scale(rect.getScale())
	{

	}

	Rect::~Rect(){

	}

	// get
	int Rect::getX() const{
		return this->clip.getX();
	}

	int Rect::getY() const{
		return this->clip.getY();
	}

	int Rect::getWidth() const{
		return this->clip.getWidth();
	}

	int Rect::getHeight() const{
		return this->clip.getHeight();
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
		this->clip.setX(x);
	}

	void Rect::setY(int y){
		this->clip.setY(y);
	}

	void Rect::setWidth(int width){
		this->clip.setWidth(width);
	}

	void Rect::setHeight(int height){
		this->clip.setHeight(height);
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
		string tmp = L"WIDTH";
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

	Clip Rect::toClip(){
		return this->clip;
	}

	bool Rect::empty(){
		return this->clip.empty();
	}
};
