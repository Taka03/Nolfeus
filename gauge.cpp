//================================================
//include
//================================================
#include "gauge.h"
#include "gamemode.h"

//================================================
//�R���X�g���N�^
//================================================
CGauge::CGauge()
{
	fPosX = 450;
	fPosY = 200;
	
	pPos.Set(300, 200);
	
	GAUGE_MIN = 0;
	
	Width = 96;
	Height = 96;
	
	Angle = 100;
	
	radius = 100;
	
}

//================================================
//�R���X�g���N�^
//================================================
CGauge::CGauge(float posx, float posy)
{
	fPosX = posx;
	fPosY = posy;
	
	pPos.Set(300, 200);
	
	GAUGE_MIN = 0;
	
	Width = 96;
	Height = 96;
	
	Angle = 100;
	
	radius = 100;
	
}

//================================================
//�f�X�g���N�^
//================================================
CGauge::~CGauge()
{

}

//================================================
//������
//================================================
void CGauge::Initialize(void)
{
	ability = 0;
}

//================================================
//�ʒu�Z�b�g
//================================================
void CGauge::SetPosition(float posx, float posy)
{
	fPosX = F(posx);
	fPosY = F(posy);
}

//================================================
//�摜���Z�b�g
//================================================
void CGauge::SetGraphInfo(int width, int height)
{
	Width = width;
	Height = height;
}

//================================================
//�Q�[�W����
//================================================
void CGauge::AddGauge(bool *Flag)
{
	counter++;
	
	if(counter > 30)
	{
		if(!*Flag)
		{
			ability += 3;
		}
		
		if(*Flag)
		{
			ability -= 18;
		}
		
		counter = 0;
	}
	
	if(ability <= GAUGE_MIN)
	{
		ability = GAUGE_MIN;
	}
	
	if(ability >= GAUGE_MAX)
	{
		ability = GAUGE_MAX;	
	}
	
	
	
}

//================================================
//�ɍ��W�ϊ�
//================================================
void CGauge::PolarTrans(float x, float y)
{
	radius = sqrt(x*x+y*y);
	
	Angle = LunaMath::Atan(x, y);
}

//================================================
//�摜�t�@�C���ǂݍ���
//================================================
void CGauge::LoadImage(char *name, int ColorKey)
{
	Tex = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_2D, ColorKey);
	
	CreateSprite();
}

//================================================
//�X�v���C�g����
//================================================
void CGauge::CreateSprite(void)
{
	/*��̃X�v���C�g����*/
	Spr = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
				
	/*�X�v���C�g�Ƀe�N�X�`����ڑ�*/
	LunaSprite::AttatchTexture(Spr, 0, Tex);
	
}

//================================================
//�`��
//================================================
void CGauge::Draw(int Hp, int Color)
{
	/*�`���*/
	Dst.Set(fPosX, fPosY, F(Hp), F(5) );
	
	LunaSimple::LineSquare(&Dst, 0, Color);
}


//================================================
//�`��
//================================================
void CGauge::Draw(void)
{
	/*�`���*/
	Dst.Set(fPosX, fPosY, F(ability), F(2) );
	
	/*�`��*/
	LunaSimple::LineSquare(&Dst, 0, COLOR_BLUE);
}

//===============================================
//�`��
//===============================================
void CGauge::DrawLine(float posx, float posy, int Hp)
{
	/*�`���*/
	Dst.Set(fPosX+posx, fPosY+posy, F(Hp), F(2) );
	
	/*�`��*/
	LunaSimple::LineSquare(&Dst, 0, COLOR_BLUE);
	
	if(Hp <= 0)
	{
		Hp = 0;
	}
	
}

//================================================
//�`��
//================================================
void CGauge::Draw(float posx, float posy, int Hp)
{
	/*�o�b�t�@���Z�b�g*/
	LunaSprite::ResetBuffer(Spr);
	
	/*�`���*/
	Dst.Set(fPosX + posx, fPosY + posy, F(Hp), F(Height) );
	
	/*�`�挳*/
	Src.Set( F(0), F(0), F(Width), F(Height) );
	
	/*�`��*/
	LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	/*�o�b�t�@�X�V*/
	LunaSprite::UpdateBuffer(Spr);
	
}

//================================================
//�����_�����O
//================================================
void CGauge::Rendering()
{
	/*�����_�����O*/
	LunaSprite::Rendering(Spr);
}

//================================================
//�~�`�`��
//================================================
void CGauge::DrawCircuit(void)
{
	//PolarTrans(fPosX, fPosY);
	
	Circle.Radius = 5;
	Circle.Center.Px = 5;
	Circle.Center.Py = 5;
	
	Angle += 100;
	
	/*�`���*/
	Dst.Set(pPos.x, pPos.y, F(Width), F(Height) );
	
	/*�`�挳*/
	Src.Set(0, radius*LunaMath::Sin(Angle), F(Width), F(Height) );

	/*�X�v���C�g�����_�����O*/
	LunaSprite::Rendering(Spr);

	/*�X�v���C�g�o�b�t�@�N���A*/
	LunaSprite::ResetBuffer(Spr);
		
	/*�`��L���[�ɒǉ�*/
	//LunaSprite::DrawRing(Spr, pPos.x, pPos.y, PRIMITIVE_Z_CENTER, &Src, 100, 120, COLOR_BASE, COLOR_BASE, 100, 1);
	
	LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	//LunaSprite::DrawSquareRotate(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE, Angle);
		
	/*�X�v���C�g�o�b�t�@�X�V*/
	LunaSprite::UpdateBuffer(Spr);
	
}

//================================================
//�������J��
//================================================
void CGauge::Release()
{
	LunaTexture::Release(Tex);
	
	LunaSprite::Release(Spr);
	
}

