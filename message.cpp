//================================================
//include
//================================================
#include "message.h"

//================================================
//�R���X�g���N�^
//================================================
CMessage::CMessage()
{
	Px = 0;
	Py = 300;
	
	StrPx = Px + 130;
	StrPy = Py + 30;
	
	Sp = 0;
	Cp = 0;
	
	FONT_SIZE = 20;

	Count = 1;
}

//================================================
//�f�X�g���N�^
//================================================
CMessage::~CMessage()
{

}

//================================================
//������
//================================================
void CMessage::Initialize()
{
	Sp = 0;
	Cp = 0;
	
	IsDisp = FALSE;
}

//================================================
//�摜�ǂݍ���
//================================================
void CMessage::LoadImage(char *name, int ColorKey)
{
	Tex = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_2D, ColorKey);
	
	CreateSprite();
}

void CMessage::LoadImage()
{
	char *name[] =
	{
		"system\\isla_up.png",
		"system\\rai_up.png",
		"system\\ame_up.png",
		"system\\jack_up.png",
	};
	
	for(int i = 0;i < CHARA_MAX;i++)
	{
		FaceTex[i] = LunaTexture::CreateFromFile(name[i], FORMAT_TEXTURE_2D, COLORKEY_DISABLE);
	}
	
	CreateSprite();
}

//================================================
//�X�N���v�g�f�[�^�ǂݍ���
//================================================
void CMessage::LoadScriptData(void)
{
	FILE *fp;
	
	fp = fopen("conv.dat", "rb");
	
	if(fp == NULL)
	{
		Luna::MsgBox(0, "Error", "conv.dat��������܂���");
		
		Luna::Exit();
	}
	
	for(int line = 0;line < LINE_NUM;line++)
	{
		if(fgets(strdata[line], 256, fp) == NULL)
		{
			break;
		}
	}
	
}

//================================================
//�t�H���g����
//================================================
void CMessage::CreateFont(void)
{
	Font = LunaFont::Create("�قɂ᎚", 30);
}

//================================================
//�t�H���g�X�v���C�g����
//================================================
void CMessage::CreateFontSprite(void)
{
	char *pBuff = (char*)MemoryAlloc(2048);
	
	for(Sint32 i = 0;i < LINE_NUM;i++)
	{
		strcat(pBuff, strdata[i]);
	}
	
	Font = LunaFont::Create("�قɂ᎚", FONT_SIZE);
	
	FontSpr = LunaFontSprite::Create(pBuff, true, 2048, Font);

	LunaFont::Release(Font);
	
	MemoryFree(pBuff);

}

//================================================
//�X�v���C�g����
//================================================
void CMessage::CreateSprite()
{
	for(int i = 0;i < CHARA_MAX;i++)
	{
		Spr[i] = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
		
		LunaSprite::AttatchTexture(Spr[i], 0, FaceTex[i]);
	}
	
}

//================================================
//�摜���Z�b�g
//================================================
void CMessage::Set(int posx, int posy, int width, int height)
{
	Px = posx;
	Py = posy;
	Width = width;
	Height = height;
}


//================================================
//�X�N���v�g����
//================================================
void CMessage::ScriptTreat(int *mode)
{
	DrawChara(StrPx, StrPy);
	
	if(Sp == 12)
	{
		*mode = SCENE_MAIN;
		
		Sp = 13;
	}
	
	if(Sp == 29)
	{
		*mode = SCENE_GAMECLEAR;
		
		Sp = 30;
	}
	
	if(Sp == LINE_NUM)
	{
		*mode = SCENE_INITIALIZE;
	}
		
}

//================================================
//��b���Ƃ̊�O���t�B�b�N
//================================================
void CMessage::ScriptFaceData()
{
	switch(Sp)
	{
		/*�C�X���̃f�[�^*/
		case 2:
		case 7:
		case 14:
		case 19:
		case 21:
		case 26:
		{
			Type = CHARA_ISLA;
			break;
		}
		
		/*���C�̃f�[�^*/
		case 4:
		case 8:
		case 11:
		case 16:
		case 18:
		case 28:
		{
			Type = CHARA_RAI;
			break;
		}
		
		/*�A���E�X�̃f�[�^*/	
		case 0:
		case 5:
		case 9:
		case 23:
		case 25:
		{
			Type = CHARA_AMEUS;
			break;
		}
		
		/*�W���b�N�̃f�[�^*/
		case 1:
		case 3:
		case 6:
		case 10:
		case 13:
		case 15:
		case 17:
		case 20:
		case 22:
		case 24:
		case 27:
		{
			Type = CHARA_JACK;
			break;
		}
		
	}
	
	Draw();
	
	Rendering();
}

//================================================
//�ꕶ�����`��
//================================================
void CMessage::DrawChara(int posx, int posy)
{
	if(Luna::GetSyncCounter() % 5 == 0)
	{
		Count += 3;
	}
	
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		Count += 5;
	}
	
	/*�o�b�t�@�N���A*/
	LunaFontSprite::ResetBuffer(FontSpr);

	LUNARECT Dst = { F(posx), F(posy), F(0), F(0) };
	
	LunaFontSprite::GetHeight(FontSpr, &StrHeight);
	
	char *pStr = strdata[Sp];
	
	Sint32 cnt = Count;
	
	while( (*pStr != '\0') && (cnt > 0) )
	{
		Is2Byte = LunaChara::IsKanji( (unsigned char)(*pStr) );
		
		if(!Is2Byte)
		{
			if(*pStr == '\n')
			{
				Dst.Py += toF(StrHeight);
				Dst.Px = F(StrPx);
				pStr += 1;
				continue;
			}
		}
			
		LunaFontSprite::GetWidth(FontSpr, pStr, &StrLeft, &StrCenter, &StrRight);
		
		Dst.Px += F(StrLeft);
		Dst.Sx = F(StrCenter);
		Dst.Sy = F(StrHeight);
		
		/*�`��*/
		LunaFontSprite::DrawChara(FontSpr, pStr, &Dst, PRIMITIVE_Z_CENTER, COLOR_BLACK);
		
		/*�`����*/
		Dst.Px -= F(StrLeft);
		
		if(Is2Byte)
		{
			Dst.Px += F(StrHeight);
		}
		
		else
		{
			Dst.Px += F(StrHeight/2);
		}
		
		if(Dst.Px >= 620)
		{
			Dst.Px = F(StrPx);
			Dst.Py += FONT_SIZE;
		}
		
		pStr += Is2Byte ? 2 : 1;
		cnt--;
		
	}
	
	if(cnt > 0)
	{
		if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
		{
			Count = 1;
			Sp += 1;
		}
		
		if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_02) )
		{
			Count = 100;
			Sp += 1;
		}
		
	}
	
	/*�o�b�t�@�X�V*/
	LunaFontSprite::UpdateBuffer(FontSpr);
}

//================================================
//�t�H���g�`��
//================================================
void CMessage::DrawFont(char *data)
{
	/*�`��J�n*/
	LunaFont::Begin(Font);
	
	LunaFont::DrawText(StrPx, StrPy, COLOR_BLACK, data);
	
	/*�`��I��*/
	LunaFont::End();
}

//================================================
//�t�H���g�`��2
//================================================
void CMessage::DrawFont(int score)
{
	/*�`��J�n*/
	LunaFont::Begin(Font);
	
	LunaFont::DrawText(450, 50, COLOR_BLACK, "Score %d", score);
	
	/*�`��I��*/
	LunaFont::End();
}

//================================================
//�t�H���g�`��3
//================================================
void CMessage::DrawFont(int posx, int posy, char *data)
{
	LunaFont::Begin(Font);
	
	LunaFont::DrawText(posx, posy, COLOR_WHITE, data);
	
	LunaFont::End();
}

//================================================
//�t�H���g�`��4
//================================================
void CMessage::DrawFont(int posx, int posy)
{
	LunaFont::Begin(Font);
	
	LunaFont::DrawText(StrPx+posx, StrPy+posy, COLOR_BLACK, "�X�^�[�g(S)�Ō���");
	
	LunaFont::End();
}


//================================================
//�t�H���g�X�v���C�g�`��
//================================================
void CMessage::DrawFontSprite(char *data)
{
	/*�o�b�t�@�N���A*/
	LunaFontSprite::ResetBuffer(FontSpr);

	/*�`��*/
	LunaFontSprite::DrawString(FontSpr, data, StrPx, StrPy, PRIMITIVE_Z_CENTER, COLOR_BLACK);
	
	/*�o�b�t�@�X�V*/
	LunaFontSprite::UpdateBuffer(FontSpr);
	
}

//================================================
//�t�H���g�X�v���C�g�`��(2)
//================================================
void CMessage::DrawFontSprite(int posx, int posy, char *data)
{
	/*�o�b�t�@�N���A*/
	LunaFontSprite::ResetBuffer(FontSpr);

	/*�`��*/
	LunaFontSprite::DrawString(FontSpr, data, posx, posy, PRIMITIVE_Z_CENTER, COLOR_BLACK);
	
	/*�o�b�t�@�X�V*/
	LunaFontSprite::UpdateBuffer(FontSpr);
	
}

//================================================
//�t�H���g�����_�����O
//================================================
void CMessage::RenderingFont()
{
	if(Luna3D::BeginScene() )
	{
		/*���ۂ̕`��*/
		LunaFontSprite::Rendering(FontSpr);
		
		Luna3D::EndScene();
	}
}

//================================================
//�E�B���h�E���b�Z�[�W�`��
//================================================
void CMessage::DrawMessage(Sint32 cursor)
{
	for(int i = 0;i < 7;i++)
	{
		if(cursor == i)
		{
			Sp = i*2;
		}
	}
	
	DrawFontSprite(StrPx, StrPy, strdata[Sp]);
}

//===============================================
//�e�N�X�`���`��
//===============================================
void CMessage::DrawTexture()
{
	if(IsDisp)
	{
		/*�`���*/
		Dst.Set( F(Px), F(Py), F(Width), F(Height) );
		
		/*�`�挳*/
		Src.Set(F(0), F(0), F(Width), F(Height) );
		
		/*�`��*/
		LunaTexture::Draw(Tex, &Dst, &Src, COLOR_WHITE);
		
	}
	
}

//================================================
//�`��
//================================================
void CMessage::Draw(void)
{
	/*�o�b�t�@���Z�b�g*/
	LunaSprite::ResetBuffer(Spr[Type]);
	
	/*�`���*/
	Dst.Set( F(Px+20), F(Py+40), F(100), F(100) );
	
	/*�`�挳*/
	Src.Set(F(0), F(0), F(100), F(100) );
	
	/*�`��*/
	LunaSprite::DrawSquare(Spr[Type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	/*�o�b�t�@�X�V*/
	LunaSprite::UpdateBuffer(Spr[Type]);
		
}

//================================================
//�`��
//================================================
void CMessage::Draw(float posx, float posy, int type)
{
	/*�o�b�t�@���Z�b�g*/
	LunaSprite::ResetBuffer(Spr[type]);
	
	/*�`���*/
	Dst.Set(posx, posy, F(50), F(50) );
	
	/*�`�挳*/
	Src.Set(F(10), F(10), F(50), F(50) );
	
	/*�`��*/
	LunaSprite::DrawSquare(Spr[type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	//LunaSprite::DrawRing(Spr[type], posx, posy, PRIMITIVE_Z_CENTER, &Src, 50, 100, COLOR_BASE, COLOR_BASE, 4, 1); 
	
	/*�o�b�t�@�X�V*/
	LunaSprite::UpdateBuffer(Spr[type]);
	
	Rendering(type);
	
}

//================================================
//�����_�����O
//================================================
void CMessage::Rendering()
{
	if(IsDisp)
	{
		LunaSprite::Rendering(Spr[Type]);
	}
}

//================================================
//�����_�����O
//================================================
void CMessage::Rendering(int type)
{
	/*�����_�����O*/
	LunaSprite::Rendering(Spr[type]);
}

//================================================
//�f�o�b�O
//================================================
void CMessage::Debug(void)
{
	LunaDebug::DrawString("data:%s", strdata);
	LunaDebug::DrawString("debug:%d", IsDebug);
	LunaDebug::DrawString("Width:%d", Width);
	LunaDebug::DrawString("Height:%d", Height);
}

//================================================
//�������J��
//================================================
void CMessage::Release(void)
{
	LunaTexture::Release(Tex);
	
	LunaFont::Release(Font);
	
	//LunaFontSprite::Release(FontSpr);
}