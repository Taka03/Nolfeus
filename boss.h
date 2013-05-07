//================================================
//boss.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "character.h"
#include "gauge.h"

//================================================
//define
//================================================
const int SKULL_NUM = 4;
const int KNIFE_NUM = 5;

//================================================
//class
//================================================
class CBoss
{
	private:
		
		float fPosX;//X���W
		float fPosY;//Y���W
		
		float fVx;//X���x
		float fVy;//Y���x
		
		int Hp;//�̗�
		
		int Width;//��
		int Height;//����
		
		int DivNum;//������
		
		int dcounter;//�_���[�W�J�E���^
		
		float fTime;
		
		bool IsDamage;//�_���[�W����t���O
		bool IsDead;//���S�t���O
		
		Sint32 fAngle;//�p�x
		
		Sint32 rand;//�s���p�^�[��
		
		int SummonType;
		
		int COMP;//�����蔻��␳�l
		
		LANIMATION lAnimX;
		LANIMATION lAnimY;
		
		LTEXTURE Tex;//�e�N�X�`���n���h��
		LSPRITE Spr;//�X�v���C�g�n���h��
		
		LUNARECT Dst;//�`���
		LUNARECT Src;//�`�挳
		
		CGauge lgauge;//���C�t�Q�[�W
		
		enum
		{
			SE_SHOT,
			SE_MOVE,
			SE_MAX,
		};
		
		CSound Se[SE_MAX];
		
	public:

		bool IsExist;//���݂��邩�ǂ���
		int counter;//�ėp�J�E���^
		
		int animcounter;//�A�j���[�V�����p�J�E���^
		int Score;//�X�R�A
		int Attack;//�U����
		int Defence;//�h���
		
		RECT2D HitRect;//�����蔻��p
		
		CBullet bullet;//�e
		
		CChara skull[SKULL_NUM];
		CChara knife[KNIFE_NUM];
		
		CBoss();//�R���X�g���N�^
		virtual ~CBoss();//�f�X�g���N�^
		
		void Initialize(void);//������
		
		float Get_PosX(void);//X���W�𓾂�
		
		float Get_PosY(void);//Y���W�𓾂�
		
		int Get_Life(void);//HP�𓾂�
		
		void LoadSound(void);//�T�E���h�ǂݍ���
		
		void LoadImage(char *name, int ColorKey);//�e�N�X�`���ǂݍ���
		void CreateSprite(void);//�X�v���C�g����
		
		void Set(int width, int height, int divnum);
		void SetRect(void);//�����蔻��̈�ݒ�
		void SetPosition(float posx, float posy);//�ʒu�Z�b�g
		
		void CalcDamage(int attack, int defence);//�_���[�W�v�Z
		void Dead(int *mode);//���S����
		
		void Move(int *mode, float tax, float tay);//�ړ�
		void SummonKnife();//�i�C�t����
		void SummonSkull();//�[������
		void Shoot(float tax, float tay);//�V���b�g����
		
		void MoveAdjust(int left, int right, int top, int bottom); 
		
		void CreateKeyData(void);//�L�[�f�[�^�쐬
		
		void MovePattern1(void);//�ړ��p�^�[��1
		void MovePattern2(void);//�ړ��p�^�[��2
		void MovePattern3(void);//�ړ��p�^�[��3
		void MovePattern4(void);//�ړ��p�^�[��4
		void MovePattern5(void);
		
		void Draw(void);//�`��
		void Rendering(void);//�����_�����O
		void Debug(void);//�f�o�b�O�p
		
		void Release(void);//�������J��
};
