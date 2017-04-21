#include "App.h"
#include "Rect.h"
#include "Button.h"

namespace KeiUI{

	App::App(string name, HINSTANCE hInstance) : Window(name, hInstance){
		this->uiTest = new UI(L"form", Rect(50, 50, 300, 300));

	}

	App::~App(){
		Utility::Delete(this->uiTest);
	}

	bool App::load(){

		// Set parent color
		this->uiTest->setColor(Color(67, 238, 156));

		Button* button = new Button(L"btn1", Rect(10, 10, 120, 120));
		button->setTexture(L"Resource/1.png");

		this->uiTest->add(button);

		return true;
	}

	void App::update(Input* input){
		this->uiTest->update(input);
	}

	void App::render(){

	}

	void App::draw(Canvas* canvas){
		this->uiTest->draw(canvas);
	}

	void App::recover(){

	}

};
