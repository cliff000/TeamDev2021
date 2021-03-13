#include "EnemyFactory.h"
#include "Arrow.h"


EnemyFactory::EnemyFactory()
{
}


EnemyFactory::~EnemyFactory()
{
}


void EnemyFactory::update(){
	if (count++ >= countMax) {
		mgr->add(new Arrow());
		count = 0;
	}
}

void EnemyFactory::draw(){
}
