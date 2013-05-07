//================================================
//menu.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "sound.h"

//================================================
//define
//================================================
#define CURSOR_NUM 2

//================================================
//enum
//================================================
enum
{
	ITEM_START,
	//ITEM_TUTOLIAL,
	ITEM_CONFIG,
	ITEM_EXIT,
	ITEM_MAX,
};

enum
{
	SCENE_FIRST,
	SCENE_SECOND,
	SCENE_THIRD,
	SCENE_END,
};

static char *TitleMenu[] =
{
	"�Q�[�����n�߂�",
	//"�`���[�g���A��",
	"�L�[�R���t�B�O",
	"�Q�[������߂�",
};

static char *Menu2[] =
{
	"�V���b�g %d",
	"��� %d",
	"���� %d",
	//"�X���[�ړ� %d",
	"�|�[�Y %d",
	"�I��",
};

static char *Menu3[] =
{
	"�Q�[���𑱂���",
//	"�Q�[������߂�",
	"���j���[�ɖ߂�",
};

static char *Menu4[] =
{
	"��b�m��",
	"��{�s��",
	"����\��",
	"���",
	"���K",
	"�I��",
};

static char *Menu5[] =
{
	"CONTINUE",
	"END",
};

static char *Menu6[] =
{
	"�͂�",
	"������",
};

//================================================
//class
//================================================
class CMenu
{
	private:
		
		enum
		{
			SE_ENTER,
			SE_CANCEL,
			SE_CURSOR,
			SE_MAX,
		};
		
		int Px;//X���W
		int Py;//Y���W
		
		int CursorX;//�J�[�\��X���W
		int CursorY;//�J�[�\��Y���W
		
		Sint32 StrPx[10];
		Sint32 StrPy[10];
		
		int Width;//��
		int Height;//����
		
		int Shot;//�V���b�g�{�^��
		int Change;//�`�F���W�{�^��
		int Special;//����{�^��
		int Slow;//�X���[�ړ��{�^��
		int Pause;//�|�[�Y�{�^��
		
		int DivNum;//������
		
		Sint32 OldCursor;
		
		int tmp;//�L��������ւ��p
		
		int counter;//�ėp�J�E���^
		
		int FONT_SIZE;//�t�H���g�T�C�Y
		int NUM_MENU;//���j���[��
		int MOVE;//�ړ���
		int TOP;//�ŏ��̃��j���[���W
		int BOTTOM;//�Ō�̃��j���[���W
		
		CSound Se[SE_MAX];//���ʉ�
		
		LTEXTURE Tex[CURSOR_NUM];//�e�N�X�`���n���h��
		LSPRITE Spr[CURSOR_NUM];//�X�v���C�g�n���h��
		
		LFONT Font;//�t�H���g�n���h��
		LFONTSPRITE FontSpr;//�t�H���g�X�v���C�g�n���h��
		
		LUNARECT Dst;//�`���
		LUNARECT Src;//�`�挳
		
	public:

		JOYSTICKDATA Pad;
		
		Sint32 Cursor;
		
		int animcounter;//�A�j���[�V�����J�E���^
		
		bool Flag;//�ėp�t���O
		bool IsSelected;//�I�𔻒�t���O
		
		int Scene;//�L�����I��p
		
		CMenu();//�R���X�g���N�^
		virtual ~CMenu();//�f�X�g���N�^
		
		void Initialize(void);//������
		
		void CreateFont(void);
		void CreateFontSprite(char *StrTbl[], int MenuMax);//�t�H���g����
		void CreateFontSprite(void);//�t�H���g�X�v���C�g����(�t�@�C���ǂݍ���)
		void DrawFont(int posx, int posy, char *string);//�t�H���g�`��
		void DrawFont(char *StrTbl[], int MenuMax);//�t�H���g�`��()
		void DrawFontSpr(char *StrTbl[], int MenuMax);//�t�H���g�X�v���C�g�`��
		void DrawErrorMessage(void);//�G���[�`��
		
		void CalcFontPos(int posx, int posy, int MenuMax);
		void CalcFontSprPos(int posx, int posy, char *StrTbl[], int MenuMax);//�����ʒu�Z�o
		void CalcCharaPos(int posx, int posy, int move);//�v���C���[�ʒu�Z�o
		
		void LoadImage(void);//�摜�ǂݍ���
		void CreateSprite(void);//�X�v���C�g����
		
		void LoadSound();//�ǂݍ���
		
		void DrawCursor(void);//�J�[�\���`��
		void DrawCursor(int Cursor, int no);//�J�[�\���`��
		void Rendering(void);//�����_�����O
		void Rendering(int no);//�����_�����O
		
		void Move(int MenuMax);//�J�[�\���ړ�
		void MoveLeftRight(int MenuMax);//�J�[�\���ړ�(���E)
		
		void ModeSelect(int *mode);//���[�h�Z���N�g
		void PauseSelect(int *mode);//�|�[�Y�Z���N�g
		void CharaSelect(int *mode, int *first, int *second, int *third);//�L�����Z���N�g
		void CharaSelectExit(int *mode);//�L�����Z���N�g�I���m�F���
		void Select(int *mode);//�I���m�F�Z���N�g
		void PauseExitSelect(int *mode);//�|�[�Y�I���m�F�Z���N�g
		void GameOverSelect(int *mode);//�Q�[���I�[�o�[�Z���N�g
		void KeyConfig(int *mode);//�L�[�R���t�B�O
		
		void Swap(int *x, int *y);//����ւ�
		void Swap(int *x, int *y, bool *Flag);//�L��������ւ�
		
		void Debug(void);//�f�o�b�O
		
		void Release(void);//�������J��
		
};
