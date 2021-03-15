#include "Carriage.h"
#include "DxLib.h"


Carriage::Carriage()
{
	id = "Carriage";
	w = 100;
	h = 100;
	x = WINDOWSIZE_X / 2;
	y = 600;
	col->setPos(-12, 0);
	col->setSize(70, 240);
	img = Image("Resource/Image/carriage.png");
}


Carriage::~Carriage()
{
}

void Carriage::update() {
	if (y > 360) {
		y -= 3;
	}
}

void Carriage::draw() {
	img.draw(x, y, 0.5, 0, true, false);
	//col->draw();
}

void Carriage::hitAction(GameObject* other) {
}