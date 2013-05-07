//================================================
//camera.h
//================================================
#pragma once

//================================================
//include
//================================================
#include "Luna.h"

//================================================
//struct
//================================================

class CCameraData
{
	private:
	
	    float Vx;//�ړ����xX
		float Vy;//�ړ����xY
	    
		float fDistance;
		float fDistance2;
		float fDistance3;
	    
		bool IsLoop;//���[�v�������ǂ���
	    
		Sint32 Angle;//�p�x
		Sint32 Pitch;
		Sint32 RotY;
		Sint32 RotX;
	    
		LVECTOR3 vPos;
	    
		LMATRIX mProjection;
		LMATRIX mCamera;
		LSTYLE Style;
		LVECTOR3 vUp;
		LVECTOR3 vFront;
		LVECTOR3 vRight;
		LVECTOR3 vEye;
	    
		LCAMERA lCam;
	
	public:

		CCameraData();
		virtual ~CCameraData();
		
		MOUSEDATA Mouse;
		MOUSEDATA MouseOld;
	    
		
		
		void Initialize();//������
		void Create();//�J��������
		void ChangeCordinate();//���W�ϊ�
		void Change();
		void Move();//�J�����̈ړ�
		void Update();//�J�����X�V
		void Release();//�J�����������J��
		void Debug();//�f�o�b�O�p
	
};

