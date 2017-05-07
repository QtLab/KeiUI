#ifndef _Label_H_
#define _Label_H_

#include "UI.h"
#include "Font.h"

namespace KeiUI{

	class Label : public UI{
	private:
		Font text;

	public:
		Label(string name, Clip rect);
		~Label();

		virtual void draw(Canvas* canvas);
		void setText(string text);

	};

};

#endif _Label_H_