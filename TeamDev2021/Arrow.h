#pragma once
#include "GameObject.h"
#include "Image.h"

class Arrow :
	public GameObject
{
protected:
	Image img;
	int side; //0‚¾‚Æ¶‚©‚çA1‚¾‚Æ‰E‚©‚ç”ò‚ñ‚Å‚­‚é

public:
	Arrow();
	Arrow(int side);
	~Arrow();

	void init();
	void update();
	void draw();
	void hitAction(GameObject* other);
};
