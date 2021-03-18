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
	se_damage = Sound("Resource/Sound/se_damage.ogg");
	se_horse = Sound("Resource/Sound/se_horse_long.ogg");
	se_horse.changeVolume(255);
}


Carriage::~Carriage()
{
}

void Carriage::update() {
	
	if (speedX != 0 || speedY != 0) {  //speed‚ª‚ ‚ê‚ÎˆÚ“®
		x += speedX;
		y += speedY;
		se_horse.play(DX_PLAYTYPE_BACK, true);
	}
	else if(count++ >= 180){  //ƒ‰ƒ“ƒ_ƒ€‚ÉˆÚ“®æ‚ğŒˆ‚ß‚é
		int rand = GetRand(100);
		if (rand < 20) nextX = 480, nextY = 360;
		else if (rand < 40) nextX = 480, nextY = 260;
		else if (rand < 45) nextX = 380, nextY = 360;
		else if (rand < 50) nextX = 380, nextY = 260;
		else if (rand < 55) nextX = 580, nextY = 360;
		else if (rand < 60) nextX = 580, nextY = 260;
		count = 0;
	}

	//nextX,nextY‚É‚ä‚Á‚­‚èˆÚ“®‚·‚é‚æ‚¤‚É‚·‚éˆ—
	if (abs(x - nextX) < 1 && abs(y - nextY) < 1) {
		speedX = 0;
		speedY = 0;
		x = (int)nextX;
		y = (int)nextY;
		se_horse.stop();
	}
	else if (speedX == 0 && speedY == 0) {
		speedX = (nextX - x) / 50.0;
		speedY = (nextY - y) / 50.0;
	}

	//–î‚É“–‚½‚é‚Æ“_–Å
	if (hitCount != 0) {
		if (hitCount % 16 < 8) {
			alpha -= 10;
		}
		else {
			alpha += 10;
		}

		if (hitCount++ >= 80) hitCount = 0, alpha = 255;
	}
}

void Carriage::draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	img.draw(x, y, 0.5, 0, true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//col->draw();
}

void Carriage::setNextPos(int x, int y) {
	nextX = x;
	nextY = y;
}

void Carriage::hitAction(GameObject* other) {
	if (other->getID() == "Arrow" && hitCount == 0) {
		if (speed > 1) {
			speed -= 0.5;
		}
		hitCount = 1;
		alpha = 158;
		se_damage.play(DX_PLAYTYPE_BACK, true);
	}
		
}