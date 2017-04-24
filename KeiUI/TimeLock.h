#ifndef _TimeLock_H_
#define _TimeLock_H_

namespace KeiUI{

	class TimeLock{
	private:
		float lastTime;
		float firstTime;

	public:
		TimeLock();
		TimeLock(float firstTime);

		bool isTime(float nowTime);
		void clear();

		bool empty();
	};

};


#endif