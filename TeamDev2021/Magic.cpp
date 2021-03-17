#include "Magic.h"
#include "DxLib.h"

#define ALPHA_DEF 160


Magic::Magic()
{
	init();

}

Magic::Magic(int x, int y)
{
	init();
	this->x = x;
	this->y = y;
}

Magic::Magic(int x, int y, int w, int h)
{
	init();
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	col->setSize(w, h);
}



Magic::~Magic()
{
}


void Magic::init() {
	id = "Magic";
	w = 50;
	h = 50;
	x = 0;
	y = 0;
	col->setPos(0, 0);
	col->setSize(50, 50);
	//img = Image("Resource/Image/impact.jpg");
}

void Magic::update() {
	if (count++ >= 2) {
		mgr->del(this);
	}
}

void Magic::draw() {
	col->draw();
}

void Magic::hitAction(GameObject* other) {
}