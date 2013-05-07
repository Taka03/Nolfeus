//================================================
//include
//================================================
#include "function.h"
#include "gamemode.h"

//================================================
//パッド処理関数
//================================================
void PadProcess(void)
{
	//----------------------------------------
	//パッドシステムの初期化
	//----------------------------------------
	LunaPad::Initialize(1, TRUE, FRAME_RATE / 2, FRAME_RATE / 20 );
	
	/*POVを使う*/
	LunaPad::UsePOVDirection(0, true);
	
	/*パッド1のボタン割り当て*/
	LunaPad::SetButton(0, PAD_BUTTON_01, PAD_BUTTON_A);//ボタン1をパッドのボタン0に割り当て
	
	LunaPad::SetButton(0, PAD_BUTTON_02, PAD_BUTTON_B);//ボタン2をパッドのボタン1に割り当て
	
	LunaPad::SetButton(0, PAD_BUTTON_03, PAD_BUTTON_X);//ボタン3をパッドのボタン2に割り当て
	
	LunaPad::SetButton(0, PAD_BUTTON_04, PAD_BUTTON_Y);//ボタン4をパッドのボタン3に割り当て
	
	LunaPad::SetButton(0, PAD_BUTTON_05, PAD_BUTTON_START);//ボタン5をパッドのボタン7に割り当て
	
	/*キーボードのエイリアス(パッド1)*/
	LunaPad::SetAlias(0, PAD_BUTTON_01, DIK_Z);//ボタン1をZに割り当て
	
	LunaPad::SetAlias(0, PAD_BUTTON_02, DIK_X);//ボタン2をXに割り当て
	
	LunaPad::SetAlias(0, PAD_BUTTON_03, DIK_C);//ボタン3をCに割り当て
	
	LunaPad::SetAlias(0, PAD_BUTTON_04, DIK_V);//ボタン4をVに割り当て
	
	LunaPad::SetAlias(0, PAD_BUTTON_05, DIK_S);//ボタン5をSに割り当て
	
	LunaPad::SetAlias(0, PAD_DIR_UP, DIK_UP);//↑をキーボードの↑に割り当て
	
	LunaPad::SetAlias(0, PAD_DIR_DOWN, DIK_DOWN);//↓をキーボードの↓に割り当て
	
	LunaPad::SetAlias(0, PAD_DIR_LEFT, DIK_LEFT);//←をキーボードの←に割り当て
	
	LunaPad::SetAlias(0, PAD_DIR_RIGHT, DIK_RIGHT);//→をキーボードの→に割り当て
		
}

//================================================
//当たり判定
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
//会話用スクリプト読み込み
//==========================================================
int LoadScriptData(char *datname, int max, char **data)
{
	FILE *fp;
	
	fp = fopen(datname, "r");
	
	if(fp == NULL)
	{
		return 0;
	}
	
	/*マップ文字列読み込み*/
	for(int i = 0;i < max;i++)
	{
		fgets(data[i], 256, fp);
	}
	
	fclose(fp);
	
	return 0;
}


