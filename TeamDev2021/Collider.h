#pragma once


class Collider
{
protected:
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
	bool collide(Collider* other); //衝突しているかの判定
	bool include(Collider* other); //自分がotherを包含しているかどうかの判定

	double getX() { return x + *ownerX; }
	double getY() { return y + *ownerY; }
	double getW() { return w; }
	double getH() { return h; }
	void setPos(double x, double y) { this->x = x;  this->y = y; }
	void setSize(double w, double h) { this->w = w;  this->h = h; }
};

