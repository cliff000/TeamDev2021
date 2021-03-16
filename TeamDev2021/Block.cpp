#include "Block.h"
#include "DxLib.h"

#define ALPHA_DEF 160


Block::Block()
{
	init();
	
}

Block::Block(int x, int y)
{
	init();
	this->x = x;
	this->y = y;
}

Block::Block(int x, int y, int w, int h)
{
	init();
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	col->setSize(w, h);
}



Block::~Block()
{
}


void Block::init() {
	id = "Block";
	w = 50;
	h = 50;
	x = 0;
	y = 0;
	alpha = ALPHA_DEF;
	col->setPos(0, 0);
	col->setSize(50, 50);
	//img = Image("Resource/Image/block.jpg");
}

void Block::update() {
	if (count++ >= 90){
		if (alpha == ALPHA_DEF) {
			alpha = ALPHA_DEF / 2;
			count = 45;
		}else{
			mgr->del(this);
		}
	}

	if (alpha != ALPHA_DEF) {
		if (count % 4 < 2) {
			alpha += 5;
		}
		else {
			alpha -= 5;
		}
	}

}

void Block::draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(x - w/2, y - h/2, x + w/2, y + h/2, color, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,  1.0 * 255 / ALPHA_DEF * alpha);
	DrawBoxAA(x - w / 2, y - h / 2, x + w / 2, y + h / 2, 0xbce2e8, false, 3);
	//img.draw(x, y, 0.148, 0, true, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//col->draw();
}

void Block::hitAction(GameObject* other) {
	if (other->getID() == "Carriage")
		mgr->del(this);
}

void Block::setColor(int color) {
	this->color = color;
}