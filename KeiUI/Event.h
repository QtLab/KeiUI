#ifndef _Event_H_
#define _Event_H_

#include "UI.h"
#include "Input.h"

namespace KeiUI{

	class UI;
	typedef void (UI::*Function)(Input* input);

	class Event{
	public:
		enum EventType{
			MouseLeftClickEvent,
			MouseRightClickEvent,
			MouseLeftDragEvent,
			MouseRightDragEvent
		};

	private:
		UI* object;
		Function callback;
		EventType type;

	public:

		Event(){

		}

		Event(UI* object, Function callback, EventType type) : object(object), callback(callback), type(type){

		}

		void callEvent(Input* input){
			if(this->object != nullptr && this->callback != nullptr){
				(this->object->*(callback))(input);
			}
		}

		EventType getType(){
			return this->type;
		}
	};

};

#endif _Event_H_