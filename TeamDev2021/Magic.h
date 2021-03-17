#pragma once
#include "GameObject.h"
#include "Image.h"

class Magic :
	public GameObject
{
protected:
	int count = 0;
	Image img;

public:
	Magic();
	Magic(int x, int y);
	Magic(int x, int y, int w, int h);
	~Magic();

	void init();
	void update();
	void draw();
	void hitAction(GameObject* other);
};
