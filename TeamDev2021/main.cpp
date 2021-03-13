#include "DxLib.h"

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

void MainGame_Init();
void MainGame_Update();
void MainGame_Draw();
void counter(int num, int x, int y, int block_exRate);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
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
	castle_length = speed * 10 * 60;	//��܂ŏ����X�s�[�h��10�b����Ɠ��B
	castle_flag = 0;		//�铞�B�t���O�̏�����
}

void MainGame_Update()
{
	if (timer <= time_limit && castle_flag == 0) {		//���Ԑ���������ɓ��B���Ă��Ȃ��Ƃ�
		road_y += speed;		//1�t���[�����Ƃɒn�ʂ�speed���ړ�����
		if (road_y >= 480)		//�n�ʂ̍��W��480�𒴂�����0�ɖ߂�
			road_y = 0;
		timer++;				//1�t���[�����Ƃ�1�ǉ�
		run_length += speed;	//����������
		if (run_length >= castle_length)
			castle_flag = 1;					//��ɓ��B�����ꍇ�铞�B�t���O��1��
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
}

void MainGame_Draw()
{
	DrawRotaGraph(320, road_y - 240, 1, 0, road_grHandle, 1);
	DrawRotaGraph(320, road_y + 240, 1, 0, road_grHandle, 1);
	DrawRotaGraph(320, 360, 4, 0, carriage_grHandle, 1);
	counter((time_limit - timer) / 60, 600, 50, 2);			//�������Ԃ̃J�E���^�[
	if (castle_flag == 1)
		DrawRotaGraph(320, castle_y - 240, 1, 0, castle_grHandle, 1);
}

void counter(int num, int x, int y, int block_exRate)		//������\������֐��A�����͐擪����\�����鐔���Ax���W�Ay���W�A�\���{��
{
	DrawRotaGraph(x - 2 * (16) * block_exRate, y, block_exRate, 0, number_grHandle[num / 100], 1);
	DrawRotaGraph(x - (16) * block_exRate, y, block_exRate, 0, number_grHandle [(num / 10) % 10] , 1);
	DrawRotaGraph(x, y, block_exRate, 0, number_grHandle[(num) % 10], 1);
}