#include "DxLib.h"

int road_grHandle;		//地面のグラフィック
int road_y;			//地面のy座標
int speed;			//速さ
int carriage_grHandle;	//馬車のグラフィック

void MainGame_Init();
void MainGame_Update();
void MainGame_Draw();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
	MainGame_Init();

	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		MainGame_Update();
		MainGame_Draw();
	}
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}

void MainGame_Init()
{
	SetTransColor(0, 255, 0);
	road_grHandle = LoadGraph("Resource/Image/floor.png");
	speed = 5;
	carriage_grHandle = LoadGraph("Resource/Image/carriage.png");
}

void MainGame_Update()
{
	road_y += speed;		//1フレームごとに地面をspeed分移動する
	if (road_y >= 480)		//地面の座標が480を超えたら0に戻す
		road_y = 0;
}

void MainGame_Draw()
{
	DrawRotaGraph(320, road_y - 240, 1, 0, road_grHandle, 1);
	DrawRotaGraph(320, road_y + 240, 1, 0, road_grHandle, 1);
	DrawRotaGraph(320, 360, 4, 0, carriage_grHandle, 1);
}