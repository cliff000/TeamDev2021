#include "Collider.h"
#include "Dxlib.h"
#include <math.h>

Collider::Collider(double* ownerX, double* ownerY)
{
	this->ownerX = ownerX;
	this->ownerY = ownerY;
}


Collider::~Collider()
{
}


void Collider::update() {

}

void Collider::draw() {
	DrawBox(getX() - w/2, getY() - h/2, getX() + w/2, getY() + h/2, 0xff0000, false);
}

bool Collider::collide(Collider* other)
{
	int dx = abs((int)(getX() - other->getX()));
	int dy = abs((int)(getY() - other->getY()));
	int ww = (w + other->getW()) / 2;
	int hh = (h + other->getH()) / 2;
	if (dx <= ww && dy <= hh) {
		return true;
	}
	else {
		return false;
	}
		
}
