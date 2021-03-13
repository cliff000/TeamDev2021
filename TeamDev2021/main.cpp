#include "DxLib.h"


int mouse;
int mouseKeep;
int *mouseX, *mouseY;


void update() {
	mouse = GetMouseInput(); //マウスの入力状態取得

	//マウスが左クリックされていれば位置を取得
	if (mouse & MOUSE_INPUT_LEFT) {
		GetMousePoint(mouseX, mouseY);
	}
}

void draw() {
	//マウスが左クリックされていれば描画
	if (mouse & MOUSE_INPUT_LEFT) {
		GetMousePoint(mouseX, mouseY);
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	

	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}
