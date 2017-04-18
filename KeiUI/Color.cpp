#include "Color.h"

namespace KeiUI{

	Color::Color(int r, int g, int b, int a){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color::Color(int r, int g, int b){
		new (this)Color(r, g, b, 100);
	}

	D3DCOLOR Color::rgba(int r, int g, int b, int a){
		return ((D3DCOLOR)(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g &0xff) << 8) | (b & 0xff)));
	}

	D3DCOLOR Color::rgb(int r, int g, int b){
		return Color::rgba(r, g, b, 0xff);
	}

};