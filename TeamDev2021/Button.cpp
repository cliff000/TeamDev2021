#include <DxLib.h>
#include "Button.h"
#include "main.h"

#define NORMAL 0
#define ON_CURSOR 1
#define CLICKED 2
#define PRESSING 3
#define RELEASED 4



Button::Button() {

}

Button::~Button() {

}

Button::Button(int x, int y, int w, int h, const char* str)
{
	this->x = x;  
	this->y = y;
	this->w = w;
	this->h = h;
	this->str = str;
}


//ボタンの更新
void Button::update() {
	int _x = x - w / 2;
	int _y = y - h / 2;
	int mx, my;
	GetMousePoint(&mx, &my);

	//ボタンが押されてないとき
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		if (state == CLICKED || state == PRESSING)
			state = RELEASED;
		else {
			if (_x <= mx && mx <= _x + w && _y <= my && my <= _y + h) {
				//if (state == NORMAL)
					//PlaySoundMem(se[6], DX_PLAYTYPE_BACK, TRUE);
				state = ON_CURSOR;
			}
			else
				state = 0;
		}
	}

	//ボタンが押されたとき
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		if (_x <= mx && mx <= _x + w && _y <= my && my <= _y + h) {
			if (state == NORMAL || state == ON_CURSOR)
				state = CLICKED;
			else
				state = PRESSING;
		}
		else {
			state = NORMAL;
		}
	}
}

//ボタンの描画
void Button::draw() {
	int waku = 2;
	int _x = x - w / 2;
	int _y = y - h / 2;
	int sub = 0;
	if (state == CLICKED || state == PRESSING) {
		sub = 3;
	}
	//ボタン表示
	if (state == ON_CURSOR) {//カーソルがのってるとき
		for (int i = 4; i >= 0; i--) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220 - 40 * i);
			DrawBox(_x - i, _y - i, _x + w + i, _y + h + i, 0xffffff, TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	DrawBox(_x + sub, _y + sub, _x + w - sub, _y + h - sub, frame_color, TRUE);//枠
	DrawBox(_x + sub + waku, _y + sub + waku, _x + w - sub - waku, _y + h - sub - waku, main_color, TRUE);//本体


	//文字表示
	int strW = GetDrawStringWidth(str, strlen(str));
	int strX = _x + w / 2 - strW / 2;
	int strY = _y + h / 2 - DEFAULT_FONT_SIZE / 2;
	DrawString(strX, strY, str, str_color);
}


//ボタンの状態を得る
bool Button::isOnCursor() {
	if (state == ON_CURSOR)
		return true;
	else
		return false;
}
bool Button::isClicked() {
	if (state == CLICKED)
		return true;
	else
		return false;
}
bool Button::isPressing() {
	if (state == PRESSING)
		return true;
	else
		return false;
}
bool Button::isReleased() {
	if (state == RELEASED)
		return true;
	else
		return false;
}
