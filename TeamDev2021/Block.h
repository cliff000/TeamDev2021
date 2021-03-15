#pragma once
#include "GameObject.h"
#include "Image.h"

class Block :
	public GameObject
{
protected:
	int alpha;
	int count;
	Image img;

public:
	Block();
	Block(int x, int y);
	Block(int x, int y, int w, int h);
	~Block();

	void init();
	void update();
	void draw();
	void hitAction(GameObject* other);
};
