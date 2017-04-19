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
		this->uiTest->setColor(67, 238, 156);

		Button* button = new Button(L"btn1", Rect(10, 10, 100, 100));
		button->setTexture(this->loadTexture(L"Resource/1.png"));

		this->uiTest->add(button);

		return true;
	}

	void App::update(){

	}

	void App::render(){

	}

	void App::draw(const Canvas* canvas){
		this->uiTest->draw(canvas);
	}

	void App::recover(){

	}

};
