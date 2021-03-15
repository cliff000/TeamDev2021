#include "Spotter.h"
#include "DxLib.h"


Spotter::Spotter()
{
	id = "Spotter";
	w = 100;
	h = 100;
	x = -500;
	y = -500;
	side = GetRand(1);
	x = side * (WINDOWSIZE_X + w) - w / 2;
	y = GetRand(WINDOWSIZE_Y - h) + h / 2;
	col->setSize(50, 50);

	if (side == 0) {
		col->setPos(5, -5);
		img = Image("Resource/Image/spotter_R.png");
	}
	else {
		col->setPos(-5, -5);
		img = Image("Resource/Image/spotter_L.png");
	}
}


Spotter::~Spotter()
{
}

void Spotter::update() {
	if (x <= WINDOWSIZE_X*0.1 || x >= WINDOWSIZE_X*0.9)
		x += 4 - side * 8;
}

void Spotter::draw() {
	img.draw(x, y, 0.2, 0, true, true);
	//col->draw();
}

void Spotter::hitAction(GameObject* other) {
}