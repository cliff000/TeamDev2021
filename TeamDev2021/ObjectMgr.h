#pragma once
#include <list>

class GameObject;

class ObjectMgr
{
protected:
	std::list<GameObject*> list; //GameObjectのリスト
	std::list<GameObject*> delList; //削除予定のGameObject、イテレータ破壊回避のためのもの

public:
	ObjectMgr();
	~ObjectMgr();

	void update();
	void draw();
	void add(GameObject* object);
	void del(GameObject* object);
	GameObject* getObject(const char* id);
};
