#ifndef _Event_H_
#define _Event_H_

namespace KeiUI{

	template<class T>
	class Event{
	private:
		T* object;
		typedef void (T::*Function)(void);
		Function function;

	public:
		Event(T* object, Function function) : object(object), function(function){

		}

		void clickEvent(){
			(this->object->*(function))();
		}
	};

};

#endif _Event_H_