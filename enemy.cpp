//================================================
//include
//================================================
#include "enemy.h"
#include "gamemode.h"

//================================================
//コンストラクタ
//================================================
CEnemy::CEnemy()
{
	COMP = 5;
}

//================================================
//デストラクタ
//================================================
CEnemy::~CEnemy()
{

}

//================================================
//初期化
//================================================
void CEnemy::Initialize(void)
{
	IsExist = FALSE;
	IsDamage = FALSE;
	
	counter = 0;
	fTime = 0.0f;
	
	bullet.Initialize();
	bullet.SetGraphInfo(12, 12, 1);
	
	burst.Initialize();
	
	burst.Set(56, 56, 8); 
	
}

//================================================
//テクスチャ読み込み
//================================================
void CEnemy::LoadImage(void)
{
	char *ename[]  =
	{
		"enemy\\nuno.png",
		"enemy\\bat.png",
		"enemy\\crow.png",
		"enemy\\mummy.png",
		"enemy\\spider.png",
	};
		
	
	for(int i = 0;i < TYPE_MAX;i++)
	{
		Tex[i] = LunaTexture::CreateFromFile(ename[i], FORMAT_TEXTURE_3D, COLORKEY_WHITE);
	}
	
	CreateSprite();
	
	burst.LoadImageA("effect\\burst_small.bmp", COLORKEY_BLACK);
	
	bullet.LoadImageA("shot\\red.png", COLORKEY_WHITE);
	
}

//================================================
//エフェクト画像ロード
//================================================
void CEnemy::LoadEffect()
{

}

//================================================
//スプライト生成
//================================================
void CEnemy::CreateSprite(void)
{
	/*空のスプライト生成*/
	for(int i = 0;i < TYPE_MAX;i++)
	{
		Spr[i] = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
			
		/*スプライトにテクスチャを接続*/
		LunaSprite::AttatchTexture(Spr[i], 0, Tex[i]);
	}
	
}

//================================================
//パラメーター読み込み
//================================================
void CEnemy::LoadParam()
{
	FILE *fp;
	
	fp = fopen("enemy.dat", "rb");
	
	if(fp == NULL)
	{
		Luna::MsgBox(0, "ERROR", "enemy.datが見つかりません");
		Luna::Exit();
	}
	
	for(int i = 0;i < TYPE_MAX;i++)
	{
		fread(&edata[i], sizeof(DATA), 1, fp);
	}
	
	fclose(fp);
}

//================================================
//出現ポイント読み込み
//================================================
void CEnemy::LoadPoint()
{
	FILE *fp;
	
	fp = fopen("epoint.dat", "rb");
	
	if(fp == NULL)
	{
		Luna::MsgBox(0, "ERROR", "epoint.datが見つかりません");
		Luna::Exit();
	}
	
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		fread(&epoint[i], sizeof(EPOINT), 1, fp);
	}
	
	fclose(fp);
	
}

//================================================
//サウンド読み込み
//================================================
void CEnemy::LoadSound()
{
	char *sename[] =
	{
		"sound\\enemyshoot.wav",
		"sound\\crow.wav",
		"sound\\bat.wav",
	};
	
	for(int i = 0;i < SE_MAX;i++)
	{
		Se[i].LoadSound(sename[i]);
	}
}

//================================================
//画像情報セット
//================================================
void CEnemy::SetGraphInfo()
{
	Width = edata[Type].Width;
	Height = edata[Type].Height;
	DivNum = edata[Type].Divnum;
}

//================================================
//HPセット
//================================================
void CEnemy::SetHp(void)
{
}

//================================================
//座標セット
//================================================
void CEnemy::SetPosition(float posx, float posy)
{
	fPosX = posx;
	fPosY = posy;
}

//================================================
//当たり判定領域設定
//================================================
void CEnemy::SetRect(void)
{
	HitRect.Sx = fPosX + COMP;
	HitRect.Sy = fPosY + COMP;
	HitRect.Ex = fPosX + Width - COMP;
	HitRect.Ey = fPosY + Height - COMP;
	
	bullet.SetRect();
}

//================================================
//敵タイプセット
//================================================
void CEnemy::SetType(eEnemyType type)
{
	Type = type;
}

//================================================
//ステータスセット
//================================================
void CEnemy::SetStatus(void)
{
	Attack = edata[Type].Attack;
	Hp = edata[Type].Hp;
	Defence = edata[Type].Defence;
	Score = edata[Type].Score;
}

//================================================
//ダメージ計算
//================================================
void CEnemy::CalcDamage(int attack, int defence)
{
	Hp -= attack;
	
	IsDamage = TRUE;
}

//================================================
//死亡処理
//================================================
void CEnemy::Dead(void)
{
	if(Hp <= 0)
	{
		IsExist = FALSE;
		burst.IsExist = TRUE;
	}
	
	if(burst.IsExist)
	{
		if(Luna::GetSyncCounter() % 5 == 0)
		{
			burst.animcounter++;
		}
		
		if(++burst.counter > 200)
		{
			burst.IsExist = FALSE;
			burst.counter = 0;
			burst.animcounter = 0;
		}
		
	}
	
}

//================================================
//アニメーション生成
//================================================
void CEnemy::CreateAnimation(void)
{

}

//================================================
//パターンデータ読み込み
//================================================
void CEnemy::LoadPattern(char *datname)
{
//	FILE *fp;
//	
//	fp = fopen(datname, "r");
//	
//	if(fp == NULL)
//	{
//		Luna::Exit();
//	}
//	
//	fclose(fp);

}

//================================================
//移動
//================================================
void CEnemy::Move()
{
	fPosX += fVx;
	fPosY += fVy;
}

//================================================
//移動パターン
//================================================
void CEnemy::MovePattern(float tax, float tay)
{
	if(!IsExist)
	{
		rand = LunaRand::GetFloat(-200.0, 200.0);
		rand2 = LunaRand::GetInt(0, 1);
	}
	
	if(IsExist)
	{
		switch(Type)
		{
			case ENEMY_NUNO:
			{
				Move();
				MovePattern2(tax, tay);
				//MovePattern6();
				break;
			}
			
			case ENEMY_BAT:
			{
				//Move();
				MovePattern3(tax, tay);
				
				Se[SE_BAT].PlaySoundA();
				break;
			}
			
			case ENEMY_CROW:
			{
				Move();
				MovePattern4(tax, tay);
				
				Se[SE_CROW].PlaySoundA();
				
				break;
			}
			
			case ENEMY_MUMMY:
			{
				Move();
				MovePattern1();
				break;
			}
			
			case ENEMY_SPIDER:
			{
				Move();
				MovePattern5();
				break;
			}
		}
	}
	
}

//================================================
//ショットパターン
//================================================
void CEnemy::ShootPattern(float tax, float tay)
{
	bullet.Move(ENEMY);
	
	if(IsExist)
	{
		switch(Type)
		{
			case ENEMY_NUNO:
			{
				bullet.CreateBullet(fPosX + Width/3, fPosY+Height, tax, tay);
				
				Se[SE_SHOT].PlaySoundA();
				
				bullet.MovePattern1();
				
				bullet.MovePattern6();
				
				break;
			}
			
			case ENEMY_BAT:
			{
				break;
			}
			
			case ENEMY_CROW:
			{
				break;
			}
			
			case ENEMY_MUMMY:
			{
				bullet.CreateBullet(fPosX + Width / 3, fPosY + Height, tax, tay);
				
				Se[SE_SHOT].PlaySoundA();
				
				bullet.MovePattern6();
				
				break;
			}
			
			case ENEMY_SPIDER:
			{
				if(counter > 100 && counter < 200)
				{
					bullet.CreateBullet(fPosX + Width / 3, fPosY + Height, tax, tay);
					
					Se[SE_SHOT].PlaySoundA();
					
					bullet.MovePattern2();
				}
				
				break;
			}
		}
	}
}

//================================================
//移動パターン1(直線的に進む)
//================================================
void CEnemy::MovePattern1(void)
{
	fVy = 1;

	if(fPosY > SCREEN_HEIGHT)
	{
		IsExist = FALSE;
	}
}

//================================================
//敵の移動パターン2(プレイヤーについてくる(布の動き) )
//================================================
void CEnemy::MovePattern2(float tax, float tay)
{
	Angle = LunaMath::Atan(tax - fPosX, tay - fPosY);
	 
	fVx = LunaMath::Cos(Angle);
	
	if(tay > fPosY)
	{ 
		fVy = LunaMath::Sin(Angle);
	}
	
	else
	{
		fVy = 1;
	}
	
}

//================================================
//敵の移動パターン3(キーデータに従って(蝙蝠の動き) )
//================================================
void CEnemy::MovePattern3(float tax, float tay)
{
	
	lAnimX = LunaAnimation::Create(5);
	
	switch(rand2)
	{
		case 0:
		{
			LunaAnimation::SetKey(lAnimX, 0, 0.0f, SCREEN_WIDTH/2 - 200.0f);
			LunaAnimation::SetKey(lAnimX, 1, 1.0f, SCREEN_WIDTH/2);
			LunaAnimation::SetKey(lAnimX, 2, 2.0f, SCREEN_WIDTH/2 + 200.0f);
			LunaAnimation::SetKey(lAnimX, 3, 3.0f, SCREEN_WIDTH/2);
			LunaAnimation::SetKey(lAnimX, 4, 4.0f, SCREEN_WIDTH/2 - 500.0f);
			
			break;
		}
		
		case 1:
		{
			LunaAnimation::SetKey(lAnimX, 0, 0.0f, SCREEN_WIDTH/2 + 200.0f);
			LunaAnimation::SetKey(lAnimX, 1, 1.0f, SCREEN_WIDTH/2);
			LunaAnimation::SetKey(lAnimX, 2, 2.0f, SCREEN_WIDTH/2 - 500.0f);
			LunaAnimation::SetKey(lAnimX, 3, 3.0f, SCREEN_WIDTH/2);
			LunaAnimation::SetKey(lAnimX, 4, 4.0f, SCREEN_WIDTH/2 + 500.0f);
			
			break;
			
		}
		
	}
	
	LunaAnimation::Optimize(lAnimX);
	
	lAnimY = LunaAnimation::Create(5);
	LunaAnimation::SetKey(lAnimY, 0, 0.0f, SCREEN_HEIGHT/2 - 300.0f);
	LunaAnimation::SetKey(lAnimY, 1, 1.0f, SCREEN_HEIGHT/2 - 100.0f);
	LunaAnimation::SetKey(lAnimY, 2, 2.0f, SCREEN_HEIGHT/2);
	LunaAnimation::SetKey(lAnimY, 3, 3.0f, SCREEN_HEIGHT/2 + 100.0f);
	LunaAnimation::SetKey(lAnimY, 4, 4.0f, SCREEN_HEIGHT/2 + rand);
	LunaAnimation::Optimize(lAnimY);
		
	fTime += 1.0f/ F(FRAME_RATE);
//	Angle = LunaMath::Atan(tax - fPosX, tay - fPosY); 
	
	fPosX = LunaAnimation::GetParameter(lAnimX, fTime, ANIM_TYPE_NEWTON, 0);//sin(PI*Angle/160.0f)*5.0f;
	fPosY = LunaAnimation::GetParameter(lAnimY, fTime, ANIM_TYPE_NEWTON, 0);
	
	if(fPosX < 0)
	{
		IsExist = FALSE;
	}
	
}

//================================================
//敵の移動パターン4(カラスの動き)
//================================================
void CEnemy::MovePattern4(float tax, float tay)
{
	counter++;
	
	if(counter > 0 && counter < 100)
	{
		fVx = 0;
		fVy = 1;
	}
	
	if(counter > 100 && counter < 200)
	{
		fVx = 0;
		fVy = 0;
		Angle = LunaMath::Atan(tax - fPosX, tay - fPosY);
	}
	
	if(counter > 200)
	{
		fVx = LunaMath::Cos(Angle) * F(5);
		fVy = LunaMath::Sin(Angle) * F(5);
	}
	
}

//================================================
//敵の移動パターン5(蜘蛛の動き)
//================================================
void CEnemy::MovePattern5(void)
{
	counter++;
	
	if(counter > 0 && counter < 100)
	{
		fVx = 0;
		fVy = 3;
	}
	
	if(counter > 100 && counter < 200)
	{
		fVx = 0;
		fVy = 0;
	}
	
	if(counter > 200 && counter < 300)
	{
		
		switch(rand2)
		{
			case 0:
			{
				fVx = 3;
				break;
			}
			
			case 1:
			{
				fVx = -3;
				break;
			}
		}
		
		fVy = 0;
	}
	
	if(counter > 300)
	{
		fVy = 3;
	}

}

//================================================
//移動範囲補正
//================================================
void CEnemy::MoveAdjust(int left, int right, int top, int bottom)
{
	if(fPosX < left)
	{
		fPosX = F(left);
	}
	
	if(fPosX > right - Width)
	{
		fPosX = F(right - Width);
	}
	
	if(fPosY < top)
	{
		//fPosY = -100;
	}
	
	if(fPosY > bottom)
	{
		IsExist = FALSE;
	}
}

//================================================
//X座標を得る
//================================================
float CEnemy::Get_PosX(void)
{
	return fPosX;
}

//================================================
//Y座標を得る
//================================================
float CEnemy::Get_PosY(void)
{
	return fPosY;
}

//================================================
//デバッグ用
//================================================
void CEnemy::Debug(void)
{
	//LunaDebug::DrawString("Px:%f", fPosX);
	//LunaDebug::DrawString("Py:%f", fPosY);
	
	//LunaDebug::DrawString("IsExist:%d", IsExist);
	
	LunaDebug::DrawString("Hp:%d", Hp);
	LunaDebug::DrawString("point:%d", epoint[0].point);
	LunaDebug::DrawString("type:%d", epoint[0].Type);
	
	burst.Debug();
}

//================================================
//スプライト描画
//================================================
void CEnemy::Draw(eEnemyType type)
{

	Type = type;
	
	if(!IsExist)
	{
		SetGraphInfo();
		SetStatus();
	}
	
	/*スプライトバッファクリア*/
	LunaSprite::ResetBuffer(Spr[type]);

	/*描画先*/
	Dst.Set(fPosX, fPosY, F(Width), F(Height) );
	//Dst.Set(100, 100, F(Width), F(Height) );
		
	/*描画元*/
	Src.Set( F( (animcounter%DivNum)*Width ), F(0), F(Width), F(Height) );
		
	/*描画キューに追加*/
	if(type == ENEMY_NUNO)
	{
		LunaSprite::DrawSquareRotate(Spr[type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE, Angle);
	}
	
	else
	{
		LunaSprite::DrawSquare(Spr[type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	}
		
	/*スプライトバッファ更新*/
	LunaSprite::UpdateBuffer(Spr[type]);
	
	bullet.Draw();
	
	burst.Draw(fPosX, fPosY);
	
}

//================================================
//レンダリング
//================================================
void CEnemy::Rendering()
{
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetFilterEnable(TRUE);
		
		if(IsExist)
		{
			if(!IsDamage)
			{
				LunaSprite::Rendering(Spr[Type]);
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
					LunaSprite::Rendering(Spr[Type]);
					Luna3D::SetBlendingType(BLEND_NORMAL);
				}
			}
		}
		
		bullet.Rendering();
		
		burst.Rendering();
		
		Luna3D::EndScene();
		
	}
}


//================================================
//メモリ開放
//================================================
void CEnemy::Release(void)
{
	for(int i = 0;i < TYPE_MAX;i++)
	{
		LunaTexture::Release(Tex[i]);
		LunaSprite::Release(Spr[i]);
	}
	
	bullet.Release();
	
	burst.Release();
}
