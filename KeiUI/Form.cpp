#include "Form.h"

namespace KeiUI{

	Form::Form(string name, Window* window) : UI(name, Clip()), window(window) {

	}

	Form::~Form(){

	}

};