#pragma once
#include <list>

class GameObject;

class ObjectMgr
{
protected:
	std::list<GameObject*> list; //GameObject�̃��X�g
	std::list<GameObject*> delList; //�폜�\���GameObject�A�C�e���[�^�j�����̂��߂̂���

public:
	ObjectMgr();
	~ObjectMgr();

	void update();
	void draw();
	void add(GameObject* object);
	void del(GameObject* object);
	GameObject* getObject(const char* id);
};
