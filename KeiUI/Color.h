#ifndef _Color_H_
#define _Color_H_

#include "Utility.h"

namespace KeiUI{

	class Color{
	public:
		int r, g, b, a;

		Color(int r = 255, int g = 255, int b = 255, int a = 255);

		static D3DCOLOR rgba(int r, int g, int b, int a);
		static D3DCOLOR rgb(int r, int g, int b);

		D3DCOLOR toD3DCOLOR();
		string toString();

		bool empty();
	};

};


#endif _Color_H_