#pragma once
#include "GameObject.h"
#include "Image.h"
#include "Sound.h"

class Spotter :
	public GameObject
{
protected:
	Image img;
	Image effect;
	Sound se;
	int side; //0ÇæÇ∆ç∂ÅA1ÇæÇ∆âE
	int count = 0;
	int deleteCount = 0;

public:
	Spotter();
	~Spotter();

	void update();
	void draw();
	void hitAction(GameObject* other);
};
