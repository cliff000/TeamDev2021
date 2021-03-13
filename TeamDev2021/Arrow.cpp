#include "Arrow.h"
#include "DxLib.h"


Arrow::Arrow()
{
	id = "Arrow";
	w = 100;
	h = 100;
	side = GetRand(1);
	x = side * (windowW + w) - w/2;
	y = GetRand(windowH - h) + h / 2;
	col->setPos(0, 0);
	col->setSize(80, 5);
	img = Image("Resource/Image/arrow.png");
}


Arrow::~Arrow()
{
}

void Arrow::update() {
	x += 4 - side*8;
	if (x <= -w || x >= windowW+w)
		mgr->del(this);
}

void Arrow::draw() {
	img.draw(x, y, 1, PI/2 - side*PI, true, true);
	//col->draw();
}

void Arrow::hitAction(GameObject* other) {
	if (other->getID() == "Carriage")
		mgr->del(this);
}