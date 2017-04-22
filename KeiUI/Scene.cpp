#include "Scene.h"

namespace KeiUI{
	Scene::Scene(){
		this->panel = new Panel(L"panel", Rect(50, 50, 300, 300));
		//this->button = new Button(L"btn1", Rect(10, 10, 120, 120));
	}

	Scene::~Scene(){
		//Utility::Delete(this->button);
		Utility::Delete(this->panel);
	}

	bool Scene::load(){

		// Set parent color
		this->panel->setColor(Color(67, 238, 156));

		return this->panel->load();
	}

	void Scene::update(Input* input){
		this->panel->update(input);
	}

	void Scene::render(){

	}

	void Scene::draw(Canvas* canvas){
		this->panel->draw(canvas);
	}

	void Scene::recover(){
		this->panel->recover();
	}

};