//================================================
//include
//================================================
#include "function.h"
#include "gamemode.h"

//================================================
//�p�b�h�����֐�
//================================================
void PadProcess(void)
{
	//----------------------------------------
	//�p�b�h�V�X�e���̏�����
	//----------------------------------------
	LunaPad::Initialize(1, TRUE, FRAME_RATE / 2, FRAME_RATE / 20 );
	
	/*POV���g��*/
	LunaPad::UsePOVDirection(0, true);
	
	/*�p�b�h1�̃{�^�����蓖��*/
	LunaPad::SetButton(0, PAD_BUTTON_01, PAD_BUTTON_A);//�{�^��1���p�b�h�̃{�^��0�Ɋ��蓖��
	
	LunaPad::SetButton(0, PAD_BUTTON_02, PAD_BUTTON_B);//�{�^��2���p�b�h�̃{�^��1�Ɋ��蓖��
	
	LunaPad::SetButton(0, PAD_BUTTON_03, PAD_BUTTON_X);//�{�^��3���p�b�h�̃{�^��2�Ɋ��蓖��
	
	LunaPad::SetButton(0, PAD_BUTTON_04, PAD_BUTTON_Y);//�{�^��4���p�b�h�̃{�^��3�Ɋ��蓖��
	
	LunaPad::SetButton(0, PAD_BUTTON_05, PAD_BUTTON_START);//�{�^��5���p�b�h�̃{�^��7�Ɋ��蓖��
	
	/*�L�[�{�[�h�̃G�C���A�X(�p�b�h1)*/
	LunaPad::SetAlias(0, PAD_BUTTON_01, DIK_Z);//�{�^��1��Z�Ɋ��蓖��
	
	LunaPad::SetAlias(0, PAD_BUTTON_02, DIK_X);//�{�^��2��X�Ɋ��蓖��
	
	LunaPad::SetAlias(0, PAD_BUTTON_03, DIK_C);//�{�^��3��C�Ɋ��蓖��
	
	LunaPad::SetAlias(0, PAD_BUTTON_04, DIK_V);//�{�^��4��V�Ɋ��蓖��
	
	LunaPad::SetAlias(0, PAD_BUTTON_05, DIK_S);//�{�^��5��S�Ɋ��蓖��
	
	LunaPad::SetAlias(0, PAD_DIR_UP, DIK_UP);//�����L�[�{�[�h�́��Ɋ��蓖��
	
	LunaPad::SetAlias(0, PAD_DIR_DOWN, DIK_DOWN);//�����L�[�{�[�h�́��Ɋ��蓖��
	
	LunaPad::SetAlias(0, PAD_DIR_LEFT, DIK_LEFT);//�����L�[�{�[�h�́��Ɋ��蓖��
	
	LunaPad::SetAlias(0, PAD_DIR_RIGHT, DIK_RIGHT);//�����L�[�{�[�h�́��Ɋ��蓖��
		
}

//================================================
//�����蔻��
//================================================
bool HitCheck(RECT2D &Rect1, RECT2D &Rect2)
{
	if(LunaCollision::Rect_Rect(&Rect1, &Rect2) )
	{
		return true;
	}
	
	else 
	{
		return false;
	}
}

//==========================================================
//��b�p�X�N���v�g�ǂݍ���
//==========================================================
int LoadScriptData(char *datname, int max, char **data)
{
	FILE *fp;
	
	fp = fopen(datname, "r");
	
	if(fp == NULL)
	{
		return 0;
	}
	
	/*�}�b�v������ǂݍ���*/
	for(int i = 0;i < max;i++)
	{
		fgets(data[i], 256, fp);
	}
	
	fclose(fp);
	
	return 0;
}


