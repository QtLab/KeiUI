#ifndef _Utility_H_
#define _Utility_H_

#include <d3dx9.h>
#include <string>
#include <sstream>

namespace KeiUI{

	using std::wstring;
	typedef wstring string;

	class Utility{
	public:

		static string loadText(string fileName);

		// Other types are converted to functions of string types
		template<class T>
		static string toString(const T value){
			string tmp;
			std::wstringstream stream;
			stream << value;
			stream >> tmp;

			return tmp;
		}

		// Convert string types to other types of functions
		template<class T>
		static T stringTo(string value){
			T tmp;
			std::wstringstream stream;
			stream << value;
			stream >> tmp;

			return tmp;
		}

		// Release the function of the resource
		template<class T>
		static void Release(T tmp)
		{
			if(tmp)
			{
				tmp->Release();
				tmp = nullptr;
			}
		}

		// Delete the function of the pointer
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

#endif _Utility_H_