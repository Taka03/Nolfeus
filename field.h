//================================================
//include
//================================================
#include "Luna.h"
#ifndef __FIELD_H__
#define __FIRLD_H__

//================================================
//class
//================================================
struct FieldData
{
	LFIELD Field;
	LSHADERFX lShaderFx;
	
};

//================================================
//�֐��̃v���g�^�C�v�錾
//================================================
void Init_Field(FieldData &field);//������
void Load_Field(FieldData &field, char *name, Sint32 ZoomSize, int ColorKey);//�t�B�[���h�ǂݍ���
void ViewFrustumCulling(FieldData &field);//�r���[�t���X�^���J�����O

void Rendering_Field(FieldData &field);//�����_�����O����
void SetShader(FieldData &field);//�V�F�[�_�[�ݒ�
void Release_Field(FieldData &field);//�������J��


#endif