#include "EnemyFactory.h"
#include "Arrow.h"
#include "Spotter.h"


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
	}

	if (count_spotter++ >= countMax_spotter) {
		mgr->add(new Spotter());
		count_spotter = 0;
	}
}

void EnemyFactory::draw(){
}
