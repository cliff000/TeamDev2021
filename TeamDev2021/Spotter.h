#pragma once
#include "GameObject.h"
#include "Image.h"

class Spotter :
	public GameObject
{
protected:
	Image img;
	int side; //0ÇæÇ∆ç∂ÅA1ÇæÇ∆âE

public:
	Spotter();
	~Spotter();

	void update();
	void draw();
	void hitAction(GameObject* other);
};
