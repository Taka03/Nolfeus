//================================================
//character.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "bullet.h"
#include "sound.h"
#include "effect.h"

//================================================
//enum
//================================================
enum
{
	SKULL,
	KNIFE,
};

//================================================
//class
//================================================
class CChara
{
	private:
		
		float fPosX;//X���W
		float fPosY;//Y���W
		
		float fOldPosX;//X���W�ێ�
		float fOldPosY;//Y���W�ێ�
		
		float fVx;//X���x
		float fVy;//Y���x
		
		Sint32 Angle;//�p�x
		
		int Width;//��
		int Height;//����
		
		int Divnum;//������
		int count_charge;//�`���[�W�J�E���g
		
		int CHARGE_MAX;//�`���[�W�ő�l
		int COMP;//�����蔻��␳�l
		
		LTEXTURE Tex;//�e�N�X�`���n���h��
		LSPRITE Spr;//�X�v���C�g�n���h��
		
		LUNARECT Dst;//�`���
		LUNARECT Src;//�`�挳
		
		enum
		{
			SE_CHARGE,
			SE_CHARGESHOT,
			SE_UMBRELLA,
			SE_MAX,
		};
		
		CSound Se[SE_MAX];
		
	public:
		
		int animcounter;//�A�j���[�V�����p�J�E���^�[
		int Attack;//�U����
		int Defence;//�h���
		
		int counter;//�P�p�J�E���^�[
		int knifecounter;
		
		bool IsExist;//���ݔ���p�t���O
		
		RECT2D HitRect;//�����蔻��
		
		CBullet bullet;//�e
		
		CEffect chargefx;
		CEffect mchargefx;
		
		CChara();//�R���X�g���N�^
		CChara(int width, int height, int divnum);//�R���X�g���N�^
		virtual ~CChara();//�f�X�g���N�^
		
		void Initialize(void);//������

		float Get_PosX(void);//X���W�𓾂�
		float Get_PosY(void);//Y���W�𓾂�
		
		void LoadImage(char *name, int ColorKey);//�e�N�X�`���ǂݍ���
		void CreateSprite(void);//�X�v���C�g����
		
		void LoadSound();//�T�E���h�ǂݍ���
		
		void Set(int width, int height, int divnum);
		void SetRect(void);//�����蔻��
		void SetPosition(float posx, float posy);
		
		void Move(void);//�ړ�
		void Shoot(void);//�e������
		
		void SetUmbrella(float posx, float posy);//�P�Z�b�g
		
		void ChargeShoot(bool *charge);//�`���[�W�V���b�g
		void PutAttack(bool *charge);//�ݒu�U��
		
		void MovePattern1(bool *charge);//�ړ��p�^�[��1
		void MovePattern3(float tax, float tay);//�ړ��p�^�[��3
		void MovePattern4();//�ړ��p�^�[��4
		
		void Draw(float posx, float posy);//�`��
		void Draw(void);//�`��
		void DrawRotate(float posx, float posy);//��]�`��
		void Rendering(void);//�����_�����O
		void Debug(void);//�f�o�b�O�p
		
		void Release(void);//�������J��
};
