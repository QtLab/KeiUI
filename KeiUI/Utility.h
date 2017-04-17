#ifndef _Utility_H_
#define _Utility_H_

#include <string>

namespace KeiUI{

	using std::wstring;
	typedef wstring string;

	class Utility{
	public:

		static string loadText(string fileName);

		//ÊÍ·Åº¯Êý
		template<class T>
		static void Release(T tmp)
		{
			if(tmp)
			{
				tmp->Release();
				tmp = nullptr;
			}
		}

		//É¾³ýº¯Êý
		template<class T>
		static void Delete(T tmp)
		{
			if(tmp)
			{
				delete tmp;
				tmp = nullptr;
			}
		}

	};

};

#endif