//================================================
//include
//================================================
#include "bullet.h"
#include "gamemode.h"

//================================================
//�R���X�g���N�^
//================================================
CBullet::CBullet()
{
	COMP = 2;
	CHARGE_MAX = 100;
}

//================================================
//�f�X�g���N�^
//================================================
CBullet::~CBullet()
{

}

//================================================
//������
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
//�����ǂݍ���
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
//�e�N�X�`�����[�h
//================================================
void CBullet::LoadImage(char *name, int ColorKey)
{
	Tex = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_3D, ColorKey);
	
	CreateSprite();
}

//================================================
//�X�v���C�g����
//================================================
void CBullet::CreateSprite()
{
	/*��̃X�v���C�g����*/
	Spr = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
	
	/*�ڑ�*/
	LunaSprite::AttatchTexture(Spr, 0, Tex);
}

//================================================
//�����蔻��̈�ݒ�
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
//�e�ʒu�Z�b�g
//================================================
void CBullet::SetPosition(int no)
{
	fPosX[no] = -200;
	fPosY[no] = 600;
}

//================================================
//�摜���Z�b�g
//================================================
void CBullet::SetGraphInfo(int width, int height, int divnum)
{
	Width = width;
	Height = height;
	Divnum = divnum;
}

//================================================
//�e�̐���
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
//�e�̐���(�p�x�t��)
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
//��Ēe�̐���
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
//�e�̐���(n-way�e�p)
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
//�e�̐���(�{�X�p)
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
//���˒e�̐���
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
//�e�̓���
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
//�e������1
//================================================
void CBullet::Shoot(float posx, float posy)
{
	
}

//================================================
//���ߌ���(�C�X����p)
//================================================
void CBullet::ChargeShoot()
{

}

//================================================
//�P�U��(���C��p)
//================================================
void CBullet::UmbrellaAttack(float posx, float posy)
{
}

//================================================
//�ݒu�U��(�A���E�X��p)
//================================================
void CBullet::PutAttack()
{

}

//================================================
//�e�̓����p�^�[��1(������)
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
//�e�̓����p�^�[��2(�G�Ɍ�����)
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
//�e�̓����p�^�[��3(�j���e)
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
//�ړ��p�^�[��4
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
//�ړ��p�^�[��5
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
//�ړ��p�^�[��6
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
//�ړ��␳(�e�������p)
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
//�`��
//================================================
void CBullet::Draw(void)
{
	for(int i = 0;i < BULLET_MAX;i++)
	{
		/*�o�b�t�@���Z�b�g*/
		LunaSprite::ResetBuffer(Spr);
		
		if(Flag[i])
		{
			if(Luna::GetSyncCounter() % 5 == 0)
			{
				animcounter++;
			}
			
			/*�`���*/
			Dst.Set(fPosX[i], fPosY[i], F(Width), F(Height) );
						
			/*�`�挳*/
			Src.Set(F(animcounter%Divnum)*Width, F(0), F(Width), F(Height) );
		
			/*�`��*/
			LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
		}
		
		/*�o�b�t�@�X�V*/
		LunaSprite::UpdateBuffer(Spr);
		
		Rendering();
		
	}
	
		
}

//================================================
//�����_�����O
//================================================
void CBullet::Rendering()
{
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		Luna3D::SetFilterEnable(TRUE);
		
		/*�����_�����O*/
		LunaSprite::Rendering(Spr);
		
		Luna3D::EndScene();
	}
}

//================================================
//�������J��
//================================================
void CBullet::Release(void)
{
	LunaTexture::Release(Tex);
	
	LunaSprite::Release(Spr);
}

//================================================
//�f�o�b�O�p�֐�
//================================================
void CBullet::Debug(void)
{
	LunaDebug::DrawString("DisX:%f", DisX);
	LunaDebug::DrawString("DisY:%f", DisY);
	LunaDebug::DrawString("Count:%d", count_charge);
	LunaDebug::DrawString("Charge:%d", ChargeFlag);
	//LunaDebug::DrawString("counter:%d", counter);
}

