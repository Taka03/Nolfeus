//================================================
//effect.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"

//================================================
//class
//================================================
class CEffect
{
	private:
		
		float fPosX;//X座標
		float fPosY;//Y座標
		
		int Width;//幅
		int Height;//高さ
		
		int Divnum;
		
		LTEXTURE Tex;//テクスチャハンドル
		LSPRITE Spr;//スプライトハンドル
		
		LUNARECT Dst;//描画先
		LUNARECT Src;//描画元
		
	public:
	
		int animcounter;//アニメ用カウンタ
		int counter;//汎用カウンタ
		
		bool IsExist;//存在判定フラグ
		
		CEffect();//コンストラクタ
		virtual ~CEffect();//デストラクタ
		
		void Initialize(void);//初期化
		
		void LoadImage(char *name, int ColorKey);//テクスチャ読み込み
		void CreateSprite(void);//スプライト生成
		
		void Set(int width, int height, int divnum);//画像情報セット
		
		void Draw(float posx, float posy);//描画
		void Rendering();//レンダリング
		
		void Debug();//デバッグ
		
		void Release(void);//メモリ開放
		
};
