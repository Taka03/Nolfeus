//================================================
//include
//================================================
#include "player.h"
#include "gamemode.h"

//================================================
//コンストラクタ
//================================================
CPlayer::CPlayer()
{
	first = ID_PLAYER1;
	second = ID_PLAYER2;
	third = ID_PLAYER3;
	
	COMP = 10;
	
	InvinceTime = 100;
	
	RecoverLife = 1;


}

//================================================
//コンストラクタ
//================================================
CPlayer::CPlayer(float Px, float Py, int width, int height, int divnum)
{
	fPosX = Px;
	fPosY = Py;
	
	Width = width;
	Height = height;
	
	Divnum = divnum;
	
}

//================================================
//デストラクタ
//================================================
CPlayer::~CPlayer()
{

}

//================================================
//初期化
//================================================
void CPlayer::Initialize(void)
{
	for(int i = 0;i < PLAYER_NUM;i++)
	{
		Hp[i] = MAX_LIFE;
		OldHp[i] = Hp[i];
		RecoverMax[i] = MAX_LIFE;
	}
	
	Invcounter = 0;
	
	IsUseSpecial = FALSE;
	IsWolf = FALSE;
	IsStop = FALSE;
	IsClear = FALSE;
	
	IsDead = FALSE;
	IsInvince = FALSE;
	
	bullet.Initialize();
	bullet.SetGraphInfo(8, 16, 1);
	
	for(int i = 0;i < AME_NUM;i++)
	{
		amebullet[i].Initialize();
		amebullet[i].SetGraphInfo(16, 16, 4);
	}
	
	shadow.bullet.SetGraphInfo(16, 16, 1);
	
	lightball.Initialize();
	
	lightball.Set(121, 121, 8); 
	
	charge.Initialize();
	charge.Set(40, 40, 2);
	
	change.Initialize();
	change.Set(60, 60, 16);
	
	umbrella.Initialize();
	umbrella.Set(48, 48, 3);
	
	shadow.Initialize();
	shadow.Set(32, 32, 6);
	
	for(int i = 0;i < PLAYER_NUM-1;i++)
	{
		lgauge[i].Initialize();
		lgauge[i].SetPosition(430, F(170) );
		lgauge[i].SetGraphInfo(100, 20);
		
		rgauge[i].Initialize();
		rgauge[i].SetPosition(430, F(170) );
		rgauge[i].SetGraphInfo(100, 20);
		
	}
	
	magauge.Initialize();
	magauge.SetPosition(430, 400);
	magauge.SetGraphInfo(100, 20);
	
	agauge.Initialize();
	agauge.SetPosition(430, 400);
	agauge.SetGraphInfo(100, 20);
	
	face.Initialize();
	
	first = ID_PLAYER1;
	second = ID_PLAYER2;
	third = ID_PLAYER3;
}

//================================================
//パラメータ読み込み
//================================================
void CPlayer::LoadParam(void)
{
	FILE *fp;
	fp = fopen("player.dat", "rb");
	
	if(fp == NULL)
	{
		Luna::MsgBox(0, "Error", "plater.datが見つかりません");
	}
	
	for(int i = 0;i < PLAYER_NUM;i++)
	{
		fread(&pdata[i], sizeof(DATA), 1, fp);
	}
	
	fclose(fp);
	
}

//================================================
//座標等セット
//================================================
void CPlayer::Set(float Px, float Py, int width, int height, int divnum)
{
	fPosX = Px;
	fPosY = Py;
	Width = width;
	Height = height;
	Divnum = divnum;
}

//================================================
//座標セット
//================================================
void CPlayer::SetPosition(float Px, float Py)
{
	fPosX = Px;
	fPosY = Py;
}

//================================================
//テクスチャ読み込み
//================================================
void CPlayer::LoadImage(char *name, int ColorKey)
{
	for(int i = 0;i < PLAYER_NUM;i++)
	{
		Tex[i] = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_2D, ColorKey);
	}
	
}

void CPlayer::LoadImage(void)
{
	char *name[]  =
	{
		"player\\isla.png",
		"player\\rai.png",
		"player\\ame.png",
		"player\\rai_wolf.png",
	};
	
	char *window[] =
	{
		"player\\win_isla.png",
		"player\\win_rai.png",
		"plater\\win_ame.png",
	};
	
	for(int i = 0;i < PLAYER_NUM;i++)
	{
		Tex[i] = LunaTexture::CreateFromFile(name[i], FORMAT_TEXTURE_2D, COLORKEY_WHITE);
	}
	
	for(int i = 0;i < PLAYER_NUM - 1;i++)
	{
		windowTex[i] = LunaTexture::CreateFromFile(window[i], FORMAT_TEXTURE_2D, COLORKEY_WHITE);
	}
	
	CreateSprite();
	
	bullet.LoadImageA("shot\\isla_knife.png", COLORKEY_WHITE);
	
	for(int i = 0;i < AME_NUM;i++)
	{
		amebullet[i].LoadImageA("shot\\ame_shot.png", COLORKEY_WHITE);
	}
	
	shadow.bullet.LoadImageA("shot\\shot_blue1.png", COLORKEY_WHITE);
	
	charge.LoadImageA("shot\\charge_shot.png", COLORKEY_WHITE);
	umbrella.LoadImageA("shot\\rai_kasa.png", COLORKEY_WHITE);
	shadow.LoadImageA("player\\amec.png", COLORKEY_WHITE);
	
	lightball.LoadImageA("effect\\lightball3.bmp", COLORKEY_WHITE);
	//chargefx.LoadImageA("effect\\charge.png", COLORKEY_WHITE);
	//mchargefx.LoadImageA("effect\\charge_max.png", COLORKEY_WHITE);
	
	face.LoadImageA();
	
	for(int i = 0;i < PLAYER_NUM - 1;i++)
	{
		lgauge[i].LoadImageA("system\\life1.png", COLORKEY_WHITE);
		rgauge[i].LoadImageA("system\\life2.png", COLORKEY_WHITE);
	}
	
	agauge.LoadImageA("system\\agauge2.png", COLORKEY_DISABLE);
	magauge.LoadImageA("system\\agauge1.png", COLORKEY_DISABLE);
	
	change.LoadImageA("effect\\change.bmp", COLORKEY_WHITE);

}

//================================================
//サウンド読み込み
//================================================
void CPlayer::LoadSound()
{
	char *sename[] =
	{
		"sound\\shot1.wav",
		"sound\\shot2.wav",
		"sound\\stop.wav",
		"sound\\wolf.wav",
		"sound\\clear.wav",
		"sound\\change.wav",
		"sound\\nedeath.wav",
		"sound\\death.wav",
	};
	
	for(int i = 0;i < SE_MAX;i++)
	{
		Se[i].LoadSound(sename[i]);
	}
	
	charge.LoadSound();
	umbrella.LoadSound();
	shadow.LoadSound();

}

//================================================
//スプライト生成
//================================================
void CPlayer::CreateSprite(void)
{
	for(int i = 0;i < PLAYER_NUM;i++)
	{
		/*空のスプライト生成*/
		Spr[i] = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
				
		/*スプライトにテクスチャを接続*/
		LunaSprite::AttatchTexture(Spr[i], 0, Tex[i]);
	}
	
	for(int i = 0;i < PLAYER_NUM - 1;i++)
	{
		windowSpr[i] = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
		
		/*スプライトにテクスチャを接続*/
		LunaSprite::AttatchTexture(windowSpr[i], 0, windowTex[i]);
		
	}
	
}

//================================================
//移動
//================================================
void CPlayer::Move(void)
{
	if(LunaPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_LEFT) )
	{
		fPosX -= Speed;
	}
	
	if(LunaPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_RIGHT) )
	{
		fPosX += Speed;
	}
	
	if(LunaPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_UP) )
	{
		fPosY -= Speed;
	}
	
	if(LunaPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_DOWN) )
	{
		fPosY += Speed;
	}
	
	MoveAdjust(MINI_RANGE_X, MAX_RANGE_X, MINI_RANGE_Y, MAX_RANGE_Y);
	
}

//================================================
//移動範囲補正
//================================================
void CPlayer::MoveAdjust(int left, int right, int top, int bottom)
{
	if(fPosX <= left)
	{
		fPosX = F(left);
	}
	
	if(fPosX >= right-Width)
	{
		fPosX = F(right-Width);
	}
	
	if(fPosY <= top)
	{
		fPosY = F(top);
	}
	
	if(fPosY >= bottom-Height)
	{
		fPosY = F(bottom-Height);
	}
}

//================================================
//デバッグ用
//================================================
void CPlayer::Debug(void)
{
	//LunaDebug::DrawString("Px:%f", fPosX);
	//LunaDebug::DrawString("Py:%f", fPosY);
//	LunaDebug::DrawString("Width:%d", Width);
//	LunaDebug::DrawString("Height:%d", Height);
//	
//	LunaDebug::DrawString("Type:%d", Type);
	
	//LunaDebug::DrawString("life:%d", life);
	
	//LunaDebug::DrawString("Defence:%d", Defence);
	//LunaDebug::DrawString("Speed:%d", Speed);
	//LunaDebug::DrawString("Width:%d", pdata[1].Height);
	
	//LunaDebug::DrawString("fTime:%f", fTime);
	
	//LunaDebug::DrawString("OldHp:%d", OldHp[0]);
	//LunaDebug::DrawString("ChargeFlag:%d", bullet.ChargeFlag);
	//LunaDebug::DrawString("RecoverMax:%d", RecoverMax);
	
	//LunaDebug::DrawString("first:%d", first);
	//LunaDebug::DrawString("second:%d", second);
	//LunaDebug::DrawString("third:%d", third);
	//LunaDebug::DrawString("IsInvince:%d", IsInvince);
	//
	////LunaDebug::DrawString("data[0]:%s", data[2]);
	////LunaDebug::DrawString("Special:%d", IsUseSpecial);
	//LunaDebug::DrawString("counter:%d", Invcounter);
	
	for(int i = 0;i < PLAYER_NUM - 1;i++)
	{
		LunaDebug::DrawString("Hp[%d]:%d", i, Hp[i]);
	}
	
	//LunaDebug::DrawString("gauge:%d", agauge.ability);
	
	charge.Debug();
}

//================================================
//X座標を得る
//================================================
float CPlayer::Get_PosX(void)
{
	return fPosX;
}

//================================================
//Y座標を得る
//================================================
float CPlayer::Get_PosY(void)
{
	return fPosY;
}

//================================================
//幅を得る
//================================================
int CPlayer::GetWidth(void)
{
	return Width;
}

//================================================
//高さを得る
//================================================
int CPlayer::GetHeight(void)
{
 	return Height;
}

//================================================
//HPを得る
//================================================
int CPlayer::Get_Life(void)
{
	return life;
}

//================================================
//画像情報セット
//================================================
void CPlayer::SetGraphInfo()
{
	Width = pdata[Type].Width;
	Height = pdata[Type].Height;
	Divnum = pdata[Type].Divnum;
	Hp[Type] = pdata[Type].Hp;
}

//================================================
//HPをセット
//================================================
void CPlayer::SetHp(int Hp)
{
	life = Hp;
}

//================================================
//ステータスセット
//================================================
void CPlayer::SetStatus(void)
{
	Speed = pdata[Type].Speed;
	Defence = pdata[Type].Defence;
	Weight = pdata[Type].Weight;
}

//================================================
//当たり判定領域設定
//================================================
void CPlayer::SetRect(void)
{
	HitRect.Sx = fPosX + COMP;
	HitRect.Sy = fPosY + COMP;
	HitRect.Ex = fPosX + Width - COMP;
	HitRect.Ey = fPosY + Height - COMP;
	
	bullet.SetRect();
	
	for(int i = 0;i < AME_NUM;i++)
	{
		amebullet[i].SetRect();
	}
	
	charge.SetRect();
		
	umbrella.SetRect();
	
	shadow.SetRect();
	
}

//================================================
//ゲージ使用
//================================================
void CPlayer::UseGauge()
{
	const int ABILITY_MIN = 20;
	
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_03) )
	{
		if(agauge.ability == GAUGE_MAX)
		{
			if(!IsUseSpecial)
			{
				agauge.ability -= ABILITY_MIN;
			}

			IsUseSpecial = TRUE;
		}
		
		else
		{
			if(IsUseSpecial)
			{
				IsUseSpecial = FALSE;
			}
		}
		
	}
	
	UseSpecial();
	
	if(agauge.ability <= 0)
	{
		IsUseSpecial = FALSE;
	}
	
	if(!IsUseSpecial)
	{
		IsStop = FALSE;
		IsWolf = FALSE;
		IsClear = FALSE;
	}
	
	/*ゲージ増加*/
	agauge.AddGauge(&IsUseSpecial);

}

//================================================
//キャラチェンジ使用
//================================================
void CPlayer::UseCharaChange()
{
	const int ABILITY_MIN = 60;
	
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_02) )
	{
		if(agauge.ability >= ABILITY_MIN)
		{
			ChangeChara();
			
			Se[SE_CHANGE].PlaySoundA();
			
			change.IsExist = TRUE;
			
			KeepHp();
			
			charge.IsExist = FALSE;
			shadow.IsExist = FALSE;
			umbrella.IsExist = FALSE;
			
			IsUseSpecial = FALSE;
			
			for(int i = 0;i < BULLET_MAX;i++)
			{
				bullet.Flag[i] = FALSE;
				
				for(int j = 0;j < AME_NUM;j++)
				{
					amebullet[j].Flag[i] = FALSE;
				}
				
				shadow.bullet.Flag[i] = FALSE;
			}
			
			agauge.ability -= ABILITY_MIN;
			
		}
		
	}
	
	if(change.IsExist)
	{
		change.animcounter++;
	}
	
	if(change.animcounter == 16)
	{
		change.animcounter = 0;
		change.IsExist = FALSE;
	}
			
	
}

//================================================
//ショット処理
//================================================
void CPlayer::Shoot()
{
	switch(Type)
	{
		case ID_PLAYER1:
		{
			if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				bullet.CreateBullet(fPosX+(Width/3), fPosY, BULLET_MAX);
				Se[SE_SHOT1].PlaySoundA();
			}
			
			bullet.MovePattern1();
			
			charge.ChargeShoot(&bullet.ChargeFlag);
			
			if(bullet.ChargeFlag)
			{
				charge.MovePattern1(&bullet.ChargeFlag);	
			}
			
			bullet.Move(PLAYER);
			
			break;
		}
		
		case ID_PLAYER2:
		{
			/*傘セット*/
			umbrella.SetUmbrella(fPosX, fPosY);
			break;
		}
		
		case ID_PLAYER3:
		{
			Sint32 Angle[] =
			{
				60,
				90,
				120,
			};
			
			for(int i = 0;i < AME_NUM;i++)
			{
				if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					amebullet[i].CreateBullet(fPosX+(Width/3), fPosY, GET_ANGLE(Angle[i]) );
					
					Se[SE_SHOT2].PlaySoundA();
				}
				
				amebullet[i].Move(PLAYER);
				
				amebullet[i].MovePattern4(fPosX, fPosY);
				
				
			}
			
			shadow.ChargeShoot(&amebullet[0].ChargeFlag);
			
			shadow.PutAttack(&amebullet[0].ChargeFlag);
			
			break;
		}
		
	}
	
	if(bullet.IsRefrect)
	{
		bullet.Move(PLAYER);
		bullet.MovePattern1();
	}			
	
	if(!bullet.IsRefrect)
	{
		if(Type == ID_PLAYER2)
		{
			for(int i = 0;i < BULLET_MAX;i++)
			{
				bullet.Flag[i] = FALSE;
			}
		}
	}	
		

}


//================================================
//スプライト描画
//================================================
void CPlayer::Draw(void)
{
	if(IsWolf)
	{
		/*描画先*/
		Dst.Set(fPosX, fPosY, F(Width), F(Height) );
								
		/*描画元*/
		Src.Set( F( (animcounter%Divnum)*Width), F(0), F(Width), F(Height) );
		
		/*スプライトバッファクリア*/
		LunaSprite::ResetBuffer(Spr[3]);
		
		/*描画キューに追加*/
		LunaSprite::DrawSquare(Spr[3], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
		
		/*スプライトバッファ更新*/
		LunaSprite::UpdateBuffer(Spr[3]);
		
		/*HPセット*/
		SetHp(Hp[1]);
		
		/*ステータスセット*/
		Speed = pdata[3].Speed;
		
		if(Luna::GetSyncCounter() % 5 == 0)
		{
			lightball.animcounter++;
		}
		
		lightball.IsExist = TRUE;
		
		lightball.Draw(fPosX-32, fPosY-32);
		
	}
	
	if(!IsWolf)
	{
		/*描画先*/
		Dst.Set(fPosX, fPosY, F(Width), F(Height) );
								
		/*描画元*/
		Src.Set( F( (animcounter%Divnum)*Width), F(0), F(Width), F(Height) );
		
		/*スプライトバッファクリア*/
		LunaSprite::ResetBuffer(Spr[Type]);
		
		if(Hp[Type] >= MAX_LIFE / 4)
		{
			/*描画キューに追加*/
			LunaSprite::DrawSquare(Spr[Type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
		}
			
		if(Hp[Type] < MAX_LIFE / 4)
		{
			/*描画キューに追加*/
			LunaSprite::DrawSquare(Spr[Type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_RED);
		}
			
		/*スプライトバッファ更新*/
		LunaSprite::UpdateBuffer(Spr[Type]);
		
		charge.Draw(fPosX, fPosY);
		umbrella.Draw(fPosX, fPosY);
		shadow.Draw(fPosX, fPosY);
		
		bullet.Draw();
		
		for(int i = 0;i < AME_NUM;i++)
		{
			amebullet[i].Draw();
		}
		
		lightball.IsExist = FALSE;
	
		/*HPセット*/
		SetHp(Hp[Type]);
		
		/*ステータスセット*/
		SetStatus();
		
		change.Draw(fPosX, fPosY);
		
		charge.chargefx.Draw(fPosX, fPosY);
		shadow.chargefx.Draw(fPosX, fPosY);
		
		charge.mchargefx.Draw(fPosX, fPosY);
		shadow.mchargefx.Draw(fPosX, fPosY);
		
	}
	
	if(Luna::GetSyncCounter() % 10 == 0)
	{
		charge.animcounter++;
		shadow.animcounter++;
	}

}

//================================================
//描画
//================================================
void CPlayer::Draw(float posx, float posy, int type)
{
	/*描画先*/
	Dst.Set(posx, posy, F(Width), F(Height) );
	
	/*描画元*/
	Src.Set( F( (animcounter%Divnum)*Width), F(0), F(Width), F(Height) );
	
	/*スプライトレンダリング*/
	LunaSprite::Rendering(Spr[type]);
			
	/*スプライトバッファクリア*/
	LunaSprite::ResetBuffer(Spr[type]);

	/*描画キューに追加*/
	LunaSprite::DrawSquare(Spr[type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	/*スプライトバッファ更新*/
	LunaSprite::UpdateBuffer(Spr[type]);
}

//================================================
//描画
//================================================
//void CPlayer::Draw(void)
//{
//	描画先
//	Dst.Set(fPosX, fPosY, Width, Height);
//						
//	描画元
//	Src.Set((animcounter%Divnum)*Width, 0, Width, Height);
//	
//	スプライトレンダリング
//	LunaSprite::Rendering(Spr);
//
//	スプライトバッファクリア
//	LunaSprite::ResetBuffer(Spr);
//
//	描画キューに追加
//	LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
//	
//	スプライトバッファ更新
//	LunaSprite::UpdateBuffer(Spr);
//	
//	HPセット
//	SetHp(Hp);
//}

//===============================================
//レンダリング
//===============================================
void CPlayer::Rendering()
{
	const int FACE_LEFT = 430;
	
	if(IsWolf)
	{
		LunaSprite::Rendering(Spr[3]);
		
		lightball.Rendering();
	}
	
	if(!IsWolf)
	{
		charge.Rendering();
		umbrella.Rendering();
		shadow.Rendering();
		
		if(!IsInvince)
		{
			/*スプライトレンダリング*/
			LunaSprite::Rendering(Spr[Type]);
		}
		
		
		if(IsInvince)
		{
			Invcounter++;
			
			if(Invcounter >= InvinceTime)
			{
				Invcounter = 0;
				IsInvince = FALSE;
			}
			
			if(Invcounter % 3 == 0)
			{
				Luna3D::SetBlendingType(BLEND_ADD);
				LunaSprite::Rendering(Spr[Type]);
				Luna3D::SetBlendingType(BLEND_NORMAL);
			}
		}
		
		bullet.Rendering();
		
		for(int i = 0;i < AME_NUM;i++)
		{
			amebullet[i].Rendering();
		}
		
	}
	
	if(IsClear)
	{
		charge.Rendering();
		umbrella.Rendering();
		shadow.Rendering();
		
		for(int i = 0;i < AME_NUM;i++)
		{
			amebullet[i].Rendering();
		}
		
		Luna3D::SetBlendingType(BLEND_ADD);
		
		/*スプライトレンダリング*/
		LunaSprite::Rendering(Spr[Type]);
		
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
	}
	
	switch(Type)
	{
		case ID_PLAYER1:
		{
			face.Draw(F(FACE_LEFT), F(100), ID_PLAYER1);
				
			lgauge[0].Draw(F(0), F(0), life);
			rgauge[0].Draw(F(0), F(0), RecoverMax[0]);
			
			face.Draw(F(FACE_LEFT), F(200), ID_PLAYER2);
			lgauge[1].Draw(F(0), F(100), Hp[1]);
			rgauge[1].Draw(F(0), F(100), RecoverMax[1]);
			
			
			face.Draw(F(FACE_LEFT), F(300), ID_PLAYER3);
			lgauge[2].Draw(F(0), F(200), Hp[2]);
			rgauge[2].Draw(F(0), F(200), RecoverMax[2]);
			
			
			break;
		}
		
		case ID_PLAYER2:
		{
			face.Draw(F(FACE_LEFT), F(100), ID_PLAYER2);
				
			lgauge[0].Draw(F(0), F(0), life);
			rgauge[0].Draw(F(0), F(0), RecoverMax[1]);
			
			face.Draw(F(FACE_LEFT), F(200), ID_PLAYER1);
			lgauge[1].Draw(F(0), F(100), Hp[0]);
			rgauge[1].Draw(F(0), F(100), RecoverMax[0]);
			
			face.Draw(F(FACE_LEFT), F(300), ID_PLAYER3);
			lgauge[2].Draw(F(0), F(200), Hp[2]);
			rgauge[2].Draw(F(0), F(200), RecoverMax[2]);
			
			break;
		}
		
		case ID_PLAYER3:
		{
			face.Draw(F(FACE_LEFT), F(100), Type);
			
			lgauge[0].Draw(F(0), F(0), life);
			rgauge[0].Draw(F(0), F(0), RecoverMax[2]);
			
			
			face.Draw(F(FACE_LEFT), F(200), ID_PLAYER1);
			lgauge[1].Draw(F(0), F(100), Hp[0]);
			rgauge[1].Draw(F(0), F(100), RecoverMax[0]);
			
			
			face.Draw(F(FACE_LEFT), F(300), ID_PLAYER2);
			lgauge[2].Draw(F(0), F(200), Hp[1]);
			rgauge[2].Draw(F(0), F(200), RecoverMax[1]);
			
			break;
		}
	}
	
	magauge.Draw(F(0), F(0), GAUGE_MAX);
	agauge.Draw(F(0), F(0), agauge.ability);			
	
	for(int i = 0;i < PLAYER_NUM - 1;i++)
	{
		rgauge[i].Rendering();
		lgauge[i].Rendering();
	}
	
	magauge.Rendering();
	agauge.Rendering();
	
	change.Rendering();
}

//void CPlayer::DrawTex()
//{
//	switch(Type)
//	{
//		case ID_PLAYER1:
//		{
//        		LunaTexture::Draw(Tex[0], &Dst, &Src, COLOR_BASE);
//	
//			SetHp(Hp[0]);
//			
//			break;
//		}
//		
//		case ID_PLAYER2:
//		{
//			/*スプライトレンダリング*/
//			LunaSprite::Rendering(Spr[1]);
//		
//			/*スプライトバッファクリア*/
//			LunaSprite::ResetBuffer(Spr[1]);
//			
//			/*描画キューに追加*/
//			LunaSprite::DrawSquare(Spr[1], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
//			
//			/*スプライトバッファ更新*/
//			LunaSprite::UpdateBuffer(Spr[1]);
//			
//			SetHp(Hp[1]);
//			
//			break;
//		
//		}
//		
//		case ID_PLAYER3:
//		{
//			/*スプライトレンダリング*/
//			LunaSprite::Rendering(Spr[2]);
//		
//			/*スプライトバッファクリア*/
//			LunaSprite::ResetBuffer(Spr[2]);
//			
//			/*描画キューに追加*/
//			LunaSprite::DrawSquare(Spr[2], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
//			
//			/*スプライトバッファ更新*/
//			LunaSprite::UpdateBuffer(Spr[2]);
//			
//			SetHp(Hp[2]);
//			
//			break;
//		}
//	}
//	
//	/*描画先*/
//	Dst.Set(fPosX, fPosY, Width, Height);
//						
//	/*描画元*/
//	Src.Set(0,/*(animcounter%divnum)*Width,*/ 0, Width, Height);
//	
//	
//}

//================================================
//必殺技使用
//================================================
void CPlayer::UseSpecial(void)
{
	if(IsUseSpecial)
	{
		switch(Type)
		{
			case ID_PLAYER1:
			{
				IsStop = TRUE;
				break;
			}
			
			case ID_PLAYER2:
			{
				IsWolf = TRUE;
				break;
			}
			
			case ID_PLAYER3:
			{
				IsClear = TRUE;
				break;
			}
		}			
	}
}

//================================================
//時間停止(イスラの必殺技:「神通力」)
//================================================
void CPlayer::TimeStop(void)
{
	
}

//================================================
//獣化(ライの必殺技:「変化」)
//================================================
void CPlayer::ChangeWolf(void)
{
	IsWolf = TRUE;
}

//================================================
//半透明化(アメウスの必殺技:「ワンダリングシャドウ」)
//================================================
void CPlayer::Clearize(void)
{
	IsClear = !IsClear;	
}


//================================================
//キャラ変更用
//================================================
void CPlayer::ChangeChara(void)
{
	if(Type == first)	
	{
		Type = second;	
	}
	
	else if(Type == second)
	{
		Type = third;
	}
	
	else
	{
		Type = first;
	}
	
	fTime = 0;
	
}

//================================================
//のけぞり
//================================================
void CPlayer::KnockBack(void)
{
	if(!IsInvince)
	{
		IsInvince = TRUE;
	}
}

//================================================
//キャラ入れ替え
//================================================
//void CPlayer::SwapChara(int *x, int *y)
//{
//	
//}

//================================================
//ダメージ計算
//================================================
void CPlayer::CalcDamage(int attack, int defence)
{
	int Damage = (attack  - defence / 2) ;
	
	Hp[Type] -= Damage;	
	
	RecoverMax[Type] -= Damage - 2;
	
	for(int i = 0;i < PLAYER_NUM;i++)
	{
		if(Hp[i] <= 0)
		{
			Hp[i] = 0;
			IsDead = TRUE;
		}
	}
}

//================================================
//ライフ保持
//================================================
void CPlayer::KeepHp()
{
	for(int i = 0;i < PLAYER_NUM;i++)
	{
		OldHp[i] = Hp[i];
	}
}

//================================================
//ライフ回復
//================================================
void CPlayer::Recoverlife(void)
{
	fTime += 1.0f / F(FRAME_RATE);
	
	switch(Type)
	{
		case ID_PLAYER1:
		{
			Hp[1] += 1;
			Hp[2] += 1;
			
			if(Hp[1] >= RecoverMax[1])
			{
				Hp[1] = RecoverMax[1];
			}
			
			if(Hp[2] >= RecoverMax[2])
			{
				Hp[2] = RecoverMax[2];
			}
			
			break;
		}
		
		case ID_PLAYER2:
		{
			Hp[0] += 1;
			Hp[2] += 1;
			
			if(Hp[0] >= RecoverMax[0])
			{
				Hp[0] = RecoverMax[0];
			}
			
			if(Hp[2] >= RecoverMax[2])
			{
				Hp[2] = RecoverMax[2];
			}
			
			break;
		}
		
		case ID_PLAYER3:
		{
			Hp[0] += 1;
			Hp[1] += 1;
			
			if(Hp[0] >= RecoverMax[0])
			{
				Hp[0] = RecoverMax[0];
			}
			
			if(Hp[1] >= RecoverMax[1])
			{
				Hp[1] = RecoverMax[1];
			}
			
			break;
		}
	}
	
}


//================================================
//メモリ開放
//================================================
void CPlayer::Release(void)
{
	for(int i = 0;i < PLAYER_NUM;i++)
	{
		LunaTexture::Release(Tex[i]);
		
		LunaSprite::Release(Spr[i]);
	}
	
	bullet.Release();
	
	for(int i = 0;i < AME_NUM;i++)
	{
		amebullet[i].Release();
	}
	
	charge.Release();
	umbrella.Release();
	shadow.Release();
	
	for(int i = 0;i < PLAYER_NUM - 1;i++)
	{
		rgauge[i].Release();
		lgauge[i].Release();
	}
	
	lightball.Release();
}
