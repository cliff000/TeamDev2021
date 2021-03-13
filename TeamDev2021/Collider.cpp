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
	DrawBox(getX1(), getY1(), getX2(), getY2(), 0xff0000, false);
}

bool Collider::collide(Collider* other)
{
	if (((other->getX1() > getX1() && other->getX1() < getX2()) || (other->getX2() > getX1() && other->getX2() < getX2())) &&
		((other->getY1() > getY1() && other->getY1() < getY2()) || (other->getY2() > getY1() && other->getY2() < getY2()))) {
		return true;
	}
	else {
		return false;
	}
		
}
