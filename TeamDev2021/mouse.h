#pragma once

#define BUTTON_NUM 8

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2
#define MOUSE_3 3
#define MOUSE_4 4
#define MOUSE_5 5
#define MOUSE_6 6
#define MOUSE_7 7

#define MOUSE_X 8
#define MOUSE_Y 9

int gpUpdateMouse();
extern int Mouse[BUTTON_NUM + 2];
