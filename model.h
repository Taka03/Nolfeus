//================================================
//model.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"

//================================================
//class
//================================================
class CModelData
{
	private:

		float fPosX;
		float fPosY;
		float fPosZ;
				
		LMODELEX lModel;
		
	public:
	
		void Initialize(void);//初期化関数
		void LoadData(char *name, int ColorKey);//モデルの読み込み
		void Translation(void);//変形
		void Rendering(void);//モデルのレンダリング
		void Release(void);//モデルのメモリ開放
		void Debug(void);//デバッグ用
	
};

