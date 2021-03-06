#pragma once
#include "GameObject.h"
#include "Sound.h"

class Block :
	public GameObject
{
protected:
	int alpha;
	int count;
	int color = 0x1CFFFF;
	Sound se;

public:
	Block();
	Block(int x, int y);
	Block(int x, int y, int w, int h);
	~Block();

	void init();
	void update();
	void draw();
	void hitAction(GameObject* other);
	void setColor(int color);
};
