#include "Scene1.h"
#include "Window.h"

namespace KeiUI{

	Scene1::Scene1(string name, Rect rect) : UI(name, rect) {
		this->button = new Button(L"btn1", Rect(10, 10, 120, 120));
	}

	Scene1::~Scene1(){
		Utility::Delete(this->button);
	}

	bool Scene1::load(){
		this->button->setTexture(L"Resource/1.png");
		this->button->setEvent((UI*)this, (Function)(&Scene1::buttonClickEvent));

		this->add(button);

		return true;
	}

	void Scene1::update(Input* input){
		UI::update(input);
	}

	void Scene1::render(){

	}

	void Scene1::draw(Canvas* canvas){
		UI::draw(canvas);
	}

	void Scene1::recover(){

	}

	void Scene1::buttonClickEvent(){
		Window::messageBox(nullptr, L"Event Test", this->button->getName(), MB_ICONSTOP);
	}
};