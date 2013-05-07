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
//�v���g�^�C�v�錾
//================================================
void InitProcess(void);//��������
void Initialize(void);//������
void DrawLogo(void);//���S���
void DrawTitle(void);//�^�C�g�����
void DrawCharaSelect(void);//�L�����N�^�[�Z���N�g���
void DrawMain(void);//���C�����
void DrawOption(void);//�I�v�V�������
void DrawTutorial(void);//�`���[�g���A�����	
void DrawGameOver(void);//�Q�[���I�[�o�[���
void DrawGameClear(void);//�Q�[���N���A���
void DrawPause(void);//�|�[�Y���
void DrawPauseExit(void);//�|�[�Y�I���m�F���
void DrawError(void);//�G���[���
void Conversation(void);//��b���
void DrawContinue(void);//�R���e�B�j���[�������
void DrawExit(void);//�I���m�F���
void Finalize(void);//�I������

void AddScore(int Score);//�X�R�A�v�Z
void EnemyPoint(void);//�G�o���|�C���g
void DrawMethod(void);//�`��
void CreateSprite(void);//�X�v���C�g����
void SetLight(void);//���C�g�̐ݒ�
void MoveAdjust(void);//�ړ��͈͕␳
void SetHitRect(void);//�����蔻��Z�b�g
void CheckHitRect(void);//�����蔻��`�F�b�N
void PlayerShoot(void);//�v���C���[�̃V���b�g����
void EnemyShoot(void);//�G�̃V���b�g����
void EnemyMove(void);//�G�̓���
void BossMove(void);//�{�X�̓���
void LoadGraphics(void);//�摜�ǂݍ���
void LoadSounds(void);//���ǂݍ���
void Release(void);//�������J��
void Debug(void);//�f�o�b�O�p

