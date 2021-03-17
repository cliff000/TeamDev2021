#include "Dxlib.h"
#include "mouse.h"

int Mouse[BUTTON_NUM + 2]; // キーが押されているフレーム数を格納する

// キーの入力状態を更新する
int gpUpdateMouse() {
	int nowInput = GetMouseInput();      //今のキーの入力状態を取得
	for (int i = 0; i<BUTTON_NUM; i++) {
		if ((nowInput >> i) & 0x01) {    //i番のキーが押されていたら
			Mouse[i]++;          //カウンタを増やす
		}
		else { //押されていなければ
			Mouse[i] = 0;    //0に戻す
		}
	}
	GetMousePoint(&Mouse[MOUSE_X], &Mouse[MOUSE_Y]);

	return 0;
}