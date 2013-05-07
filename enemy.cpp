//================================================
//include
//================================================
#include "enemy.h"
#include "gamemode.h"

//================================================
//�R���X�g���N�^
//================================================
CEnemy::CEnemy()
{
	COMP = 5;
}

//================================================
//�f�X�g���N�^
//================================================
CEnemy::~CEnemy()
{

}

//================================================
//������
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
//�e�N�X�`���ǂݍ���
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
//�G�t�F�N�g�摜���[�h
//================================================
void CEnemy::LoadEffect()
{

}

//================================================
//�X�v���C�g����
//================================================
void CEnemy::CreateSprite(void)
{
	/*��̃X�v���C�g����*/
	for(int i = 0;i < TYPE_MAX;i++)
	{
		Spr[i] = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
			
		/*�X�v���C�g�Ƀe�N�X�`����ڑ�*/
		LunaSprite::AttatchTexture(Spr[i], 0, Tex[i]);
	}
	
}

//================================================
//�p�����[�^�[�ǂݍ���
//================================================
void CEnemy::LoadParam()
{
	FILE *fp;
	
	fp = fopen("enemy.dat", "rb");
	
	if(fp == NULL)
	{
		Luna::MsgBox(0, "ERROR", "enemy.dat��������܂���");
		Luna::Exit();
	}
	
	for(int i = 0;i < TYPE_MAX;i++)
	{
		fread(&edata[i], sizeof(DATA), 1, fp);
	}
	
	fclose(fp);
}

//================================================
//�o���|�C���g�ǂݍ���
//================================================
void CEnemy::LoadPoint()
{
	FILE *fp;
	
	fp = fopen("epoint.dat", "rb");
	
	if(fp == NULL)
	{
		Luna::MsgBox(0, "ERROR", "epoint.dat��������܂���");
		Luna::Exit();
	}
	
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		fread(&epoint[i], sizeof(EPOINT), 1, fp);
	}
	
	fclose(fp);
	
}

//================================================
//�T�E���h�ǂݍ���
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
//�摜���Z�b�g
//================================================
void CEnemy::SetGraphInfo()
{
	Width = edata[Type].Width;
	Height = edata[Type].Height;
	DivNum = edata[Type].Divnum;
}

//================================================
//HP�Z�b�g
//================================================
void CEnemy::SetHp(void)
{
}

//================================================
//���W�Z�b�g
//================================================
void CEnemy::SetPosition(float posx, float posy)
{
	fPosX = posx;
	fPosY = posy;
}

//================================================
//�����蔻��̈�ݒ�
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
//�G�^�C�v�Z�b�g
//================================================
void CEnemy::SetType(eEnemyType type)
{
	Type = type;
}

//================================================
//�X�e�[�^�X�Z�b�g
//================================================
void CEnemy::SetStatus(void)
{
	Attack = edata[Type].Attack;
	Hp = edata[Type].Hp;
	Defence = edata[Type].Defence;
	Score = edata[Type].Score;
}

//================================================
//�_���[�W�v�Z
//================================================
void CEnemy::CalcDamage(int attack, int defence)
{
	Hp -= attack;
	
	IsDamage = TRUE;
}

//================================================
//���S����
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
//�A�j���[�V��������
//================================================
void CEnemy::CreateAnimation(void)
{

}

//================================================
//�p�^�[���f�[�^�ǂݍ���
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
//�ړ�
//================================================
void CEnemy::Move()
{
	fPosX += fVx;
	fPosY += fVy;
}

//================================================
//�ړ��p�^�[��
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
//�V���b�g�p�^�[��
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
//�ړ��p�^�[��1(�����I�ɐi��)
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
//�G�̈ړ��p�^�[��2(�v���C���[�ɂ��Ă���(�z�̓���) )
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
//�G�̈ړ��p�^�[��3(�L�[�f�[�^�ɏ]����(�啂̓���) )
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
//�G�̈ړ��p�^�[��4(�J���X�̓���)
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
//�G�̈ړ��p�^�[��5(�w偂̓���)
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
//�ړ��͈͕␳
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
//X���W�𓾂�
//================================================
float CEnemy::Get_PosX(void)
{
	return fPosX;
}

//================================================
//Y���W�𓾂�
//================================================
float CEnemy::Get_PosY(void)
{
	return fPosY;
}

//================================================
//�f�o�b�O�p
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
//�X�v���C�g�`��
//================================================
void CEnemy::Draw(eEnemyType type)
{

	Type = type;
	
	if(!IsExist)
	{
		SetGraphInfo();
		SetStatus();
	}
	
	/*�X�v���C�g�o�b�t�@�N���A*/
	LunaSprite::ResetBuffer(Spr[type]);

	/*�`���*/
	Dst.Set(fPosX, fPosY, F(Width), F(Height) );
	//Dst.Set(100, 100, F(Width), F(Height) );
		
	/*�`�挳*/
	Src.Set( F( (animcounter%DivNum)*Width ), F(0), F(Width), F(Height) );
		
	/*�`��L���[�ɒǉ�*/
	if(type == ENEMY_NUNO)
	{
		LunaSprite::DrawSquareRotate(Spr[type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE, Angle);
	}
	
	else
	{
		LunaSprite::DrawSquare(Spr[type], &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	}
		
	/*�X�v���C�g�o�b�t�@�X�V*/
	LunaSprite::UpdateBuffer(Spr[type]);
	
	bullet.Draw();
	
	burst.Draw(fPosX, fPosY);
	
}

//================================================
//�����_�����O
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
//�������J��
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
