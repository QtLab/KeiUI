#include "TimeLock.h"

namespace KeiUI{

	TimeLock::TimeLock() : lastTime(0), firstTime(0){

	}

	TimeLock::TimeLock(float firstTime) : lastTime(0), firstTime(firstTime){

	}

	bool TimeLock::isTime(float nowTime){
		this->lastTime += nowTime;

		if (this->lastTime >= this->firstTime)
		{
			this->lastTime -= this->firstTime;
			return true;
		}
		else
		{
			return false;
		}
	}

	void TimeLock::clear(){
		this->firstTime = 0;
	}

	bool TimeLock::empty(){
		if(this->firstTime != 0){
			return false;
		}else{
			return true;
		}
	}

};
