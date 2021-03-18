#include "DxLib.h"
#include "main.h"
#include "ObjectMgr.h"
#include "Carriage.h"
#include "EnemyFactory.h"
#include "BlockFactory.h"
#include "Button.h"
#include "main.h"
#include <iostream>
#include "mouse.h"
#include "Sound.h"

enum GameMode { Title, MainGame, Pause };

#define LINE_NUM 5			//�������Ƃ̂ł�����̖{��
#define POINT_NUM 300		//�������̍��W�����邩
#define LINE_LENGTH 500		//�������Ƃ̂ł�����̒���
#define TOTAL_LINE_LENGTH 5000   //�������Ƃ̂ł�����̒����̍��v�l
#define FIRST_SPEED 5       //�n�߂̃X�s�[�h
#define TIME_LIMIT 20*60		//��������
int road_grHandle;		//�n�ʂ̃O���t�B�b�N
double road_y;			//�n�ʂ�y���W
double speed;			//����
int carriage_grHandle;	//�n�Ԃ̃O���t�B�b�N
int timer;				//���Ԑ����p�̃^�C�}�[
int number_grHandle[10];		//�^�C�}�[�̃O���t�B�b�N(��)
int clock_grHandle;		//�^�C�}�[�̃O���t�B�b�N
int clock_hand_grHandle;//�^�C�}�[�̐j�̃O���t�B�b�N
int run_length;			//�����������̑���
int castle_grHandle;	//��̃O���t�B�b�N
double castle_y;		//���y���W
int castle_length;		//��܂ł̓��̂�̒���
int castle_flag;		//�铞�B�t���O�A1�œ��B
int title_grHandle;     //�^�C�g���̃O���t�B�b�N
int title_y;            //�^�C�g����Y���W
int brightPause;        //�|�[�Y��ʂł̔w�i�̖��邳
bool changeScene_Title_to_MainGame;  //�^�C�g�����烁�C���Q�[���ւ̈ڍs�t���O
bool changeScene_Pause_to_MainGame;  //�|�[�Y���烁�C���Q�[���ւ̈ڍs�t���O
int clear_screen;      //�N���A���̕`���O���t�B�b�N
int gameMode;           //�Q�[���̏��(�^�C�g�������C���Q�[����)
int mouse_x[LINE_NUM][POINT_NUM];
int mouse_y[LINE_NUM][POINT_NUM];		//�}�E�X��x�Ay���W�̕ۑ�
int mouse_status;		//�}�E�X�����t���[���̊ԉE�N���b�N���ꂽ��
int mouse_status_tmp[LINE_NUM];	//��L�Ƃقړ����A������x�����ꂽ�^�C�~���O�ŏ�����
int line_count;			//���݉��{�ڂ̐��������Ă��邩
int line_clear_timer[LINE_NUM];	//�������Ԍo�߂ŏ������߂̃^�C�}�[
double line_length[LINE_NUM];			//���̒���
int blend_alpha;			//�摜�Ȃǂ𓧉߂ł�����蕂���オ�点�邽�߂̕ϐ�
int FontHandle;			//�N���A���A�Q�[���I�[�o�[���̃t�H���g�f�[�^�̕ۑ�
int scroll_bar_grHandle;	//�n�Ԃ̌��ݒn�������X�N���[���o�[�̃O���t�B�b�N
double remain_length;       //���̎c��̒���

void Title_Init();
void Title_Update();
void Title_Draw();
void MainGame_Init();
void MainGame_Update();
void MainGame_Draw();
void Pause_Init();
void Pause_Update();
void Pause_Draw();
void counter(int num, int x, int y, int block_exRate);
void line_clear(int *mouse_x, int *mouse_y, int num, int *mouse_status, int *clear_timer, int frame);	//�`�悵�����������֐��A�����͐擪�����������x���W�Ay���W�A���W�̌��A�����n�߂�m�邽�߂Ƀt���[�����i�[�����ϐ��A���Ԍv���̕ϐ��A�����܂ł̃t���[����

ObjectMgr* objectMgr = nullptr;
Button *menu, *resume, *restart;
Carriage* carriage;
ObjectMgr* pauseObjectMgr = nullptr;
Sound bgm_maingame, bgm_title, se_clear, se_gameover, se_pause;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 16);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	
	gameMode = Title;
	Title_Init();
	MainGame_Init();

	// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateMouse() == 0) {
		if (gameMode == Title) {
			Title_Update();
			Title_Draw();
		}
		else if (gameMode == MainGame) {
			MainGame_Update();
			MainGame_Draw();
		}
		else if (gameMode == Pause) {
			Pause_Update();
			Pause_Draw();
		}
	}
	DxLib_End(); // DX���C�u�����I������
	return 0;
}

void Title_Init() {
	changeScene_Title_to_MainGame = false;
	title_y = WINDOWSIZE_Y / 2;
	road_grHandle = LoadGraph("Resource/Image/floor.png");
	title_grHandle = LoadGraph("Resource/Image/title.png");
	bgm_title = Sound("Resource/Sound/bgm_title.ogg");
	bgm_title.stop();
}

void Title_Update() {
	bgm_maingame.stop();
	bgm_title.play(DX_PLAYTYPE_LOOP, true); //bgm�Đ�

	//�N���b�N���ꂽ�烁�C���Q�[���Ɉڍs����
	if (Mouse[MOUSE_LEFT] == 1)
		changeScene_Title_to_MainGame = true;

	if (changeScene_Title_to_MainGame) {
		if (title_y < WINDOWSIZE_Y / 2 * 3)
			title_y += FIRST_SPEED;
		else {
			gameMode = MainGame;
			bgm_title.stop();
		}
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
	road_y = 0;				//�n�ʂ�y���W�̏�����
	speed = FIRST_SPEED;	//�X�s�[�h�̏�����
	carriage_grHandle = LoadGraph("Resource/Image/carriage.png");
	timer = 0;				//�^�C�}�[�̏�����
	LoadDivGraph("Resource/Image/number.png", 10, 10, 1, 16, 16, number_grHandle);
	clock_grHandle = LoadGraph("Resource/Image/clock.png");
	clock_hand_grHandle = LoadGraph("Resource/Image/clock_hand.png");

	run_length = 0;			//�����������̏�����
	castle_grHandle = LoadGraph("Resource/Image/castle.png");
	castle_y = 0;			//���y���W�̏�����
	castle_length = speed * 15 * 60;	//��܂ŏ����X�s�[�h��20�b����Ɠ��B
	castle_flag = 0;		//�铞�B�t���O�̏�����
	mouse_status = 0;
	line_count = 1;	
	blend_alpha = 0;
	FontHandle = CreateFontToHandle("Georgia", 64, -1, DX_FONTTYPE_ANTIALIASING);
	scroll_bar_grHandle = LoadGraph("Resource/Image/scroll_bar.png");

	for (int i = 0; i < LINE_NUM; i++) {
		mouse_status_tmp[i] = 0;
		line_clear_timer[i] = 0;
	}
	clear_screen = MakeScreen(WINDOWSIZE_X, WINDOWSIZE_Y, true); //�N���A��ʗp�̕`���
	remain_length = TOTAL_LINE_LENGTH;
	
	
	//�I�u�W�F�N�g�̏�����
	if (objectMgr != nullptr) {
		delete objectMgr;
		objectMgr = nullptr;
	}
	objectMgr = new ObjectMgr();
	menu = new Button(75, 50, 100, 50, "Menu");
	carriage = new Carriage();
	objectMgr->add(carriage);
	objectMgr->add(new EnemyFactory());
	objectMgr->add(menu);

	//�T�E���h�̓ǂݍ���
	bgm_maingame = Sound("Resource/Sound/bgm.ogg");
	se_clear = Sound("Resource/Sound/se_clear.ogg");
	se_gameover = Sound("Resource/Sound/se_gameover.ogg");
	se_pause = Sound("Resource/Sound/se_title.ogg");
	bgm_maingame.changeVolume(190);
}

void MainGame_Update()
{
	bgm_maingame.play(DX_PLAYTYPE_LOOP, true); //bgm�Đ�

	if (timer <= TIME_LIMIT && castle_flag == 0) {		//���Ԑ���������ɓ��B���Ă��Ȃ��Ƃ�
		road_y += speed;		//1�t���[�����Ƃɒn�ʂ�speed���ړ�����

		if (speed < FIRST_SPEED * 2)  //���񂾂��������
			speed += 0.001;
		if (remain_length < TOTAL_LINE_LENGTH)  //�����钷�������񂾂�񕜂���
			remain_length += 1.0 * TOTAL_LINE_LENGTH / 10000;

		if (road_y >= WINDOWSIZE_Y)		//�n�ʂ̍��W��WINDOWSIZE_Y�𒴂�����0�ɖ߂�
			road_y = 0;
		timer++;				//1�t���[�����Ƃ�1�ǉ�
		run_length += speed;	//����������
		if (run_length >= castle_length) {
			castle_flag = 1;					//��ɓ��B�����ꍇ�铞�B�t���O��1��
			objectMgr->del(menu);
			objectMgr->update();
		}
		//�}�E�X�̏���
		if (GetMouseInput() & MOUSE_INPUT_LEFT && mouse_status < POINT_NUM && line_length[line_count - 1] < LINE_LENGTH && remain_length >= line_length[line_count - 1]) {			//�}�E�X�̍��N���b�N�������ꂽ��
			mouse_status++;									//�}�E�X�̍��N���b�N�������ꂽ�t���[�����𑪒�
			if (mouse_status == 1) {						//���݈����Ă�����̖{����ۑ�
				line_count++;
			}
			if (line_count > LINE_NUM)
				line_count = 1;

			if (mouse_status > 0 && mouse_status <= POINT_NUM)	//���N���b�N��������Ă���ԃ}�E�X�̍��W��ۑ�
			{
				GetMousePoint(&mouse_x[line_count - 1][mouse_status - 1], &mouse_y[line_count - 1][mouse_status - 1]);
			}
			mouse_status_tmp[line_count - 1] = mouse_status;
			line_length[line_count - 1] = 0;
			for (int i = 0; i < mouse_status_tmp[line_count - 1] - 1; i++)		//���̒����𑪂�
			{
				line_length[line_count - 1] += sqrt(pow(mouse_x[line_count - 1][i] - mouse_x[line_count - 1][i + 1], 2) + pow(mouse_y[line_count - 1][i] - mouse_y[line_count - 1][i + 1], 2));
			}

		}
		else if (!(GetMouseInput() & MOUSE_INPUT_LEFT)) {
			if (line_count > 0 && mouse_status > 0) {
				objectMgr->add(new BlockFactory(mouse_x[line_count - 1], mouse_y[line_count - 1], mouse_status));
				remain_length -= line_length[line_count - 1];
				if (remain_length < 0)  remain_length = 0;
			}
			line_length[line_count - 1] = 0;
			mouse_status = 0;
			for (int i = 0; i < LINE_NUM; i++)
				line_clear(mouse_x[i], mouse_y[i], POINT_NUM, &mouse_status_tmp[i], &line_clear_timer[i], 10);		//������������莞�Ԃŏ���
		}


		objectMgr->update(); //�I�u�W�F�N�g�̃A�b�v�f�[�g
	}

	else if (castle_flag == 1) {			//��ɓ��B�����ꍇ
		speed = std::cos(castle_y / WINDOWSIZE_Y * PI / 2) * (FIRST_SPEED - 1) + 1;  //��邭����
		bgm_maingame.stop();

		if (castle_y < WINDOWSIZE_Y) {
			castle_y += speed;
			
		}
		if (castle_y >= WINDOWSIZE_Y) {
			if (blend_alpha < 255) {
				blend_alpha += 5;
				se_clear.play(DX_PLAYTYPE_BACK, true);  //�N���ASE�̍Đ�
			}
			if (blend_alpha > 255)
				blend_alpha = 255;
		}
		if (blend_alpha >= 255) {
			if (mouse_status > 0)
				mouse_status--;
			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				mouse_status = 3;
			}
			if (Mouse[MOUSE_LEFT] == 1) {
				Title_Init();
				gameMode = Title;
				MainGame_Init();
				se_clear.stop();
			}
		}

	}
	else {					//�������Ԃ𒴂����ꍇ
		if(mouse_status > 0)
			mouse_status--;
		castle_flag = 0;
		bgm_maingame.stop();
		blend_alpha += 5;
		if (blend_alpha < 255 && blend_alpha >= 200) {
			se_gameover.play(DX_PLAYTYPE_BACK, true);  //�Q�[���I�[�o�[SE�̍Đ�
		}
		if (blend_alpha > 255)
			blend_alpha = 255;
		if (blend_alpha >= 255) {
			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				mouse_status = 3;
			}
			if (Mouse[MOUSE_LEFT] == 1) {
				Title_Init();
				gameMode = Title;
				MainGame_Init();
			}
		}

		bgm_maingame.stop();
	}


	//���j���[�{�^���������ꂽ�ꍇ�̏���
	if (menu->isReleased()) {
		gameMode = Pause;
		Pause_Init();
		bgm_maingame.stop();
		se_pause.play(DX_PLAYTYPE_BACK, true);
	}

}

void MainGame_Draw()
{
	//�^�C�g���ɖ߂�Ƃ��`����s��Ȃ�
	if (gameMode == Title) return;

	//��ɓ��B�����ꍇ
	if (castle_flag == 1)
		SetDrawScreen(clear_screen); //�`����ύX

	//�n�ʂ̕`��
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y - WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y + WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);

	objectMgr->draw();//�I�u�W�F�N�g�̕`��

	//�}�E�X�̕`��
	for (int j = 0; j < LINE_NUM; j++)
		for (int i = 1; i < mouse_status_tmp[j] - 1; i++)
			if (mouse_status <= POINT_NUM){
				//�����Ă銴���̐��Ɍ�������
				int color = 0xFE44FE;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], color, 12);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], color, 10);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], color, 8);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], color, 6);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], color, 4);
				DrawLineAA(mouse_x[j][i - 1], mouse_y[j][i - 1], mouse_x[j][i], mouse_y[j][i], color, 2);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			}
	/*counter(mouse_status_tmp[0], WINDOWSIZE_X - 100, 100, 2);
	counter(mouse_status_tmp[1], WINDOWSIZE_X - 100, 150, 2);
	counter(mouse_status_tmp[2], WINDOWSIZE_X - 100, 200, 2);
	counter(mouse_status_tmp[3], WINDOWSIZE_X - 100, 250, 2);
	counter(mouse_status_tmp[4], WINDOWSIZE_X - 100, 300, 2);
	counter(mouse_x[3][1], WINDOWSIZE_X - 100, 400, 2);
	counter(line_count, WINDOWSIZE_X - 100, 500, 2);*/

	//�`�����Ƃ��ł�����̎c��̒���(��)
	DrawBox(WINDOWSIZE_X - 200, 500, WINDOWSIZE_X - 50, 530, GetColor(255, 255, 255), TRUE);
	DrawBox(WINDOWSIZE_X - 195, 505, WINDOWSIZE_X - 55, 525, GetColor(255, 50, 50), TRUE);
	DrawBox(WINDOWSIZE_X - 195 + 140 * (remain_length / TOTAL_LINE_LENGTH), 505, WINDOWSIZE_X - 55, 525, GetColor(200, 200, 200), TRUE);
	/*for (int i = 0; i < LINE_NUM; i++)
	{
		DrawBox(WINDOWSIZE_X - 55 - 110 * (line_length[i] / LINE_LENGTH), 505, WINDOWSIZE_X - 55, 525, GetColor(200, 200, 200), TRUE);
	}
	if (mouse_status >= POINT_NUM || line_length[line_count - 1] >= LINE_LENGTH)
		DrawBox(WINDOWSIZE_X - 195, 505, WINDOWSIZE_X - 55, 525, GetColor(200, 200, 200), TRUE);*/
	

	if (castle_flag == 0) {
		//��܂ł̋���
		DrawBox((WINDOWSIZE_X / 2) - 200, 525, (WINDOWSIZE_X / 2) + 200, 535, GetColor(255, 255, 255), TRUE);
		//DrawBox((WINDOWSIZE_X / 2) - 195 + 400 * run_length / castle_length, 515, (WINDOWSIZE_X / 2) - 205 + 400 * run_length / castle_length, 525, GetColor(100, 255, 100), TRUE);
		DrawRotaGraph((WINDOWSIZE_X / 2) - 200 + 400 * run_length / castle_length, 510, 0.3, 0, scroll_bar_grHandle, 1);

		//�c�莞�Ԃ̕`��
		DrawRotaGraph(WINDOWSIZE_X - 50, 50, 0.5, 0, clock_grHandle, 1);
		DrawRotaGraph(WINDOWSIZE_X - 50, 50, 0.5, 2 * PI * timer / (TIME_LIMIT), clock_hand_grHandle, 1);
		//counter((TIME_LIMIT - timer) / 60, WINDOWSIZE_X - 100, 200, 2);
	}
	

	//��ɓ��B�����ꍇ
	if (castle_flag == 1) { //�`���𗠉�ʂɖ߂��ĕ`��
		SetDrawScreen(DX_SCREEN_BACK);
		DrawRotaGraph(WINDOWSIZE_X / 2, castle_y + WINDOWSIZE_Y / 2, 1, 0, clear_screen, 1);
		DrawRotaGraph(WINDOWSIZE_X / 2, castle_y - WINDOWSIZE_Y / 2, 1, 0, castle_grHandle, 1); //��̕`��
		if (castle_y >= WINDOWSIZE_Y) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend_alpha);
			DrawStringToHandle(WINDOWSIZE_X / 2 - 195, WINDOWSIZE_Y / 2 - 50, "GAME CLEAR", 0x000000, FontHandle);
			DrawStringToHandle(WINDOWSIZE_X / 2 - 200, WINDOWSIZE_Y / 2 - 55, "GAME CLEAR", 0xffffff, FontHandle);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			if (blend_alpha >= 255) {
				DrawString(WINDOWSIZE_X / 2 - 80, WINDOWSIZE_Y - 120, "Click to back to title", 0xffffff);
				DrawFormatString(WINDOWSIZE_X - 180, 50, 0xffffff, "Time : %.2f", (double)timer / 60);
			}
		}

	}

	//���Ԑ����𒴂����ꍇ
	if (timer > TIME_LIMIT) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend_alpha);
		DrawBox(0, 0, WINDOWSIZE_X, WINDOWSIZE_Y, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		if (blend_alpha >= 255) {
			DrawStringToHandle(WINDOWSIZE_X / 2 - 195, WINDOWSIZE_Y / 2 - 50, "GAME OVER", 0xffffff, FontHandle);
			DrawString(WINDOWSIZE_X / 2 - 80, WINDOWSIZE_Y - 120, "Click to back to title", 0xffffff);
		}
	}
}

void counter(int num, int x, int y, int block_exRate)		//������\������֐��A�����͐擪����\�����鐔���Ax���W�Ay���W�A�\���{��
{
	DrawRotaGraph(x - 2 * (16) * block_exRate, y, block_exRate, 0, number_grHandle[num / 100], 1);
	DrawRotaGraph(x - (16) * block_exRate, y, block_exRate, 0, number_grHandle [(num / 10) % 10] , 1);
	DrawRotaGraph(x, y, block_exRate, 0, number_grHandle[(num) % 10], 1);
}

void line_clear(int *mouse_x, int *mouse_y, int num, int *mouse_status, int *clear_timer, int frame)	//�`�悵�����������֐��A�����͐擪�����������x���W�Ay���W�A���W�̌��A�����n�߂�m�邽�߂Ƀt���[�����i�[�����ϐ��A���Ԍv���̕ϐ��A�����܂ł̃t���[����
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


void Pause_Init() {
	changeScene_Pause_to_MainGame = false;
	brightPause = 96;

	//�I�u�W�F�N�g�̏�����
	if (pauseObjectMgr != nullptr) {
		delete pauseObjectMgr;
		pauseObjectMgr = nullptr;
	}
	pauseObjectMgr = new ObjectMgr();
	resume = new Button(WINDOWSIZE_X / 2, WINDOWSIZE_Y / 2 - 50, 150, 50, "Continue");
	restart = new Button(WINDOWSIZE_X / 2, WINDOWSIZE_Y / 2 + 50, 150, 50, "Retry");
	pauseObjectMgr->add(resume);
	pauseObjectMgr->add(restart);
}

void Pause_Update() {
	if (changeScene_Pause_to_MainGame == 0) {
		pauseObjectMgr->update();
	}

	//�{�^���������ꂽ�ꍇ
	if (resume->isReleased()) {
		changeScene_Pause_to_MainGame = true;
	}
	if (restart->isReleased()) {
		MainGame_Init();
		gameMode = MainGame;
	}

	//�|�[�Y�����̏���
	if (changeScene_Pause_to_MainGame) {
		brightPause += 5;
	}
	if (brightPause >= 255) {
		gameMode = MainGame;
		bgm_maingame.play(DX_PLAYTYPE_LOOP, false); //bgm�Đ�
	}
}

void Pause_Draw() {
	SetDrawBright(brightPause, brightPause, brightPause);
	MainGame_Draw();
	SetDrawBright(255, 255, 255);
	if (changeScene_Pause_to_MainGame == 0) {
		pauseObjectMgr->draw();
	}
}