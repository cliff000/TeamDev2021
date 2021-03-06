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
	int side; //0だと左、1だと右
	int count = 0;
	int deleteCount = 0;

public:
	Spotter();
	~Spotter();

	void update();
	void draw();
	void hitAction(GameObject* other);
};
