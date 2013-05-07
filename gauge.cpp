//================================================
//include
//================================================
#include "gauge.h"
#include "gamemode.h"

//================================================
//コンストラクタ
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
//コンストラクタ
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
//デストラクタ
//================================================
CGauge::~CGauge()
{

}

//================================================
//初期化
//================================================
void CGauge::Initialize(void)
{
	ability = 0;
}

//================================================
//位置セット
//================================================
void CGauge::SetPosition(float posx, float posy)
{
	fPosX = F(posx);
	fPosY = F(posy);
}

//================================================
//画像情報セット
//================================================
void CGauge::SetGraphInfo(int width, int height)
{
	Width = width;
	Height = height;
}

//================================================
//ゲージ増加
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
//極座標変換
//================================================
void CGauge::PolarTrans(float x, float y)
{
	radius = sqrt(x*x+y*y);
	
	Angle = LunaMath::Atan(x, y);
}

//================================================
//画像ファイル読み込み
//================================================
void CGauge::LoadImage(char *name, int ColorKey)
{
	Tex = LunaTexture::CreateFromFile(name, FORMAT_TEXTURE_2D, ColorKey);
	
	CreateSprite();
}

//================================================
//スプライト生成
//================================================
void CGauge::CreateSprite(void)
{
	/*空のスプライト生成*/
	Spr = LunaSprite::Create(10, PRIM_VERTEX_UV1, false);
				
	/*スプライトにテクスチャを接続*/
	LunaSprite::AttatchTexture(Spr, 0, Tex);
	
}

//================================================
//描画
//================================================
void CGauge::Draw(int Hp, int Color)
{
	/*描画先*/
	Dst.Set(fPosX, fPosY, F(Hp), F(5) );
	
	LunaSimple::LineSquare(&Dst, 0, Color);
}


//================================================
//描画
//================================================
void CGauge::Draw(void)
{
	/*描画先*/
	Dst.Set(fPosX, fPosY, F(ability), F(2) );
	
	/*描画*/
	LunaSimple::LineSquare(&Dst, 0, COLOR_BLUE);
}

//===============================================
//描画
//===============================================
void CGauge::DrawLine(float posx, float posy, int Hp)
{
	/*描画先*/
	Dst.Set(fPosX+posx, fPosY+posy, F(Hp), F(2) );
	
	/*描画*/
	LunaSimple::LineSquare(&Dst, 0, COLOR_BLUE);
	
	if(Hp <= 0)
	{
		Hp = 0;
	}
	
}

//================================================
//描画
//================================================
void CGauge::Draw(float posx, float posy, int Hp)
{
	/*バッファリセット*/
	LunaSprite::ResetBuffer(Spr);
	
	/*描画先*/
	Dst.Set(fPosX + posx, fPosY + posy, F(Hp), F(Height) );
	
	/*描画元*/
	Src.Set( F(0), F(0), F(Width), F(Height) );
	
	/*描画*/
	LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	/*バッファ更新*/
	LunaSprite::UpdateBuffer(Spr);
	
}

//================================================
//レンダリング
//================================================
void CGauge::Rendering()
{
	/*レンダリング*/
	LunaSprite::Rendering(Spr);
}

//================================================
//円形描画
//================================================
void CGauge::DrawCircuit(void)
{
	//PolarTrans(fPosX, fPosY);
	
	Circle.Radius = 5;
	Circle.Center.Px = 5;
	Circle.Center.Py = 5;
	
	Angle += 100;
	
	/*描画先*/
	Dst.Set(pPos.x, pPos.y, F(Width), F(Height) );
	
	/*描画元*/
	Src.Set(0, radius*LunaMath::Sin(Angle), F(Width), F(Height) );

	/*スプライトレンダリング*/
	LunaSprite::Rendering(Spr);

	/*スプライトバッファクリア*/
	LunaSprite::ResetBuffer(Spr);
		
	/*描画キューに追加*/
	//LunaSprite::DrawRing(Spr, pPos.x, pPos.y, PRIMITIVE_Z_CENTER, &Src, 100, 120, COLOR_BASE, COLOR_BASE, 100, 1);
	
	LunaSprite::DrawSquare(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE);
	
	//LunaSprite::DrawSquareRotate(Spr, &Dst, PRIMITIVE_Z_CENTER, &Src, COLOR_BASE, Angle);
		
	/*スプライトバッファ更新*/
	LunaSprite::UpdateBuffer(Spr);
	
}

//================================================
//メモリ開放
//================================================
void CGauge::Release()
{
	LunaTexture::Release(Tex);
	
	LunaSprite::Release(Spr);
	
}

