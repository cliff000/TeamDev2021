#include "BlockFactory.h"
#include "Block.h"
#include <math.h>
#include "DxLib.h"


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
	bool circleflag = false;

	//円形かどうかの判定
	for (int i = 0; i < line_length / 2; i++) {
		for (int j = i + line_length / 2; j < line_length; j++) {
			if (abs(line_x[i] - line_x[j]) <= 20 && abs(line_y[i] - line_y[j]) <= 20) {
				circleflag = true;
				break;
			}
		}
		if (circleflag) break;
	}

	if (circleflag) {
		//円形なら攻撃位置に赤ブロック
		int min_x = line_x[0];
		int min_y = line_y[0];
		int max_x = line_x[0];
		int max_y = line_y[0];
		for (int i = 1; i < line_length; i++) {
			if (line_x[i] < min_x) min_x = line_x[i];
			if (line_y[i] < min_y) min_y = line_y[i];
			if (line_x[i] > max_x) max_x = line_x[i];
			if (line_y[i] > max_y) max_y = line_y[i];
		}
		Block* b = new Block((min_x + max_x) / 2, (min_y + max_y) / 2, max_x - min_x, max_y - min_y);
		b->setColor(0xff0000);
		mgr->add(b);
	}
	else {
		//線の位置にブロック追加
		pre_block_num = 0;
		for (int i = 1; i < line_length; i++) {
			int dx = abs((int)(line_x[pre_block_num] - line_x[i]));
			int dy = abs((int)(line_y[pre_block_num] - line_y[i]));
			if (dx >= 50 || dy >= 50) {
				int block_x = (line_x[pre_block_num] + line_x[i]) / 2;
				int block_y = (line_y[pre_block_num] + line_y[i]) / 2;
				int block_w = 25;
				int block_h = (dy < 50) ? 50 : dy;
				mgr->add(new Block(block_x, block_y, block_w, block_h));
				pre_block_num = i;
			}
		}
	}

	mgr->del(this);
}

void BlockFactory::draw() {
}
