#ifndef _Textbox_H_
#define _Textbox_H_

#include "UI.h"
#include "Label.h"

namespace KeiUI{

	class Textbox : public UI{
	private:
		Label* text;

	public:
		Textbox(string name, Clip rect);
		~Textbox();

		virtual bool load();
		virtual void update(Input* input);

		void setText(string text);

	};

};

#endif _Textbox_H_