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
		
		LSOUND Snd;//�T�E���h�n���h��
	
	public:
	
		CSound();//�R���X�g���N�^
		~CSound();//�f�X�g���N�^
		
		void LoadSound(char *name);//�T�E���h�t�@�C���ǂݍ���
		void PlaySound(float volume);//�T�E���h�Đ�
		void PlaySound(void);
		void PlaySound(int loop, int sampoint);
		
		void StopSound(void);//�T�E���h��~
		void Release(void);//�������J��
};
