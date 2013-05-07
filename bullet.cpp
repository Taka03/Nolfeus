//================================================
//include
//================================================
#include "bullet.h"
#include "gamemode.h"

//================================================
//コンストラクタ
//================================================
CBullet::CBullet()
{
	COMP = 2;
	CHARGE_MAX = 100;
}

//================================================
//デストラクタ
//================================================
CBullet::~CBullet()
{

}

//================================================
//初期化
//================================================
void CBullet::Initialize(void)
{
	ChargeFlag = FALSE;
	
	for(int i = 0;i < BULLET_MAX;i++)
	{
		Flag[i] = FALSE;
		IsRefrect[i] = FALSE;
	}
	
	LoadSound();
}

//================================================
//音声読み込み
//================================================
void CBullet::LoadSound()
{
	char *sename[] =
	{
		"sound\\refrect.wav",
		"sound\\gun.wav",
	};
	
	for(int i = 0;i < SE_MAX;i++)
	{
		Se[i].LoadSound(sename[i]);
	}
}

//================================================
//テクスチャロード
//================================================
void CBullet::LoadImage(char *name, int ColorKey)
{
	Tex = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_3D, ColorKey);
	
	CreateSprite();
}

//================================================
//スプライト生成
//================================================
void CBullet::CreateSprite()
{
	/*空のスプライト生成*/
	Spr = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
	
	/*接続*/
	LunaSprite::AttatchTexture(Spr, 0, Tex);
}

//================================================
//当たり判定領域設定
//================================================
void CBullet::SetRect(void)
{
	for(int i = 0;i < BULLET_MAX;i++)
	{
		HitRect[i].Sx = fPosX[i] + COMP;
		HitRect[i].Sy = fPosY[i] + COMP;
		HitRect[i].Ex = fPosX[i] + Width - COMP;
		HitRect[i].Ey = fPosY[i] + Height - COMP;
	}
}

//================================================
//弾位置セット
//================================================
void CBullet::SetPosition(int no)
{
	fPosX[no] = -200;
	fPosY[no] = 600;
}

//================================================
//画像情報セット
//================================================
void CBullet::SetGraphInfo(int width, int height, int divnum)
{
	Width = width;
	Height = height;
	Divnum = divnum;
}

//================================================
//弾の生成
//================================================
void CBullet::CreateBullet(float posx, float posy, int num)
{
	if(trigger == 0)
	{
		for(int i = 0;i < num;i++)
		{
			if(!Flag[i])
			{
				Flag[i] = TRUE;
				fPosX[i] = posx;
				fPosY[i] = posy;
				trigger = 0;
				break;
			}
			
		}
	}
	
}

//================================================
//弾の生成(角度付き)
//================================================
void CBullet::CreateBullet(float posx, float posy, float tax, float tay)
{
	if(trigger == 0)
	{
		for(int i = 0;i < BULLET_MAX;i++)
		{
			if(!Flag[i])
			{
				Flag[i] = TRUE;
				fPosX[i] = posx;
				fPosY[i] = posy;
				fAngle[i] = LunaMath::Atan(tax - posx, tay - posy);
			
				trigger = 30;
				break;
			}
		}
	}
	
}

//================================================
//一斉弾の生成
//================================================
void CBullet::CreateBullet(float posx, float posy)
{
	for(int i = 0;i < BULLET_MAX;i++)
	{
		if(!Flag[i])
		{
			Flag[i] = TRUE;
			fPosX[i] = posx;
			fPosY[i] = posy;
		}
	}
}

//================================================
//弾の生成(n-way弾用)
//================================================
void CBullet::CreateBullet(float posx, float posy, Sint32 Angle)
{
	for(int i = 0;i < 2;i++)
	{
		if(!Flag[i])
		{
			Flag[i] = TRUE;
			fPosX[i] = posx;
			fPosY[i] = posy;
			fAngle[i] = Angle;
			
			break;
		}
	}
}

//================================================
//弾の生成(ボス用)
//================================================
void CBullet::CreateBossBullet(float posx, float posy, float tax, float tay)
{
	if(trigger == 0)
	{
		for(int i = 0;i < BULLET_MAX;i++)
		{
			if(!Flag[i])
			{
				Flag[i] = TRUE;
				fPosX[i] = posx;
				fPosY[i] = posy;
				fAngle[i] = LunaMath::Atan(tax - posx, tay - posy);
				
				trigger = 2;
			
				break;
			}
		}
	}
}



//================================================
//反射弾の生成
//================================================
void CBullet::CreateRefBullet(float posx, float posy, int num)
{
	for(int i = 0;i < num;i++)
	{
		if(!Flag[i])
		{
			Flag[i] = TRUE;
			fPosX[i] = posx;
			fPosY[i] = posy;
			Se[SE_REFRECT].PlaySoundA();
			break;
		}
	}
}

//================================================
//弾の動き
//================================================
void CBullet::Move(int Type)
{
	switch(Type)
	{
		case PLAYER:
		{
			for(int i = 0;i < BULLET_MAX;i++)
			{
				if(Flag[i])
				{
					fPosX[i] -= Vx[i];
					fPosY[i] -= Vy[i];
				}
			}
			
			if(trigger > 0)
			{
				trigger -= 1;
			}
		
			break;	
		}
		
		case ENEMY:
		{
			for(int i = 0;i < BULLET_MAX;i++)
			{
				if(Flag[i])
				{
					fPosX[i] += Vx[i];
					fPosY[i] += Vy[i];
				}
			}
			
			if(trigger > 0)
			{
				trigger -= 1;
			}
			
			break;
		}
		
	}
	
	MoveAdjust(MINI_RANGE_X, MAX_RANGE_X, MINI_RANGE_Y, MAX_RANGE_Y); 
	
}

//================================================
//弾を撃つ1
//================================================
void CBullet::Shoot(float posx, float posy)
{
	
}

//================================================
//溜め撃ち(イスラ専用)
//================================================
void CBullet::ChargeShoot()
{

}

//================================================
//傘攻撃(ライ専用)
//================================================
void CBullet::UmbrellaAttack(float posx, float posy)
{
}

//================================================
//設置攻撃(アメウス専用)
//================================================
void CBullet::PutAttack()
{

}

//================================================
//弾の動きパターン1(直線状)
//================================================
void CBullet::MovePattern1(void)
{
	Attack = 10;
	
	for(int i = 0;i < BULLET_MAX;i++)
	{
		Vx[i] = 0;
		Vy[i] = 4;
	}
}

//================================================
//弾の動きパターン2(敵に向かう)
//================================================
void CBullet::MovePattern2(void)
{
	Attack = 3;
	
	for(int i = 0;i < BULLET_MAX;i++)
	{
		Vx[i] = LunaMath::Cos(fAngle[i])*F(2);
		Vy[i] = LunaMath::Sin(fAngle[i])*F(2);
	}
}

//================================================
//弾の動きパターン3(破裂弾)
//================================================
void CBullet::MovePattern3(void)
{
	Attack = 15;
	
	fAngle[0] = GET_ANGLE(10);
	
	for(int i = 0;i < BULLET_MAX;i++)
	{
		Vx[i] = LunaMath::Cos(fAngle[0])*2.0f;
		Vy[i] = LunaMath::Sin(fAngle[0])*2.0f;
		fAngle[0] += GET_ANGLE(30);
	}
}

//================================================
//移動パターン4
//================================================
void CBullet::MovePattern4(float posx, float posy)
{
	const int RANGE = 150;
	
	Attack = 9;
	
	for(int i = 0;i < BULLET_MAX;i++)
	{
		Vx[i] = LunaMath::Cos(fAngle[i])*5;
		Vy[i] = LunaMath::Sin(fAngle[i])*5;
		
		if(fPosX[i] < posx - RANGE)
		{
			if(Flag[i])
			{
				Flag[i] = FALSE;
			}
		}
		
		if(fPosX[i] > posx + RANGE)
		{
			if(Flag[i])
			{
				Flag[i] = FALSE;
			}
		}
		
		if(fPosY[i] < posy - RANGE)
		{
			if(Flag[i])
			{
				Flag[i] = FALSE;
			}
		}
	}
}	

//================================================
//移動パターン5
//================================================
void CBullet::MovePattern5(float posx, float posy)
{
	const int RANGE = 100;
	
	Attack = 7;
	
	fAngle[0] = GET_ANGLE(90);
		
	for(int i = 0;i < BULLET_MAX;i++)
	{
		Vx[i] = LunaMath::Cos(fAngle[0])*2;
		Vy[i] = LunaMath::Sin(fAngle[0])*2;
		
		fAngle[0] += GET_ANGLE(30);
		
		if(fPosX[i] < posx - RANGE)
		{
			Flag[i] = FALSE;
		}
		
		if(fPosX[i] > posx + RANGE)
		{
			Flag[i] = FALSE;
		}
		
		if(fPosY[i] < posy - RANGE)
		{
			Flag[i] = FALSE;
		}
		
		if(fPosY[i] > posy + RANGE)
		{
			Flag[i] = FALSE;
		}
		
	}	

}

//================================================
//移動パターン6
//================================================
void CBullet::MovePattern6()
{
	Attack = 11;
	
	fAngle[0] = GET_ANGLE(90);
	
	for(int i = 0;i < BULLET_MAX;i++)
	{
		Vx[i] = LunaMath::Cos(fAngle[0]) * 2;
		Vy[i] = LunaMath::Sin(fAngle[0]) * 2;
		
		fAngle[0] += GET_ANGLE(20);
	}
}

//================================================
//移動補正(弾を消す用)
//================================================
void CBullet::MoveAdjust(int left, int right, int top, int bottom)
{
	for(int i = 0;i < BULLET_MAX;i++)
	{
		if(fPosX[i] < left)
		{
			Flag[i] = FALSE;
		}
		
		if(fPosX[i] > right-Width)
		{
			Flag[i] = FALSE;
		}
		
		if(fPosY[i] < top - 20)
		{
			Flag[i] = FALSE;
		}
		
		if(fPosY[i] > bottom + 20)
		{
			Flag[i] = FALSE;
		}
	}
}


//================================================
//描画
//================================================
void CBullet::Draw(void)
{
	for(int i = 0;i < BULLET_MAX;i++)
	{
		/*バッファリセット*/
		LunaSprite::ResetBuffer(Spr);
		
		if(Flag[i])
		{
			if(Luna::GetSyncCounter() % 5 == 0)
			{
				animcounter++;
			}
			
			/*描画先*/
			Dst.Set(fPosX[i], fPosY[i], F(Width), F(Height) );
						
			/*描画元*/
			Src.Set(F(animcounter%Divnum)*Width, F(0), F(Width), F(Height) );
		
			/*描画*/
			LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
		}
		
		/*バッファ更新*/
		LunaSprite::UpdateBuffer(Spr);
		
		Rendering();
		
	}
	
		
}

//================================================
//レンダリング
//================================================
void CBullet::Rendering()
{
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		Luna3D::SetFilterEnable(TRUE);
		
		/*レンダリング*/
		LunaSprite::Rendering(Spr);
		
		Luna3D::EndScene();
	}
}

//================================================
//メモリ開放
//================================================
void CBullet::Release(void)
{
	LunaTexture::Release(Tex);
	
	LunaSprite::Release(Spr);
}

//================================================
//デバッグ用関数
//================================================
void CBullet::Debug(void)
{
	LunaDebug::DrawString("DisX:%f", DisX);
	LunaDebug::DrawString("DisY:%f", DisY);
	LunaDebug::DrawString("Count:%d", count_charge);
	LunaDebug::DrawString("Charge:%d", ChargeFlag);
	//LunaDebug::DrawString("counter:%d", counter);
}

