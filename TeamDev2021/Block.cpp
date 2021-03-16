#include "Block.h"
#include "DxLib.h"


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
	alpha = 255;
	col->setPos(0, 0);
	col->setSize(50, 50);
	//img = Image("Resource/Image/block.jpg");
}

void Block::update() {
	if (count++ >= 90){
		if (alpha == 255) {
			alpha = 128;
			count = 45;
		}else{
			mgr->del(this);
		}
	}

	if (alpha != 255) {
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
	//img.draw(x, y, 0.148, 0, true, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//col->draw();
}

void Block::hitAction(GameObject* other) {
	if (other->getID() == "Carriage")
		mgr->del(this);
}

void Block::setColor(int color) {
	this->color = color;
}