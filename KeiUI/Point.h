#ifndef _Point_H_
#define _Point_H_

template<class T>
class Point{
public:
	T x, y;

public:
	Point(T x, T y);
	Point();

	void operator =(Point value){
		this->x = value.x;
		this->y = value.y;
	}

	void operator /(Point value){
		this->x /= value.x;
		this->y /= value.y;
	}
};

#endif