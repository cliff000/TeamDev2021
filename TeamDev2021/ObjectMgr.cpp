#include "ObjectMgr.h"
#include "GameObject.h"


ObjectMgr::ObjectMgr()
{
}


ObjectMgr::~ObjectMgr()
{
	list.clear();
}


void ObjectMgr::update() {
	//XV
	for (auto& e : list) {
		e->update();
	}


	//“–‚½‚è”»’è
	for (auto& e : list) {
		for (auto& f : list) {
			if (e != f && e->collide(f)) {
				e->hitAction(f);
			}
		}
	}

	//íœ
	for (auto itr = delList.begin(); itr != delList.end(); itr = delList.erase(itr)) {
		list.remove(*itr);
		delete *itr;
		*itr = nullptr;
	}
}

void ObjectMgr::draw() {
	for (auto i : list)
		i->draw();
}

void ObjectMgr::add(GameObject* obj) {
	obj->setMgr(this);
	list.push_back(obj);
}

void ObjectMgr::del(GameObject* obj) {
	auto result = std::find(delList.begin(), delList.end(), obj);
	if (result == delList.end())
		delList.push_back(obj);
}

GameObject* ObjectMgr::getObject(const char* id) {
	for (auto& e : list) {
		if (e->getID() == id)
			return e;
	}
	return nullptr;
}
