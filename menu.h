//================================================
//menu.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "sound.h"

//================================================
//define
//================================================
#define CURSOR_NUM 2

//================================================
//enum
//================================================
enum
{
	ITEM_START,
	//ITEM_TUTOLIAL,
	ITEM_CONFIG,
	ITEM_EXIT,
	ITEM_MAX,
};

enum
{
	SCENE_FIRST,
	SCENE_SECOND,
	SCENE_THIRD,
	SCENE_END,
};

static char *TitleMenu[] =
{
	"ゲームを始める",
	//"チュートリアル",
	"キーコンフィグ",
	"ゲームをやめる",
};

static char *Menu2[] =
{
	"ショット %d",
	"交代 %d",
	"特殊 %d",
	//"スロー移動 %d",
	"ポーズ %d",
	"終了",
};

static char *Menu3[] =
{
	"ゲームを続ける",
//	"ゲームをやめる",
	"メニューに戻る",
};

static char *Menu4[] =
{
	"基礎知識",
	"基本行動",
	"特殊能力",
	"交代",
	"演習",
	"終了",
};

static char *Menu5[] =
{
	"CONTINUE",
	"END",
};

static char *Menu6[] =
{
	"はい",
	"いいえ",
};

//================================================
//class
//================================================
class CMenu
{
	private:
		
		enum
		{
			SE_ENTER,
			SE_CANCEL,
			SE_CURSOR,
			SE_MAX,
		};
		
		int Px;//X座標
		int Py;//Y座標
		
		int CursorX;//カーソルX座標
		int CursorY;//カーソルY座標
		
		Sint32 StrPx[10];
		Sint32 StrPy[10];
		
		int Width;//幅
		int Height;//高さ
		
		int Shot;//ショットボタン
		int Change;//チェンジボタン
		int Special;//特殊ボタン
		int Slow;//スロー移動ボタン
		int Pause;//ポーズボタン
		
		int DivNum;//分割数
		
		Sint32 OldCursor;
		
		int tmp;//キャラ入れ替え用
		
		int counter;//汎用カウンタ
		
		int FONT_SIZE;//フォントサイズ
		int NUM_MENU;//メニュー数
		int MOVE;//移動量
		int TOP;//最初のメニュー座標
		int BOTTOM;//最後のメニュー座標
		
		CSound Se[SE_MAX];//効果音
		
		LTEXTURE Tex[CURSOR_NUM];//テクスチャハンドル
		LSPRITE Spr[CURSOR_NUM];//スプライトハンドル
		
		LFONT Font;//フォントハンドル
		LFONTSPRITE FontSpr;//フォントスプライトハンドル
		
		LUNARECT Dst;//描画先
		LUNARECT Src;//描画元
		
	public:

		JOYSTICKDATA Pad;
		
		Sint32 Cursor;
		
		int animcounter;//アニメーションカウンタ
		
		bool Flag;//汎用フラグ
		bool IsSelected;//選択判定フラグ
		
		int Scene;//キャラ選択用
		
		CMenu();//コンストラクタ
		virtual ~CMenu();//デストラクタ
		
		void Initialize(void);//初期化
		
		void CreateFont(void);
		void CreateFontSprite(char *StrTbl[], int MenuMax);//フォント生成
		void CreateFontSprite(void);//フォントスプライト生成(ファイル読み込み)
		void DrawFont(int posx, int posy, char *string);//フォント描画
		void DrawFont(char *StrTbl[], int MenuMax);//フォント描画()
		void DrawFontSpr(char *StrTbl[], int MenuMax);//フォントスプライト描画
		void DrawErrorMessage(void);//エラー描画
		
		void CalcFontPos(int posx, int posy, int MenuMax);
		void CalcFontSprPos(int posx, int posy, char *StrTbl[], int MenuMax);//文字位置算出
		void CalcCharaPos(int posx, int posy, int move);//プレイヤー位置算出
		
		void LoadImage(void);//画像読み込み
		void CreateSprite(void);//スプライト生成
		
		void LoadSound();//読み込み
		
		void DrawCursor(void);//カーソル描画
		void DrawCursor(int Cursor, int no);//カーソル描画
		void Rendering(void);//レンダリング
		void Rendering(int no);//レンダリング
		
		void Move(int MenuMax);//カーソル移動
		void MoveLeftRight(int MenuMax);//カーソル移動(左右)
		
		void ModeSelect(int *mode);//モードセレクト
		void PauseSelect(int *mode);//ポーズセレクト
		void CharaSelect(int *mode, int *first, int *second, int *third);//キャラセレクト
		void CharaSelectExit(int *mode);//キャラセレクト終了確認画面
		void Select(int *mode);//終了確認セレクト
		void PauseExitSelect(int *mode);//ポーズ終了確認セレクト
		void GameOverSelect(int *mode);//ゲームオーバーセレクト
		void KeyConfig(int *mode);//キーコンフィグ
		
		void Swap(int *x, int *y);//入れ替え
		void Swap(int *x, int *y, bool *Flag);//キャラ入れ替え
		
		void Debug(void);//デバッグ
		
		void Release(void);//メモリ開放
		
};
