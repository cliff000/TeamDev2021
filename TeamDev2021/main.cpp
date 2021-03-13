#include "DxLib.h"

int road_grHandle;		//地面のグラフィック
double road_y;			//地面のy座標
double speed;			//速さ
int carriage_grHandle;	//馬車のグラフィック
int timer;				//時間制限用のタイマー
int number_grHandle[10];		//タイマーのグラフィック(仮)
int time_limit;			//制限時間
int run_length;			//走った距離の測定
int castle_grHandle;	//城のグラフィック
double castle_y;		//城のy座標
int castle_length;		//城までの道のりの長さ
int castle_flag;		//城到達フラグ、1で到達

void MainGame_Init();
void MainGame_Update();
void MainGame_Draw();
void counter(int num, int x, int y, int block_exRate);

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
	road_y = 0;				//地面のy座標の初期化
	speed = 5;				//スピードの初期化
	carriage_grHandle = LoadGraph("Resource/Image/carriage.png");
	timer = 0;				//タイマーの初期化
	LoadDivGraph("Resource/Image/number.png", 10, 10, 1, 16, 16, number_grHandle);
	time_limit = 20*60;		//制限時間の設定(現在は20秒)
	run_length = 0;			//走った距離の初期化
	castle_grHandle = LoadGraph("Resource/Image/castle.png");
	castle_y = 0;			//城のy座標の初期化
	castle_length = speed * 10 * 60;	//城まで初期スピードで10秒走ると到達
	castle_flag = 0;		//城到達フラグの初期化
}

void MainGame_Update()
{
	if (timer <= time_limit && castle_flag == 0) {		//時間制限内かつ城に到達していないとき
		road_y += speed;		//1フレームごとに地面をspeed分移動する
		if (road_y >= 480)		//地面の座標が480を超えたら0に戻す
			road_y = 0;
		timer++;				//1フレームごとに1追加
		run_length += speed;	//走った距離
		if (run_length >= castle_length)
			castle_flag = 1;					//城に到達した場合城到達フラグを1に
	}
	else if (castle_flag == 1) {			//城に到達した場合
		if (speed > 0) {		//ゆるく減速
			speed -= 0.1;
			road_y += speed;
			castle_y += speed;
		}
	}
	else {					//制限時間を超えた場合
		castle_flag = 0;
	}
}

void MainGame_Draw()
{
	DrawRotaGraph(320, road_y - 240, 1, 0, road_grHandle, 1);
	DrawRotaGraph(320, road_y + 240, 1, 0, road_grHandle, 1);
	DrawRotaGraph(320, 360, 4, 0, carriage_grHandle, 1);
	counter((time_limit - timer) / 60, 600, 50, 2);			//制限時間のカウンター
	if (castle_flag == 1)
		DrawRotaGraph(320, castle_y - 240, 1, 0, castle_grHandle, 1);
}

void counter(int num, int x, int y, int block_exRate)		//数字を表示する関数、引数は先頭から表示する数字、x座標、y座標、表示倍率
{
	DrawRotaGraph(x - 2 * (16) * block_exRate, y, block_exRate, 0, number_grHandle[num / 100], 1);
	DrawRotaGraph(x - (16) * block_exRate, y, block_exRate, 0, number_grHandle [(num / 10) % 10] , 1);
	DrawRotaGraph(x, y, block_exRate, 0, number_grHandle[(num) % 10], 1);
}