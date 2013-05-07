//================================================
//include
//================================================
#include "boss.h"
#include "gamemode.h"

const int MAX_LIFE = 2000;

//================================================
//コンストラクタ
//================================================
CBoss::CBoss()
{
	IsExist = FALSE;
	
	COMP = 5;
	
	Hp = MAX_LIFE;
	
	Attack = 20;
	Defence = 12;
	
}

//================================================
//デストラクタ
//================================================
CBoss::~CBoss()
{

}

//================================================
//初期化
//================================================
void CBoss::Initialize(void)
{
	IsExist = FALSE;
	IsDamage = FALSE;
	IsDead = FALSE;
	counter = 0;
	Hp = MAX_LIFE;
	
	bullet.Initialize();
	bullet.SetGraphInfo(12, 12, 1);
	
	for(int i = 0;i < SKULL_NUM;i++)
	{
		skull[i].Initialize();
		skull[i].Set(40, 40, 2);
		
		skull[i].bullet.SetGraphInfo(12, 12, 1);
	}
	
	for(int i = 0;i < KNIFE_NUM;i++)
	{
		knife[i].Initialize();
		knife[i].Set(32, 32, 4);
	}
	
	lgauge.Initialize();
	lgauge.SetPosition(0, 10);
	lgauge.SetGraphInfo(500, 10);
	
}

//================================================
//テクスチャ読み込み
//================================================
void CBoss::LoadImage(char *name, int ColorKey)
{
	Tex = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_3D, ColorKey);
	
	CreateSprite();
	
	bullet.LoadImage("shot\\yellow.png", COLORKEY_WHITE);
	
	for(int i = 0;i < SKULL_NUM;i++)
	{
		skull[i].LoadImage("boss\\jack_skull.png", COLORKEY_WHITE);
		skull[i].bullet.LoadImageA("shot\\red.png", COLORKEY_WHITE);
	}
	
	for(int i = 0;i < KNIFE_NUM;i++)
	{
		knife[i].LoadImage("boss\\jack_knife.png", COLORKEY_WHITE);
	}
	
	lgauge.LoadImageA("system\\bosslife.png", COLORKEY_DISABLE);
	
}

//================================================
//スプライト生成
//================================================
void CBoss::CreateSprite(void)
{
	/*空のスプライト生成*/
	Spr = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
		
	/*スプライトにテクスチャを接続*/
	LunaSprite::AttatchTexture(Spr, 0, Tex);
}

//================================================
//サウンド読み込み
//================================================
void CBoss::LoadSound()
{
	char *sename[] =
	{
		"sound\\bossshot.wav",
		"sound\\move.wav",
	};
	
	for(int i = 0;i < SE_MAX;i++)
	{
		Se[i].LoadSound(sename[i]);
	}
}

//================================================
//キーデータ生成
//================================================
void CBoss::CreateKeyData(void)
{
	lAnimX = LunaAnimation::Create(5);
	LunaAnimation::SetKey(lAnimX, 0, 0.0f, F(200) );
	LunaAnimation::SetKey(lAnimX, 1, 1.0f, F(100) );
	LunaAnimation::SetKey(lAnimX, 2, 2.0f, F(0)   );
	LunaAnimation::SetKey(lAnimX, 3, 3.0f, F(100) );
	LunaAnimation::SetKey(lAnimX, 4, 4.0f, F(200) );
	LunaAnimation::Optimize(lAnimX);
	
	lAnimY = LunaAnimation::Create(5);
	LunaAnimation::SetKey(lAnimY, 0, 0.0f, F(0)   );
	LunaAnimation::SetKey(lAnimY, 1, 1.0f, F(100) );
	LunaAnimation::SetKey(lAnimY, 2, 2.0f, F(100) );
	LunaAnimation::SetKey(lAnimY, 3, 3.0f, F(100) );
	LunaAnimation::SetKey(lAnimY, 4, 4.0f, F(0)  );
	LunaAnimation::Optimize(lAnimY);
	
}

//================================================
//座標等セット
//================================================
void CBoss::Set(int width, int height, int divnum)
{
	Width = width;
	Height = height;
	DivNum = divnum;
}

//================================================
//当たり判定領域設定
//================================================
void CBoss::SetRect(void)
{
	HitRect.Sx = fPosX + COMP;
	HitRect.Sy = fPosY + COMP;
	HitRect.Ex = fPosX + Width - COMP;
	HitRect.Ey = fPosY + Height - COMP;
	
	bullet.SetRect();
	
	for(int i = 0;i < SKULL_NUM;i++)
	{
		skull[i].SetRect();
	}
	
	for(int i = 0;i < KNIFE_NUM;i++)
	{
		knife[i].SetRect();
	}
	
}

//================================================
//位置セット
//================================================
void CBoss::SetPosition(float posx, float posy)
{
	fPosX = posx;
	fPosY = posy;
}

//================================================
//X座標を得る
//================================================
float CBoss::Get_PosX(void)
{
	return fPosX;
}

//================================================
//Y座標を得る
//================================================
float CBoss::Get_PosY(void)
{
	return fPosY;
}

//================================================
//HPを得る
//================================================
int CBoss::Get_Life(void)
{
	return Hp;
}	

//================================================
//デバッグ用
//================================================
void CBoss::Debug(void)
{
	//LunaDebug::DrawString("Px:%d", fPosX);
	//LunaDebug::DrawString("Py:%d", fPosY);
	//LunaDebug::DrawString("Width:%d", Width);
	LunaDebug::DrawString("Hp:%d", Hp);
	
	LunaDebug::DrawString("rand:%d", rand);
	
	//LunaDebug::DrawString("Height:%d", Height);
}

//================================================
//スプライト描画
//================================================
void CBoss::Draw(void)
{
	/*スプライトバッファクリア*/
	LunaSprite::ResetBuffer(Spr);

	/*描画先*/
	Dst.Set(fPosX, fPosY, F(Width), F(Height));
		
	/*描画元*/
	Src.Set( F( (animcounter%DivNum)*Width ), F(0), F(Width), F(Height) );
		
	/*描画キューに追加*/
	LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
		
	/*スプライトバッファ更新*/
	LunaSprite::UpdateBuffer(Spr);
	
	bullet.Draw();
	
	for(int i = 0;i < SKULL_NUM;i++)
	{
		//skbullet[i].Draw();
		skull[i].Draw();
	}
	
	for(int i = 0;i < KNIFE_NUM;i++)
	{
		knife[i].Draw();
	}
}

//================================================
//レンダリング
//================================================
void CBoss::Rendering()
{
	if(IsExist)
	{
		if(!IsDamage)
		{
			/*スプライトレンダリング*/
			LunaSprite::Rendering(Spr);
		}
		
		if(IsDamage)
		{
			dcounter++;
			
			if(dcounter > 3)
			{
				IsDamage = FALSE;
				dcounter = 0;
			}
			
			if(dcounter % 3 == 0)
			{
				Luna3D::SetBlendingType(BLEND_ADD);
				LunaSprite::Rendering(Spr);
				Luna3D::SetBlendingType(BLEND_NORMAL);
			}
		}
		
		bullet.Rendering();
		
		for(int i = 0;i < SKULL_NUM;i++)
		{
			skull[i].Rendering();
			//skbullet[i].Rendering();
		}
		
		for(int i = 0;i < KNIFE_NUM;i++)
		{
			knife[i].Rendering();
		}
		
		lgauge.Draw(0, 0, Hp/4);		
		
		lgauge.Rendering();
	}
}

//================================================
//移動
//================================================
void CBoss::Move(int *mode, float tax, float tay)
{
	fPosX += fVx;
	fPosY += fVy;
	
	counter++;
	
	if(counter < 200)
	{
		fVy = 1;
	}
	
	if(counter == 200)
	{
		rand = LunaRand::GetInt(0, 2);
		
		fVy = 0;	
		*mode = SCENE_CONV;
	}
	
	if(counter > 200 && counter < 400)
	{
		switch(rand)
		{
			case 0:
			{
				for(int i = 0;i < KNIFE_NUM;i++)
				{
					knife[i].IsExist = TRUE;
				}
				
				MovePattern4();
				
				MoveAdjust(MINI_RANGE_X, MAX_RANGE_X, MINI_RANGE_Y, MAX_RANGE_Y);
				
				break;
			}
			
			case 1:
			{
				for(int i = 0;i < SKULL_NUM;i++)
				{
					skull[i].IsExist = TRUE;
				}
				
				MovePattern2();
				
				MoveAdjust(MINI_RANGE_X, MAX_RANGE_X, MINI_RANGE_Y, MAX_RANGE_Y);
					
				break;
			}
			
			default:
			{
				MovePattern1();	
				
				Se[SE_MOVE].PlaySoundA();
				
				MoveAdjust(MINI_RANGE_X, MAX_RANGE_X, MINI_RANGE_Y, MAX_RANGE_Y);
				
				break;
			}
			
		}
		
	}
	
	if(counter > 400)
	{
		rand = LunaRand::GetInt(0, 3);
		
		counter = 201;
	}
	
	for(int i = 0;i < SKULL_NUM;i++)
	{
		if(!skull[i].IsExist)
		{
			skull[i].SetPosition(i*70+20, -100);	
		}
		
		skull[i].Move();
		skull[i].MovePattern4();
	}
	
	for(int i = 0;i < KNIFE_NUM;i++)
	{
		if(!knife[i].IsExist)
		{
			knife[i].SetPosition(i*100+20, 0);
		}
		
		knife[i].Move();
		knife[i].MovePattern3(tax, tay);
	}
	
}

//================================================
//ナイフ召喚
//================================================
void CBoss::SummonKnife()
{
	if(counter > 200 && counter < 400)
	{
		switch(rand)
		{
			case 0:
			{
				for(int i = 0;i < KNIFE_NUM;i++)
				{
					knife[i].IsExist = TRUE;
				}
				
				break;
			}
		}
	}
}

//================================================
//骸骨召喚
//================================================
void CBoss::SummonSkull()
{
	if(counter > 200 && counter < 400)
	{
		switch(rand)
		{
			case 1:
			{
				for(int i = 0;i < SKULL_NUM;i++)
				{
					skull[i].IsExist = TRUE;
				}
				
				break;
				
			}
		}
	}
}

//================================================
//ショット処理
//================================================
void CBoss::Shoot(float tax, float tay)
{
	if(counter > 200)
	{
		bullet.Move(ENEMY);
		
		switch(rand)
		{
			case 0:
			{
				bullet.CreateBullet(fPosX+(Width/3), fPosY+Height, tax, tay);
				
				bullet.MovePattern2();
				
				break;
			}
			
			case 1:
			{
				break;
			}
				
			default:
			{
				if(counter > 200 && counter < 250)
				{
					bullet.CreateBossBullet(fPosX+(Width/3), fPosY+Height, tax, tay);
				}
				
				Se[SE_SHOT].PlaySoundA();
			
				if(counter > 250 && counter < 400)
				{
					bullet.MovePattern1();
				}
				
				break;
			}
		}
		
	}
}

//================================================
//移動補正
//================================================
void CBoss::MoveAdjust(int left, int right, int top, int bottom)
{
	if(IsExist)
	{
		if(fPosX <= left-20)
		{
			fPosX = F(left-20);
		}
		
		if(fPosX >= right-Width)
		{
			fPosX = F(right-Width);
		}
		
		if(fPosY <= top)
		{
		
		}
		
		if(fPosY >= bottom - Height)
		{
			fPosY = F(bottom - Height);
		}
	}
	
}

//================================================
//移動パターン1(円状に回る)
//================================================
void CBoss::MovePattern1(void)
{
	fAngle += GET_ANGLE(10);
	
	fVx = LunaMath::Cos(fAngle)*F(30);
	fVy = LunaMath::Sin(fAngle)*F(5);
}

//================================================
//移動パターン2(ナイフを出す)
//================================================
void CBoss::MovePattern2(void)
{
	fVx = 0;
	fVy = 0;
}

//================================================
//移動パターン3(ドクロを出す)
//================================================
void CBoss::MovePattern3(void)
{
	fVy = 0;
	fVx = 0;
	
	fPosY = 100;
}

//================================================
//移動パターン4
//================================================
void CBoss::MovePattern4(void)
{
	CreateKeyData();
	
	fTime += 1.0f/ F(FRAME_RATE);
	
	fPosX = LunaAnimation::GetParameter(lAnimX, fTime, ANIM_TYPE_NEWTON, 0);
	fPosY = LunaAnimation::GetParameter(lAnimY, fTime, ANIM_TYPE_NEWTON, 0);
	
}

//================================================
//移動パターン5(振り子)
//================================================
void CBoss::MovePattern5()
{
	lAnimY = LunaAnimation::Create(5);
	LunaAnimation::SetKey(lAnimY, 0, 0.0f, F(1)   );
	LunaAnimation::SetKey(lAnimY, 1, 1.0f, F(1) );
	LunaAnimation::SetKey(lAnimY, 2, 2.0f, F(-1) );
	LunaAnimation::SetKey(lAnimY, 3, 3.0f, F(-1) );
	LunaAnimation::SetKey(lAnimY, 4, 4.0f, F(-1)  );
	LunaAnimation::Optimize(lAnimY);
	
	fTime += 1.0f / F(FRAME_RATE);
	
	fAngle += GET_ANGLE(5);
	
	fVx = LunaMath::Cos(fAngle)*F(10);
	fVy = LunaAnimation::GetParameter(lAnimY, fTime, ANIM_TYPE_STEP, 0);
	
}

//================================================
//ダメージ計算
//================================================
void CBoss::CalcDamage(int attack, int defence)
{
	Hp -= attack;
	
	IsDamage = TRUE;
	
	Score = 500;
	
	if(Hp <= 0)
	{
		IsDead = TRUE;
	}
}

//================================================
//死亡処理
//================================================
void CBoss::Dead(int *mode)
{
	if(IsDead)
	{
		for(int i = 0;i < BULLET_MAX;i++)
		{
			bullet.Flag[i] = FALSE;
		}
		
		fPosX = 200;
		fPosY = 150;
		
		for(int i = 0;i < SKULL_NUM;i++)
		{
			skull[i].IsExist = FALSE;
			
			for(int j = 0;j < BULLET_MAX;j++)
			{
				skull[i].bullet.Flag[j] = FALSE; 
			}
		}
		
		for(int i = 0;i < KNIFE_NUM;i++)
		{
			knife[i].IsExist = FALSE;
			
			for(int j = 0;j < BULLET_MAX;j++)
			{
				knife[i].bullet.Flag[j] = FALSE;
			}
		}
		
		*mode = SCENE_CONV;
		
	}
}

//================================================
//メモリ開放
//================================================
void CBoss::Release(void)
{
	LunaTexture::Release(Tex);
	LunaSprite::Release(Spr);
	
	LunaAnimation::Release(lAnimX);
	LunaAnimation::Release(lAnimY);
	
	bullet.Release();
	
	for(int i = 0;i < SKULL_NUM;i++)
	{
		skull[i].Release();
	}
	
	for(int i = 0;i < KNIFE_NUM;i++)
	{
		knife[i].Release();
	}
	
	lgauge.Release();
}
