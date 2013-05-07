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

/*�N���X�̐錾*/
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

int g_GameMode = SCENE_INITIALIZE;//�Q�[�����[�h�ؑ�

int g_Second = 0;//����

LSURFACE lSurfZ = INVALID_SURFACE;
LPRIMITIVE lPrim = INVALID_PRIMITIVE;

Sint32 g_Score = 0;//�X�R�A
Sint32 g_Time = 0;//�t�F�[�h�p
Sint32 g_gamecounter = 0;//�Q�[���p�J�E���^

//======================================
//���b�Z�[�W�����p�֐�
//======================================
bool Luna::MessageProc(long Msg, long wParam, long lParam)
{
	switch(Msg)
	{
		/*�L�[�����C�x���g*/
		case WM_KEYDOWN:
		{
			switch(wParam)
			{
				case VK_ESCAPE:
				{
					if(Luna::SelectBox("�I���m�F", "�I�����܂���?") )
					{
						/*�I��*/
						Luna::Exit();
					}
					
					break;
				}
				
				case VK_F1:
				{
					/*��ʐؑ�*/
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
//�A�v���P�[�V���������ݒ�
//======================================
bool Luna::Init(void)
{
	/*�o�̓��O��*/
	//Luna::SetLogFileName("debug.log");
	
	/*�A�v���P�[�V������*/
	Luna::SetApplicationName("�m���t�F�E�X");
	
	/*��ʏ��̐ݒ�*/
	Luna::SetScreenInfo(SCREEN_WIDTH, SCREEN_HEIGHT, true);
	
	/*�t���[�����[�g�ݒ�*/
	Luna::SetFrameRate(FRAME_RATE);
	
	/*�A�v���P�[�V�����̃^�C�g���o�[�ɏ��\��*/
	//Luna::SetDrawTitleInfo();
	
	/*�N�����O���E�B���h�E�ɏo��*/
	//Luna::SetBootLogUse(true);
	
	/*�R�[���o�b�N�֐��ݒ�*/
	//Luna::SetInitCallback(CallbackInit);
	
	/*�g�p����I�v�V������ݒ�*/
	Luna::SetUseOption(OPTION_DIRECTINPUT | OPTION_DIRECTSHOW | OPTION_DIRECTSOUND);
	
	/*�t�@�C���ǂݍ��ݐ�*/
	LunaFile::SetRootPath(0, "data", "data.bin");
	
	LunaFile::SetCurrentDirectory("graphic");
	
	/*�}�E�X�`��*/
	Luna::SetDrawMouse();
	
	/*�_�C�A���O���[�h�Z�b�g*/
	Luna3D::SetDialogMode(true);
	
	/*2�d�N������*/
	//Luna::AllowMultiBoot();
	
	//Luna::SetVirtualScreenEnable(true);
	
	//Luna::SetVirtualScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	return true;
	
}

//================================================
//���C�����[�v
//================================================
void Luna::Main(long ArgNum, char *pArgStr[])
{

	//----------------------------------------
	//�S�V�X�e���̊J�n
	//----------------------------------------	
	if(Luna::Start() )
	{
		//--------------------------------
		//����������
		//--------------------------------
		InitProcess();
		
		//LunaInput::GetMouseData(&camera.Mouse);
		//LunaInput::GetMouseData(&camera.MouseOld);
		
		//--------------------------------
		//�Q�[���p���[�v
		//--------------------------------
		while(Luna::WaitForMsgLoop() )
		{
			
			/*��ʃN���A*/
			Luna3D::Clear(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, COLOR_BLACK, 1.0f);
			
			//Luna3D::Clear(D3DCLEAR_TARGET, COLOR_WHITE);
			
			/*�f�o�b�O��ʃN���A*/
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
			
			/*��ʍX�V*/
			Luna3D::Refresh();
			
			/*�f�o�b�O����*/
		//	Debug();
		}

		/*�I������*/
		Finalize();
	}
}

//================================================
//��������
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
	//�[�x�o�b�t�@����
	//--------------------------------
	lSurfZ = LunaSurface::CreateDepthStencil(SCREEN_WIDTH, SCREEN_HEIGHT, FORMAT_DEPTH32);
	
	/*�f�o�C�X�ɐݒ�*/
	Luna3D::SetDepthStencilSurface(lSurfZ);
	
	/*Z�o�b�t�@��ON*/
	Luna3D::SetRenderState(D3DRS_ZENABLE, TRUE);
	Luna3D::SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	Luna3D::SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW );
	
	//--------------------------------
	//��b�f�[�^�ǂݍ���
	//--------------------------------
	window.LoadScriptData();

	//--------------------------------
	//�t�H�O�̐ݒ�
	//--------------------------------
	Luna3D::SetFogParameter(10, 150, COLOR_WHITE);
	
	/*�p�b�h���͏���*/
	PadProcess();
	
	/*�J���[�L�[����ON*/
	Luna3D::SetColorkeyEnable(true);
	
	/*�f�o�b�O�E�B���h�EOPEN*/
	//LunaDebug::OpenWindow();
	
	//-------------------------------
	//���������l�ݒ�
	//-------------------------------
	LunaRand::Seed(100);

}

//================================================
//������
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
	
	/*�������W���Z�b�g*/
	player.SetPosition(200, 400);
	
	//--------------------------------
	//���ǂݍ���
	//--------------------------------
	
	//--------------------------------
	//�e�N�X�`���ǂݍ���
	//--------------------------------
	LoadGraphics();
	
	//--------------------------------
	//�J��������
	//--------------------------------
	camera.Create();
	tcamera.Create();
	
	//--------------------------------
	//���C�g�̐ݒ�
	//--------------------------------
	SetLight();
	
	//--------------------------------
	//���f������
	//--------------------------------
	model.LoadData("field\\field_5_3.x", COLORKEY_DISABLE);
	
	//--------------------------------
	//�t�H���g����
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
	//�v���~�e�B�u����
	//--------------------------------
	lPrim = LunaPrimitive::Create(512, PRIM_VERTEX_UV0, false);

	/*���f���f�[�^�ό`*/
	//model.Translation();
	
	g_GameMode = SCENE_TITLE;
	
}

//================================================
//�t�F�[�h�C��
//================================================
void Fadein(void)
{
	/*�o�b�t�@���Z�b�g*/
	LunaPrimitive::ResetBuffer(lPrim);
	
	Sint32 Alpha = toI(LunaAnimation::FlatSpeed( 255, 0, toF(FRAME_RATE), toF(g_Time) ));
	
	LUNARECT Dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	LunaEffect::FillSquare( lPrim, &Dst, PRIMITIVE_Z_CENTER, D3DCOLOR_ARGB(Alpha,0,0,0) );
	
	// �P�b�Ŏ���
	if ( ++g_Time >= FRAME_RATE )
	{
		g_Time = 0;
		
		g_GameMode = SCENE_INITIALIZE;
	}
	
	/*�o�b�t�@�X�V*/
	LunaPrimitive::UpdateBuffer(lPrim);
	
	/*�V�[���J�n*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetTexture(0, INVALID_TEXTURE);
		
		/*�����_�����O*/
		LunaPrimitive::Rendering(lPrim);
		
		/*�V�[���I��*/
		Luna3D::EndScene();
	}

}

//================================================
//�t�F�[�h�A�E�g
//================================================
void Fadeout(void)
{
	/*�o�b�t�@���Z�b�g*/
	LunaPrimitive::ResetBuffer(lPrim);
	
	Sint32 Alpha = L(LunaAnimation::FlatSpeed( 0.0f, 255.0f, toF(FRAME_RATE), toF(g_Time) ));

	LUNARECT Dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	LunaEffect::FillSquare( lPrim, &Dst, PRIMITIVE_Z_CENTER, D3DCOLOR_ARGB(Alpha, 0,0,0) );
	
	// �P�b�Ŏ���
	if ( ++g_Time >= FRAME_RATE )
	{
		g_Time = 0;
		g_GameMode = SCENE_FADEIN;
	}
	
	/*�o�b�t�@�X�V*/
	LunaPrimitive::UpdateBuffer(lPrim);
	
	/*�V�[���J�n*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetTexture(0, INVALID_TEXTURE);
		
		/*�����_�����O*/
		LunaPrimitive::Rendering(lPrim);
		
		/*�V�[���I��*/
		Luna3D::EndScene();
	}
	
}

//================================================
//���S��ʕ`��
//================================================
void DrawLogo(void)
{

}


//================================================
//�^�C�g����ʕ`��
//================================================
void DrawTitle(void)
{
	
	bgm[BGM_BOSS].StopSound();
	
	bgm[BGM_MAIN].StopSound();
	
	bgm[BGM_TITLE].PlaySoundA();
	
	frame.IsDisp = TRUE;
	
	/*���[�h�Z���N�g*/
	menu.ModeSelect(&g_GameMode);
	
	LunaPrimitive::UpdateBuffer(lPrim);
	
	tcamera.Update();
	
	model.Translation();
	
	
	/*�J�[�\���ړ�*/
	menu.Move(ITEM1_MAX);
	
	/*�V�[���J�n*/
	if(Luna3D::BeginScene() )
	{
		menu.DrawCursor();
			
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		LunaPrimitive::Rendering(lPrim);
		
		model.Rendering();
		
		frame.DrawTexture();
		
		menu.Rendering();
		
		/*�`��ʒu�Z�o*/
		menu.CalcFontSprPos(100, 200, TitleMenu, ITEM1_MAX);
		
		menu.DrawFontSpr(TitleMenu, ITEM1_MAX);
	
		/*�V�[���I��*/
		Luna3D::EndScene();
	}
	
	
}

//================================================
//�L�����N�^�[�Z���N�g��ʕ`��
//================================================
void DrawCharaSelect(void)
{
	int LEFT = 200;
	int TOP = 100;
	int MOVE = 50;
	
	window.IsDisp = TRUE;
	
	/*�V�[���J�n*/
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
			
				window.DrawFont("�L�����̏��Ԃ�I��ł�������");
				
				window.DrawFont(0, 50);
				
				menu.Move(3);
		
				menu.CharaSelect(&g_GameMode, &player.first, &player.second, &player.third);
	
				break;
			}
			
			case SCENE_SECOND:
			{
				window.DrawFont("�L�����̏��Ԃ�I��ł�������");
				
				window.DrawFont(0, 50);
				
				menu.CalcCharaPos(LEFT, TOP, MOVE);
			
				menu.Move(3);
		
				menu.CharaSelect(&g_GameMode, &player.first, &player.second, &player.third);
				
				break;
			}
			
			case SCENE_THIRD:
			{
				window.DrawFont("�L�����̏��Ԃ�I��ł�������");
				
				break;
			}
			
			case SCENE_END:
			{
				window.DrawFont("����ł����ł���?");
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
		
		/*�V�[���I��*/
		Luna3D::EndScene();
	}
	
	
}

//================================================
//�Q�[���N���A����
//================================================
void DrawGameClear()
{
	bgm[BGM_BOSS].StopSound();
	
	window.IsDisp = TRUE;
	
	/*�V�[���J�n*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		window.DrawFont(200, 100, "GAME CLEAR");
		
		window.DrawTexture();
		
		window.ScriptTreat(&g_GameMode);
		
		window.RenderingFont();
	
		/*�V�[���I��*/
		Luna3D::EndScene();
	}	
	
}

//================================================
//�Q�[���I�[�o�[����
//================================================
void DrawGameOver(void)
{
	bgm[BGM_MAIN].StopSound();
	
	bgm[BGM_BOSS].StopSound();
	
	menu.Move(2);
	
	menu.CalcFontSprPos(200, 200, Menu5, 2);
	
	menu.GameOverSelect(&g_GameMode);
	
	/*�V�[���J�n*/
	if(Luna3D::BeginScene() )
	{
		Luna3D::SetBlendingType(BLEND_NORMAL);
		
		window.DrawFont(200, 100, "Game Over");
		
		menu.DrawFontSpr(Menu5, 2);
			
		menu.DrawCursor();
		
		menu.Rendering();

		/*�V�[���I��*/
		Luna3D::EndScene();
	}	
}

//================================================
//�R���e�B�j���[���
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
	
	/*�������W���Z�b�g*/
	player.SetPosition(200, 400);
	
	//--------------------------------
	//�e�N�X�`���ǂݍ���
	//--------------------------------
	LoadGraphics();
	
	//--------------------------------
	//���ǂݍ���
	//--------------------------------
	//LoadSounds();
	
	//--------------------------------
	//�J��������
	//--------------------------------
	camera.Create();
	
	g_GameMode = SCENE_MAIN;
	
}

//================================================
//�Q�[�����C����ʕ`��
//================================================
void DrawMain(void)
{
	frame.IsDisp = TRUE;
	
	/*�����蔻��̈�ݒ�*/
	SetHitRect();
	
	g_Second++;
	
	if(!player.IsStop)
	{
		g_gamecounter++;
	}
	
	//------------------------------------------
	//�A�j���[�V��������
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

	/*�V���b�g����*/
	player.Shoot();
		
	/*�����蔻��`�F�b�N*/
	CheckHitRect();
	
	//----------------------------------------
	//�ړ�
	//----------------------------------------
	player.Move();
	
	/*�G�̈ړ�����*/
	if(!player.IsStop)
	{
		EnemyMove();
		EnemyShoot();
	}
	
	/*�{�X�̈ړ�����*/
	if(!player.IsStop)
	{
		BossMove();
	}
	
	/*�ړ��͈͕␳*/
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
	//���g���
	//-----------------------------------------------------
	
	/*�|�[�Y*/
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_05) )
	{
		g_GameMode = SCENE_PAUSE;
	}
	
	/*�J�����X�V*/
	if(!player.IsStop)
	{
		camera.Update();
	}
	
	model.Translation();
	
	/*�L�����N�^�ύX*/
	player.UseCharaChange();
	
	/*�ҋ@���C�t��*/
	if(Luna::GetSyncCounter() % 20 == 0)
	{
		player.Recoverlife();
	}
	
	/*�Q�[���I�[�o�[����*/
	if(player.IsDead)
	{
		g_GameMode = SCENE_GAMEOVER;
	}
	
	/*�{�X���S����*/
	boss.Dead(&g_GameMode);
	
	player.Draw();
	
	//----------------------------------
	//�V�[���J�n
	//----------------------------------
	if ( Luna3D::BeginScene() )
	{
		/*�����_�����O*/
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
		
		/*�G�o���|�C���g*/
		EnemyPoint();
		
		frame.DrawTexture();
		
		player.Rendering();
		
		score.DrawFont(g_Score);
	
		boss.Rendering();
		
		// �V�[���I��
		Luna3D::EndScene();
	}
	
}

//================================================
//�`���[�g���A����ʕ`��
//================================================
void DrawTutorial(void)
{
	menu.Move(ITEM4_MAX);
	
	g_Second++;
	
	if(Luna3D::BeginScene() )
	{
		/*�`��*/
		DrawMethod();
		
		Luna3D::EndScene();
	}
	
}

//================================================
//�I�v�V������ʕ`��
//================================================
void DrawOption(void)
{
	/*�J�[�\���ړ�*/
	menu.Move(ITEM2_MAX);
	
	/*�V�[���J�n*/
	if(Luna3D::BeginScene() )
	{
		g_Second++;
		
		/*�`��*/
		DrawMethod();
		
		/*�L�[�R���t�B�O*/
		menu.KeyConfig(&g_GameMode);
		
		
		/*�V�[���I��*/
		Luna3D::EndScene();
	}
}

//================================================
//�|�[�Y��ʕ`��
//================================================
void DrawPause(void)
{
	menu.Move(ITEM3_MAX);
	
	menu.CalcFontSprPos(100, 100, Menu3, ITEM3_MAX);
	menu.DrawFontSpr(Menu3, ITEM3_MAX);
	
	/*�V�[���J�n*/
	if(Luna3D::BeginScene() )
	{
		menu.PauseSelect(&g_GameMode);
		
		g_Second++;
		
		/*�V�[���I��*/
		Luna3D::EndScene();
	}
}

//================================================
//�|�[�Y�I���m�F���
//================================================
void DrawPauseExit()
{
	menu.Move(2);
	
	menu.DrawFont(50, 100, "�^�C�g���ɖ߂�܂���?");
	menu.CalcFontSprPos(100, 200, Menu6, 2);
	menu.DrawFontSpr(Menu6, 2);
	
	menu.DrawCursor();
	
	menu.PauseExitSelect(&g_GameMode);
	
	menu.Rendering();
}

//================================================
//�G���[��ʕ`��
//================================================
void DrawError(void)
{
	if(LunaPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		g_GameMode = SCENE_TITLE;
	}
	
	/*�V�[���J�n*/
	if(Luna3D::BeginScene() )
	{
		/*�`��*/
		DrawMethod();
		
		/*�V�[���I��*/
		Luna3D::EndScene();
	}
}

//================================================
//��b��ʕ`��
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
		
		/*�����_�����O*/
		Luna3D::SetRenderState(D3DRS_FOGENABLE, TRUE);
			
		/*�����_�����O*/
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
//�I�����
//================================================
void DrawExit(void)
{
	/*�ړ�*/
	menu.Move(2);
	
	/*�`��ʒu�Z�o*/
	menu.CalcFontSprPos(100, 200, Menu6, 2);
	
	menu.Select(&g_GameMode);
	
	menu.DrawFont(100, 50, "�Q�[�����I�����܂���?");
	
	/*�`��*/
	menu.DrawFontSpr(Menu6, 2);
	
	/*�J�[�\���`��*/
	menu.DrawCursor();
	
	/*�����_�����O*/
	menu.Rendering();
}

//================================================
//�摜�ǂݍ���
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
//���ǂݍ���
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
//���C�g�̐ݒ�
//================================================
void SetLight(void)
{
	/*���C�g���*/
	LunaLight::SetLightType(0, LIGHT_DIRECTION);

	/*���C�g�F*/
	LunaLight::SetDiffuse(0, 0.1f, 0.1f, 0.1f);
	
	/*���C�g����*/
	LVECTOR3 vDir(1, -1, 2);
	LunaLight::SetDirection(0, &vDir);
	
	/*���C�g�Z�b�g*/
	Luna3D::SetLight(0, true);

}

//================================================
//�`��
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
			/*�`��ʒu�Z�o*/
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
			
			/*�`��ʒu�Z�o*/
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
//�ړ��͈͕␳
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
//�����蔻��̈�Z�b�g
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
//�����蔻��`�F�b�N
//================================================
void CheckHitRect(void)
{
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		/*�v���C���[�ƓG�Ƃ̔���*/
		object.CheckHitRect(player, enemy[i]);
		
		/*�C�X���e�ƓG�Ƃ̔���*/
		object.CheckHitRect(player.bullet, enemy[i]);
		
		/*�A���E�X�e�ƓG�Ƃ̔���*/
		for(int j = 0;j < AME_NUM;j++)
		{
			object.CheckHitRect(player.amebullet[j], enemy[i]);
		}
		
		/*�`���[�W�V���b�g�ƓG�Ƃ̔���*/
		object.CheckHitRect(player.charge, enemy[i]);
		
		/*�P�ƓG�Ƃ̔���*/
		object.CheckHitRect(player.umbrella, enemy[i]);
		
		/*���g�e�ƓG�Ƃ̔���*/
		object.CheckHitRect(player.shadow.bullet, enemy[i]);
		
		/*�G�e�ƃv���C���[�Ƃ̔���*/
		object.CheckHitRect(enemy[i].bullet, player);
		
	}
	
	/*�v���C���[�ƃ{�X�Ƃ̔���*/
	object.CheckHitRect(player, boss);
	
	/*�v���C���[�e�ƃ{�X�Ƃ̔���*/
	object.CheckHitRect(player.bullet, boss);
	
	/*�A���E�X�e�ƃ{�X�Ƃ̔���*/
	for(int i = 0;i < AME_NUM;i++)
	{
		object.CheckHitRect(player.amebullet[i], boss);
	}
	
	/*�`���[�W�V���b�g�ƃ{�X�Ƃ̔���*/
	object.CheckHitRect(player.bullet, player.charge, boss);
	
	/*�P�ƃ{�X�Ƃ̔���*/
	object.CheckHitRect(player.umbrella,  boss);
	
	/*���g�e�ƓG�Ƃ̔���*/
	object.CheckHitRect(player.shadow.bullet, boss);
	
	/*�{�X�e�ƃv���C���[�Ƃ̔���*/
	object.CheckHitRect(boss.bullet, player);
	
	/*�h�N���ƃv���C���[�Ƃ̔���*/
	for(int i = 0;i < SKULL_NUM;i++)
	{
		object.CheckHitRect(player.bullet, boss.skull[i]);
		object.CheckHitRect(boss.skull[i], player);
		object.CheckHitRect(boss.skull[i].bullet, player);
	}
	
	/*�i�C�t�ƃv���C���[�Ƃ̔���*/
	for(int i = 0;i < KNIFE_NUM;i++)
	{
		object.CheckHitRect(boss.knife[i], player);
	}
}

//================================================
//�v���C���[�̃V���b�g����
//================================================
void PlayerShoot(void)
{
	
}

//================================================
//�G�̈ړ�
//================================================
void EnemyMove(void)
{
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].MovePattern(player.Get_PosX(), player.Get_PosY() );
	}
}

//================================================
//�G�̃V���b�g����
//================================================
void EnemyShoot(void)
{
	for(int i = 0;i < ENEMY_NUM;i++)
	{
		enemy[i].ShootPattern(player.Get_PosX(), player.Get_PosY() );
	}
	
}

//================================================
//�{�X�̓���
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
//�G�o���|�C���g
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
//�X�R�A�v�Z
//================================================
void AddScore(int Score)
{
	g_Score += Score;
}

//================================================
//�I������
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
	
	/*�f�o�b�O�E�B���h�ECLOSE*/
	//LunaDebug::CloseWindow();
	
	for(int i = 0;i < BGM_NUM;i++)
	{
		bgm[i].Release();
	}
	
	//g_GameMode = SCENE_TITLE;
	
}

//================================================
//�f�o�b�O�p
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
