#include "BlockFactory.h"
#include "Block.h"


BlockFactory::BlockFactory()
{
}

BlockFactory::BlockFactory(int* line_x, int* line_y,  int length)
{
	this->line_x = line_x;
	this->line_y = line_y;
	this->line_length = length;
}


BlockFactory::~BlockFactory()
{
}


void BlockFactory::update() {
	mgr->add(new Block(line_x[1], line_y[1]));
	pre_block_num = 1;

	for (int i = 2; i <= line_length; i++) {
		int dx = abs((int)(line_x[pre_block_num] - line_x[i]));
		int dy = abs((int)(line_y[pre_block_num] - line_y[i]));
		if (dx >= 50 && dy >= 50) {
			mgr->add(new Block(line_x[i], line_y[i]));
			pre_block_num = i;
		}
	}

	mgr->del(this);
}

void BlockFactory::draw() {
}
