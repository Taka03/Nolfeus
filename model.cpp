//================================================
//include
//================================================
#include "model.h"

//================================================
//���f���������֐�
//================================================
void CModelData::Initialize()
{
	fPosX = 100;
	fPosY = 0;
	fPosZ = 0;
	
}

//================================================
//���f���f�[�^�ǂݍ���
//================================================
void CModelData::LoadData(char *name, int ColorKey)
{
	lModel = LunaModelEx::CreateFromFile(name, FORMAT_TEXTURE_3D, ColorKey);
	
	LunaModelEx::AutoCreateShader(lModel, AUTO_SHADER_NORMAL_NOLIGHT);
	
}

//================================================
//���f���f�[�^�ό`
//================================================
void CModelData::Translation()
{
	/*�ϊ�������*/
	LunaModelEx::TransformInit(lModel);
	
	/*�ړ�*/
	//LunaModel::Translation(lModel, 0, 0, 0);
	
	/*�g��*/
	LunaModelEx::Scaling(lModel, 2, 2, 2);
	
	/*��]*/
	//LunaModelEx::RotationY(lModel, GET_ANGLE(-5) );
	
	/*�ϊ��X�V*/
	LunaModelEx::TransformUpdate(lModel);
	
}

//================================================
//���f���f�[�^�����_�����O
//================================================
void CModelData::Rendering()
{
	LunaModelEx::Rendering(lModel);
}

//================================================
//���f���f�[�^�������J��
//================================================
void CModelData::Release()
{
	LunaModelEx::Release(lModel);
}

//================================================
//���f���f�[�^�f�o�b�O
//================================================
void CModelData::Debug()
{
	LunaDebug::DrawString("Px:%f", fPosX);
	LunaDebug::DrawString("Py:%f", fPosY);
	LunaDebug::DrawString("Pz:%f", fPosZ);
}