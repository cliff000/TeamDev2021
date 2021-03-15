#include "DxLib.h"
#include "ObjectMgr.h"
#include "Carriage.h"
#include "EnemyFactory.h"
#include "Block.h"
#include "main.h"

#define LINE_NUM 5			//�������Ƃ̂ł�����̖{��
#define POINT_NUM 50		//�������̍��W�����邩

int road_grHandle;		//�n�ʂ̃O���t�B�b�N
double road_y;			//�n�ʂ�y���W
double speed;			//����
int carriage_grHandle;	//�n�Ԃ̃O���t�B�b�N
int timer;				//���Ԑ����p�̃^�C�}�[
int number_grHandle[10];		//�^�C�}�[�̃O���t�B�b�N(��)
int time_limit;			//��������
int run_length;			//�����������̑���
int castle_grHandle;	//��̃O���t�B�b�N
double castle_y;		//���y���W
int castle_length;		//��܂ł̓��̂�̒���
int castle_flag;		//�铞�B�t���O�A1�œ��B
int mouse_x[LINE_NUM][POINT_NUM];
int mouse_y[LINE_NUM][POINT_NUM];		//�}�E�X��x�Ay���W�̕ۑ�
int mouse_status;		//�}�E�X�����t���[���̊ԉE�N���b�N���ꂽ��
int mouse_status_tmp[LINE_NUM];	//��L�Ƃقړ����A������x�����ꂽ�^�C�~���O�ŏ�����
int line_count;			//���݉��{�ڂ̐��������Ă��邩
int line_clear_timer[LINE_NUM];	//�������Ԍo�߂ŏ������߂̃^�C�}�[

void MainGame_Init();
void MainGame_Update();
void MainGame_Draw();
void counter(int num, int x, int y, int block_exRate);
void line_clear(int mouse_x[], int mouse_y[], int num, int *mouse_status, int *clear_timer, int frame);	//�`�悵�����������֐��A�����͐擪�����������x���W�Ay���W�A���W�̌��A�����n�߂�m�邽�߂Ƀt���[�����i�[�����ϐ��A���Ԍv���̕ϐ��A�����܂ł̃t���[����

ObjectMgr *objectMgr = new ObjectMgr();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 16);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	MainGame_Init();

	// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		MainGame_Update();
		MainGame_Draw();
	}
	DxLib_End(); // DX���C�u�����I������
	return 0;
}

void MainGame_Init()
{
	SetTransColor(0, 255, 0);
	road_grHandle = LoadGraph("Resource/Image/floor.png");
	road_y = 0;				//�n�ʂ�y���W�̏�����
	speed = 5;				//�X�s�[�h�̏�����
	carriage_grHandle = LoadGraph("Resource/Image/carriage.png");
	timer = 0;				//�^�C�}�[�̏�����
	LoadDivGraph("Resource/Image/number.png", 10, 10, 1, 16, 16, number_grHandle);
	time_limit = 20*60;		//�������Ԃ̐ݒ�(���݂�20�b)
	run_length = 0;			//�����������̏�����
	castle_grHandle = LoadGraph("Resource/Image/castle.png");
	castle_y = 0;			//���y���W�̏�����
	castle_length = speed * 20 * 60;	//��܂ŏ����X�s�[�h��10�b����Ɠ��B
	castle_flag = 0;		//�铞�B�t���O�̏�����
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
	if (timer <= time_limit && castle_flag == 0) {		//���Ԑ���������ɓ��B���Ă��Ȃ��Ƃ�
		road_y += speed;		//1�t���[�����Ƃɒn�ʂ�speed���ړ�����
		if (road_y >= WINDOWSIZE_Y)		//�n�ʂ̍��W��WINDOWSIZE_Y�𒴂�����0�ɖ߂�
			road_y = 0;
		timer++;				//1�t���[�����Ƃ�1�ǉ�
		run_length += speed;	//����������
		if (run_length >= castle_length)
			castle_flag = 1;					//��ɓ��B�����ꍇ�铞�B�t���O��1��
		//�}�E�X�̏���
		if (mouse_status > 0 && mouse_status <= POINT_NUM)	//���N���b�N��������Ă���ԃ}�E�X�̍��W��ۑ�
		{
			GetMousePoint(&mouse_x[line_count-1][mouse_status - 1], &mouse_y[line_count-1][mouse_status - 1]);
		}
		if (GetMouseInput() & MOUSE_INPUT_LEFT && mouse_status < POINT_NUM) {			//�}�E�X�̍��N���b�N�������ꂽ�t���[�����𑪒�
			mouse_status++;									//�t���[�������i�[
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

	else if (castle_flag == 1) {			//��ɓ��B�����ꍇ
		if (speed > 0) {		//��邭����
			speed -= 0.1;
			road_y += speed;
			castle_y += speed;
		}
	}
	else {					//�������Ԃ𒴂����ꍇ
		castle_flag = 0;
	}


	
	
	objectMgr->update(); //�I�u�W�F�N�g�̃A�b�v�f�[�g
}

void MainGame_Draw()
{
	//�n�ʂ̕`��
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y - WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y + WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);
	//�}�E�X�̕`��
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

	//�^�C�}�[�̕`��
	counter((time_limit - timer) / 60, WINDOWSIZE_X - 100, 50, 2);
	//��̕`��
	if (castle_flag == 1)
		DrawRotaGraph(WINDOWSIZE_X / 2, castle_y - WINDOWSIZE_Y / 2, 1, 0, castle_grHandle, 1);


	objectMgr->draw();//�I�u�W�F�N�g�̕`��
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