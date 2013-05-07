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
	
	    float Vx;//移動速度X
		float Vy;//移動速度Y
	    
		float fDistance;
		float fDistance2;
		float fDistance3;
	    
		bool IsLoop;//ループしたかどうか
	    
		Sint32 Angle;//角度
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
	    
		
		
		void Initialize();//初期化
		void Create();//カメラ生成
		void ChangeCordinate();//座標変換
		void Change();
		void Move();//カメラの移動
		void Update();//カメラ更新
		void Release();//カメラメモリ開放
		void Debug();//デバッグ用
	
};

