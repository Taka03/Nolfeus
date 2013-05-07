//=================================================
//enemy.h
//=================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "bullet.h"
#include "sound.h"
#include "effect.h"

//================================================
//define
//================================================
const int TYPE_MAX = 5;
const int ENEMY_NUM = 156;

//================================================
//enum
//================================================
enum eEnemyType
{
	ENEMY_NUNO,
	ENEMY_BAT,
	ENEMY_CROW,
	ENEMY_MUMMY,
	ENEMY_SPIDER,
};

//================================================
//class
//================================================
class CEnemy
{
	private:

		float fPosX;//X座標
		float fPosY;//Y座標
		
		float fVx;//X速度
		float fVy;//Y速度
		
		int Width;//幅
		int Height;//高さ
		
		int counter;//出現カウンタ
		int dcounter;//ダメージ用カウンタ
		
		int Hp;//体力
		
		int DivNum;//分割数
		
		int Type;//敵タイプ
		
		char *name;//敵名
		
		Sint32 Angle;//角度
		float fTime;//時間
		
		int COMP;//当たり判定補正値
		
		char Pattern[4];
		
		float rand;//乱数値
		
		Sint32 rand2;
		
		bool IsDamage;//ダメージ判定フラグ
		
		LTEXTURE Tex[TYPE_MAX];//敵テクスチャハンドル
		LSPRITE Spr[TYPE_MAX];//敵スプライトハンドル
		
		LANIMATION lAnimX;
		LANIMATION lAnimY;
		
		LUNARECT Dst;//描画先
		LUNARECT Src;//描画元
		
		typedef struct DATA
		{
			int Attack;
			int Defence;
			int Hp;
			int Score;
			int Width;
			int Height;
			int Divnum;
		};
		
		typedef struct EPOINT
		{
			int point;//出現ポイント
			eEnemyType Type;//タイプ
		};
		
		enum
		{
			SE_SHOT,
			SE_CROW,
			SE_BAT,
			SE_MAX,
		};
		
		DATA edata[TYPE_MAX];
		
		CSound Se[SE_MAX];
		
		CEffect burst;//爆発エフェクト
		
		void LoadEffect();//エフェクト読み込み
		

	public:

		int Score;//スコア
		int animcounter;//アニメ用カウンター
		
		int Attack;//攻撃力
		int Defence;//防御力　
		
		bool IsExist;//敵が存在するか
		bool IsDead;//敵が死亡したか
		
		EPOINT epoint[ENEMY_NUM];
		
		RECT2D HitRect;//当たり判定用
		
		CBullet bullet;//弾
		
		CEnemy();//コンストラクタ
		virtual ~CEnemy();//デストラクタ
		
		void Initialize(void);//初期化
		
		float Get_PosX(void);//X座標を得る
		float Get_PosY(void);//Y座標を得る
		
		void LoadParam(void);//パラメーター読み込み
		void LoadPoint(void);//出現ポイント読み込み
		
		void LoadSound(void);//サウンド読み込み
		
		void SetGraphInfo(void);//画像情報セット
		void SetHp(void);//敵体力セット
		void SetRect(void);//当たり判定領域セット
		void SetPosition(float posx, float posy);//座標セット
		void SetType(eEnemyType type);//敵タイプセット
		void SetScore(void);//スコアセット
		void SetStatus(void);//ステータスセット
		
		void CalcDamage(int attack, int defence);//ダメージ計算
		void Dead(void);//死亡処理
		
		void LoadImage(void);//テクスチャ読み込み
		void CreateSprite(void);//スプライト生成
		
		void CreateAnimation(void);//キーデータ生成
		
		void LoadPattern(char *datname);//パターンデータ読み込み
		
		void Move(void);//移動
		
		void MovePattern(float tax, float tay);//移動パターン
		void ShootPattern(float tax, float tay);//ショットパターン
		void MovePattern1(void);//移動パターン1
		void MovePattern2(float tax, float tay);//移動パターン2
		void MovePattern3(float tax, float tay);//移動パターン3
		void MovePattern4(float tax, float tay);//移動パターン4
		void MovePattern5(void);//移動パターン5
		
		void Draw(eEnemyType type);//描画
		void Rendering(void);//レンダリング
		void Debug(void);//デバッグ用
		
		void MoveAdjust(int left, int right, int top, int bottom);//移動補正
		
		void Release(void);//メモリ開放
};
