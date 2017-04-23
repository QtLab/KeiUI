#ifndef _Event_H_
#define _Event_H_

#include "UI.h"
#include "Input.h"

namespace KeiUI{

	class UI;
	typedef void (UI::*Function)();
	typedef void (UI::*Callback)(Input* input);

	class Event{
	public:
		enum EventType{
			MouseLeftClickEvent,
			MouseRightClickEvent,
			MouseLeftDragEvent
		};

	private:
		UI* object;
		Function function;
		Callback callback;
		EventType type;

	public:

		Event(){

		}

		Event(UI* object, Function function, EventType type) : object(object), function(function), type(type){

		}

		Event(UI* object, Callback callback, EventType type) : object(object), callback(callback), type(type){

		}

		void callEvent(){
			if(this->object != nullptr && this->function != nullptr){
				(this->object->*(function))();
			}
		}

		void callEvent(Input* input){
			if(this->object != nullptr && this->function != nullptr){
				(this->object->*(callback))(input);
			}
		}

		EventType getType(){
			return this->type;
		}
	};

};

#endif _Event_H_