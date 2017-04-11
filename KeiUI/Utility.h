#ifndef _Utility_H_
#define _Utility_H_

#include <string>
using std::wstring;
typedef wstring string;

class Utility{
public:

	static string loadText(string fileName);

	//ÊÍ·Åº¯Êý
	template<class T>
	static void Release(T tmp)
	{
		if(tmp)
		{
			tmp->Release();
			tmp = nullptr;
		}
	}

	//É¾³ýº¯Êý
	template<class T>
	static void Delete(T tmp)
	{
		if(tmp)
		{
			delete tmp;
			tmp = nullptr;
		}
	}

	template<class T>
	struct Vector2{
		T x, y;

		Vector2(T x, T y) : x(x), y(y){

		}

		Vector2() : Vector2(0, 0){

		}

		void operator =(Vector2 value){
			this->x = value.x;
			this->y = value.y;
		}

		void operator /(Vector2 value){
			this->x /= value.x;
			this->y /= value.y;
		}
	};
};

#endif