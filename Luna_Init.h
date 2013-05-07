//======================================
//Luna_Init.h
//======================================
#pragma once

//======================================
//include
//======================================
#include "Luna.h"

//======================================
//define
//======================================
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define FRAME_RATE     60

//=============================================================================
//3Dアダプタ初期化後コールバック関数
//=============================================================================
/*void CallbackInit(void)
{

	//-------------------------------------------
	//ピクセルシェーダがHALで使用できるかチェック
	//-------------------------------------------
	if(!Luna3D::CheckPixelShaderSupport(2, 0) )
	{
		Luna3D::EnableEmulationMode();
	}

}*/


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
					/*終了*/
					Luna::Exit();
					
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
	Luna::SetLogFileName("debug.log");
	
	/*アプリケーション名*/
	Luna::SetApplicationName("Sample");
	
	/*画面情報の設定*/
	Luna::SetScreenInfo(SCREEN_WIDTH, SCREEN_HEIGHT, true);
	
	/*フレームレート設定*/
	Luna::SetFrameRate(FRAME_RATE);
	
	/*アプリケーションのタイトルバーに情報表示*/
	Luna::SetDrawTitleInfo();
	
	/*起動ログをウィンドウに出力*/
	//Luna::SetBootLogUse(true);
	
	/*コールバック関数設定*/
	//Luna::SetInitCallback(CallbackInit);
	
	/*使用するオプションを設定*/
	Luna::SetUseOption(OPTION_DIRECTINPUT | OPTION_DIRECTSHOW | OPTION_DIRECTSOUND);
	
	/*ファイル読み込み先*/
	LunaFile::SetRootPath(0, "data", "data.bin");
	
	/*ファイル検索ディレクトリ*/
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