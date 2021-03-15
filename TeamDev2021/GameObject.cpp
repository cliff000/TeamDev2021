#include <math.h>
#include "GameObject.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
	if (col != nullptr) {
		delete col;
		col = nullptr;
	}
}


bool GameObject::collide(GameObject* other) {
	return col->collide(other->col);
}

void GameObject::setMgr(ObjectMgr* mgr) {
	this->mgr = mgr;
}


