//================================================
//include
//================================================
#include "effect.h"

//================================================
//コンストラクタ
//================================================
CEffect::CEffect()
{

}

//================================================
//デストラクタ
//================================================
CEffect::~CEffect()
{

}

//================================================
//初期化
//================================================
void CEffect::Initialize(void)
{
	IsExist = FALSE;	
}

//================================================
//画像読み込み
//================================================
void CEffect::LoadImage(char *name, int ColorKey)
{
	Tex = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_2D, ColorKey);
	
	CreateSprite();
}

//================================================
//スプライト生成
//================================================
void CEffect::CreateSprite(void)
{
	/*空のスプライト生成*/
	Spr = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
				
	/*スプライトにテクスチャを接続*/
	LunaSprite::AttatchTexture(Spr, 0, Tex);
}

//================================================
//画像情報セット
//================================================
void CEffect::Set(int width, int height, int divnum)
{
	Width = width;
	Height = height;
	Divnum = divnum;
}

//================================================
//描画
//================================================
void CEffect::Draw(float posx, float posy)
{
	/*スプライトバッファクリア*/
	LunaSprite::ResetBuffer(Spr);

	/*描画先*/
	Dst.Set(posx, posy, F(Width), F(Height) );
		
	/*描画元*/
	Src.Set( F( (animcounter%Divnum)*Width), F(0), F(Width), F(Height) );
		
	/*描画キューに追加*/
	LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
		
	/*スプライトバッファ更新*/
	LunaSprite::UpdateBuffer(Spr);
}

//================================================
//レンダリング
//================================================
void CEffect::Rendering()
{
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetFilterEnable(TRUE);
		
		if(IsExist)
		{
			/*スプライトレンダリング*/
			LunaSprite::Rendering(Spr);
		}
		
		Luna3D::EndScene();
	}
}

//================================================
//メモリ開放
//================================================
void CEffect::Release(void)
{
	LunaTexture::Release(Tex);
	
	LunaSprite::Release(Spr);
}

//================================================
//デバッグ
//================================================
void CEffect::Debug()
{
	LunaDebug::DrawString("counter:%d", counter);
}

