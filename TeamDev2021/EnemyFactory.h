#pragma once
#include "GameObject.h"

class EnemyFactory :
	public GameObject
{
	int count_arrow = 0;
	int countMax_arrow = 120;
	int count_spotter = 0;
	int countMax_spotter = 240;

public:
	EnemyFactory();
	~EnemyFactory();

	void update();
	void draw();
};

