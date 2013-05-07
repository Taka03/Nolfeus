//================================================
//gamemain.cpp
//================================================

//================================================
//include
//================================================
#include "object.h"
#include "player.h"
#include "model.h"
#include "camera.h"
#include "boss.h"
#include "bullet.h"
#include "gauge.h"
#include "enemy.h"
#include "character.h"
#include "gamemode.h"
#include "effect.h"
#include "sound.h"
#include "menu.h"
#include "message.h"
#include "function.h"
//================================================
//define
//================================================
const int E_BULLET = 5;

const int ITEM1_MAX = 3;
const int ITEM2_MAX = 5;
const int ITEM3_MAX = 2;
const int ITEM4_MAX = 6;

const int BGM_NUM = 4;

//================================================
//variable
//================================================

/*クラスの宣言*/
static CObject object;

static CPlayer player;

static CMenu menu;

static CMessage window;
static CMessage frame;
static CMessage score;
static CMessage title;
static CMessage screen;

static CEnemy enemy[ENEMY_NUM];
static CEnemy esystem;

static CBoss boss;

static CSound bgm[BGM_NUM];

static CCameraData camera;
static CCameraData tcamera;
static CModelData model;

int g_GameMode = SCENE_INITIALIZE;//ゲームモード切替

int g_Second = 0;//時間

LSURFACE lSurfZ = INVALID_SURFACE;
LPRIMITIVE lPrim = INVALID_PRIMITIVE;

Sint32 g_Score = 0;//スコア
Sint32 g_Time = 0;//フェード用
Sint32 g_gamecounter = 0;//ゲーム用カウンタ

//======================================
//メッセージ処理用関数
//======================================
bool Luna::MessageProc(long Msg, long wParam, long lParam)
{
	switch(Msg)
	{
		/*キー押下イベント*/
		case WM_KEYDOWN:
		{
			switch(wParam)
			{
				case VK_ESCAPE:
				{
					if(Luna::SelectBox("終了確認", "終了しますか?") )
					{
						/*終了*/
						Luna::Exit();
					}
					
					break;
				}
				
				case VK_F1:
				{
					/*画面切替*/
					Luna::ChangeScreenMode();
					break;
				}
				
			}
			break;
		}
	}
	
	return true;
}

//======================================
//アプリケーション初期設定
//======================================
bool Luna::Init(void)
{
	/*出力ログ名*/
	//Luna::SetLogFileName("debug.log");
	
	/*アプリケーション名*/
	Luna::SetApplicationName("ノルフェウス");
	
	/*画面情報の設定*/
	Luna::SetScreenInfo(SCREEN_WIDTH, SCREEN_HEIGHT, true);
	
	/*フレームレート設定*/
	Luna::SetFrameRate(FRAME_RATE);
	
	/*アプリケーションのタイトルバーに情報表示*/
	//Luna::SetDrawTitleInfo();
	
	/*起動ログをウィンドウに出力*/
	//Luna::SetBootLogUse(true);
	
	/*コールバック関数設定*/
	//Luna::SetInitCallback(CallbackInit);
	
	/*使用するオプションを設定*/
	Luna::SetUseOption(OPTION_DIRECTINPUT | OPTION_DIRECTSHOW | OPTION_DIRECTSOUND);
	
	/*ファイル読み込み先*/
	LunaFile::SetRootPath(0, "data", "data.bin");
	
	LunaFile::SetCurrentDirectory("graphic");
	
	/*マウス描画*/
	Luna::SetDrawMouse();
	
	/*ダイアログモードセット*/
	Luna3D::SetDialogMode(true);
	
	/*2重起動許可*/
	//Luna::AllowMultiBoot();
	
	//Luna::SetVirtualScreenEnable(true);
	
	//Luna::SetVirtualScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	return true;
	
}

//================================================
//メインループ
//================================================
void Luna::Main(long ArgNum, char *pArgStr[])
{

	//----------------------------------------
	//全システムの開始
	//----------------------------------------	
	if(Luna::Start() )
	{
		//--------------------------------
		//初期化処理
		//--------------------------------
		InitProcess();
		
		//LunaInput::GetMouseData(&camera.Mouse);
		//LunaInput::GetMouseData(&camera.MouseOld);
		
		//--------------------------------
		//ゲーム用ループ
		//--------------------------------
		while(Luna::WaitForMsgLoop() )
		{
			
			/*画面クリア*/
			Luna3D::Clear(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, COLOR_BLACK, 1.0f);
			
			//Luna3D::Clear(D3DCLEAR_TARGET, COLOR_WHITE);
			
			/*デバッグ画面クリア*/
		//	LunaDebug::Clear();
			
			switch(g_GameMode)
			{
				case SCENE_INITIALIZE:
				{
					Initialize();
					break;
				}
				
				case SCENE_LOGO:
				{
					//DrawLogo();
					break;
				}
				
				case SCENE_TITLE:
				{
					DrawTitle();
					break;
				}
				
				case SCENE_CHARSEL:
				{
					DrawCharaSelect();
					break;
				}
				
				case SCENE_MAIN:
				{
					DrawMain();
					break;
				}
				
				case SCENE_OPTION:
				{
					DrawOption();
					break;
				}
				
				case SCENE_TUTOLIAL:
				{
					DrawTutorial();
					break;
				}
				
				case SCENE_PAUSE:
				{
					DrawPause();
					break;
				}
				
				case SCENE_PAUSEEXIT:
				{
					DrawPauseExit();
					break;
				}
				
				case SCENE_ERROR:
				{
					DrawError();
					break;
				}
				
				case SCENE_EXIT:
				{
					DrawExit();
					break;
				}
				
				case SCENE_FADEIN:
				{
					Fadein();
					break;
				}
				
				case SCENE_FADEOUT:
				{
					Fadeout();	
					break;
				}
				
				case SCENE_CONV:
				{
					Conversation();
					break;
				}
				
				case SCENE_GAMECLEAR:
				{
					DrawGameClear();
					break;
				}
				
				case SCENE_GAMEOVER:
				{
					DrawGameOver();
					break;
				}
				
				case SCENE_CONTINUE:
				{
					DrawContinue();
					break;
				}
				
				case SCENE_FINALIZE:
				{
					Finalize();
					break;
				}
				
			}
			
			/*画面更新*/
			Luna3D::Refresh();
			
			/*デバッグ処理*/
		//	Debug();
		}

		/*終了処理*/
		Finalize();
	}
}

//================================================
//初期処理
//================================================
void InitProcess(void)
{
	LoadSounds();
	
	player.LoadParam();
	player.SetGraphInfo();
	
	esystem.LoadPoint();
	
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].LoadParam();
		enemy[i].SetGraphInfo();
		enemy[i].SetStatus();
	}
	
	boss.Set(144, 144, 3);
	
	window.Set(0, 300, 640, 180);
	frame.Set(0, 0, 640, 480);
	screen.Set(0, 0, 640, 480);
	title.Set(0, 0, 640, 480);
	
	//--------------------------------
	//深度バッファ生成
	//--------------------------------
	lSurfZ = LunaSurface::CreateDepthStencil(SCREEN_WIDTH, SCREEN_HEIGHT, FORMAT_DEPTH32);
	
	/*デバイスに設定*/
	Luna3D::SetDepthStencilSurface(lSurfZ);
	
	/*ZバッファはON*/
	Luna3D::SetRenderState(D3DRS_ZENABLE, TRUE);
	Luna3D::SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	Luna3D::SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW );
	
	//--------------------------------
	//会話データ読み込み
	//--------------------------------
	window.LoadScriptData();

	//--------------------------------
	//フォグの設定
	//--------------------------------
	Luna3D::SetFogParameter(10, 150, COLOR_WHITE);
	
	/*パッド入力処理*/
	PadProcess();
	
	/*カラーキー処理ON*/
	Luna3D::SetColorkeyEnable(true);
	
	/*デバッグウィンドウOPEN*/
	//LunaDebug::OpenWindow();
	
	//-------------------------------
	//乱数初期値設定
	//-------------------------------
	LunaRand::Seed(100);

}

//================================================
//初期化
//================================================
void Initialize(void)
{
	g_Score = 0;
	g_gamecounter = 0;
	
	model.Initialize();
	camera.Initialize();
	tcamera.Initialize();
	
	player.Initialize();
	
	menu.Initialize();
	//pause.Initialize();
	//tuto_menu.Initialize();
	
	window.Initialize();
	
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].Initialize();
	}
	
	boss.Initialize();
	
	/*初期座標等セット*/
	player.SetPosition(200, 400);
	
	//--------------------------------
	//音読み込み
	//--------------------------------
	
	//--------------------------------
	//テクスチャ読み込み
	//--------------------------------
	LoadGraphics();
	
	//--------------------------------
	//カメラ生成
	//--------------------------------
	camera.Create();
	tcamera.Create();
	
	//--------------------------------
	//ライトの設定
	//--------------------------------
	SetLight();
	
	//--------------------------------
	//モデル生成
	//--------------------------------
	model.LoadData("field\\field_5_3.x", COLORKEY_DISABLE);
	
	//--------------------------------
	//フォント生成
	//--------------------------------
	window.CreateFontSprite();
	window.CreateFont();
	
	score.CreateFont();
	
	menu.CreateFontSprite();
	//pause.CreateFontSprite();
	//tuto_menu.CreateFontSprite();
	//mode.CreateFontSprite();
	menu.CreateFont();
	
	//--------------------------------
	//プリミティブ生成
	//--------------------------------
	lPrim = LunaPrimitive::Create(512, PRIM_VERTEX_UV0, false);

	/*モデルデータ変形*/
	//model.Translation();
	
	g_GameMode = SCENE_TITLE;
	
}

//================================================
//フェードイン
//================================================
void Fadein(void)
{
	/*バッファリセット*/
	LunaPrimitive::ResetBuffer(lPrim);
	
	Sint32 Alpha = toI(LunaAnimation::FlatSpeed( 255, 0, toF(FRAME_RATE), toF(g_Time) ));
	
	LUNARECT Dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	LunaEffect::FillSquare( lPrim, &Dst, PRIMITIVE_Z_CENTER, D3DCOLOR_ARGB(Alpha,0,0,0) );
	
	// １秒で次へ
	if ( ++g_Time >= FRAME_RATE )
	{
		g_Time = 0;
		
		g_GameMode = SCENE_INITIALIZE;
	}
	
	/*バッファ更新*/
	LunaPrimitive::UpdateBuffer(lPrim);
	
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetTexture(0, INVALID_TEXTURE);
		
		/*レンダリング*/
		LunaPrimitive::Rendering(lPrim);
		
		/*シーン終了*/
		Luna3D::EndScene();
	}

}

//================================================
//フェードアウト
//================================================
void Fadeout(void)
{
	/*バッファリセット*/
	LunaPrimitive::ResetBuffer(lPrim);
	
	Sint32 Alpha = L(LunaAnimation::FlatSpeed( 0.0f, 255.0f, toF(FRAME_RATE), toF(g_Time) ));

	LUNARECT Dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	LunaEffect::FillSquare( lPrim, &Dst, PRIMITIVE_Z_CENTER, D3DCOLOR_ARGB(Alpha, 0,0,0) );
	
	// １秒で次へ
	if ( ++g_Time >= FRAME_RATE )
	{
		g_Time = 0;
		g_GameMode = SCENE_FADEIN;
	}
	
	/*バッファ更新*/
	LunaPrimitive::UpdateBuffer(lPrim);
	
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetTexture(0, INVALID_TEXTURE);
		
		/*レンダリング*/
		LunaPrimitive::Rendering(lPrim);
		
		/*シーン終了*/
		Luna3D::EndScene();
	}
	
}

//================================================
//ロゴ画面描画
//================================================
void DrawLogo(void)
{

}


//================================================
//タイトル画面描画
//================================================
void DrawTitle(void)
{
	
	bgm[BGM_BOSS].StopSound();
	
	bgm[BGM_MAIN].StopSound();
	
	bgm[BGM_TITLE].PlaySoundA();
	
	frame.IsDisp = TRUE;
	
	/*モードセレクト*/
	menu.ModeSelect(&g_GameMode);
	
	LunaPrimitive::UpdateBuffer(lPrim);
	
	tcamera.Update();
	
	model.Translation();
	
	
	/*カーソル移動*/
	menu.Move(ITEM1_MAX);
	
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		menu.DrawCursor();
			
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		LunaPrimitive::Rendering(lPrim);
		
		model.Rendering();
		
		frame.DrawTexture();
		
		menu.Rendering();
		
		/*描画位置算出*/
		menu.CalcFontSprPos(100, 200, TitleMenu, ITEM1_MAX);
		
		menu.DrawFontSpr(TitleMenu, ITEM1_MAX);
	
		/*シーン終了*/
		Luna3D::EndScene();
	}
	
	
}

//================================================
//キャラクターセレクト画面描画
//================================================
void DrawCharaSelect(void)
{
	int LEFT = 200;
	int TOP = 100;
	int MOVE = 50;
	
	window.IsDisp = TRUE;
	
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		if(++g_Second % 20 == 0)
		{
			player.animcounter++;
		}
		
		window.DrawTexture();
		
		player.Draw(F(LEFT), F(TOP), player.first);
		player.Draw(F(LEFT), F(TOP+MOVE), player.second);
		player.Draw(F(LEFT), F(TOP+2*MOVE), player.third);
		
		switch(menu.Scene)
		{
			
			case SCENE_FIRST:
			{
				menu.CalcCharaPos(LEFT, TOP, MOVE);
			
				window.DrawFont("キャラの順番を選んでください");
				
				window.DrawFont(0, 50);
				
				menu.Move(3);
		
				menu.CharaSelect(&g_GameMode, &player.first, &player.second, &player.third);
	
				break;
			}
			
			case SCENE_SECOND:
			{
				window.DrawFont("キャラの順番を選んでください");
				
				window.DrawFont(0, 50);
				
				menu.CalcCharaPos(LEFT, TOP, MOVE);
			
				menu.Move(3);
		
				menu.CharaSelect(&g_GameMode, &player.first, &player.second, &player.third);
				
				break;
			}
			
			case SCENE_THIRD:
			{
				window.DrawFont("キャラの順番を選んでください");
				
				break;
			}
			
			case SCENE_END:
			{
				window.DrawFont("これでいいですか?");
				menu.CalcFontSprPos(200, 400, Menu6, 2);
				menu.DrawFontSpr(Menu6, 2);
				
				menu.CharaSelectExit(&g_GameMode);
				menu.Move(2);
				menu.DrawCursor();
				menu.Rendering();

				player.Type = player.first;
				break;
			}
		}
		
		/*シーン終了*/
		Luna3D::EndScene();
	}
	
	
}

//================================================
//ゲームクリア処理
//================================================
void DrawGameClear()
{
	bgm[BGM_BOSS].StopSound();
	
	window.IsDisp = TRUE;
	
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		window.DrawFont(200, 100, "GAME CLEAR");
		
		window.DrawTexture();
		
		window.ScriptTreat(&g_GameMode);
		
		window.RenderingFont();
	
		/*シーン終了*/
		Luna3D::EndScene();
	}	
	
}

//================================================
//ゲームオーバー処理
//================================================
void DrawGameOver(void)
{
	bgm[BGM_MAIN].StopSound();
	
	bgm[BGM_BOSS].StopSound();
	
	menu.Move(2);
	
	menu.CalcFontSprPos(200, 200, Menu5, 2);
	
	menu.GameOverSelect(&g_GameMode);
	
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		window.DrawFont(200, 100, "Game Over");
		
		menu.DrawFontSpr(Menu5, 2);
			
		menu.DrawCursor();
		
		menu.Rendering();

		/*シーン終了*/
		Luna3D::EndScene();
	}	
}

//================================================
//コンティニュー画面
//================================================
void DrawContinue()
{
	g_Score = 0;
	g_gamecounter = 0;
	
	model.Initialize();
	camera.Initialize();
	
	player.Initialize();
	
	menu.Initialize();
	//pause.Initialize();
	//tuto_menu.Initialize();
	
	window.Initialize();
	
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].Initialize();
	}
	
	boss.Initialize();
	
	/*初期座標等セット*/
	player.SetPosition(200, 400);
	
	//--------------------------------
	//テクスチャ読み込み
	//--------------------------------
	LoadGraphics();
	
	//--------------------------------
	//音読み込み
	//--------------------------------
	//LoadSounds();
	
	//--------------------------------
	//カメラ生成
	//--------------------------------
	camera.Create();
	
	g_GameMode = SCENE_MAIN;
	
}

//================================================
//ゲームメイン画面描画
//================================================
void DrawMain(void)
{
	frame.IsDisp = TRUE;
	
	/*当たり判定領域設定*/
	SetHitRect();
	
	g_Second++;
	
	if(!player.IsStop)
	{
		g_gamecounter++;
	}
	
	//------------------------------------------
	//アニメーション処理
	//------------------------------------------
	if(g_Second % 20 == 0)
	{
		player.animcounter++;

		if(!player.IsStop)
		{
			for(int i = 0;i < ENEMY_NUM;i++)
			{
				enemy[i].animcounter++;
			}
			
			boss.animcounter++;
		}
		
	}
	
	if(g_Second % 5 == 0)
	{
		if(!player.IsStop)
		{
			for(int i = 0;i < SKULL_NUM;i++)
			{
				boss.skull[i].animcounter++;
			}
			
			for(int i = 0;i < KNIFE_NUM;i++)
			{
				boss.knife[i].animcounter++;
			}
		}
		
	}

	/*ショット処理*/
	player.Shoot();
		
	/*当たり判定チェック*/
	CheckHitRect();
	
	//----------------------------------------
	//移動
	//----------------------------------------
	player.Move();
	
	/*敵の移動処理*/
	if(!player.IsStop)
	{
		EnemyMove();
		EnemyShoot();
	}
	
	/*ボスの移動処理*/
	if(!player.IsStop)
	{
		BossMove();
	}
	
	/*移動範囲補正*/
	MoveAdjust();
	
	player.UseGauge();
		
	//if(player.IsUseSpecial)
	//{
	//	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_03) )
	//	{
	//		player.IsUseSpecial = FALSE;
	//	}
	//}
		
	//-----------------------------------------------------
	//化身状態
	//-----------------------------------------------------
	
	/*ポーズ*/
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_05) )
	{
		g_GameMode = SCENE_PAUSE;
	}
	
	/*カメラ更新*/
	if(!player.IsStop)
	{
		camera.Update();
	}
	
	model.Translation();
	
	/*キャラクタ変更*/
	player.UseCharaChange();
	
	/*待機ライフ回復*/
	if(Luna::GetSyncCounter() % 20 == 0)
	{
		player.Recoverlife();
	}
	
	/*ゲームオーバー処理*/
	if(player.IsDead)
	{
		g_GameMode = SCENE_GAMEOVER;
	}
	
	/*ボス死亡処理*/
	boss.Dead(&g_GameMode);
	
	player.Draw();
	
	//----------------------------------
	//シーン開始
	//----------------------------------
	if ( Luna3D::BeginScene() )
	{
		/*レンダリング*/
		Luna3D::SetRenderState(D3DRS_FOGENABLE, TRUE);
		
		model.Rendering();
		
		if(player.IsStop)
		{
			screen.IsDisp = TRUE;
			
			Luna3D::SetBlendingType(BLEND_REVERSE);
			screen.DrawTexture();
			Luna3D::SetBlendingType(BLEND_NORMAL);
		}
		
		Luna3D::SetRenderState(D3DRS_FOGENABLE, FALSE);
		
		Luna3D::SetFilterEnable(TRUE);
		
		/*敵出現ポイント*/
		EnemyPoint();
		
		frame.DrawTexture();
		
		player.Rendering();
		
		score.DrawFont(g_Score);
	
		boss.Rendering();
		
		// シーン終了
		Luna3D::EndScene();
	}
	
}

//================================================
//チュートリアル画面描画
//================================================
void DrawTutorial(void)
{
	menu.Move(ITEM4_MAX);
	
	g_Second++;
	
	if(Luna3D::BeginScene() )
	{
		/*描画*/
		DrawMethod();
		
		Luna3D::EndScene();
	}
	
}

//================================================
//オプション画面描画
//================================================
void DrawOption(void)
{
	/*カーソル移動*/
	menu.Move(ITEM2_MAX);
	
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		g_Second++;
		
		/*描画*/
		DrawMethod();
		
		/*キーコンフィグ*/
		menu.KeyConfig(&g_GameMode);
		
		
		/*シーン終了*/
		Luna3D::EndScene();
	}
}

//================================================
//ポーズ画面描画
//================================================
void DrawPause(void)
{
	menu.Move(ITEM3_MAX);
	
	menu.CalcFontSprPos(100, 100, Menu3, ITEM3_MAX);
	menu.DrawFontSpr(Menu3, ITEM3_MAX);
	
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		menu.PauseSelect(&g_GameMode);
		
		g_Second++;
		
		/*シーン終了*/
		Luna3D::EndScene();
	}
}

//================================================
//ポーズ終了確認画面
//================================================
void DrawPauseExit()
{
	menu.Move(2);
	
	menu.DrawFont(50, 100, "タイトルに戻りますか?");
	menu.CalcFontSprPos(100, 200, Menu6, 2);
	menu.DrawFontSpr(Menu6, 2);
	
	menu.DrawCursor();
	
	menu.PauseExitSelect(&g_GameMode);
	
	menu.Rendering();
}

//================================================
//エラー画面描画
//================================================
void DrawError(void)
{
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		g_GameMode = SCENE_TITLE;
	}
	
	/*シーン開始*/
	if(Luna3D::BeginScene() )
	{
		/*描画*/
		DrawMethod();
		
		/*シーン終了*/
		Luna3D::EndScene();
	}
}

//================================================
//会話画面描画
//================================================
void Conversation()
{
	window.IsDisp = TRUE;
	
	frame.IsDisp = TRUE;
	
	for(int i = 0;i < BULLET_MAX;i++)
	{
		if(player.bullet.Flag[i])
		{
			player.bullet.Flag[i] = FALSE;
		}
	}
	
	player.Draw();
	
	boss.Draw();
	
	boss.Dead(&g_GameMode);
	
	if(Luna::GetSyncCounter() % 20 == 0)
	{
		boss.animcounter++;
	}
	
	camera.Update();
	
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		/*レンダリング*/
		Luna3D::SetRenderState(D3DRS_FOGENABLE, TRUE);
			
		/*レンダリング*/
		model.Rendering();
		
		Luna3D::SetRenderState(D3DRS_FOGENABLE, FALSE);
		
		player.Rendering();

		boss.Rendering();
		
		frame.DrawTexture();
		
		window.DrawTexture();
		
		window.ScriptFaceData();
		
		window.ScriptTreat(&g_GameMode);
		
		window.RenderingFont();
	
		score.DrawFont(g_Score);
		
		Luna3D::EndScene();	
	}
	
}




//================================================
//終了画面
//================================================
void DrawExit(void)
{
	/*移動*/
	menu.Move(2);
	
	/*描画位置算出*/
	menu.CalcFontSprPos(100, 200, Menu6, 2);
	
	menu.Select(&g_GameMode);
	
	menu.DrawFont(100, 50, "ゲームを終了しますか?");
	
	/*描画*/
	menu.DrawFontSpr(Menu6, 2);
	
	/*カーソル描画*/
	menu.DrawCursor();
	
	/*レンダリング*/
	menu.Rendering();
}

//================================================
//画像読み込み
//================================================
void LoadGraphics(void)
{
	player.LoadImage();
	
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].LoadImage();
	}
	
	boss.LoadImage("boss\\jack.png", COLORKEY_WHITE);
	
	menu.LoadImage();
	
	window.LoadImage("system\\window.png", COLORKEY_DISABLE);
	window.LoadImage();
	frame.LoadImage("system\\flame.png", COLORKEY_WHITE);
	screen.LoadImage("sysyem\\screen.png", COLORKEY_WHITE);
	title.LoadImageA("system\\title.png", COLORKEY_WHITE);
}

//================================================
//音読み込み
//================================================
void LoadSounds(void)
{
	char *bgmname[] =
	{
		"sound\\title.ogg",
		"sound\\field.ogg",
		"sound\\jack.ogg",
		"sound\\gameover.ogg",
	};
	
	for(int i = 0;i < BGM_NUM;i++)
	{
		bgm[i].LoadSound(bgmname[i]);
	}	
	
	object.LoadSound();
	
	player.LoadSound();
	
	menu.LoadSound();
	
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].LoadSound();
	}
	
	boss.LoadSound();
	
	
	
	
}

//================================================
//ライトの設定
//================================================
void SetLight(void)
{
	/*ライト種類*/
	LunaLight::SetLightType(0, LIGHT_DIRECTION);

	/*ライト色*/
	LunaLight::SetDiffuse(0, 0.1f, 0.1f, 0.1f);
	
	/*ライト方向*/
	LVECTOR3 vDir(1, -1, 2);
	LunaLight::SetDirection(0, &vDir);
	
	/*ライトセット*/
	Luna3D::SetLight(0, true);

}

//================================================
//描画
//================================================
void DrawMethod(void)
{
	switch(g_GameMode)
	{
		case SCENE_LOGO:
		{
			break;
		}
		
		case SCENE_TITLE:
		{
			break;
		}
		
		case SCENE_CHARSEL:
		{
			break;
		}
		
		case SCENE_MAIN:
		{

		}
		
		case SCENE_OPTION:
		{
			menu.DrawCursor();
			/*描画位置算出*/
			menu.CalcFontPos(100, 200, ITEM2_MAX);
			
			menu.DrawFont(Menu2, ITEM2_MAX);
			
			break;
		}
		
		case SCENE_TUTOLIAL:
		{
			window.DrawTexture();
			//window.DrawFont("Test");
			
			window.DrawMessage(menu.Cursor);
			
			menu.DrawCursor();
			
			/*描画位置算出*/
			menu.CalcFontSprPos(100, 100, Menu4, ITEM4_MAX);
			
			menu.DrawFontSpr(Menu4, ITEM4_MAX);
			
			break;
		}
		
		case SCENE_PAUSE:
		{
			break;
		}
		
		case SCENE_ERROR:
		{
			menu.DrawErrorMessage();
			break;
		}
	}
	
}

//================================================
//移動範囲補正
//================================================
void MoveAdjust(void)
{
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].MoveAdjust(MINI_RANGE_X, MAX_RANGE_X, MINI_RANGE_Y, MAX_RANGE_Y);
	}
	
	boss.MoveAdjust(MINI_RANGE_X, MAX_RANGE_X, MINI_RANGE_Y, MAX_RANGE_Y);
	
}

//================================================
//当たり判定領域セット
//================================================
void SetHitRect(void)
{
	player.SetRect();

	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].SetRect();
	}

	boss.SetRect();
	
}

//================================================
//当たり判定チェック
//================================================
void CheckHitRect(void)
{
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		/*プレイヤーと敵との判定*/
		object.CheckHitRect(player, enemy[i]);
		
		/*イスラ弾と敵との判定*/
		object.CheckHitRect(player.bullet, enemy[i]);
		
		/*アメウス弾と敵との判定*/
		for(int j = 0;j < AME_NUM;j++)
		{
			object.CheckHitRect(player.amebullet[j], enemy[i]);
		}
		
		/*チャージショットと敵との判定*/
		object.CheckHitRect(player.charge, enemy[i]);
		
		/*傘と敵との判定*/
		object.CheckHitRect(player.umbrella, enemy[i]);
		
		/*分身弾と敵との判定*/
		object.CheckHitRect(player.shadow.bullet, enemy[i]);
		
		/*敵弾とプレイヤーとの判定*/
		object.CheckHitRect(enemy[i].bullet, player);
		
	}
	
	/*プレイヤーとボスとの判定*/
	object.CheckHitRect(player, boss);
	
	/*プレイヤー弾とボスとの判定*/
	object.CheckHitRect(player.bullet, boss);
	
	/*アメウス弾とボスとの判定*/
	for(int i = 0;i < AME_NUM;i++)
	{
		object.CheckHitRect(player.amebullet[i], boss);
	}
	
	/*チャージショットとボスとの判定*/
	object.CheckHitRect(player.bullet, player.charge, boss);
	
	/*傘とボスとの判定*/
	object.CheckHitRect(player.umbrella,  boss);
	
	/*分身弾と敵との判定*/
	object.CheckHitRect(player.shadow.bullet, boss);
	
	/*ボス弾とプレイヤーとの判定*/
	object.CheckHitRect(boss.bullet, player);
	
	/*ドクロとプレイヤーとの判定*/
	for(int i = 0;i < SKULL_NUM;i++)
	{
		object.CheckHitRect(player.bullet, boss.skull[i]);
		object.CheckHitRect(boss.skull[i], player);
		object.CheckHitRect(boss.skull[i].bullet, player);
	}
	
	/*ナイフとプレイヤーとの判定*/
	for(int i = 0;i < KNIFE_NUM;i++)
	{
		object.CheckHitRect(boss.knife[i], player);
	}
}

//================================================
//プレイヤーのショット処理
//================================================
void PlayerShoot(void)
{
	
}

//================================================
//敵の移動
//================================================
void EnemyMove(void)
{
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].MovePattern(player.Get_PosX(), player.Get_PosY() );
	}
}

//================================================
//敵のショット処理
//================================================
void EnemyShoot(void)
{
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].ShootPattern(player.Get_PosX(), player.Get_PosY() );
	}
	
}

//================================================
//ボスの動き
//================================================
void BossMove(void)
{
	if(boss.IsExist)
	{
		boss.Move(&g_GameMode, player.Get_PosX(), player.Get_PosY() );
		
		boss.Shoot(player.Get_PosX(), player.Get_PosY() );
	}
}

//================================================
//敵出現ポイント
//================================================
void EnemyPoint(void)
{
	const int POINT_BOSS = 10800;
	
	//if(g_gamecounter > 0 && g_gamecounter < POINT_BOSS)
	//{
	//	bgm[BGM_TITLE].StopSound();
	//	
	//	bgm[BGM_MAIN].PlaySoundA();
	//}
	
	if(g_gamecounter > 0)
	{
		bgm[BGM_MAIN].StopSound();
		
		bgm[BGM_BOSS].PlaySoundA();
	}
	
	//for(int i = 0;i < ENEMY_NUM;i++)
	//{
	//	if(g_gamecounter == esystem.epoint[i].point)
	//	{
	//		enemy[i].SetPosition(LunaRand::GetFloat(0.0, 400.0), F(-100) );
	//		enemy[i].IsExist = TRUE;
	//	}
	//	
	//	enemy[i].Draw( (eEnemyType)(esystem.epoint[i].Type) );
	//	enemy[i].Rendering();
	//	
	//}
	//

	
	if(g_gamecounter == 100)
	//if(g_gamecounter == 100)
	{
		boss.SetPosition( F(150), F(-180) );
		boss.IsExist = TRUE;
	}
	
	boss.Draw();
	
}

//================================================
//スコア計算
//================================================
void AddScore(int Score)
{
	g_Score += Score;
}

//================================================
//終了処理
//================================================
void Finalize(void)
{
	LunaPrimitive::Release(lPrim);
	
	player.Release();
	
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].Release();
	}
	
	boss.Release();
	
	menu.Release();
	
	window.Release();
	
	frame.Release();
	screen.Release();
	score.Release();
	
	model.Release();

	camera.Release();
	
	LunaSurface::Release(lSurfZ);
	
	/*デバッグウィンドウCLOSE*/
	//LunaDebug::CloseWindow();
	
	for(int i = 0;i < BGM_NUM;i++)
	{
		bgm[i].Release();
	}
	
	//g_GameMode = SCENE_TITLE;
	
}

//================================================
//デバッグ用
//================================================
void Debug(void)
{
	player.Debug();
	//bullet.Debug();
	//shadow.Debug();
	//umbrella.Debug();
	//boss.Debug();
	
	//enemy[0].Debug();
	//model.Debug();
	//camera.Debug();
	//enemy[4].Debug();
	//esystem.Debug();
	
	
	//charge.Debug();
	//menu.Debug();
	
	//window.Debug();
	
	LunaDebug::DrawString("gamecounter:%d", g_gamecounter);
	LunaDebug::DrawString("Score:%d\n", g_Score);
	
	
	//LunaDebug::DrawString("Time:%d")
	//Debug(model);
	//camera.Debug();

}
