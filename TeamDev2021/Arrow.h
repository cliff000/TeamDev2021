#pragma once
#include "GameObject.h"
#include "Image.h"

class Arrow :
	public GameObject
{
protected:
	Image img;
	bool side; //0だと左から、1だと右から飛んでくる

public:
	Arrow();
	~Arrow();

	void update();
	void draw();
	void hitAction(GameObject* other);
};
