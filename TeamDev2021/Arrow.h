#pragma once
#include "GameObject.h"
#include "Image.h"
#include "Sound.h"

class Arrow :
	public GameObject
{
protected:
	Image img;
	Sound se;
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
