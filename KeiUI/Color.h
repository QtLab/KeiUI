#ifndef _Color_H_
#define _Color_H_

#include "Utility.h"

namespace KeiUI{

	class Color{
	public:
		int r, g, b, a;

		Color(int r, int g, int b, int a);
		Color(int r, int g, int b);

		static D3DCOLOR rgba(int r, int g, int b, int a);
		static D3DCOLOR rgb(int r, int g, int b);

	};

};


#endif _Color_H_