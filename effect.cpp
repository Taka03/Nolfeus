//================================================
//include
//================================================
#include "effect.h"

//================================================
//�R���X�g���N�^
//================================================
CEffect::CEffect()
{

}

//================================================
//�f�X�g���N�^
//================================================
CEffect::~CEffect()
{

}

//================================================
//������
//================================================
void CEffect::Initialize(void)
{
	IsExist = FALSE;	
}

//================================================
//�摜�ǂݍ���
//================================================
void CEffect::LoadImage(char *name, int ColorKey)
{
	Tex = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_2D, ColorKey);
	
	CreateSprite();
}

//================================================
//�X�v���C�g����
//================================================
void CEffect::CreateSprite(void)
{
	/*��̃X�v���C�g����*/
	Spr = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
				
	/*�X�v���C�g�Ƀe�N�X�`����ڑ�*/
	LunaSprite::AttatchTexture(Spr, 0, Tex);
}

//================================================
//�摜���Z�b�g
//================================================
void CEffect::Set(int width, int height, int divnum)
{
	Width = width;
	Height = height;
	Divnum = divnum;
}

//================================================
//�`��
//================================================
void CEffect::Draw(float posx, float posy)
{
	/*�X�v���C�g�o�b�t�@�N���A*/
	LunaSprite::ResetBuffer(Spr);

	/*�`���*/
	Dst.Set(posx, posy, F(Width), F(Height) );
		
	/*�`�挳*/
	Src.Set( F( (animcounter%Divnum)*Width), F(0), F(Width), F(Height) );
		
	/*�`��L���[�ɒǉ�*/
	LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
		
	/*�X�v���C�g�o�b�t�@�X�V*/
	LunaSprite::UpdateBuffer(Spr);
}

//================================================
//�����_�����O
//================================================
void CEffect::Rendering()
{
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetFilterEnable(TRUE);
		
		if(IsExist)
		{
			/*�X�v���C�g�����_�����O*/
			LunaSprite::Rendering(Spr);
		}
		
		Luna3D::EndScene();
	}
}

//================================================
//�������J��
//================================================
void CEffect::Release(void)
{
	LunaTexture::Release(Tex);
	
	LunaSprite::Release(Spr);
}

//================================================
//�f�o�b�O
//================================================
void CEffect::Debug()
{
	LunaDebug::DrawString("counter:%d", counter);
}

