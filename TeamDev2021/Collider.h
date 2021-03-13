#pragma once


class Collider
{
	double x = 0;
	double y = 0;
	double w = 16;
	double h = 16;

	double* ownerX;
	double* ownerY;


public:
	Collider(double* ownerX, double* ownerY);
	~Collider();

	void update();
	void draw();
	bool collide(Collider* other);

	double getX1() { return x - w/2 + *ownerX; }
	double getY1() { return y - h/2 + *ownerY; }
	double getX2() { return x + w/2 + *ownerX; }
	double getY2() { return y + h/2 + *ownerY; }
	void setPos(double x, double y) { this->x = x;  this->y = y; }
	void setSize(double w, double h) { this->w = w;  this->h = h; }
};

