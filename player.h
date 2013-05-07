//================================================
//player.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "bullet.h"
#include "effect.h"
#include "message.h"
#include "character.h"
#include "gauge.h"

//================================================
//define
//================================================
const int PLAYER_NUM = 4;
const int MAX_LIFE = 100;
const int TYPE_AGAUGE = 2;

const int AME_NUM = 3;
const int LAG_NUM = 20;

//================================================
//enum
//================================================
enum ePlayerType
{
	ID_PLAYER1,
	ID_PLAYER2,
	ID_PLAYER3,
	ID_PLAYER4,
};

//================================================
//variable
//================================================

//================================================
//class
//================================================
class CPlayer
{
	private:

		float fPosX;//X���W
		float fPosY;//Y���W
		
		//float PosX[LAG_NUM];//X���W(�c���p)
		//float PosY[LAG_NUM];//Y���W(�c���p)
		
 		int life;//�̗͏����p�ϐ�
		
		int Speed;//�ړ����x
		
		int Width;//��
		int Height;//����
		
		int Weight;//�d��
		
		int Divnum;//������
		
		int tmp;//�L��������ւ��p
		
		int COMP;//�����蔻��␳�l
		
		int counter;//�ėp�J�E���^
		
		float fTime;//����
		
		int RecoverLife;//�񕜗�
		int RecoverMax[PLAYER_NUM-1];//�񕜍ő��
		
		bool IsChange;//�L�����ύX�p�t���O
		bool IsDamege;//�_���[�W����t���O

		LTEXTURE Tex[PLAYER_NUM];//�v���C���[�e�N�X�`���n���h��
		LTEXTURE windowTex[PLAYER_NUM - 1];//�v���C���[�E�B���h�E�e�N�X�`��
		
		LSPRITE Spr[PLAYER_NUM];//�v���C���[�X�v���C�g�n���h��
		LSPRITE windowSpr[PLAYER_NUM - 1];
		
		LUNARECT Dst;//�`���
		LUNARECT Src;//�`�挳
		
		typedef struct DATA
		{
			int Defence;
			int Speed;
			int Hp;
			int Weight;
			int Width;
			int Height;
			int Divnum;
		};
		
		enum 
		{
			SE_SHOT1,
			SE_SHOT2,
			SE_STOP,
			SE_WOLF,
			SE_CLEAR,
			SE_CHANGE,
			SE_NEDEATH,
			SE_DEATH,
			SE_MAX,
		};
		
		DATA pdata[PLAYER_NUM];
		
		CEffect lightball;//���̒e
		CEffect change;//�`�F���W�G�t�F�N�g
		CEffect stop;//���Ԓ�~�p
		CEffect wolf;//�b���p
		
		CGauge lgauge[PLAYER_NUM-1];//���C�t�Q�[�W
		CGauge rgauge[PLAYER_NUM-1];//���C�t�Q�[�W(�ő�񕜗�)
		//CGauge wlgauge[WAIT_LIFE];//�ҋ@���C�t�Q�[�W
		CGauge agauge;//�A�r���e�B�Q�[�W
		CGauge magauge;//�A�r���e�B�Q�[�WMAX
		
		CMessage face;
		
		CSound Se[SE_MAX];
		
		void LoadEffect(void);
		
	public:
	
		int Hp[PLAYER_NUM];//�̗�
		int OldHp[PLAYER_NUM];//�̗͕ێ��p
		
		int Attack;//�U����
		int Defence;//�h���
		
		int first;//��Ԗڂ̃L����
		int second;//��Ԗڂ̃L����
		int third;//�O�Ԗڂ̃L����
		
		float OldPosX;//X���W(�ێ��p)
		float OldPosY;//Y���W(�ێ��p)
		
		int Type;//�v���C���[�^�C�v
		int ChangeTime;//�L�����ύX����
		int InvinceTime;//���G����
		int animcounter;//�A�j���J�E���^�[
		
		int Invcounter;//���G���ԗp�J�E���^�[
		
		bool IsUseSpecial;//����U���g�p����t���O
		bool IsDead;//���S�t���O
		bool IsInvince;//���G�t���O
		
		bool IsStop;//���Ԓ�~�p�t���O(�C�X���K�E�Z�p)
		bool IsWolf;//�b������t���O(���C�K�E�Z�p)
		bool IsClear;//���������p�t���O(�A���E�X�K�E�Z�p)
		
		CBullet bullet;//�v���C���[�e
		CBullet amebullet[AME_NUM];//�A���E�X���g�e
		
		CChara charge;
		CChara umbrella;
		CChara shadow;
		
		RECT2D HitRect;//�����蔻��p
		
		CPlayer();//�R���X�g���N�^
		CPlayer(float Px, float Py, int width, int height, int divnum);//�R���X�g���N�^
		virtual ~CPlayer();//�f�X�g���N�^
		
		void Initialize(void);//������
		
		float Get_PosX(void);//X���W�𓾂�
		float Get_PosY(void);//Y���W�𓾂�
		int Get_Life(void);//Hp�𓾂�
		
		int GetWidth(void);//���𓾂�
		int GetHeight(void);//�����𓾂�
		
		void LoadParam(void);//�p�����[�^�ǂݍ���
		
		void Set(float Px, float Py, int width, int height, int divnum);
		void SetRect(void);//�����蔻��̈�ݒ�
		void SetPosition(float Px, float Py);
		
		void SetGraphInfo(void);//�摜���Z�b�g
		
		void SetHp(int Hp);//HP�Z�b�g
		void SetSpeed(void);//�ړ����x�Z�b�g
		void SetStatus(void);//�X�e�[�^�X�Z�b�g
		
		void LoadImage(char *name, int ColorKey);
		void LoadImage(void);//�e�N�X�`���ǂݍ���
		void CreateSprite(void);//�X�v���C�g����
		
		void LoadSound(void);//�T�E���h�ǂݍ���

		
		void ChangeChara(void);//�L�����ύX
		void UseSpecial(void);//�K�E�Z�g�p
		void UseGauge(void);//�Q�[�W�g�p
		void UseCharaChange(void);//�L�����`�F���W�g�p
		
		void TimeStop(void);//���Ԓ�~
		void ChangeWolf(void);//�b��
		void Clearize(void);//��������
		
		void CalcDamage(int attack, int defence);//�_���[�W�v�Z
		
		void Move(void);//�ړ�
		void MoveAdjust(int left, int right, int top, int bottom);//�ړ��␳
		void Shoot(void);//�V���b�g����
		
		void SwapChara(int *x, int *y, int *z);//�L��������ւ�
		
		void Recoverlife(void);//���C�t��
		void KeepHp(void);//���C�t�ێ�
		void KnockBack(void);//�̂�����
		
		void Draw(void);//�e�N�X�`���`��
		void Draw(float posx, float posy, int type);
		void Rendering(void);//�����_�����O
		void DrawTex();
		void Debug(void);//�f�o�b�O�p
		
		//void DrawGauge(void);//�Q�[�W�`��
		
		void Release(void);//�������J��
};

