//================================================
//bullet.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "sound.h"

//================================================
//define
//================================================
#define BULLET_MAX 20

//================================================
//enum
//================================================
enum
{
	PLAYER,
	ENEMY,
};

//================================================
//class
//================================================
class CBullet
{
	private:

		float fPosX[BULLET_MAX];//X座標
		float fPosY[BULLET_MAX];//Y座標
		
		float fOldPosX[BULLET_MAX];//X座標(保持用)
		float fOldPosY[BULLET_MAX];//Y座標(保持用)
		
		float Vx[BULLET_MAX];//X速度
		float Vy[BULLET_MAX];//Y速度

		int Width;//幅
		int Height;//高さ
		
		int Divnum;//分割数
		
		float DisX;//X距離
		float DisY;//Y距離
		
		int count_charge;//チャージカウント
		
		float fTime;//時間
		Sint32 fAngle[BULLET_MAX];//角度
		
		int COMP;//当たり判定補正値
		int CHARGE_MAX;//チャージカウントのMax
		
		LTEXTURE Tex;//テクスチャハンドル
		LSPRITE Spr;//スプライトハンドル
		
		LUNARECT Dst;//描画先
		LUNARECT Src;//描画元
		
		enum
		{
			SE_REFRECT,
			SE_SHOT,
			SE_MAX,
		};
		
		CSound Se[SE_MAX];
		
		void LoadSound();
		
	public:

		
		bool Flag[BULLET_MAX];//弾が撃てるかどうか(フラグ)
		bool ChargeFlag;//チャージショット用フラグ
		bool IsRefrect[BULLET_MAX];//反射判定フラグ
		
		int counter;//汎用カウンター
		int trigger;//弾のトリガー
		int umbcounter;//傘用カウンター
		
		int animcounter;//アニメ用カウンタ
		
		int Attack;//攻撃力
		
		RECT2D HitRect[BULLET_MAX];//当たり判定用
		RECT DHitRect[BULLET_MAX];
		
		CBullet();//コンストラクタ
		virtual ~CBullet();//デストラクタ
		
		void Initialize(void);//初期化
		
		void SetRect(void);//当たり判定領域設定
		void SetPosition(int no);
		void SetGraphInfo(int width, int height, int divnum);
		
		void LoadImage(char *name, int ColorKey);//テクスチャ読み込み
		void CreateSprite(void);//スプライト生成
		
		void CreateBullet(float posx, float posy, int num);//弾の生成
		void CreateBullet(float posx, float posy, float tax, float tay);//弾の生成(角度つき) 
		void CreateBullet(float posx, float posy);//一斉弾の生成
		void CreateBullet(float posx, float posy, Sint32 Angle);//n-way弾の生成
		void CreateBossBullet(float posx, float posy, float tax, float tay);
		void CreateRefBullet(float posx, float posy, int num);//反射弾生成
		
		
		void Move(int Type);//弾の動き
		
		void Shoot(float posx, float posy);//弾を撃つ
		
		void Refrect(float posx, float posy);//反射弾
		
		void ChargeShoot(void);//チャージショット
		void UmbrellaAttack(float posx, float posy);//傘攻撃
		void PutAttack(void);//設置攻撃
		
		void LoadPattern(int Pattern);//パターン読み出し
//		void MovePattern
		void MovePattern1(void);//弾のパターン1(直線)
		void MovePattern2(void);//弾のパターン2
		void MovePattern3(void);//弾のパターン3
		void MovePattern4(float posx, float posy);//弾のパターン4(散弾)
		void MovePattern5(float posx, float posy);//弾のパターン5(回転弾)
		void MovePattern6(void);//弾のパターン6
		
		void Draw(void);//描画
		void Rendering(void);//レンダリング
		
		void MoveAdjust(int left, int right, int top, int bottom);//移動補正
		
		void Release(void);//メモリ開放
		void Debug(void);//デバッグ用関数
		
};

