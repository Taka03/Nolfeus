//================================================
//gauge.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"

//================================================
//define
//================================================
const int TYPE_LIFE = 2;
const int GAUGE_MAX = 100;

//================================================
//class
//================================================
class CGauge
{
	private:
		
		float fPosX;//X座標
		float fPosY;//Y座標
		
		Sint32 Angle;//角度
		
		int counter;//汎用カウンター
		
		int Width;//幅
		int Height;//高さ
		
		float radius;//半径
		
		CVector2D pPos;
		CIRCLE2D Circle;
		
		int GAUGE_MIN;//ゲージの最小値
		
		LLINE lLine;//ラインハンドル
		
		LMATRIX Matrix;//行列ハンドル
		
		LTEXTURE Tex;//テクスチャハンドル
		LSPRITE Spr;//スプライトハンドル
		
		LUNARECT Dst;//描画先
		LUNARECT Src;//描画元

	public:
	
		int ability;//アビリティゲージ用
		
		CGauge();//コンストラクタ
		CGauge(float posx, float posy);//コンストラクタ
		virtual ~CGauge();//デストラクタ
		
		void Initialize(void);//初期化
		void SetPosition(float posx, float posy);//位置セット
		void SetGraphInfo(int width, int height);//画像情報セット
		
		void AddGauge(bool *Flag);//ゲージの増加
		
		void LoadImage(char *name, int ColorKey);//テクスチャ読み込み
		void CreateSprite(void);//スプライト生成
		
		void PolarTrans(float x, float y);//極座標変換
		
		void Draw(int Hp, int Color);//描画
		void Draw(void);//描画
		void DrawLine(float posx, float posy, int Hp);
		
		void Draw(float posx, float posy, int Hp);
		void DrawCircuit(void);//円形描画
		
		void Rendering(void);//レンダリング
		
		void Release(void);//メモリ開放
		
		//LoadImage();
};
