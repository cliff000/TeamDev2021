#include "DxLib.h"


int mouse;
int mouseKeep;
int *mouseX, *mouseY;


void update() {
	mouse = GetMouseInput(); //�}�E�X�̓��͏�Ԏ擾

	//�}�E�X�����N���b�N����Ă���Έʒu���擾
	if (mouse & MOUSE_INPUT_LEFT) {
		GetMousePoint(mouseX, mouseY);
	}
}

void draw() {
	//�}�E�X�����N���b�N����Ă���Ε`��
	if (mouse & MOUSE_INPUT_LEFT) {
		GetMousePoint(mouseX, mouseY);
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	

	// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}
