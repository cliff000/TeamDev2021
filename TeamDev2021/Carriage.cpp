#include "Carriage.h"
#include "DxLib.h"


Carriage::Carriage()
{
	id = "Carriage";
	w = 100;
	h = 100;
	x = WINDOWSIZE_X / 2;
	y = 360;
	col->setPos(10, 0);
	col->setSize(60, 200);
	img = Image("Resource/Image/carriage.png");
}


Carriage::~Carriage()
{
}

void Carriage::update() {
}

void Carriage::draw() {
	img.draw(x, y, 0.5, 0, true, true);
	col->draw();
}

void Carriage::hitAction(GameObject* other) {
}