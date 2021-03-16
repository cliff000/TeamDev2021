#pragma once
#include "Collider.h"
#include "main.h"
#include "ObjectMgr.h"
#include <string>


class GameObject
{
protected:
	std::string id = "Default"; //�C���X�^���X�����ʂ��邽�߂�ID�B�N���X���Ƃɐݒ肷��
	double x;
	double y;
	double w;
	double h;
	Collider* col = new Collider(&x, &y);
	ObjectMgr* mgr;

public:
	GameObject();
	~GameObject();

	bool collide(GameObject* other);
	bool include(GameObject* other);
	void setMgr(ObjectMgr* mgr); //ObjectMgr����Ă΂��
	std::string getID() { return id; }

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void hitAction(GameObject* other) {}
};



