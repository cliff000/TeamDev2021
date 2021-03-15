#pragma once
#include "GameObject.h"
#include "Image.h"
#include <iostream>


class Button :
	public GameObject
{
protected:
	int x;
	int y;
	int w;
	int h;
	int main_color = 0x274a78;
	int frame_color = 0x84a2d4;
	int str_color = 0xffffff;
	const char* str;
	int state;
	Image img;

public:
	Button();
	Button(int x, int y, int w, int h, const char* str);
	~Button();

	void update();
	void draw();
	//void hitAction(GameObject* other);

	bool isOnCursor();
	bool isClicked();
	bool isPressing();
	bool isReleased();
};