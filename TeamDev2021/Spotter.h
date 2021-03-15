#pragma once
#include "GameObject.h"
#include "Image.h"

class Spotter :
	public GameObject
{
protected:
	Image img;
	int side; //0だと左、1だと右

public:
	Spotter();
	~Spotter();

	void update();
	void draw();
	void hitAction(GameObject* other);
};
