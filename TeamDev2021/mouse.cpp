#include "Dxlib.h"
#include "mouse.h"

int Mouse[BUTTON_NUM + 2]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateMouse() {
	int nowInput = GetMouseInput();      //���̃L�[�̓��͏�Ԃ��擾
	for (int i = 0; i<BUTTON_NUM; i++) {
		if ((nowInput >> i) & 0x01) {    //i�Ԃ̃L�[��������Ă�����
			Mouse[i]++;          //�J�E���^�𑝂₷
		}
		else { //������Ă��Ȃ����
			Mouse[i] = 0;    //0�ɖ߂�
		}
	}
	GetMousePoint(&Mouse[MOUSE_X], &Mouse[MOUSE_Y]);

	return 0;
}