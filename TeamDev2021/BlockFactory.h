#pragma once
#include "GameObject.h"

class BlockFactory :
	public GameObject
{
	int* line_x;
	int* line_y;
	int line_length;
	int pre_block_num;

public:
	BlockFactory();
	BlockFactory(int* line, int* line_y, int length);
	~BlockFactory();

	void update();
	void draw();
};
