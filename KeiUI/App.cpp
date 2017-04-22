#include "App.h"
#include "Rect.h"

namespace KeiUI{

	App::App(string name, HINSTANCE hInstance) : Window(name, hInstance){

	}

	App::~App(){

	}

	bool App::load(){
		return this->scene.load();
	}

	void App::update(Input* input){
		this->scene.update(input);
	}

	void App::render(){
		this->scene.render();
	}

	void App::draw(Canvas* canvas){
		this->scene.draw(canvas);
	}

	void App::recover(){
		this->scene.recover();
	}

};
