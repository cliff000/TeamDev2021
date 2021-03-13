#include "DxLib.h"
#include "ObjectMgr.h"
#include "Carriage.h"
#include "EnemyFactory.h"
#include "main.h"

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
int mouse_x[100];
int mouse_y[100];		//�}�E�X��x�Ay���W�̕ۑ�
int mouse_status;		//�}�E�X�����t���[���̊ԉE�N���b�N���ꂽ��
int mouse_status_tmp;	//��L�Ƃقړ����A������x�����ꂽ�^�C�~���O�ŏ�����

void MainGame_Init();
void MainGame_Update();
void MainGame_Draw();
void counter(int num, int x, int y, int block_exRate);

ObjectMgr *objectMgr = new ObjectMgr();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 16);

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
	castle_length = speed * 10 * 60;	//��܂ŏ����X�s�[�h��10�b����Ɠ��B
	castle_flag = 0;		//�铞�B�t���O�̏�����
	mouse_status = 0;
	
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
		if (GetMouseInput() & MOUSE_INPUT_LEFT && mouse_status < 100) {			//�}�E�X�̍��N���b�N�������ꂽ�t���[�����𑪒�
			mouse_status++;
			mouse_status_tmp = mouse_status;
		}
		else if(!(GetMouseInput() & MOUSE_INPUT_LEFT))
			mouse_status = 0;
		if (mouse_status == 1)
			mouse_status_tmp = 0;

		if (mouse_status > 0 && mouse_status <= 100)	//���N���b�N��������Ă���ԃ}�E�X�̍��W��ۑ�
		{
			GetMousePoint(&mouse_x[mouse_status-1], &mouse_y[mouse_status-1]);
		}
		
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

	objectMgr->update();
}

void MainGame_Draw()
{
	//�n�ʁE�n�Ԃ̕`��
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y - WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);
	DrawRotaGraph(WINDOWSIZE_X / 2, road_y + WINDOWSIZE_Y / 2, 1, 0, road_grHandle, 1);
	DrawRotaGraph(WINDOWSIZE_X / 2, 360, 0.5, 0, carriage_grHandle, 1);
	//�}�E�X�̕`��
	for (int i = 1; i < mouse_status_tmp; i++)
		if(mouse_status <= 100)
			DrawLineAA(mouse_x[i - 1], mouse_y[i - 1],mouse_x[i],mouse_y[i], GetColor(255, 0, 0), 1);
	//�^�C�}�[�̕`��
	counter((time_limit - timer) / 60, WINDOWSIZE_X - 100, 50, 2);
	//��̕`��
	if (castle_flag == 1)
		DrawRotaGraph(WINDOWSIZE_X / 2, castle_y - WINDOWSIZE_Y / 2, 1, 0, castle_grHandle, 1);


	objectMgr->draw();
}

void counter(int num, int x, int y, int block_exRate)		//������\������֐��A�����͐擪����\�����鐔���Ax���W�Ay���W�A�\���{��
{
	DrawRotaGraph(x - 2 * (16) * block_exRate, y, block_exRate, 0, number_grHandle[num / 100], 1);
	DrawRotaGraph(x - (16) * block_exRate, y, block_exRate, 0, number_grHandle [(num / 10) % 10] , 1);
	DrawRotaGraph(x, y, block_exRate, 0, number_grHandle[(num) % 10], 1);
}