#pragma once
#include "GameObject.h"
#include "Image.h"

class Carriage :
	public GameObject
{
protected:
	int count = 0;
	double nextX = 0;
	double nextY = 0;
	double speedX = 0;
	double speedY = 0;
	Image img;

public:
	Carriage();
	~Carriage();

	void update();
	void draw();
	void hitAction(GameObject* other);
};

