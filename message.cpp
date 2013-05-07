//================================================
//include
//================================================
#include "message.h"

//================================================
//コンストラクタ
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
//デストラクタ
//================================================
CMessage::~CMessage()
{

}

//================================================
//初期化
//================================================
void CMessage::Initialize()
{
	Sp = 0;
	Cp = 0;
	
	IsDisp = FALSE;
}

//================================================
//画像読み込み
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
//スクリプトデータ読み込み
//================================================
void CMessage::LoadScriptData(void)
{
	FILE *fp;
	
	fp = fopen("conv.dat", "rb");
	
	if(fp == NULL)
	{
		Luna::MsgBox(0, "Error", "conv.datが見つかりません");
		
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
//フォント生成
//================================================
void CMessage::CreateFont(void)
{
	Font = LunaFont::Create("ほにゃ字", 30);
}

//================================================
//フォントスプライト生成
//================================================
void CMessage::CreateFontSprite(void)
{
	char *pBuff = (char*)MemoryAlloc(2048);
	
	for(Sint32 i = 0;i < LINE_NUM;i++)
	{
		strcat(pBuff, strdata[i]);
	}
	
	Font = LunaFont::Create("ほにゃ字", FONT_SIZE);
	
	FontSpr = LunaFontSprite::Create(pBuff, true, 2048, Font);

	LunaFont::Release(Font);
	
	MemoryFree(pBuff);

}

//================================================
//スプライト生成
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
//画像情報セット
//================================================
void CMessage::Set(int posx, int posy, int width, int height)
{
	Px = posx;
	Py = posy;
	Width = width;
	Height = height;
}


//================================================
//スクリプト処理
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
//会話ごとの顔グラフィック
//================================================
void CMessage::ScriptFaceData()
{
	switch(Sp)
	{
		/*イスラのデータ*/
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
		
		/*ライのデータ*/
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
		
		/*アメウスのデータ*/	
		case 0:
		case 5:
		case 9:
		case 23:
		case 25:
		{
			Type = CHARA_AMEUS;
			break;
		}
		
		/*ジャックのデータ*/
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
//一文字ずつ描画
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
	
	/*バッファクリア*/
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
		
		/*描画*/
		LunaFontSprite::DrawChara(FontSpr, pStr, &Dst, PRIMITIVE_Z_CENTER, COLOR_BLACK);
		
		/*描画情報*/
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
	
	/*バッファ更新*/
	LunaFontSprite::UpdateBuffer(FontSpr);
}

//================================================
//フォント描画
//================================================
void CMessage::DrawFont(char *data)
{
	/*描画開始*/
	LunaFont::Begin(Font);
	
	LunaFont::DrawText(StrPx, StrPy, COLOR_BLACK, data);
	
	/*描画終了*/
	LunaFont::End();
}

//================================================
//フォント描画2
//================================================
void CMessage::DrawFont(int score)
{
	/*描画開始*/
	LunaFont::Begin(Font);
	
	LunaFont::DrawText(450, 50, COLOR_BLACK, "Score %d", score);
	
	/*描画終了*/
	LunaFont::End();
}

//================================================
//フォント描画3
//================================================
void CMessage::DrawFont(int posx, int posy, char *data)
{
	LunaFont::Begin(Font);
	
	LunaFont::DrawText(posx, posy, COLOR_WHITE, data);
	
	LunaFont::End();
}

//================================================
//フォント描画4
//================================================
void CMessage::DrawFont(int posx, int posy)
{
	LunaFont::Begin(Font);
	
	LunaFont::DrawText(StrPx+posx, StrPy+posy, COLOR_BLACK, "スタート(S)で決定");
	
	LunaFont::End();
}


//================================================
//フォントスプライト描画
//================================================
void CMessage::DrawFontSprite(char *data)
{
	/*バッファクリア*/
	LunaFontSprite::ResetBuffer(FontSpr);

	/*描画*/
	LunaFontSprite::DrawString(FontSpr, data, StrPx, StrPy, PRIMITIVE_Z_CENTER, COLOR_BLACK);
	
	/*バッファ更新*/
	LunaFontSprite::UpdateBuffer(FontSpr);
	
}

//================================================
//フォントスプライト描画(2)
//================================================
void CMessage::DrawFontSprite(int posx, int posy, char *data)
{
	/*バッファクリア*/
	LunaFontSprite::ResetBuffer(FontSpr);

	/*描画*/
	LunaFontSprite::DrawString(FontSpr, data, posx, posy, PRIMITIVE_Z_CENTER, COLOR_BLACK);
	
	/*バッファ更新*/
	LunaFontSprite::UpdateBuffer(FontSpr);
	
}

//================================================
//フォントレンダリング
//================================================
void CMessage::RenderingFont()
{
	if(Luna3D::BeginScene() )
	{
		/*実際の描画*/
		LunaFontSprite::Rendering(FontSpr);
		
		Luna3D::EndScene();
	}
}

//================================================
//ウィンドウメッセージ描画
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
//テクスチャ描画
//===============================================
void CMessage::DrawTexture()
{
	if(IsDisp)
	{
		/*描画先*/
		Dst.Set( F(Px), F(Py), F(Width), F(Height) );
		
		/*描画元*/
		Src.Set(F(0), F(0), F(Width), F(Height) );
		
		/*描画*/
		LunaTexture::Draw(Tex, &Dst, &Src, COLOR_WHITE);
		
	}
	
}

//================================================
//描画
//================================================
void CMessage::Draw(void)
{
	/*バッファリセット*/
	LunaSprite::ResetBuffer(Spr[Type]);
	
	/*描画先*/
	Dst.Set( F(Px+20), F(Py+40), F(100), F(100) );
	
	/*描画元*/
	Src.Set(F(0), F(0), F(100), F(100) );
	
	/*描画*/
	LunaSprite::DrawSquare(Spr[Type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	/*バッファ更新*/
	LunaSprite::UpdateBuffer(Spr[Type]);
		
}

//================================================
//描画
//================================================
void CMessage::Draw(float posx, float posy, int type)
{
	/*バッファリセット*/
	LunaSprite::ResetBuffer(Spr[type]);
	
	/*描画先*/
	Dst.Set(posx, posy, F(50), F(50) );
	
	/*描画元*/
	Src.Set(F(10), F(10), F(50), F(50) );
	
	/*描画*/
	LunaSprite::DrawSquare(Spr[type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	//LunaSprite::DrawRing(Spr[type], posx, posy, PRIMITIVE_Z_CENTER, &Src, 50, 100, COLOR_BASE, COLOR_BASE, 4, 1); 
	
	/*バッファ更新*/
	LunaSprite::UpdateBuffer(Spr[type]);
	
	Rendering(type);
	
}

//================================================
//レンダリング
//================================================
void CMessage::Rendering()
{
	if(IsDisp)
	{
		LunaSprite::Rendering(Spr[Type]);
	}
}

//================================================
//レンダリング
//================================================
void CMessage::Rendering(int type)
{
	/*レンダリング*/
	LunaSprite::Rendering(Spr[type]);
}

//================================================
//デバッグ
//================================================
void CMessage::Debug(void)
{
	LunaDebug::DrawString("data:%s", strdata);
	LunaDebug::DrawString("debug:%d", IsDebug);
	LunaDebug::DrawString("Width:%d", Width);
	LunaDebug::DrawString("Height:%d", Height);
}

//================================================
//メモリ開放
//================================================
void CMessage::Release(void)
{
	LunaTexture::Release(Tex);
	
	LunaFont::Release(Font);
	
	//LunaFontSprite::Release(FontSpr);
}