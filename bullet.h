//================================================
//bullet.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "sound.h"

//================================================
//define
//================================================
#define BULLET_MAX 20

//================================================
//enum
//================================================
enum
{
	PLAYER,
	ENEMY,
};

//================================================
//class
//================================================
class CBullet
{
	private:

		float fPosX[BULLET_MAX];//X���W
		float fPosY[BULLET_MAX];//Y���W
		
		float fOldPosX[BULLET_MAX];//X���W(�ێ��p)
		float fOldPosY[BULLET_MAX];//Y���W(�ێ��p)
		
		float Vx[BULLET_MAX];//X���x
		float Vy[BULLET_MAX];//Y���x

		int Width;//��
		int Height;//����
		
		int Divnum;//������
		
		float DisX;//X����
		float DisY;//Y����
		
		int count_charge;//�`���[�W�J�E���g
		
		float fTime;//����
		Sint32 fAngle[BULLET_MAX];//�p�x
		
		int COMP;//�����蔻��␳�l
		int CHARGE_MAX;//�`���[�W�J�E���g��Max
		
		LTEXTURE Tex;//�e�N�X�`���n���h��
		LSPRITE Spr;//�X�v���C�g�n���h��
		
		LUNARECT Dst;//�`���
		LUNARECT Src;//�`�挳
		
		enum
		{
			SE_REFRECT,
			SE_SHOT,
			SE_MAX,
		};
		
		CSound Se[SE_MAX];
		
		void LoadSound();
		
	public:

		
		bool Flag[BULLET_MAX];//�e�����Ă邩�ǂ���(�t���O)
		bool ChargeFlag;//�`���[�W�V���b�g�p�t���O
		bool IsRefrect[BULLET_MAX];//���˔���t���O
		
		int counter;//�ėp�J�E���^�[
		int trigger;//�e�̃g���K�[
		int umbcounter;//�P�p�J�E���^�[
		
		int animcounter;//�A�j���p�J�E���^
		
		int Attack;//�U����
		
		RECT2D HitRect[BULLET_MAX];//�����蔻��p
		RECT DHitRect[BULLET_MAX];
		
		CBullet();//�R���X�g���N�^
		virtual ~CBullet();//�f�X�g���N�^
		
		void Initialize(void);//������
		
		void SetRect(void);//�����蔻��̈�ݒ�
		void SetPosition(int no);
		void SetGraphInfo(int width, int height, int divnum);
		
		void LoadImage(char *name, int ColorKey);//�e�N�X�`���ǂݍ���
		void CreateSprite(void);//�X�v���C�g����
		
		void CreateBullet(float posx, float posy, int num);//�e�̐���
		void CreateBullet(float posx, float posy, float tax, float tay);//�e�̐���(�p�x��) 
		void CreateBullet(float posx, float posy);//��Ēe�̐���
		void CreateBullet(float posx, float posy, Sint32 Angle);//n-way�e�̐���
		void CreateBossBullet(float posx, float posy, float tax, float tay);
		void CreateRefBullet(float posx, float posy, int num);//���˒e����
		
		
		void Move(int Type);//�e�̓���
		
		void Shoot(float posx, float posy);//�e������
		
		void Refrect(float posx, float posy);//���˒e
		
		void ChargeShoot(void);//�`���[�W�V���b�g
		void UmbrellaAttack(float posx, float posy);//�P�U��
		void PutAttack(void);//�ݒu�U��
		
		void LoadPattern(int Pattern);//�p�^�[���ǂݏo��
//		void MovePattern
		void MovePattern1(void);//�e�̃p�^�[��1(����)
		void MovePattern2(void);//�e�̃p�^�[��2
		void MovePattern3(void);//�e�̃p�^�[��3
		void MovePattern4(float posx, float posy);//�e�̃p�^�[��4(�U�e)
		void MovePattern5(float posx, float posy);//�e�̃p�^�[��5(��]�e)
		void MovePattern6(void);//�e�̃p�^�[��6
		
		void Draw(void);//�`��
		void Rendering(void);//�����_�����O
		
		void MoveAdjust(int left, int right, int top, int bottom);//�ړ��␳
		
		void Release(void);//�������J��
		void Debug(void);//�f�o�b�O�p�֐�
		
};

