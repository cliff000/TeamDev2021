#include "DxLib.h"
#include "ObjectMgr.h"
#include "Carriage.h"
#include "EnemyFactory.h"
#include "Block.h"
#include "main.h"

#define LINE_NUM 5			//引くことのできる線の本数
#define POINT_NUM 50		//引く線の座標を幾つ取るか

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
int mouse_x[LINE_NUM][POINT_NUM];
int mouse_y[LINE_NUM][POINT_NUM];		//マウスのx、y座標の保存
int mouse_status;		//マウスが何フレームの間右クリックされたか
int mouse_status_tmp[LINE_NUM];	//上記とほぼ同じ、もう一度押されたタイミングで初期化
int line_count;			//現在何本目の線を書いているか
int line_clear_timer[LINE_NUM];	//線を時間経過で消すためのタイマー

void MainGame_Init();
void MainGame_Update();
void MainGame_Draw();
void counter(int num, int x, int y, int block_exRate);
void line_clear(int mouse_x[], int mouse_y[], int num, int *mouse_status, int *clear_timer, int frame);	//描画した線を消す関数、引数は先頭から消す線のx座標、y座標、座標の個数、書き始めを知るためにフレームを格納した変数、時間計測の変数、消すまでのフレーム数

ObjectMgr *objectMgr = new ObjectMgr();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 16);
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
	castle_length = speed * 20 * 60;	//城まで初期スピードで10秒走ると到達
	castle_flag = 0;		//城到達フラグの初期化
	mouse_status = 0;
	line_count = 1;
	for (int i = 0; i < LINE_NUM; i++) {
		mouse_status_tmp[i] = 0;
		line_clear_timer[i] = 0;
	}
	
	
	objectMgr->add(new Carriage());
	objectMgr->add(new EnemyFactory());
}

void MainGame_Update()
{
	if (timer <= time_limit && castle_flag == 0) {		//時間制限内かつ城に到達していないとき
		road_y += speed;		//1フレームごとに地面をspeed分移動する
		if (road_y >= WINDOWSIZE_Y)		//地面の座標がWINDOWSIZE_Yを超えたら0に戻す
			road_y = 0;
		timer++;				//1フレームごとに1追加
		run_length += speed;	//走った距離
		if (run_length >= castle_length)
			castle_flag = 1;					//城に到達した場合城到達フラグを1に
		//マウスの処理
		if (mouse_status > 0 && mouse_status <= POINT_NUM)	//左クリックが押されている間マウスの座標を保存
		{
			GetMousePoint(&mouse_x[line_count-1][mouse_status - 1], &mouse_y[line_count-1][mouse_status - 1]);
		}
		if (GetMouseInput() & MOUSE_INPUT_LEFT && mouse_status < POINT_NUM) {			//マウスの左クリックが押されたフレーム数を測定
			mouse_status++;									//フレーム数を格納
			if (mouse_status == 1) {
				line_count++;
			}
			else if (line_count > LINE_NUM)
				line_count = 1;
			mouse_status_tmp[line_count-1] = mouse_status;
		}
		else if(!(GetMouseInput() & MOUSE_INPUT_LEFT))
			mouse_status = 0;
		
		for (int i = 0; i < LINE_NUM; i++)
			line_clear(mouse_x[i], mouse_y[i], POINT_NUM, &mouse_status_tmp[i], &line_clear_timer[i], 100);
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


	
	
	objectMgr->update(); //オブジェクトのアップデート
}

void MainGame_Draw()
{
	//地面の描画
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y - WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y + WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);
	//マウスの描画
	for (int j = 0; j < LINE_NUM; j++)
		for (int i = 1; i < mouse_status_tmp[j] - 1; i++)
			if (mouse_status <= POINT_NUM){
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], GetColor(255, 0, 0), 1);
			}
	//counter(line_clear_timer[4], WINDOWSIZE_X - 100, 100, 2);
	/*counter(mouse_status_tmp[0], WINDOWSIZE_X - 100, 100, 2);
	counter(mouse_status_tmp[1], WINDOWSIZE_X - 100, 150, 2);
	counter(mouse_status_tmp[2], WINDOWSIZE_X - 100, 200, 2);
	counter(mouse_status_tmp[3], WINDOWSIZE_X - 100, 250, 2);
	counter(mouse_status_tmp[4], WINDOWSIZE_X - 100, 300, 2);
	counter(mouse_x[3][1], WINDOWSIZE_X - 100, 400, 2);
	counter(line_count, WINDOWSIZE_X - 100, 500, 2);*/

	//タイマーの描画
	counter((time_limit - timer) / 60, WINDOWSIZE_X - 100, 50, 2);
	//城の描画
	if (castle_flag == 1)
		DrawRotaGraph(WINDOWSIZE_X / 2, castle_y - WINDOWSIZE_Y / 2, 1, 0, castle_grHandle, 1);


	objectMgr->draw();//オブジェクトの描画
}

void counter(int num, int x, int y, int block_exRate)		//数字を表示する関数、引数は先頭から表示する数字、x座標、y座標、表示倍率
{
	DrawRotaGraph(x - 2 * (16) * block_exRate, y, block_exRate, 0, number_grHandle[num / 100], 1);
	DrawRotaGraph(x - (16) * block_exRate, y, block_exRate, 0, number_grHandle [(num / 10) % 10] , 1);
	DrawRotaGraph(x, y, block_exRate, 0, number_grHandle[(num) % 10], 1);
}

void line_clear(int *mouse_x, int *mouse_y, int num, int *mouse_status, int *clear_timer, int frame)	//描画した線を消す関数、引数は先頭から消す線のx座標、y座標、座標の個数、書き始めを知るためにフレームを格納した変数、時間計測の変数、消すまでのフレーム数
{
	if (*mouse_status != 0)
	{
		*clear_timer += 1;
		if (*clear_timer >= frame) {
			*mouse_status = 0;
			*clear_timer = 0;
			for (int i = 0; i < num; i++){
				mouse_x[i] = 0;
				mouse_y[i] = 0;
			}
		}
	}
}