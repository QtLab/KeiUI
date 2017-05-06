#include "Font.h"

namespace KeiUI{

	Font::Font(string text, Clip rect, int size, Color color, bool bold)
		: text(text), rect(rect), size(size), color(color), bold(bold)
	{

	}

	// Get
	string Font::getText(){
		return this->text;
	}

	Clip Font::getRect(){
		return this->rect;
	}

	int Font::getSize(){
		return this->size;
	}

	Color Font::getColor(){
		return this->color;
	}

	bool Font::getBold(){
		return this->bold;
	}

	// Set
	void Font::setText(string text){
		this->text = text;
	}

	void Font::setRect(Clip rect){
		this->rect = rect;
	}

	void Font::setSize(int size){
		this->size = size;
	}

	void Font::setColor(Color color){
		this->color = color;
	}

	void Font::setBold(bool bold){
		this->bold = bold;
	}


};