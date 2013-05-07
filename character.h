//================================================
//character.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "bullet.h"
#include "sound.h"
#include "effect.h"

//================================================
//enum
//================================================
enum
{
	SKULL,
	KNIFE,
};

//================================================
//class
//================================================
class CChara
{
	private:
		
		float fPosX;//X座標
		float fPosY;//Y座標
		
		float fOldPosX;//X座標保持
		float fOldPosY;//Y座標保持
		
		float fVx;//X速度
		float fVy;//Y速度
		
		Sint32 Angle;//角度
		
		int Width;//幅
		int Height;//高さ
		
		int Divnum;//分割数
		int count_charge;//チャージカウント
		
		int CHARGE_MAX;//チャージ最大値
		int COMP;//当たり判定補正値
		
		LTEXTURE Tex;//テクスチャハンドル
		LSPRITE Spr;//スプライトハンドル
		
		LUNARECT Dst;//描画先
		LUNARECT Src;//描画元
		
		enum
		{
			SE_CHARGE,
			SE_CHARGESHOT,
			SE_UMBRELLA,
			SE_MAX,
		};
		
		CSound Se[SE_MAX];
		
	public:
		
		int animcounter;//アニメーション用カウンター
		int Attack;//攻撃力
		int Defence;//防御力
		
		int counter;//傘用カウンター
		int knifecounter;
		
		bool IsExist;//存在判定用フラグ
		
		RECT2D HitRect;//当たり判定
		
		CBullet bullet;//弾
		
		CEffect chargefx;
		CEffect mchargefx;
		
		CChara();//コンストラクタ
		CChara(int width, int height, int divnum);//コンストラクタ
		virtual ~CChara();//デストラクタ
		
		void Initialize(void);//初期化

		float Get_PosX(void);//X座標を得る
		float Get_PosY(void);//Y座標を得る
		
		void LoadImage(char *name, int ColorKey);//テクスチャ読み込み
		void CreateSprite(void);//スプライト生成
		
		void LoadSound();//サウンド読み込み
		
		void Set(int width, int height, int divnum);
		void SetRect(void);//当たり判定
		void SetPosition(float posx, float posy);
		
		void Move(void);//移動
		void Shoot(void);//弾を撃つ
		
		void SetUmbrella(float posx, float posy);//傘セット
		
		void ChargeShoot(bool *charge);//チャージショット
		void PutAttack(bool *charge);//設置攻撃
		
		void MovePattern1(bool *charge);//移動パターン1
		void MovePattern3(float tax, float tay);//移動パターン3
		void MovePattern4();//移動パターン4
		
		void Draw(float posx, float posy);//描画
		void Draw(void);//描画
		void DrawRotate(float posx, float posy);//回転描画
		void Rendering(void);//レンダリング
		void Debug(void);//デバッグ用
		
		void Release(void);//メモリ開放
};
