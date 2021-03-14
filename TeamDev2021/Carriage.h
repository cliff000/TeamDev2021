#pragma once
#include "GameObject.h"
#include "Image.h"

class Carriage :
	public GameObject
{
protected:
	Image img;

public:
	Carriage();
	~Carriage();

	void update();
	void draw();
	void hitAction(GameObject* other);
};

