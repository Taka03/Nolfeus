//================================================
//sound.h
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
	BGM_TITLE,
	BGM_MAIN,
	BGM_BOSS,
	BGM_GAMEOVER,
};


//================================================
//class
//================================================
class CSound
{
	private:
		
		LSOUND Snd;//サウンドハンドル
	
	public:
	
		CSound();//コンストラクタ
		~CSound();//デストラクタ
		
		void LoadSound(char *name);//サウンドファイル読み込み
		void PlaySound(float volume);//サウンド再生
		void PlaySound(void);
		void PlaySound(int loop, int sampoint);
		
		void StopSound(void);//サウンド停止
		void Release(void);//メモリ開放
};
