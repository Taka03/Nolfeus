//================================================
//boss.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "character.h"
#include "gauge.h"

//================================================
//define
//================================================
const int SKULL_NUM = 4;
const int KNIFE_NUM = 5;

//================================================
//class
//================================================
class CBoss
{
	private:
		
		float fPosX;//X座標
		float fPosY;//Y座標
		
		float fVx;//X速度
		float fVy;//Y速度
		
		int Hp;//体力
		
		int Width;//幅
		int Height;//高さ
		
		int DivNum;//分割数
		
		int dcounter;//ダメージカウンタ
		
		float fTime;
		
		bool IsDamage;//ダメージ判定フラグ
		bool IsDead;//死亡フラグ
		
		Sint32 fAngle;//角度
		
		Sint32 rand;//行動パターン
		
		int SummonType;
		
		int COMP;//当たり判定補正値
		
		LANIMATION lAnimX;
		LANIMATION lAnimY;
		
		LTEXTURE Tex;//テクスチャハンドル
		LSPRITE Spr;//スプライトハンドル
		
		LUNARECT Dst;//描画先
		LUNARECT Src;//描画元
		
		CGauge lgauge;//ライフゲージ
		
		enum
		{
			SE_SHOT,
			SE_MOVE,
			SE_MAX,
		};
		
		CSound Se[SE_MAX];
		
	public:

		bool IsExist;//存在するかどうか
		int counter;//汎用カウンタ
		
		int animcounter;//アニメーション用カウンタ
		int Score;//スコア
		int Attack;//攻撃力
		int Defence;//防御力
		
		RECT2D HitRect;//当たり判定用
		
		CBullet bullet;//弾
		
		CChara skull[SKULL_NUM];
		CChara knife[KNIFE_NUM];
		
		CBoss();//コンストラクタ
		virtual ~CBoss();//デストラクタ
		
		void Initialize(void);//初期化
		
		float Get_PosX(void);//X座標を得る
		
		float Get_PosY(void);//Y座標を得る
		
		int Get_Life(void);//HPを得る
		
		void LoadSound(void);//サウンド読み込み
		
		void LoadImage(char *name, int ColorKey);//テクスチャ読み込み
		void CreateSprite(void);//スプライト生成
		
		void Set(int width, int height, int divnum);
		void SetRect(void);//当たり判定領域設定
		void SetPosition(float posx, float posy);//位置セット
		
		void CalcDamage(int attack, int defence);//ダメージ計算
		void Dead(int *mode);//死亡処理
		
		void Move(int *mode, float tax, float tay);//移動
		void SummonKnife();//ナイフ召喚
		void SummonSkull();//骸骨召喚
		void Shoot(float tax, float tay);//ショット処理
		
		void MoveAdjust(int left, int right, int top, int bottom); 
		
		void CreateKeyData(void);//キーデータ作成
		
		void MovePattern1(void);//移動パターン1
		void MovePattern2(void);//移動パターン2
		void MovePattern3(void);//移動パターン3
		void MovePattern4(void);//移動パターン4
		void MovePattern5(void);
		
		void Draw(void);//描画
		void Rendering(void);//レンダリング
		void Debug(void);//デバッグ用
		
		void Release(void);//メモリ開放
};
