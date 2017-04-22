#ifndef _Form_H_
#define _Form_H_

#include "Panel.h"

namespace KeiUI{

	class Scene{
	private:
		Panel* panel;

	public:
		Scene();
		~Scene();

		virtual bool load();
		virtual void update(Input* input);
		virtual void render();
		virtual void draw(Canvas* canvas);
		virtual void recover();

	};

};

#endif _Form_H_