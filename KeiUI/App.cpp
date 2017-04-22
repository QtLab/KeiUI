#include "App.h"
#include "Rect.h"

namespace KeiUI{

	App::App(string name, HINSTANCE hInstance) : Window(name, hInstance){
		this->panel = new Scene1(L"panel", Rect(50, 50, 300, 300));
	}

	App::~App(){
		Utility::Delete(this->panel);
	}

	bool App::load(){

		// Set parent color
		this->panel->setColor(Color(67, 238, 156));

		return this->panel->load();
	}

	void App::update(Input* input){
		this->panel->update(input);
	}
	
	void App::render(){
		this->panel->render();
	}
	
	void App::draw(Canvas* canvas){
		this->panel->draw(canvas);
	}

	void App::recover(){
		this->panel->recover();
	}

};
