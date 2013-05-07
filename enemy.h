//=================================================
//enemy.h
//=================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "bullet.h"
#include "sound.h"
#include "effect.h"

//================================================
//define
//================================================
const int TYPE_MAX = 5;
const int ENEMY_NUM = 156;

//================================================
//enum
//================================================
enum eEnemyType
{
	ENEMY_NUNO,
	ENEMY_BAT,
	ENEMY_CROW,
	ENEMY_MUMMY,
	ENEMY_SPIDER,
};

//================================================
//class
//================================================
class CEnemy
{
	private:

		float fPosX;//X���W
		float fPosY;//Y���W
		
		float fVx;//X���x
		float fVy;//Y���x
		
		int Width;//��
		int Height;//����
		
		int counter;//�o���J�E���^
		int dcounter;//�_���[�W�p�J�E���^
		
		int Hp;//�̗�
		
		int DivNum;//������
		
		int Type;//�G�^�C�v
		
		char *name;//�G��
		
		Sint32 Angle;//�p�x
		float fTime;//����
		
		int COMP;//�����蔻��␳�l
		
		char Pattern[4];
		
		float rand;//�����l
		
		Sint32 rand2;
		
		bool IsDamage;//�_���[�W����t���O
		
		LTEXTURE Tex[TYPE_MAX];//�G�e�N�X�`���n���h��
		LSPRITE Spr[TYPE_MAX];//�G�X�v���C�g�n���h��
		
		LANIMATION lAnimX;
		LANIMATION lAnimY;
		
		LUNARECT Dst;//�`���
		LUNARECT Src;//�`�挳
		
		typedef struct DATA
		{
			int Attack;
			int Defence;
			int Hp;
			int Score;
			int Width;
			int Height;
			int Divnum;
		};
		
		typedef struct EPOINT
		{
			int point;//�o���|�C���g
			eEnemyType Type;//�^�C�v
		};
		
		enum
		{
			SE_SHOT,
			SE_CROW,
			SE_BAT,
			SE_MAX,
		};
		
		DATA edata[TYPE_MAX];
		
		CSound Se[SE_MAX];
		
		CEffect burst;//�����G�t�F�N�g
		
		void LoadEffect();//�G�t�F�N�g�ǂݍ���
		

	public:

		int Score;//�X�R�A
		int animcounter;//�A�j���p�J�E���^�[
		
		int Attack;//�U����
		int Defence;//�h��́@
		
		bool IsExist;//�G�����݂��邩
		bool IsDead;//�G�����S������
		
		EPOINT epoint[ENEMY_NUM];
		
		RECT2D HitRect;//�����蔻��p
		
		CBullet bullet;//�e
		
		CEnemy();//�R���X�g���N�^
		virtual ~CEnemy();//�f�X�g���N�^
		
		void Initialize(void);//������
		
		float Get_PosX(void);//X���W�𓾂�
		float Get_PosY(void);//Y���W�𓾂�
		
		void LoadParam(void);//�p�����[�^�[�ǂݍ���
		void LoadPoint(void);//�o���|�C���g�ǂݍ���
		
		void LoadSound(void);//�T�E���h�ǂݍ���
		
		void SetGraphInfo(void);//�摜���Z�b�g
		void SetHp(void);//�G�̗̓Z�b�g
		void SetRect(void);//�����蔻��̈�Z�b�g
		void SetPosition(float posx, float posy);//���W�Z�b�g
		void SetType(eEnemyType type);//�G�^�C�v�Z�b�g
		void SetScore(void);//�X�R�A�Z�b�g
		void SetStatus(void);//�X�e�[�^�X�Z�b�g
		
		void CalcDamage(int attack, int defence);//�_���[�W�v�Z
		void Dead(void);//���S����
		
		void LoadImage(void);//�e�N�X�`���ǂݍ���
		void CreateSprite(void);//�X�v���C�g����
		
		void CreateAnimation(void);//�L�[�f�[�^����
		
		void LoadPattern(char *datname);//�p�^�[���f�[�^�ǂݍ���
		
		void Move(void);//�ړ�
		
		void MovePattern(float tax, float tay);//�ړ��p�^�[��
		void ShootPattern(float tax, float tay);//�V���b�g�p�^�[��
		void MovePattern1(void);//�ړ��p�^�[��1
		void MovePattern2(float tax, float tay);//�ړ��p�^�[��2
		void MovePattern3(float tax, float tay);//�ړ��p�^�[��3
		void MovePattern4(float tax, float tay);//�ړ��p�^�[��4
		void MovePattern5(void);//�ړ��p�^�[��5
		
		void Draw(eEnemyType type);//�`��
		void Rendering(void);//�����_�����O
		void Debug(void);//�f�o�b�O�p
		
		void MoveAdjust(int left, int right, int top, int bottom);//�ړ��␳
		
		void Release(void);//�������J��
};
