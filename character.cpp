//================================================
//include
//================================================
#include "character.h"

//================================================
//コンストラクタ
//================================================
CChara::CChara()
{
	COMP = 7;
	CHARGE_MAX = 70;
}

//================================================
//コンストラクタ
//================================================
CChara::CChara(int width, int height, int divnum)
{
	Width = width;
	Height = height;
	Divnum = divnum;
	
	COMP = 5;
}

//================================================
//デストラクタ
//================================================
CChara::~CChara()
{

}

//================================================
//初期化
//================================================
void CChara::Initialize(void)
{
	IsExist = FALSE;
	
	bullet.Initialize();
	
	chargefx.Initialize();
	chargefx.Set(56, 56, 8);
	
	mchargefx.Initialize();
	mchargefx.Set(56, 56, 4);
	
}

//================================================
//サウンド読み込み
//================================================
void CChara::LoadSound()
{
	char *sename[] =
	{
		"sound\\charge.wav",
		"sound\\chargeshoot.wav",
		"sound\\umbrella.wav",
	};
	
	for(int i = 0;i < SE_MAX;i++)
	{
		Se[i].LoadSound(sename[i]);
	}
}

//================================================
//テクスチャ読み込み
//================================================
void CChara::LoadImage(char *name, int ColorKey)
{
	Tex = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_2D, ColorKey);
	
	CreateSprite();
	
	chargefx.LoadImageA("system\\charge.bmp", COLORKEY_WHITE);
	
	mchargefx.LoadImageA("system\\charge2.bmp", COLORKEY_WHITE);
}

//================================================
//スプライト生成
//================================================
void CChara::CreateSprite(void)
{
	/*空のスプライト生成*/
	Spr = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
				
	/*スプライトにテクスチャを接続*/
	LunaSprite::AttatchTexture(Spr, 0, Tex);
	
}

//================================================
//画像情報セット
//================================================
void CChara::Set(int width, int height, int divnum)
{
	Width = width;
	Height = height;
	Divnum = divnum;
}

//================================================
//当たり判定セット
//================================================
void CChara::SetRect(void)
{
	HitRect.Sx = fPosX + COMP;
	HitRect.Sy = fPosY + COMP;
	HitRect.Ex = fPosX + Width - COMP;
	HitRect.Ey = fPosY + Height - COMP;
	
	bullet.SetRect();
}

//================================================
//座標セット
//================================================
void CChara::SetPosition(float posx, float posy)
{
	fPosX = posx;
	fPosY = posy - 30;
}

//================================================
//X座標を得る
//================================================
float CChara::Get_PosX(void)
{
	return fPosX;
}

//================================================
//Y座標を得る　
//================================================
float CChara::Get_PosY(void)
{
	return fPosY;
}

//================================================
//デバッグ用
//================================================
void CChara::Debug(void)
{
	//LunaDebug::DrawString("CPx:%f", fPosX);
	//LunaDebug::DrawString("CPy:%f", fPosY);
	LunaDebug::DrawString("flg:%d", IsExist);
	LunaDebug::DrawString("counter:%d", counter);
	LunaDebug::DrawString("charge_counter:%d", count_charge);
}

//================================================
//スプライト描画
//================================================
void CChara::Draw(float posx, float posy)
{
	if(!IsExist)
	{
		SetPosition(posx, posy);
	}
	
	if(IsExist)
	{
		/*スプライトバッファクリア*/
		LunaSprite::ResetBuffer(Spr);
		
		/*描画先*/
		Dst.Set(fPosX, fPosY, F(Width), F(Height) );
							
		/*描画元*/
		Src.Set( F( (animcounter%Divnum)*Width ), F(0), F(Width), F(Height) );
		
		/*描画キューに追加*/
		LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
		
		/*スプライトバッファ更新*/
		LunaSprite::UpdateBuffer(Spr);
		
	}
	
	bullet.Draw();
	
}

//================================================
//描画
//================================================
void CChara::Draw(void)
{
	/*スプライトバッファクリア*/
	LunaSprite::ResetBuffer(Spr);
	
	/*描画先*/
	Dst.Set(fPosX, fPosY, F(Width), F(Height) );
						
	/*描画元*/
	Src.Set( F( (animcounter%Divnum)*Width ), F(0), F(Width), F(Height) );
	
	/*描画キューに追加*/
	LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	/*スプライトバッファ更新*/
	LunaSprite::UpdateBuffer(Spr);
		
	bullet.Draw();
	
}

//================================================
//回転描画
//================================================
void CChara::DrawRotate(float posx, float posy)
{
	/*スプライトバッファクリア*/
	LunaSprite::ResetBuffer(Spr);
	
	/*描画先*/
	Dst.Set(fPosX, fPosY, F(Width), F(Height) );
						
	/*描画元*/
	Src.Set( F( (animcounter%Divnum)*Width ), F(0), F(Width), F(Height) );
	
	/*描画キューに追加*/
	LunaSprite::DrawSquareRotate(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE, Angle);
	
	/*スプライトバッファ更新*/
	LunaSprite::UpdateBuffer(Spr);
		
	bullet.Draw();
}

//===============================================
//レンダリング
//===============================================
void CChara::Rendering()
{
	if(Luna3D::BeginScene() )
	{
		if(IsExist)
		{
			LunaSprite::Rendering(Spr);
		}
		
		bullet.Rendering();
		
		chargefx.Rendering();
		
		mchargefx.Rendering();
		
		Luna3D::EndScene();
	}
}

//================================================
//傘セット
//================================================
void CChara::SetUmbrella(float posx, float posy)
{
	if(IsExist)
	{
		fPosX = posx;
		fPosY = posy - 30;
	}
	
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		Se[SE_UMBRELLA].PlaySoundA();
	}
	
	if(LunaPad::GetState(0, PAD_STATE_HOLD, PAD_BUTTON_01) )
	{
		Attack = 1;
			
		IsExist = TRUE;
		counter++;
		
		if(IsExist)
		{
			if(Luna::GetSyncCounter() % 3 == 0)
			{
				animcounter++;
			}
			
			if(counter > 8)
			{
				Angle += GET_ANGLE(30);
			}
			
			if(animcounter >= 2)
			{
				animcounter = 2;
			}
		}
		
	}
	
	if(LunaPad::GetState(0, PAD_STATE_PULL, PAD_BUTTON_01) )
	{
		IsExist = FALSE;
		counter = 0;
		animcounter = 0;
	}
}

//================================================
//移動
//================================================
void CChara::Move(void)
{
	fPosX += fVx;
	fPosY += fVy;
}

//================================================
//ショット処理
//================================================
void CChara::ChargeShoot(bool *charge)
{
	if(LunaPad::GetState(0, PAD_STATE_HOLD, PAD_BUTTON_01) )
	{
		count_charge += 1;
		
		if(count_charge > 4)
		{
			chargefx.IsExist = TRUE;
			Se[SE_CHARGE].PlaySoundA();
		}
		
		chargefx.animcounter++;
		
		if(count_charge >= CHARGE_MAX)
		{
			chargefx.IsExist = FALSE;
			
			mchargefx.IsExist = TRUE;
			mchargefx.animcounter++;
			
			count_charge = CHARGE_MAX;
			*charge = TRUE;
			
		}
	}
	
	if(LunaPad::GetState(0, PAD_STATE_PULL, PAD_BUTTON_01) )
	{
		Se[SE_CHARGE].StopSound();
		
		chargefx.IsExist = FALSE;
		
		if(*charge)
		{
			mchargefx.IsExist = FALSE;
			IsExist = TRUE;
		}
		
		count_charge = 0;
	}
		
}

//================================================
//設置攻撃
//================================================
void CChara::PutAttack(bool *charge)
{
	if(*charge)
	{
		if(IsExist)
		{
			bullet.CreateBullet(fPosX, fPosY, BULLET_MAX/3);
			
			Se[SE_CHARGESHOT].PlaySoundA();
			
			if(bullet.trigger > 0)
			{
				bullet.trigger -= 1;
			}
			
			bullet.counter++;
			
		}
	}
	
	if(bullet.counter > 200)
	{
		IsExist = FALSE;
		*charge = FALSE;
		bullet.counter = 0;
	}
	
	bullet.Move(PLAYER);
	
	bullet.MovePattern5(fPosX, fPosY);
	
}
	

//================================================
//移動パターン1(チャージ弾の動き)
//================================================
void CChara::MovePattern1(bool *charge)
{
	if(IsExist)
	{
		Se[SE_CHARGESHOT].PlaySoundA();
		
		Attack = 20;
			
		fPosY -= 8;
		
		if(fPosY < F(-40) )
		{
			IsExist = FALSE;
			*charge = FALSE;
		}
	}

}

//================================================
//移動パターン3(ナイフの動き)
//================================================
void CChara::MovePattern3(float tax, float tay)
{
	if(IsExist)
	{
		knifecounter++;
		
		if(knifecounter > 0 && knifecounter < 100)
		{
			fVx = 0;
			fVy = 1;
		}
		
		if(knifecounter > 100 && knifecounter < 150)
		{
			fVy = 0;
			Angle = LunaMath::Atan(tax - fPosX, tay - fPosY);
		}
		
		if(knifecounter > 150)
		{
			fVx = LunaMath::Cos(Angle)*20.0f;
			fVy = LunaMath::Sin(Angle)*20.0f;
		}
		
		if(fPosY > 500)
		{
			IsExist = FALSE;
			knifecounter = 0;
		}
	}
}

//================================================
//移動パターン4(ドクロの動き)
//================================================
void CChara::MovePattern4()
{
	bullet.Move(ENEMY);
	
	bullet.MovePattern3();
	
	if(IsExist)
	{
		fVy = 3;
		
		counter++;
		
		if(fPosY > 200)
		{
			fVy = 0;			
			IsExist = FALSE;
			bullet.CreateBullet(fPosX, fPosY);
			counter = 0;
		}
				
	}

}


//================================================
//メモリ開放
//================================================
void CChara::Release(void)
{
	LunaTexture::Release(Tex);
	
	LunaSprite::Release(Spr);
	
	bullet.Release();
	
	chargefx.Release();
	
	mchargefx.Release();
	
}
