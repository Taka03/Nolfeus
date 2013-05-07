//================================================
//message.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "gamemode.h"

//================================================
//define
//================================================
const int CHARA_MAX = 4;
const int LINE_NUM = 41;

//================================================
//class
//================================================
class CMessage
{
	private:
	
		int Px;//X���W(���b�Z�[�W�E�B���h�E�p)
		int Py;//Y���W(���b�Z�[�W�E�B���h�E�p)
		
		int StrPx;//����X���W
		int StrPy;//����Y���W
		
		int DrawPointX;//�ꎚ���`��
		int DrawPointY;//
		
		int Width;//��
		int Height;//����
		
		int Type;//��O���t�B�b�N�̃^�C�v
		
		int Sp;//�Q�Ƃ��镶����ԍ�
		int Cp;//�Q�Ƃ��镶����̕�����|�C���^
		
		char *pStr;
		
		Sint32 Count;
		Sint32 StrHeight;
		Sint32 StrLeft;
		Sint32 StrCenter;
		Sint32 StrRight;

		char strdata[LINE_NUM][256];
		
		bool EndFlag;//��b�I���t���O
		bool Is2Byte;//2�o�C�g��������t���O
		
		bool IsDebug;
		
		int FONT_SIZE;
		
		LTEXTURE Tex;//�e�N�X�`���n���h��
		LTEXTURE FaceTex[CHARA_MAX];//��e�N�X�`���n���h��
		LSPRITE Spr[CHARA_MAX];
		
		LFONT Font;//�t�H���g�n���h��
		LFONTSPRITE FontSpr;//�t�H���g�X�v���C�g�n���h��
		
		LUNARECT Dst;//�`���
		LUNARECT Src;//�`�挳
		
		enum
		{
			CHARA_ISLA,
			CHARA_RAI,
			CHARA_AMEUS,
			CHARA_JACK,
		};
		
	
	public:
	
		bool IsDisp;//�\������t���O
		
		int counter;
		
		CMessage();//�R���X�g���N�^
		virtual ~CMessage();//�f�X�g���N�^
		
		void Initialize(void);//������
		
		void LoadScriptData(void);//��b�f�[�^�ǂݍ���
		void LoadImage(char *name, int ColorKey);//�E�B���h�E�摜���[�h
		void LoadImage();//��摜���[�h�p
		
		void ScriptTreat(int *mode);//�X�N���v�g����
		void ScriptFaceData(void);//�X�N���v�g���̊�f�[�^
		
		void Set(int posx, int posy, int width, int height);//�摜���Z�b�g
		
		void CreateFont(void);//�t�H���g����
		void CreateFontSprite(void);//�t�H���g�X�v���C�g����
		void CreateSprite(void);//�X�v���C�g����
		
		void CalcFontPos(void);//�`��ʒu�Z�o
		
		void DrawChara(int posx, int posy);//�ꕶ�����`��
		void DrawFont(int score);
		void DrawFont(char *data);//�t�H���g�`��
		void DrawFont(int posx, int posy, char *data);//�t�H���g�`��
		void DrawFont(int posx, int posy);
		void DrawFontSprite(int posx, int posy, char *data);//
		void DrawFontSprite(char *data);//�t�H���g�X�v���C�g�`��
		
		void RenderingFont(void);//�t�H���g�̃����_�����O
		void Rendering(void);//�����_�����O
		void Rendering(int type);//�����_�����O
		
		void DrawMessage(Sint32 cursor);//�V�[�����Ƃ̕`��

		void DrawTexture(void);//��O���t�B�b�N�`��
		void Draw(void);//�`��
		void Draw(float posx, float posy);
		void Draw(float posx, float posy, int type);
		
		void Debug(void);//�f�o�b�O�p
		void Release(void);//�������J��
};
