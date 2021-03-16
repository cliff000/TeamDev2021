#include "Carriage.h"
#include "DxLib.h"


Carriage::Carriage()
{
	id = "Carriage";
	w = 100;
	h = 100;
	x = 480;
	y = 610;
	nextX = x;
	nextY = 360;
	col->setPos(-12, 0);
	col->setSize(70, 240);
	img = Image("Resource/Image/carriage.png");
}


Carriage::~Carriage()
{
}

void Carriage::update() {
	
	if (speedX != 0 || speedY != 0) {
		x += speedX;
		y += speedY;
	}
	else if(count++ >= 180){
		int rand = GetRand(100);
		if (rand < 20) nextX = 480, nextY = 360;
		else if (rand < 40) nextX = 480, nextY = 260;
		else if (rand < 45) nextX = 380, nextY = 360;
		else if (rand < 50) nextX = 380, nextY = 260;
		else if (rand < 65) nextX = 580, nextY = 360;
		else if (rand < 70) nextX = 580, nextY = 260;
		count = 0;
	}

	if (abs(x - nextX) < 1 && abs(y - nextY) < 1) {
		speedX = 0;
		speedY = 0;
		x = (int)nextX;
		y = (int)nextY;
	}
	else if (speedX == 0 && speedY == 0) {
		speedX = (nextX - x) / 50.0;
		speedY = (nextY - y) / 50.0;
	}
}

void Carriage::draw() {
	img.draw(x, y, 0.5, 0, true, false);
	//col->draw();
}

void Carriage::hitAction(GameObject* other) {
}