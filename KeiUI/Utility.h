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

		//��������ת�ַ�������
		template<class T>
		static string toString(const T value){
			string tmp;
			std::wstringstream stream;
			stream << value;
			stream >> tmp;

			return tmp;
		}

		//�ַ���ת�������ͺ���
		template<class T>
		static T stringTo(string value){
			T tmp;
			std::wstringstream stream;
			stream << value;
			stream >> tmp;

			return tmp;
		}

		//�ͷź���
		template<class T>
		static void Release(T tmp)
		{
			if(tmp)
			{
				tmp->Release();
				tmp = nullptr;
			}
		}

		//ɾ������
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