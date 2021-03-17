#include "DxLib.h"
#include "main.h"
#include "ObjectMgr.h"
#include "Carriage.h"
#include "EnemyFactory.h"
#include "BlockFactory.h"
#include "Button.h"
#include "main.h"
#include <iostream>

enum GameMode { Title, MainGame };

#define LINE_NUM 5			//引くことのできる線の本数
#define POINT_NUM 100		//引く線の座標を幾つ取るか
#define LINE_LENGTH 500		//引くことのできる線の長さ
#define FIRST_SPEED 5       //始めのスピード
#define TIME_LIMIT 20*60		//制限時間
int road_grHandle;		//地面のグラフィック
double road_y;			//地面のy座標
double speed;			//速さ
int carriage_grHandle;	//馬車のグラフィック
int timer;				//時間制限用のタイマー
int number_grHandle[10];		//タイマーのグラフィック(仮)
int clock_grHandle;		//タイマーのグラフィック
int clock_hand_grHandle;//タイマーの針のグラフィック
int run_length;			//走った距離の測定
int castle_grHandle;	//城のグラフィック
double castle_y;		//城のy座標
int castle_length;		//城までの道のりの長さ
int castle_flag;		//城到達フラグ、1で到達
int title_grHandle;     //タイトルのグラフィック
int title_y;            //タイトルのY座標
bool changeScene_Title_to_MainGame;  //タイトルからメインゲームへの移行フラグ
int clear_screen;      //クリア時の描画先グラフィック
int gameMode;           //ゲームの状態(タイトルかメインゲームか)
int mouse_x[LINE_NUM][POINT_NUM];
int mouse_y[LINE_NUM][POINT_NUM];		//マウスのx、y座標の保存
int mouse_status;		//マウスが何フレームの間右クリックされたか
int mouse_status_tmp[LINE_NUM];	//上記とほぼ同じ、もう一度押されたタイミングで初期化
int line_count;			//現在何本目の線を書いているか
int line_clear_timer[LINE_NUM];	//線を時間経過で消すためのタイマー
double line_length[LINE_NUM];			//線の長さ
int blend_alpha;			//画像などを透過でゆっくり浮き上がらせるための変数
int FontHandle;			//クリア時、ゲームオーバー時のフォントデータの保存

void Title_Init();
void Title_Update();
void Title_Draw();
void MainGame_Init();
void MainGame_Update();
void MainGame_Draw();
void counter(int num, int x, int y, int block_exRate);
void line_clear(int *mouse_x, int *mouse_y, int num, int *mouse_status, int *clear_timer, int frame);	//描画した線を消す関数、引数は先頭から消す線のx座標、y座標、座標の個数、書き始めを知るためにフレームを格納した変数、時間計測の変数、消すまでのフレーム数

ObjectMgr* objectMgr = nullptr;
Button* menu;
Carriage* carriage;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 16);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
	
	gameMode = Title;
	Title_Init();
	MainGame_Init();

	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		if (gameMode == Title) {
			Title_Update();
			Title_Draw();
		}
		else if (gameMode == MainGame) {
			MainGame_Update();
			MainGame_Draw();
		}
	}
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}

void Title_Init() {
	changeScene_Title_to_MainGame = false;
	title_y = WINDOWSIZE_Y / 2;
	road_grHandle = LoadGraph("Resource/Image/floor.png");
	title_grHandle = LoadGraph("Resource/Image/title.png");
}

void Title_Update() {
	//クリックされたらメインゲームに移行する
	if (GetMouseInput() & MOUSE_INPUT_LEFT) 
		changeScene_Title_to_MainGame = true;

	if (changeScene_Title_to_MainGame) {
		if (title_y < WINDOWSIZE_Y / 2 * 3)
			title_y += FIRST_SPEED;
		else
			gameMode = MainGame;
	}
}

void Title_Draw() {
	DrawRotaGraph(WINDOWSIZE_X / 2, title_y - WINDOWSIZE_Y, 1, 0, road_grHandle, 1);
	DrawRotaGraph(WINDOWSIZE_X / 2, title_y, 1, 0, title_grHandle, 1);
	DrawString(420, title_y + 180, "Click to start", 0xffffff);
}

void MainGame_Init()
{
	SetTransColor(0, 255, 0);
	road_grHandle = LoadGraph("Resource/Image/floor.png");
	road_y = 0;				//地面のy座標の初期化
	speed = FIRST_SPEED;	//スピードの初期化
	carriage_grHandle = LoadGraph("Resource/Image/carriage.png");
	timer = 0;				//タイマーの初期化
	LoadDivGraph("Resource/Image/number.png", 10, 10, 1, 16, 16, number_grHandle);
	clock_grHandle = LoadGraph("Resource/Image/clock.png");
	clock_hand_grHandle = LoadGraph("Resource/Image/clock_hand.png");

	run_length = 0;			//走った距離の初期化
	castle_grHandle = LoadGraph("Resource/Image/castle.png");
	castle_y = 0;			//城のy座標の初期化
	castle_length = speed * 20 * 60;	//城まで初期スピードで20秒走ると到達
	castle_flag = 0;		//城到達フラグの初期化
	mouse_status = 0;
	line_count = 1;
	blend_alpha = 0;
	FontHandle = CreateFontToHandle("Georgia", 32, -1, DX_FONTTYPE_ANTIALIASING);

	for (int i = 0; i < LINE_NUM; i++) {
		mouse_status_tmp[i] = 0;
		line_clear_timer[i] = 0;
	}
	clear_screen = MakeScreen(WINDOWSIZE_X, WINDOWSIZE_Y, true); //クリア画面用の描画先
	
	
	//オブジェクトの初期化
	if (objectMgr != nullptr) {
		delete objectMgr;
		objectMgr = nullptr;
	}
	objectMgr = new ObjectMgr();
	menu = new Button(75, 50, 100, 50, "メニュー");
	carriage = new Carriage();
	objectMgr->add(carriage);
	objectMgr->add(new EnemyFactory());
	objectMgr->add(menu);

}

void MainGame_Update()
{
	if (timer <= TIME_LIMIT && castle_flag == 0) {		//時間制限内かつ城に到達していないとき
		road_y += speed;		//1フレームごとに地面をspeed分移動する
		if (road_y >= WINDOWSIZE_Y)		//地面の座標がWINDOWSIZE_Yを超えたら0に戻す
			road_y = 0;
		timer++;				//1フレームごとに1追加
		run_length += speed;	//走った距離
		if (run_length >= castle_length) {
			castle_flag = 1;					//城に到達した場合城到達フラグを1に
			objectMgr->del(menu);
			objectMgr->update();
		}
		//マウスの処理
		if (GetMouseInput() & MOUSE_INPUT_LEFT && mouse_status < POINT_NUM && line_length[line_count - 1] < LINE_LENGTH) {			//マウスの左クリックが押された時
			mouse_status++;									//マウスの左クリックが押されたフレーム数を測定
			if (mouse_status == 1) {						//現在引いている線の本数を保存
				line_count++;
			}
			if (line_count > LINE_NUM)
				line_count = 1;

			if (mouse_status > 0 && mouse_status <= POINT_NUM)	//左クリックが押されている間マウスの座標を保存
			{
				GetMousePoint(&mouse_x[line_count - 1][mouse_status - 1], &mouse_y[line_count - 1][mouse_status - 1]);
			}
			mouse_status_tmp[line_count - 1] = mouse_status;
			line_length[line_count - 1] = 0;
			for (int i = 0; i < mouse_status_tmp[line_count - 1] - 1; i++)		//線の長さを測る
			{
				line_length[line_count - 1] += sqrt(pow(mouse_x[line_count - 1][i] - mouse_x[line_count - 1][i + 1], 2) + pow(mouse_y[line_count - 1][i] - mouse_y[line_count - 1][i + 1], 2));
			}

		}
		else if (!(GetMouseInput() & MOUSE_INPUT_LEFT)) {
			if (line_count > 0 && mouse_status > 0) {
				objectMgr->add(new BlockFactory(mouse_x[line_count - 1], mouse_y[line_count - 1], mouse_status));
			}
			line_length[line_count - 1] = 0;
			mouse_status = 0;
			for (int i = 0; i < LINE_NUM; i++)
				line_clear(mouse_x[i], mouse_y[i], POINT_NUM, &mouse_status_tmp[i], &line_clear_timer[i], 10);		//引いた線を一定時間で消す
		}

	}

	else if (castle_flag == 1) {			//城に到達した場合
		speed = std::cos(castle_y / WINDOWSIZE_Y * PI / 2) * (FIRST_SPEED - 1) + 1;  //ゆるく減速

		if (castle_y < WINDOWSIZE_Y) {
			castle_y += speed;
		}
		if (castle_y >= WINDOWSIZE_Y) {
				blend_alpha += 5;
				if (blend_alpha > 255)
					blend_alpha = 255;
			}
			if (blend_alpha >= 255) {
				if (GetMouseInput() & MOUSE_INPUT_LEFT) {
					Title_Init();
					gameMode = Title;
					MainGame_Init();
				}			if (blend_alpha < 255) {

			}
		}

	}
	else {					//制限時間を超えた場合
		castle_flag = 0;
		blend_alpha += 5;
		if (blend_alpha > 255)
			blend_alpha = 255;
	}
	if (blend_alpha >= 255) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			Title_Init();
			gameMode = Title;
			MainGame_Init();
		}			if (blend_alpha < 255) {

		}

	}


	
	if (castle_flag == 0)
		objectMgr->update(); //オブジェクトのアップデート
}

void MainGame_Draw()
{
	//城に到達した場合
	if (castle_flag == 1)
		SetDrawScreen(clear_screen); //描画先を変更

	//地面の描画
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y - WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y + WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);

	objectMgr->draw();//オブジェクトの描画

	//マウスの描画
	for (int j = 0; j < LINE_NUM; j++)
		for (int i = 1; i < mouse_status_tmp[j] - 1; i++)
			if (mouse_status <= POINT_NUM){
				//光ってる感じの線に見せたい
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], 0xaa3333, 12);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], 0xaa3333, 10);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], 0xaa3333, 8);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], 0xaa3333, 6);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], 0xaa3333, 4);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], 0xaa3333, 2);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			}
	/*counter(mouse_status_tmp[0], WINDOWSIZE_X - 100, 100, 2);
	counter(mouse_status_tmp[1], WINDOWSIZE_X - 100, 150, 2);
	counter(mouse_status_tmp[2], WINDOWSIZE_X - 100, 200, 2);
	counter(mouse_status_tmp[3], WINDOWSIZE_X - 100, 250, 2);
	counter(mouse_status_tmp[4], WINDOWSIZE_X - 100, 300, 2);
	counter(mouse_x[3][1], WINDOWSIZE_X - 100, 400, 2);
	counter(line_count, WINDOWSIZE_X - 100, 500, 2);*/

	//描くことができる線の残りの長さ(仮)
	DrawBox(WINDOWSIZE_X - 200, 500, WINDOWSIZE_X - 50, 530, GetColor(255, 255, 255), TRUE);
	DrawBox(WINDOWSIZE_X - 195, 505, WINDOWSIZE_X - 55, 525, GetColor(255, 50, 50), TRUE);
	for (int i = 0; i < LINE_NUM; i++)
	{
		DrawBox(WINDOWSIZE_X - 55 - 110 * (line_length[i] / LINE_LENGTH), 505, WINDOWSIZE_X - 55, 525, GetColor(200, 200, 200), TRUE);
	}
	if (mouse_status >= POINT_NUM || line_length[line_count - 1] >= LINE_LENGTH)
		DrawBox(WINDOWSIZE_X - 195, 505, WINDOWSIZE_X - 55, 525, GetColor(200, 200, 200), TRUE);

	if (castle_flag == 0) {
		//城までの距離(仮)
		DrawBox((WINDOWSIZE_X / 2) - 200, 525, (WINDOWSIZE_X / 2) + 200, 535, GetColor(255, 255, 255), TRUE);
		DrawBox((WINDOWSIZE_X / 2) - 195 + 400 * run_length / castle_length, 515, (WINDOWSIZE_X / 2) - 205 + 400 * run_length / castle_length, 525, GetColor(100, 255, 100), TRUE);

		//残り時間の描画
		DrawRotaGraph(WINDOWSIZE_X - 50, 50, 0.5, 0, clock_grHandle, 1);
		DrawRotaGraph(WINDOWSIZE_X - 50, 50, 0.5, 2 * PI * timer / (TIME_LIMIT), clock_hand_grHandle, 1);
		//counter((TIME_LIMIT - timer) / 60, WINDOWSIZE_X - 100, 200, 2);
	}
	

	//城に到達した場合
	if (castle_flag == 1) { //描画先を裏画面に戻して描画
		SetDrawScreen(DX_SCREEN_BACK);
		DrawRotaGraph(WINDOWSIZE_X / 2, castle_y + WINDOWSIZE_Y / 2, 1, 0, clear_screen, 1);
		DrawRotaGraph(WINDOWSIZE_X / 2, castle_y - WINDOWSIZE_Y / 2, 1, 0, castle_grHandle, 1); //城の描画
		if (castle_y >= WINDOWSIZE_Y) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend_alpha);
			DrawStringToHandle(WINDOWSIZE_X / 2 - 105, WINDOWSIZE_Y / 2 - 16, "GAME CLEAR", 0xffffff, FontHandle);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			if (blend_alpha >= 255) {
				DrawString(WINDOWSIZE_X / 2, WINDOWSIZE_Y - 100, "Click to back to title", 0xffffff);
				DrawFormatString(WINDOWSIZE_X - 200, 100, 0xffffff, "Time : %.2f", (double)timer / 60);
			}
		}

	}

	//時間制限を超えた場合
	if (timer > TIME_LIMIT) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend_alpha);
		DrawBox(0, 0, WINDOWSIZE_X, WINDOWSIZE_Y, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		if (blend_alpha >= 255) {
			DrawStringToHandle(WINDOWSIZE_X / 2 - 100, WINDOWSIZE_Y / 2 - 16, "GAME OVER", 0xffffff, FontHandle);
			DrawString(WINDOWSIZE_X / 2, WINDOWSIZE_Y - 100, "Click to back to title", 0xffffff);
		}
	}

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