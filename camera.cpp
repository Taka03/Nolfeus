//================================================
//include
//================================================
#include "camera.h"
#include "gamemode.h"

//================================================
//�R���X�g���N�^
//================================================
CCameraData::CCameraData()
{

}

//================================================
//�f�X�g���N�^
//================================================
CCameraData::~CCameraData()
{

}

//================================================
//�J�����������֐�
//================================================
void CCameraData::Initialize()
{
	//Vx = 0.0f;
	//Vy = 0.0f;
	//
	//Angle = GET_ANGLE(30);
	//
	//fDistance = 30.0f;
	//Pitch = GET_ANGLE(30);
	//RotY = GET_ANGLE(30);
	//
	//vEye.Set(100, 200, 0);
	//vPos.Set(100, 500, -100);
	//
	//IsLoop = FALSE;
	
	RotX = 900;
	RotY = 2500;
	
	Vx = 0.0f;
	Vy = 0.0f;
	
	Angle = GET_ANGLE(30);
	
	//camera.vEye.Set(-100, -100, -100);
	vEye.Set(0, 0, -100);
	vUp.Set(0, 1, 0);
	vPos.Set(300, 200, -250);
	
	IsLoop = FALSE;
	
	Mouse.W = 0;
	
}

//================================================
//�J���������֐�
//================================================
void CCameraData::Create()
{
	//mProjection.Perspective(PI / 3, 1, 1000, F(SCREEN_WIDTH)/F(SCREEN_HEIGHT) );
	//mProjection.RotationX(Angle);
	
	lCam = LunaCamera::Create();
	LunaCamera::CreateProjection(lCam, PI / 3, 1, 1000, F(SCREEN_WIDTH)/F(SCREEN_HEIGHT) );
	
	vPos.Set(20, 72, -1050);
	vEye.Set(vPos.x, vPos.y-200, vPos.z+200);
	
}

void CCameraData::Change()
{
	//Angle += GET_ANGLE(1);
	
	if(vPos.z >=172*3+50)
	{
		Vy = 0;
	}
	
	else
	{
		Vy = 0.15;
	}
	
	//MouseOld = Mouse;
	//LunaInput::GetMouseData(&Mouse);
	
	//
	//if(Mouse.StateL == MOUSE_HOLD)
	//{
	//	RotY += (Mouse.Y - MouseOld.Y) * 50;
	//	RotX += (Mouse.X - MouseOld.X) * 50;
	//	
		//if(Pitch > GET_ANGLE(90) )
		//{
		//	Pitch = GET_ANGLE(90);
		//}
		//
		//if(Pitch < GET_ANGLE(-90) )
		//{
		//	Pitch = GET_ANGLE(-90);
		//}
	//}
	//
	//if(Mouse.StateR == MOUSE_HOLD)
	//{
	//	fDistance += F(Mouse.Y - MouseOld.Y);
	//	fDistance2 += F(Mouse.X - MouseOld.X);
	//}
	//
	//if(Mouse.StateW == MOUSE_HOLD)
	//{
	//	fDistance3 -= (Mouse.Y - MouseOld.Y);
	//}
		
	//vPos.Set(fDistance2, 200+fDistance, -250+fDistance3);
	//vEye.Set(vPos.x, fDistance, fDistance3);

	LunaCamera::LookAt(lCam, &vPos, &vEye, &vUp);
	
	LunaCamera::RotationX(lCam, RotY);
	
	LunaCamera::RotationY(lCam, RotX);
	
	Move();
	
	LunaCamera::Translation(lCam, vPos.x, vPos.y, vPos.z);
	
	//LunaCamera::RotationZ(camera.lCam, 5000);
	
	/*�ϊ��X�V*/
	LunaCamera::TransformUpdate(lCam);
	
	/*�f�o�C�X�ɐݒ�*/
	Luna3D::SetCamera(lCam);

}

//================================================
//�J�����X�V
//================================================
void CCameraData::Update()
{
	Change();
	//
	//Style.TransformInit();
	//Style.Pitching(Pitch);
	//Style.RotationY(RotY);
	//Style.TransformUpdate();
	//
	//Style.GetUp(&vUp);
	//Style.GetFront(&vFront);
	//Style.GetRight(&vRight);
	//
	//if(Mouse.StateR == MOUSE_HOLD)
	//{
	//	vPos.x -= F(Mouse.X - MouseOld.X) * vRight.x * 0.1f;
	//	vPos.y -= F(Mouse.X - MouseOld.X) * vRight.y * 0.1f;
	//	vPos.z -= F(Mouse.X - MouseOld.X) * vRight.z * 0.1f;
	//	
	//	vPos.x -= F(Mouse.Y - MouseOld.Y) * vUp.x * 0.1f;
	//	vPos.y -= F(Mouse.Y - MouseOld.Y) * vUp.y * 0.1f;
	//	vPos.z -= F(Mouse.Y - MouseOld.Y) * vUp.z * 0.1f;
	//	
	//}
	//
	//vEye.x = -vFront.x * fDistance + vPos.x;
	//vEye.y = -vFront.y * fDistance + vPos.y;
	//vEye.z = -vFront.z * fDistance + vPos.z;
	//
	//Style.LookAt(&vEye, &vPos, &vUp);
	//LunaCamera::SetMatrixDirect(&mProjection, &mCamera); 
}

//================================================
//�J�����ړ�
//================================================
void CCameraData::Move()
{
	vPos.x += Vx;
	vPos.z += Vy;
	vEye.z += Vy;
}

//================================================
//���W�ϊ�
//================================================
void CCameraData::ChangeCordinate()
{
//	Luna3D::ScreenToWorld(&pWorldPos, &pScreenPos);
}

//================================================
//�J�����������J��
//================================================
void CCameraData::Release()
{
	LunaCamera::Release(lCam);
}

//================================================
//�f�o�b�O
//================================================
void CCameraData::Debug()
{
	LunaDebug::DrawString("vPos.x:%f", vPos.x);
	LunaDebug::DrawString("vPos.y:%f", vPos.y);
	LunaDebug::DrawString("vPos.z:%f", vPos.z);
	
	LunaDebug::DrawString("vEye.x:%f", vEye.x);
	LunaDebug::DrawString("vEye.y:%f", vEye.y);
	LunaDebug::DrawString("vEye.z:%f", vEye.z);
	
	
	LunaDebug::DrawString("RotX:%d", RotX);
	LunaDebug::DrawString("RotY:%d", RotY);
	LunaDebug::DrawString("Pitch:%d", Pitch);
	LunaDebug::DrawString("Angle:%d", Angle);
}