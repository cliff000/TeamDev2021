#include "Arrow.h"
#include "DxLib.h"


Arrow::Arrow()
{
	side = GetRand(1);
	init();
}

Arrow::Arrow(int side)
{
	this->side = side;
	init();
}


Arrow::~Arrow()
{
}


void Arrow::init() {
	id = "Arrow";
	w = 100;
	h = 100;
	x = side * (WINDOWSIZE_X + w) - w / 2;
	y = GetRand(WINDOWSIZE_Y - 100 - h) + 100 + h / 2;
	col->setPos(0, 0);
	col->setSize(80, 5);
	img = Image("Resource/Image/arrow.png");
}

void Arrow::update() {
	x += 6 - side * 12;
	if (x <= -w || x >= WINDOWSIZE_X + w)
		mgr->del(this);
}

void Arrow::draw() {
	img.draw(x, y, 1, PI/2 - side*PI, true, false);
	//col->draw();
}

void Arrow::hitAction(GameObject* other) {
	if (other->getID() == "Carriage" || other->getID() == "Block")
		mgr->del(this);
}