#include "App.h"
#include "Rect.h"

namespace KeiUI{

	App::App(string name, HINSTANCE hInstance) : Window(name, hInstance){

	}

	App::~App(){
		Utility::Delete(this->form1);
	}

	bool App::load(){
		this->form1 = new Form1(L"form1", this);

		this->form1->setColor(Color(255, 219, 255));
		this->bindForm(this->form1);

		return this->form1->load();
	}

	void App::update(Input* input){
		this->form1->update(input);
	}
	
	void App::render(){
		this->form1->render();
	}
	
	void App::draw(Canvas* canvas){
		this->form1->draw(canvas);
	}

	void App::recover(){
		this->form1->recover();
	}

	void App::bindForm(UI* form){
		form->setWidth(this->rect.getWidth());
		form->setHeight(this->rect.getHeight());
	}

};