//================================================
//function.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"

//================================================
//enum
//================================================
enum
{
	PAD_BUTTON_A,
	PAD_BUTTON_B,
	PAD_BUTTON_X,
	PAD_BUTTON_Y,
	PAD_BUTTON_START = 7,	
};


//================================================
//�v���g�^�C�v�錾
//================================================
void PadProcess(void);//�p�b�h����

bool HitCheck(RECT2D &Rect1, RECT2D &Rect2);//�����蔻��`�F�b�N

int LoadScriptData(char datname, int max, char **data);//

void Fadein(void);//�t�F�[�h�C��
void Fadeout(void);//�t�F�[�h�A�E�g

















