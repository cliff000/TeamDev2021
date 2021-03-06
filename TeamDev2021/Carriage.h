#pragma once
#include "GameObject.h"
#include "Image.h"
#include "Sound.h"

class Carriage :
	public GameObject
{
protected:
	int count = 0;
	double nextX = 0;
	double nextY = 0;
	double speedX = 0;
	double speedY = 0;
	int hitCount = 0;
	int alpha = 255;
	Image img;
	Sound se_damage;
	Sound se_horse;

public:
	Carriage();
	~Carriage();

	void update();
	void draw();
	void setNextPos(int x, int y);
	void hitAction(GameObject* other);
};

