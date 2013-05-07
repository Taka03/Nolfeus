//================================================
//gamemode.h
//================================================
#pragma once

//================================================
//define
//================================================
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FRAME_RATE = 60;

const int MINI_RANGE_X = 10;
const int MAX_RANGE_X  = 410;
const int MINI_RANGE_Y = 10;
const int MAX_RANGE_Y = 470;


//================================================
//enum
//================================================
enum
{
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_CHARSEL,
	SCENE_MAIN,
	SCENE_OPTION,
	SCENE_TUTOLIAL,
	SCENE_PAUSE,
	SCENE_PAUSEEXIT,
	SCENE_ERROR,
	SCENE_EXIT,
	SCENE_FADEIN,
	SCENE_FADEOUT,
	SCENE_CONV,
	SCENE_GAMECLEAR,
	SCENE_GAMEOVER,
	SCENE_INITIALIZE,
	SCENE_CONTINUE,
	SCENE_FINALIZE,
};

//================================================
//プロトタイプ宣言
//================================================
void InitProcess(void);//初期処理
void Initialize(void);//初期化
void DrawLogo(void);//ロゴ画面
void DrawTitle(void);//タイトル画面
void DrawCharaSelect(void);//キャラクターセレクト画面
void DrawMain(void);//メイン画面
void DrawOption(void);//オプション画面
void DrawTutorial(void);//チュートリアル画面	
void DrawGameOver(void);//ゲームオーバー画面
void DrawGameClear(void);//ゲームクリア画面
void DrawPause(void);//ポーズ画面
void DrawPauseExit(void);//ポーズ終了確認画面
void DrawError(void);//エラー画面
void Conversation(void);//会話画面
void DrawContinue(void);//コンティニュー処理画面
void DrawExit(void);//終了確認画面
void Finalize(void);//終了処理

void AddScore(int Score);//スコア計算
void EnemyPoint(void);//敵出現ポイント
void DrawMethod(void);//描画
void CreateSprite(void);//スプライト生成
void SetLight(void);//ライトの設定
void MoveAdjust(void);//移動範囲補正
void SetHitRect(void);//当たり判定セット
void CheckHitRect(void);//当たり判定チェック
void PlayerShoot(void);//プレイヤーのショット処理
void EnemyShoot(void);//敵のショット処理
void EnemyMove(void);//敵の動き
void BossMove(void);//ボスの動き
void LoadGraphics(void);//画像読み込み
void LoadSounds(void);//音読み込み
void Release(void);//メモリ開放
void Debug(void);//デバッグ用

