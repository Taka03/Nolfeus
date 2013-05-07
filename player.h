//================================================
//player.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "bullet.h"
#include "effect.h"
#include "message.h"
#include "character.h"
#include "gauge.h"

//================================================
//define
//================================================
const int PLAYER_NUM = 4;
const int MAX_LIFE = 100;
const int TYPE_AGAUGE = 2;

const int AME_NUM = 3;
const int LAG_NUM = 20;

//================================================
//enum
//================================================
enum ePlayerType
{
	ID_PLAYER1,
	ID_PLAYER2,
	ID_PLAYER3,
	ID_PLAYER4,
};

//================================================
//variable
//================================================

//================================================
//class
//================================================
class CPlayer
{
	private:

		float fPosX;//X座標
		float fPosY;//Y座標
		
		//float PosX[LAG_NUM];//X座標(残像用)
		//float PosY[LAG_NUM];//Y座標(残像用)
		
 		int life;//体力所持用変数
		
		int Speed;//移動速度
		
		int Width;//幅
		int Height;//高さ
		
		int Weight;//重さ
		
		int Divnum;//分割数
		
		int tmp;//キャラ入れ替え用
		
		int COMP;//当たり判定補正値
		
		int counter;//汎用カウンタ
		
		float fTime;//時間
		
		int RecoverLife;//回復量
		int RecoverMax[PLAYER_NUM-1];//回復最大量
		
		bool IsChange;//キャラ変更用フラグ
		bool IsDamege;//ダメージ判定フラグ

		LTEXTURE Tex[PLAYER_NUM];//プレイヤーテクスチャハンドル
		LTEXTURE windowTex[PLAYER_NUM - 1];//プレイヤーウィンドウテクスチャ
		
		LSPRITE Spr[PLAYER_NUM];//プレイヤースプライトハンドル
		LSPRITE windowSpr[PLAYER_NUM - 1];
		
		LUNARECT Dst;//描画先
		LUNARECT Src;//描画元
		
		typedef struct DATA
		{
			int Defence;
			int Speed;
			int Hp;
			int Weight;
			int Width;
			int Height;
			int Divnum;
		};
		
		enum 
		{
			SE_SHOT1,
			SE_SHOT2,
			SE_STOP,
			SE_WOLF,
			SE_CLEAR,
			SE_CHANGE,
			SE_NEDEATH,
			SE_DEATH,
			SE_MAX,
		};
		
		DATA pdata[PLAYER_NUM];
		
		CEffect lightball;//光の弾
		CEffect change;//チェンジエフェクト
		CEffect stop;//時間停止用
		CEffect wolf;//獣化用
		
		CGauge lgauge[PLAYER_NUM-1];//ライフゲージ
		CGauge rgauge[PLAYER_NUM-1];//ライフゲージ(最大回復量)
		//CGauge wlgauge[WAIT_LIFE];//待機ライフゲージ
		CGauge agauge;//アビリティゲージ
		CGauge magauge;//アビリティゲージMAX
		
		CMessage face;
		
		CSound Se[SE_MAX];
		
		void LoadEffect(void);
		
	public:
	
		int Hp[PLAYER_NUM];//体力
		int OldHp[PLAYER_NUM];//体力保持用
		
		int Attack;//攻撃力
		int Defence;//防御力
		
		int first;//一番目のキャラ
		int second;//二番目のキャラ
		int third;//三番目のキャラ
		
		float OldPosX;//X座標(保持用)
		float OldPosY;//Y座標(保持用)
		
		int Type;//プレイヤータイプ
		int ChangeTime;//キャラ変更時間
		int InvinceTime;//無敵時間
		int animcounter;//アニメカウンター
		
		int Invcounter;//無敵時間用カウンター
		
		bool IsUseSpecial;//特殊攻撃使用判定フラグ
		bool IsDead;//死亡フラグ
		bool IsInvince;//無敵フラグ
		
		bool IsStop;//時間停止用フラグ(イスラ必殺技用)
		bool IsWolf;//獣化判定フラグ(ライ必殺技用)
		bool IsClear;//半透明化用フラグ(アメウス必殺技用)
		
		CBullet bullet;//プレイヤー弾
		CBullet amebullet[AME_NUM];//アメウス分身弾
		
		CChara charge;
		CChara umbrella;
		CChara shadow;
		
		RECT2D HitRect;//当たり判定用
		
		CPlayer();//コンストラクタ
		CPlayer(float Px, float Py, int width, int height, int divnum);//コンストラクタ
		virtual ~CPlayer();//デストラクタ
		
		void Initialize(void);//初期化
		
		float Get_PosX(void);//X座標を得る
		float Get_PosY(void);//Y座標を得る
		int Get_Life(void);//Hpを得る
		
		int GetWidth(void);//幅を得る
		int GetHeight(void);//高さを得る
		
		void LoadParam(void);//パラメータ読み込み
		
		void Set(float Px, float Py, int width, int height, int divnum);
		void SetRect(void);//当たり判定領域設定
		void SetPosition(float Px, float Py);
		
		void SetGraphInfo(void);//画像情報セット
		
		void SetHp(int Hp);//HPセット
		void SetSpeed(void);//移動速度セット
		void SetStatus(void);//ステータスセット
		
		void LoadImage(char *name, int ColorKey);
		void LoadImage(void);//テクスチャ読み込み
		void CreateSprite(void);//スプライト生成
		
		void LoadSound(void);//サウンド読み込み

		
		void ChangeChara(void);//キャラ変更
		void UseSpecial(void);//必殺技使用
		void UseGauge(void);//ゲージ使用
		void UseCharaChange(void);//キャラチェンジ使用
		
		void TimeStop(void);//時間停止
		void ChangeWolf(void);//獣化
		void Clearize(void);//半透明化
		
		void CalcDamage(int attack, int defence);//ダメージ計算
		
		void Move(void);//移動
		void MoveAdjust(int left, int right, int top, int bottom);//移動補正
		void Shoot(void);//ショット処理
		
		void SwapChara(int *x, int *y, int *z);//キャラ入れ替え
		
		void Recoverlife(void);//ライフ回復
		void KeepHp(void);//ライフ保持
		void KnockBack(void);//のけぞり
		
		void Draw(void);//テクスチャ描画
		void Draw(float posx, float posy, int type);
		void Rendering(void);//レンダリング
		void DrawTex();
		void Debug(void);//デバッグ用
		
		//void DrawGauge(void);//ゲージ描画
		
		void Release(void);//メモリ開放
};

