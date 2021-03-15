#include "Spotter.h"
#include "DxLib.h"
#include "Arrow.h"


Spotter::Spotter()
{
	id = "Spotter";
	w = 100;
	h = 100;
	x = -500;
	y = -500;
	side = GetRand(1);
	x = side * (WINDOWSIZE_X + w) - w / 2;
	y = GetRand(WINDOWSIZE_Y - 100 - h) + 100 + h / 2;
	col->setSize(50, 50);

	if (side == 0) {
		col->setPos(5, -5);
		img = Image("Resource/Image/spotter_L.png");
	}
	else {
		col->setPos(-5, -5);
		img = Image("Resource/Image/spotter_R.png");
	}
}


Spotter::~Spotter()
{
}

void Spotter::update() {
	if (x <= WINDOWSIZE_X*0.1 || x >= WINDOWSIZE_X*0.9)
		x += 3 - side * 6;

	if (count++ >= 120) {
		mgr->add(new Arrow(side));
		count = 0;
	}
}

void Spotter::draw() {
	img.draw(x, y, 0.2, 0, true, false);
	//col->draw();
}

void Spotter::hitAction(GameObject* other) {
}