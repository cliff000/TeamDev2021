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
	//線の位置にブロック追加
	pre_block_num = 0;
	for (int i = 1; i < line_length; i++) {
		int dx = abs((int)(line_x[pre_block_num] - line_x[i]));
		int dy = abs((int)(line_y[pre_block_num] - line_y[i]));
		if (dx >= 50 || dy >= 50) {
			int block_x = (line_x[pre_block_num] + line_x[i]) / 2;
			int block_y = (line_y[pre_block_num] + line_y[i]) / 2;
			int block_w = (dx < 50) ? 50 : dx;
			int block_h = (dy < 50) ? 50 : dy;
			mgr->add(new Block(block_x, block_y, block_w, block_h));
			pre_block_num = i;
		}
	}

	mgr->del(this);
}

void BlockFactory::draw() {
}
