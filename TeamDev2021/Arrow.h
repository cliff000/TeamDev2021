#pragma once
#include "GameObject.h"
#include "Image.h"

class Arrow :
	public GameObject
{
protected:
	Image img;
	bool side; //0���ƍ�����A1���ƉE������ł���

public:
	Arrow();
	~Arrow();

	void update();
	void draw();
	void hitAction(GameObject* other);
};
