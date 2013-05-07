//================================================
//model.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"

//================================================
//class
//================================================
class CModelData
{
	private:

		float fPosX;
		float fPosY;
		float fPosZ;
				
		LMODELEX lModel;
		
	public:
	
		void Initialize(void);//�������֐�
		void LoadData(char *name, int ColorKey);//���f���̓ǂݍ���
		void Translation(void);//�ό`
		void Rendering(void);//���f���̃����_�����O
		void Release(void);//���f���̃������J��
		void Debug(void);//�f�o�b�O�p
	
};

