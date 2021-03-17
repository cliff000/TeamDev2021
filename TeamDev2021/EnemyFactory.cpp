#include "EnemyFactory.h"
#include "Arrow.h"
#include "Spotter.h"
#include "DxLib.h"


EnemyFactory::EnemyFactory()
{
}


EnemyFactory::~EnemyFactory()
{
}


void EnemyFactory::update(){
	if (count_arrow++ >= countMax_arrow) {
		mgr->add(new Arrow());
		count_arrow = 0;
		countMax_arrow = 120 + GetRand(60);
	}

	if (count_spotter++ >= countMax_spotter) {
		mgr->add(new Spotter());
		count_spotter = 0;
		countMax_spotter = 240 + GetRand(120);
	}
}

void EnemyFactory::draw(){
}
