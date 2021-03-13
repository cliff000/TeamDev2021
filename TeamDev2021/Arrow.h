#pragma once
#include "GameObject.h"
#include "Image.h"

class Arrow :
	public GameObject
{
protected:
	Image img;
	bool side; //0‚¾‚Æ¶‚©‚çA1‚¾‚Æ‰E‚©‚ç”ò‚ñ‚Å‚­‚é

public:
	Arrow();
	~Arrow();

	void update();
	void draw();
	void hitAction(GameObject* other);
};
