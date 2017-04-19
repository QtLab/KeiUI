#include "Color.h"

namespace KeiUI{

	Color::Color(int r, int g, int b, int a){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	D3DCOLOR Color::rgba(int r, int g, int b, int a){
		return ((D3DCOLOR)(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g &0xff) << 8) | (b & 0xff)));
	}

	D3DCOLOR Color::rgb(int r, int g, int b){
		return Color::rgba(r, g, b, 0xff);
	}

	D3DCOLOR Color::toD3DCOLOR(){
		return Color::rgba(this->r, this->g, this->b, this->a);
	}

	string Color::toString(){
		string tmp = L"R";
		tmp.append(Utility::toString(this->r));

		tmp.append(L"G");
		tmp.append(Utility::toString(this->g));

		tmp.append(L"B");
		tmp.append(Utility::toString(this->b));

		tmp.append(L"A");
		tmp.append(Utility::toString(this->a));

		return tmp;
	}
};