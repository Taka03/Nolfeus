//================================================
//gauge.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"

//================================================
//define
//================================================
const int TYPE_LIFE = 2;
const int GAUGE_MAX = 100;

//================================================
//class
//================================================
class CGauge
{
	private:
		
		float fPosX;//X���W
		float fPosY;//Y���W
		
		Sint32 Angle;//�p�x
		
		int counter;//�ėp�J�E���^�[
		
		int Width;//��
		int Height;//����
		
		float radius;//���a
		
		CVector2D pPos;
		CIRCLE2D Circle;
		
		int GAUGE_MIN;//�Q�[�W�̍ŏ��l
		
		LLINE lLine;//���C���n���h��
		
		LMATRIX Matrix;//�s��n���h��
		
		LTEXTURE Tex;//�e�N�X�`���n���h��
		LSPRITE Spr;//�X�v���C�g�n���h��
		
		LUNARECT Dst;//�`���
		LUNARECT Src;//�`�挳

	public:
	
		int ability;//�A�r���e�B�Q�[�W�p
		
		CGauge();//�R���X�g���N�^
		CGauge(float posx, float posy);//�R���X�g���N�^
		virtual ~CGauge();//�f�X�g���N�^
		
		void Initialize(void);//������
		void SetPosition(float posx, float posy);//�ʒu�Z�b�g
		void SetGraphInfo(int width, int height);//�摜���Z�b�g
		
		void AddGauge(bool *Flag);//�Q�[�W�̑���
		
		void LoadImage(char *name, int ColorKey);//�e�N�X�`���ǂݍ���
		void CreateSprite(void);//�X�v���C�g����
		
		void PolarTrans(float x, float y);//�ɍ��W�ϊ�
		
		void Draw(int Hp, int Color);//�`��
		void Draw(void);//�`��
		void DrawLine(float posx, float posy, int Hp);
		
		void Draw(float posx, float posy, int Hp);
		void DrawCircuit(void);//�~�`�`��
		
		void Rendering(void);//�����_�����O
		
		void Release(void);//�������J��
		
		//LoadImage();
};
