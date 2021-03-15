#include "Arrow.h"
#include "DxLib.h"


Arrow::Arrow()
{
	id = "Arrow";
	w = 100;
	h = 100;
	side = GetRand(1);
	x = side * (WINDOWSIZE_X + w) - w/2;
	y = GetRand(WINDOWSIZE_Y - h) + h / 2;
	col->setPos(0, 0);
	col->setSize(80, 5);
	img = Image("Resource/Image/arrow.png");
}


Arrow::~Arrow()
{
}

void Arrow::update() {
	x += 8 - side * 16;
	if (x <= -w || x >= WINDOWSIZE_X + w)
		mgr->del(this);
}

void Arrow::draw() {
	img.draw(x, y, 1, PI/2 - side*PI, true, true);
	//col->draw();
}

void Arrow::hitAction(GameObject* other) {
	if (other->getID() == "Carriage" || other->getID() == "Block")
		mgr->del(this);
}