#include "DxLib.h"

int road_grHandle;		//�n�ʂ̃O���t�B�b�N
int road_y;			//�n�ʂ�y���W
int speed;			//����
int carriage_grHandle;	//�n�Ԃ̃O���t�B�b�N

void MainGame_Init();
void MainGame_Update();
void MainGame_Draw();

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
	speed = 5;
	carriage_grHandle = LoadGraph("Resource/Image/carriage.png");
}

void MainGame_Update()
{
	road_y += speed;		//1�t���[�����Ƃɒn�ʂ�speed���ړ�����
	if (road_y >= 480)		//�n�ʂ̍��W��480�𒴂�����0�ɖ߂�
		road_y = 0;
}

void MainGame_Draw()
{
	DrawRotaGraph(320, road_y - 240, 1, 0, road_grHandle, 1);
	DrawRotaGraph(320, road_y + 240, 1, 0, road_grHandle, 1);
	DrawRotaGraph(320, 360, 4, 0, carriage_grHandle, 1);
}