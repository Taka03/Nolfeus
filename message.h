//================================================
//message.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"
#include "gamemode.h"

//================================================
//define
//================================================
const int CHARA_MAX = 4;
const int LINE_NUM = 41;

//================================================
//class
//================================================
class CMessage
{
	private:
	
		int Px;//X座標(メッセージウィンドウ用)
		int Py;//Y座標(メッセージウィンドウ用)
		
		int StrPx;//文字X座標
		int StrPy;//文字Y座標
		
		int DrawPointX;//一字ずつ描画
		int DrawPointY;//
		
		int Width;//幅
		int Height;//高さ
		
		int Type;//顔グラフィックのタイプ
		
		int Sp;//参照する文字列番号
		int Cp;//参照する文字列の文字列ポインタ
		
		char *pStr;
		
		Sint32 Count;
		Sint32 StrHeight;
		Sint32 StrLeft;
		Sint32 StrCenter;
		Sint32 StrRight;

		char strdata[LINE_NUM][256];
		
		bool EndFlag;//会話終了フラグ
		bool Is2Byte;//2バイト文字判定フラグ
		
		bool IsDebug;
		
		int FONT_SIZE;
		
		LTEXTURE Tex;//テクスチャハンドル
		LTEXTURE FaceTex[CHARA_MAX];//顔テクスチャハンドル
		LSPRITE Spr[CHARA_MAX];
		
		LFONT Font;//フォントハンドル
		LFONTSPRITE FontSpr;//フォントスプライトハンドル
		
		LUNARECT Dst;//描画先
		LUNARECT Src;//描画元
		
		enum
		{
			CHARA_ISLA,
			CHARA_RAI,
			CHARA_AMEUS,
			CHARA_JACK,
		};
		
	
	public:
	
		bool IsDisp;//表示判定フラグ
		
		int counter;
		
		CMessage();//コンストラクタ
		virtual ~CMessage();//デストラクタ
		
		void Initialize(void);//初期化
		
		void LoadScriptData(void);//会話データ読み込み
		void LoadImage(char *name, int ColorKey);//ウィンドウ画像ロード
		void LoadImage();//顔画像ロード用
		
		void ScriptTreat(int *mode);//スクリプト処理
		void ScriptFaceData(void);//スクリプト毎の顔データ
		
		void Set(int posx, int posy, int width, int height);//画像情報セット
		
		void CreateFont(void);//フォント生成
		void CreateFontSprite(void);//フォントスプライト生成
		void CreateSprite(void);//スプライト生成
		
		void CalcFontPos(void);//描画位置算出
		
		void DrawChara(int posx, int posy);//一文字ずつ描画
		void DrawFont(int score);
		void DrawFont(char *data);//フォント描画
		void DrawFont(int posx, int posy, char *data);//フォント描画
		void DrawFont(int posx, int posy);
		void DrawFontSprite(int posx, int posy, char *data);//
		void DrawFontSprite(char *data);//フォントスプライト描画
		
		void RenderingFont(void);//フォントのレンダリング
		void Rendering(void);//レンダリング
		void Rendering(int type);//レンダリング
		
		void DrawMessage(Sint32 cursor);//シーンごとの描画

		void DrawTexture(void);//顔グラフィック描画
		void Draw(void);//描画
		void Draw(float posx, float posy);
		void Draw(float posx, float posy, int type);
		
		void Debug(void);//デバッグ用
		void Release(void);//メモリ開放
};
