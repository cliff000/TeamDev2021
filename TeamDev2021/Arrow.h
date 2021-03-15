#pragma once
#include "GameObject.h"
#include "Image.h"

class Arrow :
	public GameObject
{
protected:
	Image img;
	int side; //0だと左から、1だと右から飛んでくる

public:
	Arrow();
	Arrow(int side);
	~Arrow();

	void init();
	void update();
	void draw();
	void hitAction(GameObject* other);
};
