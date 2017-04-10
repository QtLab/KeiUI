#include "Utility.h"
#include <fstream>
#include <locale>
#include <codecvt>
#include <sstream>

string Utility::loadText(string fileName){
	const std::locale empty_locale = std::locale::empty();
	typedef std::codecvt_utf8<wchar_t> converter_type;  //std::codecvt_utf16
	const converter_type* converter = new converter_type;
	const std::locale utf8_locale = std::locale(empty_locale, converter);

	std::wifstream fin(fileName);  //input
	fin.imbue(utf8_locale);

	std::wstringstream buffer;
	buffer << fin.rdbuf();

	return buffer.str();
}