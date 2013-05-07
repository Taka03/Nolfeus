//================================================
//include
//================================================
#include "menu.h"
#include "function.h"
#include "gamemode.h"

//================================================
//define
//================================================
#define TOP 200
#define BOTTOM(X, Y) TOP + (Y-1)*X

//================================================
//コンストラクタ
//================================================
CMenu::CMenu()
{
	NUM_MENU = 4;
	FONT_SIZE = 32;
	MOVE = FONT_SIZE;
	
	Px = 200;
	Py = TOP;
	
	CursorX = 200-Width;
	CursorY = 0;
	
	Shot = PAD_BUTTON_A;
	Change = PAD_BUTTON_B;
	Special = PAD_BUTTON_X;
	//Slow = PAD_BUTTON_Y;
	Pause = PAD_BUTTON_START;
	
}

//================================================
//デストラクタ
//================================================
CMenu::~CMenu()
{

}

//================================================
//初期化
//================================================
void CMenu::Initialize(void)
{
	Px = 200;
	Py = TOP;
	
	Width = 38;
	Height = 32;
	DivNum = 1;
	
	CursorX = 200-Width;
	CursorY = 0;
	Cursor = 0;
	
	Flag = FALSE;
	
	IsSelected = FALSE;
	
	Scene = SCENE_FIRST;
	
}

//================================================
//サウンド読み込み
//================================================
void CMenu::LoadSound()
{
	char *sename[] =
	{
		"sound\\enter.wav",
		"sound\\cancel.wav",
		"sound\\cursor.wav",
	};
	
	for(int i = 0;i < SE_MAX;i++)
	{
		Se[i].LoadSound(sename[i]);
	}
	
}

//================================================
//フォント生成
//================================================
void CMenu::CreateFont(void)
{
	Font = LunaFont::Create("ほにゃ字", FONT_SIZE);
}

//================================================
//フォントスプライト生成
//================================================
void CMenu::CreateFontSprite(char *StrTbl[], int MenuMax)
{
	char *pBuff = (char*)MemoryAlloc( 1024 );
	
	for(Sint32 i = 0;i < MenuMax;i++)
	{
		strcat(pBuff, StrTbl[i]);
	}
	
	Font = LunaFont::Create("ほにゃ字", FONT_SIZE);
	FontSpr = LunaFontSprite::Create(pBuff, true, 1024, Font);
	
	LunaFont::Release(Font);
	
	MemoryFree(pBuff);
}

//================================================
//フォントスプライト生成
//================================================
void CMenu::CreateFontSprite(void)
{
	FontSpr = LunaFontSprite::CreateFromFile("font.lfd", ".tga", false, 256);
}

//================================================
//文字位置算出
//================================================
void CMenu::CalcFontPos(int posx, int posy, int MenuMax)
{
	for(Sint32 i = 0;i < MenuMax;i++)
	{
		StrPx[i] = posx;//(SCREEN_WIDTH - 200) / 2;
		StrPy[i] = posy + (i * 30);
	}
}

//================================================
//文字スプライト位置算出
//================================================
void CMenu::CalcFontSprPos(int posx, int posy, char *StrTbl[], int MenuMax)
{
	for(Sint32 i = 0;i < MenuMax;i++)
	{
		POINT pt = LunaFontSprite::GetStringLastPos(FontSpr, StrTbl[i], 0, 0);
		
		StrPx[i] = posx;//(SCREEN_WIDTH - pt.x) / 2;
		StrPy[i] = posy + (i * 30);
	}
}

//================================================
//プレイヤー位置算出
//================================================
void CMenu::CalcCharaPos(int posx, int posy, int move)
{
	for(Sint32 i = 0;i < 3;i++)
	{
		StrPx[i] = posx;
		StrPy[i] = posy  + (i * move);
	}
}

//================================================
//テクスチャ読み込み
//================================================
void CMenu::LoadImage()
{
	char *name[] =
	{
		"system\\hand2.png",
		"system\\hand2.png",
	};
	
	for(int i = 0;i < CURSOR_NUM;i++)
	{
		Tex[i] = LunaTexture::CreateFromFile(name[i], FORMAT_TEXTURE_3D, COLORKEY_WHITE);
	}
	
	CreateSprite();
	
}

//================================================
//スプライト生成
//================================================
void CMenu::CreateSprite(void)
{
	for(int i = 0;i < CURSOR_NUM;i++)
	{
		/*空のスプライト生成*/
		Spr[i] = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
			
		/*スプライトにテクスチャを接続*/
		LunaSprite::AttatchTexture(Spr[i], 0, Tex[i]);
	}
}

//================================================
//カーソル描画
//================================================
void CMenu::DrawCursor(void)
{
	if(Luna::GetSyncCounter() % 10 == 0)
	{
		animcounter++;
	}
	
	/*スプライトバッファクリア*/
	LunaSprite::ResetBuffer(Spr[0]);

	/*描画先*/
	Dst.Set( F(StrPx[Cursor]-Width-10), F(StrPy[Cursor]+10), F(Width), F(Height) );
			
	/*描画元*/
	Src.Set( F( (animcounter%DivNum)*Width), F(0), F(Width), F(Height) );
			
	/*描画キューに追加*/
	LunaSprite::DrawSquare(Spr[0], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
			
	/*スプライトバッファ更新*/
	LunaSprite::UpdateBuffer(Spr[0]);
	
}

//================================================
//カーソル描画
//================================================
void CMenu::DrawCursor(int Cursor, int no)
{
	if(Luna::GetSyncCounter() % 10 == 0)
	{
		animcounter++;
	}
	
	/*スプライトバッファクリア*/
	LunaSprite::ResetBuffer(Spr[no]);

	/*描画先*/
	Dst.Set( F(StrPx[Cursor]-Width-10), F(StrPy[Cursor]+10), F(Width), F(Height) );
			
	/*描画元*/
	Src.Set( F( (animcounter%DivNum)*Width), F(0), F(Width), F(Height) );
			
	/*描画キューに追加*/
	LunaSprite::DrawSquare(Spr[no], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
			
	/*スプライトバッファ更新*/
	LunaSprite::UpdateBuffer(Spr[no]);

}

//================================================
//レンダリング
//================================================
void CMenu::Rendering()
{
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		Luna3D::SetFilterEnable(TRUE);
		
		/*スプライトレンダリング*/
		LunaSprite::Rendering(Spr[0]);
		
		/*シーン終了*/
		Luna3D::EndScene();
	}

}

//================================================
//レンダリング
//================================================
void CMenu::Rendering(int no)
{
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		Luna3D::SetFilterEnable(TRUE);
		
		LunaSprite::Rendering(Spr[no]);
		
		Luna3D::EndScene();
	}
}

//================================================
//文字描画
//================================================
void CMenu::DrawFont(int posx, int posy, char *string)
{
	/*描画開始*/
	LunaFont::Begin(Font);
	
	/*描画*/
	LunaFont::DrawText(posx, posy, COLOR_RED, string);
	
	/*描画終了*/
	LunaFont::End();
	
}

//================================================
//文字(普通)描画
//================================================
void CMenu::DrawFont(char *StrTbl[], int MenuMax)
{
	/*描画開始*/
	LunaFont::Begin(Font);
	
	/*描画*/
	LunaFont::DrawText(StrPx[0], StrPy[0], COLOR_WHITE, StrTbl[0], Shot);
	LunaFont::DrawText(StrPx[1], StrPy[1], COLOR_WHITE, StrTbl[1], Change);
	LunaFont::DrawText(StrPx[2], StrPy[2], COLOR_WHITE, StrTbl[2], Special);
	//LunaFont::DrawText(StrPx[3], StrPy[3], COLOR_WHITE, StrTbl[3], Slow);
	LunaFont::DrawText(StrPx[3], StrPy[3], COLOR_WHITE, StrTbl[3], Pause);
	LunaFont::DrawText(StrPx[4], StrPy[4], COLOR_WHITE, StrTbl[4]);
	
	/*描画終了*/
	LunaFont::End();
}

//================================================
//文字(スプライト)描画
//================================================
void CMenu::DrawFontSpr(char *StrTbl[], int MenuMax)
{
	/*バッファクリア*/
	LunaFontSprite::ResetBuffer(FontSpr);
	
	for(Sint32 i = 0;i < MenuMax;i++)
	{
		/*描画*/
		LunaFontSprite::DrawString(FontSpr, StrTbl[i], StrPx[i], StrPy[i], PRIMITIVE_Z_CENTER, COLOR_RED);
	}
	
	/*バッファ更新*/
	LunaFontSprite::UpdateBuffer(FontSpr);
	
	/*実際の描画*/
	LunaFontSprite::Rendering(FontSpr);
		
}



//================================================
//メニュー移動
//================================================
void CMenu::Move(int MenuMax)
{
	if(LunaPad::GetState(0, PAD_STATE_REPEAT, LunaPad::CursorWrapUpDown(0, &Cursor, MenuMax) ) )
	{
		Se[SE_CURSOR].PlaySoundA();	
	}
}

//================================================
//メニュー移動(左右)
//================================================
void CMenu::MoveLeftRight(int MenuMax)
{
	LunaPad::CursorWrapLeftRight(0, &Cursor, MenuMax);
}

//================================================
//フォント描画
//================================================
//void CMenu::DrawFont(char *string[], int num)
//{
//	/*フォント描画開始*/
//	LunaFont::Begin(Font);
//	
//	/*文字描画*/
//	for(int i = 0;i < num;i++)
//	{
//		LunaFont::DrawText(Px, Py+i*FONT_SIZE, COLOR_WHITE, string[i]);
//	}
//	
//	/*フォント描画終了*/
//	LunaFont::End();
//}

//================================================
//フォント描画(書式付)
//================================================
//void CMenu::DrawFont(char *string[])
//{
//	/*フォント描画開始*/
//	LunaFont::Begin(Font);
//	
//	/*文字描画*/
//	LunaFont::DrawText(Px, Py, COLOR_WHITE, string[0], Shot);
//	LunaFont::DrawText(Px, Py + FONT_SIZE, COLOR_WHITE, string[1], Change);
//	LunaFont::DrawText(Px, Py + 2 * FONT_SIZE, COLOR_WHITE, string[2], Special);
//	LunaFont::DrawText(Px, Py + 3 * FONT_SIZE, COLOR_WHITE, string[3], Slow);
//	LunaFont::DrawText(Px, Py + 4 * FONT_SIZE, COLOR_WHITE, string[4], Pause);
//	LunaFont::DrawText(Px, Py + 5 * FONT_SIZE, COLOR_WHITE, string[5]);
//	
//	
//	/*フォント描画終了*/
//	LunaFont::End();
//}

//================================================
//エラー描画
//================================================
void CMenu::DrawErrorMessage(void)
{
	/*フォント描画開始*/
	LunaFont::Begin(Font);
	
	/*描画*/
	LunaFont::DrawText(200, TOP, COLOR_WHITE, "パッドが見つかりません");
	LunaFont::DrawText(200, TOP+FONT_SIZE, COLOR_WHITE, "Zキーでタイトルに戻ります");
	
	/*フォント描画終了*/
	LunaFont::End();
}

//================================================
//モード選択
//================================================
void CMenu::ModeSelect(int *mode)
{
	switch(Cursor)
	{
		case ITEM_START:
		{
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				*mode = SCENE_CHARSEL;
				Se[SE_ENTER].PlaySoundA();
				Cursor = 0;
				
			}
			//*mode = SCENE_FADEOUT;
			break;
		}
		
		//case ITEM_TUTOLIAL:
		//{
		//	*mode = SCENE_TUTOLIAL;
		//	CursorY = TOP;
		//	break;
		//}
		
		case ITEM_CONFIG:
		{
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				if(LunaInput::GetJoystickData(0, &Pad) )
				{
					*mode = SCENE_OPTION;
					Cursor = 0;
					Se[SE_ENTER].PlaySoundA();
					
				}
				
				else
				{
					*mode = SCENE_ERROR;
					Cursor = 0;
				}
			}
			
			break;
		} 
		
		case ITEM_EXIT:
		{
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				*mode = SCENE_EXIT;
				Se[SE_ENTER].PlaySoundA();
				Cursor = 0;
				
			}
			
			break;
		}
	}
}

//================================================
//キャラセレクト
//================================================
void CMenu::CharaSelect(int *mode, int *first, int *second, int *third)
{
	switch(Scene)	
	{
		case SCENE_FIRST:
		{
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				if(!IsSelected)
				{
					IsSelected = TRUE;
					
					OldCursor = Cursor;
					
					Scene = SCENE_SECOND;
					
					Se[SE_ENTER].PlaySoundA();
				}
				
			}
			
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_02) )
			{
				*mode = SCENE_TITLE;
				Cursor = 0;
				Se[SE_CANCEL].PlaySoundA();
			}
			
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_05) )
			{
				Scene = SCENE_END;
				Cursor = 0;
				Se[SE_ENTER].PlaySoundA();
			}
			
			break;
		}
		
		case SCENE_SECOND:
		{
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				if(IsSelected)
				{
					if(OldCursor == 0)
					{
						if(Cursor == 0)
						{
							Swap(first, first);
						}
						
						if(Cursor == 1)
						{
							Swap(first, second);
						}
						
						if(Cursor == 2)
						{
							Swap(first, third);
						}
						
						IsSelected = FALSE;
						Se[SE_ENTER].PlaySoundA();
					}
					
					if(OldCursor == 1)
					{
						if(Cursor == 0)
						{
							Swap(second, first);
							
						}
						
						if(Cursor == 1)
						{
							Swap(second, second);
							
						}
						
						if(Cursor == 2)
						{
							Swap(second, third);
							
						}
						
					}
					
					if(OldCursor == 2)
					{
						if(Cursor == 0)
						{
							Swap(third, first);
							
						}
						
						if(Cursor == 1)
						{
							Swap(third, second);
							
						}
						
						if(Cursor == 2)
						{
							Swap(third, third);
						}
						
					}
					
					IsSelected = FALSE;
					Se[SE_ENTER].PlaySoundA();
					
					Scene = SCENE_FIRST;
					
				}
			}
			
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_02) )
			{
				IsSelected = FALSE;
				Se[SE_CANCEL].PlaySoundA();
				
				Scene = SCENE_FIRST;
			}
			
			break;
		}
		
		case SCENE_END:
		{
			break;
		}
	}
	
	DrawCursor(Cursor, 0);
	DrawCursor(OldCursor, 1);
	
	if(!IsSelected)
	{
		Rendering(0);
	}
	
	if(IsSelected)
	{
		Rendering(0);
		
		Rendering(1);
	}
	
}

//================================================
//キャラセレクト終了確認画面
//================================================
void CMenu::CharaSelectExit(int *mode)
{
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		switch(Cursor)
		{
			case 0:
			{
				*mode = SCENE_MAIN;
				Se[SE_ENTER].PlaySoundA();
				break;
			}
			
			case 1:
			{
				Scene = SCENE_FIRST;
				Se[SE_CANCEL].PlaySoundA();
				Cursor = 0;
				break;
			}
		}
	}
	
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_02) )
	{
		Scene = SCENE_FIRST;
		Se[SE_CANCEL].PlaySoundA();
		Cursor = 0;
	}
}


//================================================
//ゲームオーバーセレクト
//================================================
void CMenu::GameOverSelect(int *mode)
{
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		switch(Cursor)
		{
			case 0:
			{
				*mode = SCENE_CONTINUE;
				Se[SE_ENTER].PlaySoundA();
				break;
			}
			
			case 1:
			{
				*mode = SCENE_INITIALIZE;
				Se[SE_ENTER].PlaySoundA();
				break;
			}
		}
	}
}

//================================================
//終了確認セレクト
//================================================
void CMenu::Select(int *mode)
{
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		switch(Cursor)
		{
			case 0:
			{
				Se[SE_ENTER].PlaySoundA();
				Luna::Exit();
				break;
			}
			
			case 1:
			{
				Se[SE_CANCEL].PlaySoundA();
				*mode = SCENE_TITLE;
				Cursor = 0;
				break;
			}
		}
	}
	
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_02) )
	{
		Se[SE_CANCEL].PlaySoundA();
		*mode = SCENE_TITLE;
		Cursor = 0;
	}
}

//================================================
//ポーズセレクト
//================================================
void CMenu::PauseSelect(int *mode)
{
	switch(Cursor)
	{
		case 0:
		{
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				*mode = SCENE_MAIN;
				Se[SE_ENTER].PlaySoundA();
			}
			break;
		}
		
		//case 1:
		//{
		//	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
		//	{
		//		*mode = SCENE_EXIT;
		//		Se[SE_ENTER].PlaySoundA();
		//	}
		//	
		//	break;
		//}
		
		case 1:
		{
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				*mode = SCENE_PAUSEEXIT;
				Se[SE_ENTER].PlaySoundA();
			}
			
			break;
		} 
		
	}
	
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_05) )
	{
		*mode = SCENE_MAIN;
		Se[SE_CANCEL].PlaySoundA();
	}
	
	DrawCursor();
	
	Rendering();
}

//================================================
//ポーズ終了確認画面
//================================================
void CMenu::PauseExitSelect(int *mode)
{
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		switch(Cursor)
		{
			case 0:
			{
				*mode = SCENE_INITIALIZE;
				Se[SE_ENTER].PlaySoundA();
				Cursor = 0;
				break;
			}
			
			case 1:
			{
				*mode = SCENE_PAUSE;
				Se[SE_CANCEL].PlaySoundA();
				Cursor = 0;
				break;
			}
		}
	}
	
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_02) )
	{
		*mode = SCENE_PAUSE;
		Se[SE_CANCEL].PlaySoundA();
		Cursor = 0;
	}
}

//================================================
//キーコンフィグ
//================================================
void CMenu::KeyConfig(int *mode)
{
	if(LunaInput::GetJoystickData(0, &Pad) )
	{
		switch(Cursor)
		{
			case 0:
			{
				for(int i = 0;i < PAD_BUTTON_MAX;i++)
				{
					if(Pad.Button[i])
					{
						if(i == Change)
						{
							Swap(&Shot, &Change);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						else if(i == Special)
						{
							Swap(&Shot, &Special);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						//else if(i == Slow)
						//{
						//	Swap(&Shot, &Slow);
						//}
						//
						else if(i == Pause)
						{
							Swap(&Shot, &Pause);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						else
						{
							Shot = i;
							Se[SE_ENTER].PlaySoundA();
							
						}
						
					}
					
				}
				
				break;	
			}
			
			case 1:
			{
				for(int i = 0;i < PAD_BUTTON_MAX;i++)
				{
					if(Pad.Button[i])
					{
						if(i == Shot)
						{
							Swap(&Change, &Shot);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						else if(i == Special)
						{
							Swap(&Change, &Special);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						//else if(i == Slow)
						//{
						//	Swap(&Change, &Slow);
						//}
						
						else if(i == Pause)
						{
							Swap(&Change, &Pause);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						else
						{
							Change = i;
							Se[SE_ENTER].PlaySoundA();
							
						}
						
					}
				}
				
				break;
			}
			
			case 2:
			{
				for(int i = 0;i < PAD_BUTTON_MAX;i++)
				{
					if(Pad.Button[i])
					{
						if(i == Shot)
						{
							Swap(&Special, &Shot);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						else if(i == Change)
						{
							Swap(&Special, &Change);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						//else if(i == Slow)
						//{
						//	Swap(&Special, &Slow);
						//}
						
						else if(i == Pause)
						{
							Swap(&Special, &Pause);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						else
						{
							Special = i;
							Se[SE_ENTER].PlaySoundA();
							
						}
						
					}
				}
				
				break;
			}
			
			//case 3:
			//{
			//	for(int i = 0;i < PAD_BUTTON_MAX;i++)
			//	{
			//		if(Pad.Button[i])
			//		{
			//			if(i == Shot)
			//			{
			//				Swap(&Slow, &Shot);
			//			}
			//			
			//			else if(i == Special)
			//			{
			//				Swap(&Slow, &Special);
			//			}
			//			
			//			else if(i == Change)
			//			{
			//				Swap(&Slow, &Change);
			//			}
			//			
			//			else if(i == Pause)
			//			{
			//				Swap(&Slow, &Pause);
			//			}
			//			
			//			
			//			else
			//			{
			//				Slow = i;
			//			}
			//		}
			//	}
			//	
			//	break;
			//}
			
			
			case 3:
			{
				for(int i = 0;i < PAD_BUTTON_MAX;i++)
				{
					if(Pad.Button[i])
					{
						if(i == Shot)
						{
							Swap(&Pause, &Shot);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						else if(i == Special)
						{
							Swap(&Pause, &Special);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						else if(i == Change)
						{
							Swap(&Pause, &Change);
							Se[SE_ENTER].PlaySoundA();
							
						}
						
						//else if(i == Slow)
						//{
						//	Swap(&Pause, &Slow);
						//}
						
						else
						{
							Pause = i;
							Se[SE_ENTER].PlaySoundA();
							
						}
						
					}
				}
				
				break;
				
			}
			
			case 4:
			{
				if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					Se[SE_ENTER].PlaySoundA();
					
					*mode = SCENE_TITLE;
					Cursor = 0;
					
					LunaPad::SetButton(0, PAD_BUTTON_01, Shot);
					LunaPad::SetButton(0, PAD_BUTTON_02, Change);
					LunaPad::SetButton(0, PAD_BUTTON_03, Special);
					LunaPad::SetButton(0, PAD_BUTTON_05, Pause);
					
				}
				
				break;
			}
		}
		
		DrawCursor();
	
		Rendering();
		
		
		
	}
	
		
}

//================================================
//キャラ入れ替え
//================================================
void CMenu::Swap(int *x, int *y)
{
	tmp = *x;
	*x = *y;
	*y = tmp;
}

void CMenu::Swap(int *x, int *y, bool *Flag)
{
	tmp = *x;
	*x = *y;
	*y = tmp;
		
	*Flag = FALSE;
	
}


//================================================
//デバッグ用
//================================================
void CMenu::Debug(void)
{
//	LunaDebug::DrawString("Shot:%d", Shot);
//	LunaDebug::DrawString("Change:%d", Change);
//	LunaDebug::DrawString("Special:%d", Special);
//	LunaDebug::DrawString("Slow:%d", Slow);
	//LunaDebug::DrawString("Flag:%d", Flag);
	//LunaDebug::DrawString("tmp:%d", tmp);
	LunaDebug::DrawString("IsSelected:%d",IsSelected);
	LunaDebug::DrawString("Cursor:%d", Cursor);
	LunaDebug::DrawString("OldCursor:%d", OldCursor);
	
}

//================================================
//メモリ開放
//================================================
void CMenu::Release(void)
{
	for(int i = 0;i < CURSOR_NUM;i++)
	{
		LunaTexture::Release(Tex[i]);
		
		LunaSprite::Release(Spr[i]);
	}
	
	LunaFont::Release(Font);
	
	for(int i = 0;i < SE_MAX;i++)
	{
		Se[i].Release();
	}
	
	//LunaFontSprite::Release(FontSpr);
}