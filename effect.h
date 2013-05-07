//================================================
//effect.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"

//================================================
//class
//================================================
class CEffect
{
	private:
		
		float fPosX;//X���W
		float fPosY;//Y���W
		
		int Width;//��
		int Height;//����
		
		int Divnum;
		
		LTEXTURE Tex;//�e�N�X�`���n���h��
		LSPRITE Spr;//�X�v���C�g�n���h��
		
		LUNARECT Dst;//�`���
		LUNARECT Src;//�`�挳
		
	public:
	
		int animcounter;//�A�j���p�J�E���^
		int counter;//�ėp�J�E���^
		
		bool IsExist;//���ݔ���t���O
		
		CEffect();//�R���X�g���N�^
		virtual ~CEffect();//�f�X�g���N�^
		
		void Initialize(void);//������
		
		void LoadImage(char *name, int ColorKey);//�e�N�X�`���ǂݍ���
		void CreateSprite(void);//�X�v���C�g����
		
		void Set(int width, int height, int divnum);//�摜���Z�b�g
		
		void Draw(float posx, float posy);//�`��
		void Rendering();//�����_�����O
		
		void Debug();//�f�o�b�O
		
		void Release(void);//�������J��
		
};
