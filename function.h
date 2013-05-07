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
//プロトタイプ宣言
//================================================
void PadProcess(void);//パッド処理

bool HitCheck(RECT2D &Rect1, RECT2D &Rect2);//当たり判定チェック

int LoadScriptData(char datname, int max, char **data);//

void Fadein(void);//フェードイン
void Fadeout(void);//フェードアウト

















