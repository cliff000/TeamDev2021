#pragma once
#include "GameObject.h"

class EnemyFactory :
	public GameObject
{
	int count = 0;
	int countMax = 60;

public:
	EnemyFactory();
	~EnemyFactory();

	void update();
	void draw();
};

