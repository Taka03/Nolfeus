//================================================
//include
//================================================
#include "field.h"

//================================================
//�������֐�
//================================================
void Init_Field(FieldData &field)
{
	field.Field = INVALID_FIELD;
	field.lShaderFx = INVALID_SHADERFX;
}


//================================================
//�ǂݍ���
//================================================
void Load_Field(FieldData &field, char *name, Sint32 ZoomSize, int ColorKey)
{
	field.Field = LunaField::CreateFromFile(name, 5, ZoomSize, FORMAT_TEXTURE_3D, false, ColorKey);
}

//================================================
//�r���[�t���X�^���J�����O
//================================================
void ViewFrustumCulling(FieldData &field)
{
	LunaField::ViewfrustumCulling(field.Field);
}

//================================================
//�����_�����O
//================================================
void Rendering_Field(FieldData &field)
{
	LunaField::Rendering(field.Field);
}

//================================================
//�V�F�[�_�[�ݒ�
//================================================
void SetShader(FieldData &field)
{
	/*�t�B�[���h�p�G�t�F�N�g�t�@�C��*/
	field.lShaderFx = LunaShaderFx::CreateFromFile("field00.fx");
		
	/*�t�B�[���h�ɃV�F�[�_�[�ݒ�*/
	LunaField::SetEffectHandle(field.Field, field.lShaderFx);
	
	LunaShaderFx::Release(field.lShaderFx);
		
	LunaField::SetEffectSendData(field.Field, FX_SEND_TRANSFORM | FX_SEND_FOGDATA);
	
}

//================================================
//�������J��
//================================================
void Release_Field(FieldData &field)
{
	LunaField::Release(field.Field);
	LunaShaderFx::Release(field.lShaderFx);
}

