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
//3D�A�_�v�^��������R�[���o�b�N�֐�
//=============================================================================
/*void CallbackInit(void)
{

	//-------------------------------------------
	//�s�N�Z���V�F�[�_��HAL�Ŏg�p�ł��邩�`�F�b�N
	//-------------------------------------------
	if(!Luna3D::CheckPixelShaderSupport(2, 0) )
	{
		Luna3D::EnableEmulationMode();
	}

}*/


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
					/*�I��*/
					Luna::Exit();
					
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
	Luna::SetLogFileName("debug.log");
	
	/*�A�v���P�[�V������*/
	Luna::SetApplicationName("Sample");
	
	/*��ʏ��̐ݒ�*/
	Luna::SetScreenInfo(SCREEN_WIDTH, SCREEN_HEIGHT, true);
	
	/*�t���[�����[�g�ݒ�*/
	Luna::SetFrameRate(FRAME_RATE);
	
	/*�A�v���P�[�V�����̃^�C�g���o�[�ɏ��\��*/
	Luna::SetDrawTitleInfo();
	
	/*�N�����O���E�B���h�E�ɏo��*/
	//Luna::SetBootLogUse(true);
	
	/*�R�[���o�b�N�֐��ݒ�*/
	//Luna::SetInitCallback(CallbackInit);
	
	/*�g�p����I�v�V������ݒ�*/
	Luna::SetUseOption(OPTION_DIRECTINPUT | OPTION_DIRECTSHOW | OPTION_DIRECTSOUND);
	
	/*�t�@�C���ǂݍ��ݐ�*/
	LunaFile::SetRootPath(0, "data", "data.bin");
	
	/*�t�@�C�������f�B���N�g��*/
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