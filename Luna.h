//==============================================================================//
//				DirectX9�p�ėp���C�u���� Luna									//
//==============================================================================//
//																				//
//	�ŐV�ł̒u���Ă���URL														//
//																				//
//		TWINTAIL LOVERS.														//
//			http://www.twin-tail.jp/											//
//																				//
//	���ⓙ�����ꏊ																//
//																				//
//		BBS																		//
//			TWINTAIL LOVERS.���̌f����											//
//																				//
// DirectX Library "Luna for DirectX 9.0c"										//
// Copyright (C) 2003-2005 �t���`												//
// All rights reserved.															//
//																				//
//==============================================================================//
#ifndef ___LUNA_DX9___
#define ___LUNA_DX9___


//================================================================================
// WARNING
//================================================================================
#pragma warning ( disable: 4127 )		// �萔�̏�����
#pragma warning ( disable: 4100 )		// ���Q�Ƃ̕ϐ�
#pragma warning ( disable: 4514 )		// ���Q�Ƃ̃C�����C���֐�
#pragma warning ( disable: 4711 )		// �����C�����C���W�J
#pragma warning ( disable: 4201 )		// �\���̊g�����[�j���O
#pragma warning ( disable: 4996 )		// �Â��`��
#pragma warning ( disable: 4819 )		// Unicode

#pragma inline_depth ( 255 )
#pragma inline_recursion ( on )


//=============================================================================
// FOR MSVC6.0
//=============================================================================
#if (_MSC_VER == 1200)
	#define for				if ( false ) ; else for
	typedef long			LONG_PTR;
	typedef unsigned long	DWORD_PTR;
	typedef void (__stdcall *PAPCFUNC)( DWORD_PTR dwParam );
#endif


//=============================================================================
// FOR BORLAND COMPILER
//=============================================================================
#ifdef __BORLAND__
#define __MT__
#endif // __BORLAND__


//================================================================================
// INCLUDE
//================================================================================
#define DIRECTINPUT_VERSION		(0x0800)			///< DirectInput�o�[�W������`
#define _WIN32_WINNT			(0x0400)			///< Fiber�p
#define WIN32_LEAN_AND_MEAN							///< �s�v�ȃw�b�_�̎Q�ƍ폜
#define STRSAFE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mbstring.h>
#include <tchar.h>
#include <wchar.h>
#include <windows.h>
#include <winsock2.h>
#include <shellapi.h>
#include <process.h>
#include <commdlg.h>
#include <strsafe.h>
#include <shlobj.h>
#include <imm.h>
#include <vfw.h>
#include <objbase.h>
#include <basetsd.h>

#include <d3dx9xof.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>
#include <dinput.h>
#include <dmusicc.h>
#include <dmusici.h>
#include <dshow.h>
#include <mmstream.h>
#include <amstream.h>
#include <ddstream.h>
#include <vmr9.h>


//================================================================================
// TYPEDEF
//================================================================================
typedef char					Sint8;								///< signed char �^�̕ʒ�`
typedef short					Sint16;								///< signed short �^�̕ʒ�`
typedef long					Sint32;								///< signed long �^�̕ʒ�`
typedef __int64					Sint64;								///< signed __int64 �^�̕ʒ�`
typedef unsigned char			Uint8;								///< unsigned char �^�̕ʒ�`
typedef unsigned short			Uint16;								///< unsigned short �^�̕ʒ�`
typedef unsigned long			Uint32;								///< unsigned long �^�̕ʒ�`
typedef unsigned __int64		Uint64;								///< unsigned __int64 �^�̕ʒ�`
typedef float					Float;								///< Float �^�̕ʒ�`
typedef float					Float32;							///< Float �^�̕ʒ�`
typedef double					Float64;							///< double �^�̕ʒ�`
typedef long double				Float80;							///< long double �^�̕ʒ�`
typedef bool					Bool;								///< Bool �^�̕ʒ�`


typedef Bool (*PCALLBACKSOCKETPROC)( HWND hWnd, long Id );			///< �\�P�b�g�����p�R�[���o�b�N�֐�
typedef void (WINAPI *PFIBERPROC)( void *pParameter );				///< �}�C�N���X���b�h�p�R�[���o�b�N�֐�
typedef Bool (*PMICROTHREADPROC)( void *pParameter );				///< �X���b�h�p�R�[���o�b�N�֐�
typedef IDirect3D9 * (WINAPI *PDIRECT3DCREATE9)( unsigned int );	///< Direct3D�I�u�W�F�N�g�����֐��p


//================================================================================
// DEFINE
//================================================================================
static const Sint32 OPTION_DIRECTINPUT			= (1 <<  0);						///< DirectInput���g�p���ăL�[���͂��s��
static const Sint32 OPTION_DIRECTSOUND			= (1 <<  1);						///< DirectSound�����g�p���ăT�E���h�Đ����s��
static const Sint32 OPTION_DIRECTMUSIC			= (1 <<  2);						///< DirectMusic���g�p���ăT�E���h�Đ����s��
static const Sint32 OPTION_DIRECTSHOW			= (1 <<  3);						///< DirectShow���g�p���ă��[�r�[�̍Đ�������
static const Sint32 OPTION_CDDA					= (1 <<  4);						///< MCI���g�p����CDDA���g�p����
static const Sint32 OPTION_FIBER				= (1 <<  5);						///< Fiber���g�p���ă^�X�N����������


static const Sint32 FX_SEND_TRANSFORM			= (1 <<  0);
static const Sint32 FX_SEND_WORLDMATRIX			= (1 <<  1);
static const Sint32 FX_SEND_WORLDVIEWMATRIX		= (1 <<  2);
static const Sint32 FX_SEND_BONEDATA			= (1 <<  3);
static const Sint32 FX_SEND_LIGHTDATA			= (1 <<  4);
static const Sint32 FX_SEND_MATERIALDATA		= (1 <<  5);
static const Sint32 FX_SEND_SLIDE_UV			= (1 <<  6);
static const Sint32 FX_SEND_VERTEXEXTRUCT		= (1 <<  7);
static const Sint32 FX_SEND_MORPFWEIGHT			= (1 <<  8);
static const Sint32 FX_SEND_CAMERAPOS			= (1 <<  9);
static const Sint32 FX_SEND_TEXTURE				= (1 << 10);
static const Sint32 FX_SEND_FOGDATA				= (1 << 11);


//================================================================================
// CLASS TYPEDEF
//================================================================================
typedef class CVector2D			LVECTOR2;
typedef class CVector3D			LVECTOR3;
typedef class CMatrix			LMATRIX;
typedef class CQuaternion		LQUATERNION;
typedef class CStyle			LSTYLE;




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
/**
	@brief	�x�N�g�����Z�N���X

	�x�N�g���֘A�̏��������e�Ղɂ��邽�߂̃N���X�ł��B
	D3DXVECTOR2�^����̔h���Ȃ̂ŃL���X�g���邱�ƂȂ�
	���̂܂ܓ����悤�Ɏg�����Ƃ��o���܂��B

    @todo	------------------------
    @bug	------------------------
*/
//=============================================================================
class CVector2D : public D3DXVECTOR2
{
public:
	//==========================================================================
	/**	�R���X�g���N�^
	*/
	//==========================================================================
	CVector2D()
	{
	}

	//==========================================================================
	/**	�R���X�g���N�^

		@param v		[in] �������Ɏg���x�N�g��
	*/
	//==========================================================================
	CVector2D( const CVector2D &v )
	{
		*this = v;
	}

	//==========================================================================
	/**	�R���X�g���N�^

		@param fPx		[in] �������Ɏg���w�l
		@param fPy		[in] �������Ɏg���x�l
	*/
	//==========================================================================
	CVector2D( Float fPx, Float fPy )
	{
		x = fPx;
		y = fPy;
	}

	void Add( CVector2D *pIn1, CVector2D *pIn2 );					///< �w�肵���x�N�g���̉��Z���擾
	void Sub( CVector2D *pIn1, CVector2D *pIn2 );					///< �w�肵���x�N�g���̌��Z���擾
	void Set( Float fPx, Float fPy );							///< �x�N�g����ݒ�

	Float LengthSq( void );										///< �����̓����擾
	Float Length( void );										///< �������擾
	Float DotProduct( CVector2D *pIn );							///< �w��x�N�g���Ƃ̓���
	void Reflect( CVector2D *pIn1, CVector2D *pIn2 );				///< �w��x�N�g���Ɣ��˃x�N�g���ł̔���

	void Normalize( void );										///< ���K��
	Float CrossProduct( CVector2D *pIn1, CVector2D *pIn2 );		///< �w��x�N�g���Ƃ̊O��

	void Normalize( CVector2D *pIn );							///< �w��x�N�g������̖�����
	Float CrossProduct( CVector2D *pIn );						///< �w��x�N�g������̊O��
	void Reflect( CVector2D *pIn );								///< ���˃x�N�g���ł̔���

	void Scaling( Float sx, Float sy );							///< �g��k��
	void Translation( Float px, Float py );						///< �ړ�

	CVector2D& operator += ( const CVector2D& );
	CVector2D& operator -= ( const CVector2D& );
	CVector2D& operator *= ( Float );
	CVector2D& operator /= ( Float );

	// unary operators
	CVector2D operator + () const;
	CVector2D operator - () const;

	// binary operators
	CVector2D operator + ( const CVector2D& ) const;
	CVector2D operator - ( const CVector2D& ) const;
	CVector2D operator * ( Float ) const;
	CVector2D operator / ( Float ) const;
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
/**
	@brief	�x�N�g�����Z�N���X

	�x�N�g���֘A�̏��������e�Ղɂ��邽�߂̃N���X�ł��B
	D3DXVECTOR3�^����̔h���Ȃ̂ŃL���X�g���邱�ƂȂ�
	���̂܂ܓ����悤�Ɏg�����Ƃ��o���܂��B

    @todo	------------------------
    @bug	------------------------
*/
//=============================================================================
class CVector3D : public D3DXVECTOR3
{
public:
	//==========================================================================
	/**	�R���X�g���N�^
	*/
	CVector3D()
	{
	}

	//==========================================================================
	/**	�R���X�g���N�^

		@param v		[in] �������Ɏg���x�N�g��
	*/
	CVector3D( const CVector3D &v )
	{
		*this = v;
	}

	//==========================================================================
	/**	�R���X�g���N�^

		@param v		[in] �������Ɏg���x�N�g��
	*/
	CVector3D( const D3DXVECTOR3 &v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	//==========================================================================
	/**	�R���X�g���N�^

		@param fPx		[in] �������Ɏg���w�l
		@param fPy		[in] �������Ɏg���x�l
		@param fPz		[in] �������Ɏg���y�l
	*/
	CVector3D( Float fPx, Float fPy, Float fPz )
	{
		x = fPx;
		y = fPy;
		z = fPz;
	}

	void Add( CVector3D *pIn1, CVector3D *pIn2 );							///< �x�N�g�����Z
	void Sub( CVector3D *pIn1, CVector3D *pIn2 );							///< �x�N�g�����Z
	void Set( Float fPx, Float fPy, Float fPz );						///< �x�N�g���ݒ�

	Float LengthSq( void );												///< �����̓��擾
	Float Length( void );												///< �����擾
	Float DotProduct( CVector3D *pIn );									///< �w��x�N�g���Ƃ̓��ώ擾

	void Normalize( void );												///< ���K��
	void CrossProduct( CVector3D *pIn1, CVector3D *pIn2 );				///< �w�肳�ꂽ�Q�x�N�g���Ƃ̊O�ώ擾
	void Reflect( CVector3D *pIn1, CVector3D *pIn2 );						///< �w�肳�ꂽ�Q�x�N�g���Ƃ̔��˃x�N�g���擾
	void TransformNormal( CVector3D *pIn1, class CMatrix *pIn2 );		///< �w��x�N�g���ł̖@���ϊ�
	void TransformCoord( CVector3D *pIn1, class CMatrix *pIn2 );			///< �w��x�N�g���ł̍��W�ϊ�
	void TransformProjection( CVector3D *pIn1, class CMatrix *pIn2 );	///< �w��x�N�g���ł̓����ϊ�

	void Normalize( CVector3D *pIn );									///< �w��x�N�g���𐳋K��
	void CrossProduct( CVector3D *pIn );									///< �w��x�N�g���Ƃ̊O�ώ擾
	void Reflect( CVector3D *pIn );										///< �w��x�N�g���ł̔��˃x�N�g�����擾
	void TransformNormal( class CMatrix *pIn );							///< �w��s��ł̖@���ϊ�
	void TransformCoord( class CMatrix *pIn );							///< �w��s��ł̍��W�ϊ�
	void TransformProjection( class CMatrix *pIn );						///< �w��s��ł̓����ϊ�

	void RotationX( Sint32 Angle );										///< �w����]������
	void RotationY( Sint32 Angle );										///< �x����]������
	void RotationZ( Sint32 Angle );										///< �y����]������
	void RotationAxis( Sint32 Angle, CVector3D *pAxis );					///< �C�ӎ���]������
	void Rotation( Sint32 rotx, Sint32 roty, Sint32 rotz );					///< �R���ŉ�]������
	void Scaling( Float sx, Float sy, Float sz );						///< �X�P�[�����O������
	void Translation( Float px, Float py, Float pz );					///< �ړ�������

	CVector3D& operator += ( const CVector3D& );
	CVector3D& operator -= ( const CVector3D& );
	CVector3D& operator *= ( Float );
	CVector3D& operator /= ( Float );

	CVector3D operator + () const;
	CVector3D operator - () const;

	CVector3D operator + ( const CVector3D& ) const;
	CVector3D operator - ( const CVector3D& ) const;
	CVector3D operator * ( Float ) const;
	CVector3D operator / ( Float ) const;
};



//=============================================================================
// INCLUDE
//=============================================================================


class CVector3D;


//=============================================================================
/**
	@brief	�s��N���X

	�s���e�ՂɈ�����悤�ɂ����N���X�ł��B
	Direct3DX�̕⏕�֐���SSE��3DNow�ł̉��Z��
	�⍲���邽�߂ɓ����I��16Byte�P�ʂŎ����I��
	�A���C�����g����܂��B
	���̂��߁A�����o�ɒ��ڃA�N�Z�X�ł��Ȃ��Ȃǂ�
	�s�ւȓ_������܂��B
*/
//=============================================================================
class CMatrix
{
	Uint8 Data[sizeof(D3DXMATRIX) + 16];															///< �s��p�f�[�^
	D3DXMATRIX *m_Ptr;																				///< �s��擪�A�h���X

public:
	CMatrix();																						///< �R���X�g���N�^
	CMatrix( CMatrix &Mat );																		///< �R���X�g���N�^
	CMatrix( D3DMATRIX &Mat );																		///< �R���X�g���N�^
	CMatrix( D3DXMATRIX &Mat );																		///< �R���X�g���N�^
	CMatrix(																						///< �R���X�g���N�^
		Float _11, Float _12, Float _13, Float _14,
		Float _21, Float _22, Float _23, Float _24,
		Float _31, Float _32, Float _33, Float _34,
		Float _41, Float _42, Float _43, Float _44 );
	~CMatrix(){}																					///< �f�X�g���N�^

	void Identity( void );																			///< �C�Ӎs���P�ʉ�
	void Transpose( CMatrix *pIn );																	///< �C�Ӎs���]�u
	void Inverse( CMatrix *pIn );																	///< �C�Ӎs����t�s��
	void Normalize( CMatrix *pIn );																	///< �C�Ӎs��𐳋K��
	void Multiply( CMatrix *pIn1, CMatrix *pIn2 );													///< �C�Ӎs�������

	void Transpose( void );																			///< �]�u
	void Inverse( void );																			///< �t�s��
	void Normalize( void );																			///< ���K��
	void Multiply( CMatrix *pIn );																	///< ����

	void RotationX( Sint32 Angle );																	///< �w����]�s�񐶐�
	void RotationY( Sint32 Angle );																	///< �x����]�s�񐶐�
	void RotationZ( Sint32 Angle );																	///< �y����]�s�񐶐�
	void RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );								///< �R����]�s�񐶐�
	void RotationAxis( Sint32 Angle, CVector3D *pAxis );											///< �C�ӎ���]�s�񐶐�
	void Rotation( Sint32 rotx, Sint32 roty, Sint32 rotz );											///< �R����]�s�񐶐�
	void Scaling( Float sx, Float sy, Float sz );													///< �g��k���s�񐶐�
	void Translation( Float px, Float py, Float pz );												///< �ړ��s�񐶐�
	void RotateVector( CVector3D *pIn1, CVector3D *pIn2, CVector3D *pAxis = NULL );					///< �C�Ӄx�N�g������C�Ӄx�N�g���ւ̉�]�s�񐶐�

	void Perspective( Float fov, Float near_z, Float far_z, Float aspect );							///< �����ϊ��p�s��̐���
	void Ortho( Float w, Float h, Float near_z, Float far_z );										///< ���ˉe�s�񐶐�

	void LookAt( CVector3D *pEye, CVector3D *pAt, CVector3D *pUp );									///< �����p�̍s������

	void Move( class CVector2D *pPos );
	void Move( CVector3D *pPos );

	void Resolution( CVector3D &vPos, CVector3D &vScale, CMatrix &mRot );

	operator       D3DMATRIX&  ()       { return *m_Ptr; }
	operator       D3DXMATRIX& ()       { return *m_Ptr; }
	operator const D3DMATRIX&  () const { return *m_Ptr; }
	operator const D3DXMATRIX& () const { return *m_Ptr; }

	operator       D3DMATRIX*  ()       { return m_Ptr; }
	operator       D3DXMATRIX* ()       { return m_Ptr; }
	operator const D3DMATRIX*  () const { return m_Ptr; }
	operator const D3DXMATRIX* () const { return m_Ptr; }

	Float & operator () ( Uint32 Row, Uint32 Col )       { return m_Ptr->m[Row][Col]; }
	Float   operator () ( Uint32 Row, Uint32 Col ) const { return m_Ptr->m[Row][Col]; }

	CMatrix &operator = ( const D3DMATRIX &In );
	CMatrix &operator = ( const D3DXMATRIX &In );
	CMatrix &operator = ( const CMatrix &In );	
	CMatrix &operator = ( const class CQuaternion &In );

	CMatrix operator * ( const D3DMATRIX &In );	
	CMatrix operator * ( const D3DXMATRIX &In );
	CMatrix operator * ( const CMatrix &In );	

	CMatrix& operator *= ( const D3DMATRIX &In );
	CMatrix& operator *= ( const D3DXMATRIX &In );
	CMatrix& operator *= ( const CMatrix &In );	
};



//=============================================================================
/**
	@brief	�l�����N���X

	�l�������������߂̃N���X�ł��B
*/
//=============================================================================
class CQuaternion : public D3DXQUATERNION
{
public:
	void Add( CQuaternion *pIn1, CQuaternion *pIn2 );						///< ���Z
	void Sub( CQuaternion *pIn1, CQuaternion *pIn2 );						///< ���Z
	void Mul( CQuaternion *pIn1, CQuaternion *pIn2 );						///< ��Z
	void Lerp( CQuaternion *pIn0, CQuaternion *pIn1, Float fRate );			///< ���`�⊮
	void Slerp( CQuaternion *pIn0, CQuaternion *pIn1, Float fRate );		///< ���ʕ⊮

	void Add( CQuaternion *pIn );											///< ���Z
	void Sub( CQuaternion *pIn );											///< ���Z
	void Mul( CQuaternion *pIn );											///< ��Z
	void Lerp( CQuaternion *pIn, Float fRate );								///< ���`�⊮
	void Slerp( CQuaternion *pIn, Float fRate );							///< ���ʕ⊮

	void Identity( void );													///< ���K��
	Float LengthSq( void );													///< �����̓��擾
	Float Length( void );													///< �����擾
	Float DotProduct( CQuaternion *pIn );									///< ����
	void Conjugate( void );													///< ���]
};



//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
/**
	@brief	�p������N���X

	�R����\���x�N�g����p���Ďp��������s��
	�ׂ̃N���X�ł��B
	��{�I�ɂ͊e��R�c�֘A�̃I�u�W�F�N�g�ɂ�
	���̃N���X���܂܂�Ă���A���ꂳ�ꂽ���@��
	�p���̐�����s�����Ƃ��o����悤�ɂȂ��Ă��܂��B
	�قƂ�ǂ̏ꍇ�A���b�p�[�ォ�瑀�삷�邱�ƂɂȂ�܂��̂ŁA
	���ڂ��̃N���X���g�p����@��͋H���Ǝv���܂��B

    @todo	------------------------
    @bug	------------------------
*/
//=============================================================================
class CStyle
{
protected:
	CMatrix m_mStyle;												///< �p���p�s��
	CMatrix m_mStyleInverse;										///< �p���̋t�s��
	CMatrix m_mTransform;											///< �ϊ��s��
	CMatrix m_mTransformInverse;									///< �ϊ��s��̋t�s��
	CVector3D m_vUp;												///< ������x�N�g��
	CVector3D m_vRight;												///< �E�����x�N�g��
	CVector3D m_vFront;												///< �O�����x�N�g��
	CVector3D m_vPosition;											///< �ʒu�x�N�g��
	CVector3D m_vScale;												///< �g��k���x�N�g��

public:
	CStyle();														///< �R���X�g���N�^
	CStyle( const CStyle &Style );									///< �R���X�g���N�^

	void Set( CStyle *pStyle );										///< �p���f�[�^�R�s�[
	void Get( CStyle *pStyle );										///< �p���f�[�^�R�s�[

	void TransformInit( void );										///< �ϊ�������
	void TransformUpdate( void );									///< �ϊ��X�V

	void RotationX( Uint32 Rot );									///< �w����]
	void RotationY( Uint32 Rot );									///< �x����]
	void RotationZ( Uint32 Rot );									///< �y����]
	void Pitching( Uint32 Rot );									///< �s�b�`���O
	void Heading( Uint32 Rot );										///< �w�b�f�B���O
	void Rolling( Uint32 Rot );										///< ���[�����O
	void RotationQuaternion( CQuaternion *pQuat );					///< �N�H�[�^�j�I���ŉ�]
	void Translation( Float fPx, Float fPy, Float fPz );			///< �ړ�
	void Scaling( Float fSx, Float fSy, Float fSz );				///< �g��k��
	void LookAt( CVector3D *pEye, CVector3D *pAt, CVector3D *pUp );	///< �C�Ӎ��W�𒍎�
	void FromMatrix( CMatrix *pMat );								///< �s�񂩂琶��
	Sint32 GetAngleX( void );										///< �w�p�x�擾
	Sint32 GetAngleY( void );										///< �x�p�x�擾
	Sint32 GetAngleZ( void );										///< �y�p�x�擾

	//==========================================================================
	/**	= ���Z�q

		@param In		[in] �R�s�[���X�^�C��
	*/
	//==========================================================================
	CStyle &operator = ( const CStyle &In )			{ Set( (CStyle*)&In ); return *this; }

	//==========================================================================
	/**	�ʒu�ݒ�

		@param pPos		[in] �ݒ茳�ʒu�x�N�g��
	*/
	//==========================================================================
	void SetPosition( CVector3D *pPos )			{ m_vPosition = *pPos; }

	//==========================================================================
	/**	�O�x�N�g���ݒ�

		@param pVec		[in] �ݒ茳�x�N�g��
	*/
	//==========================================================================
	void SetFront( CVector3D *pVec )				{ m_vFront = *pVec; }

	//==========================================================================
	/**	�E�x�N�g���ݒ�

		@param pVec		[in] �ݒ茳�x�N�g��
	*/
	//==========================================================================
	void SetRight( CVector3D *pVec )				{ m_vRight = *pVec; }

	//==========================================================================
	/**	��x�N�g���ݒ�

		@param pVec		[in] �ݒ茳�x�N�g��
	*/
	//==========================================================================
	void SetUp( CVector3D *pVec )				{ m_vUp = *pVec; }

	//==========================================================================
	/**	�ʒu�擾

		@param pPos		[ous] �ʒu�x�N�g���i�[��
	*/
	//==========================================================================
	void GetPosition( CVector3D *pPos )			{ *pPos = m_vPosition; }

	//==========================================================================
	/**	�O�x�N�g���擾

		@param pVec		[ous] �x�N�g���i�[��
	*/
	//==========================================================================
	void GetFront( CVector3D *pVec )				{ *pVec = m_vFront; }

	//==========================================================================
	/**	�E�x�N�g���擾

		@param pVec		[ous] �x�N�g���i�[��
	*/
	//==========================================================================
	void GetRight( CVector3D *pVec )				{ *pVec = m_vRight; }

	//==========================================================================
	/**	��x�N�g���擾

		@param pVec		[ous] �x�N�g���i�[��
	*/
	//==========================================================================
	void GetUp( CVector3D *pVec )				{ *pVec = m_vUp; }

	//==========================================================================
	/**	�p���s��擾

		@param pMat		[ous] �s��i�[��
	*/
	//==========================================================================
	void GetStyle( CMatrix *pMat )				{ *pMat = m_mStyle; }

	//==========================================================================
	/**	�p���s��h�̋t�s��擾

		@param pMat		[ous] �s��i�[��
	*/
	//==========================================================================
	void GetStyleInverse( CMatrix *pMat )		{ *pMat = m_mStyleInverse; }

	//==========================================================================
	/**	�ϊ��s��擾

		@param pMat		[ous] �s��i�[��
	*/
	//==========================================================================
	void GetTransform( CMatrix *pMat )			{ *pMat = m_mTransform; }

	//==========================================================================
	/**	�ϊ��s��̋t�s��擾

		@param pMat		[ous] �s��i�[��
	*/
	//==========================================================================
	void GetTransformInverse( CMatrix *pMat )	{ *pMat = m_mTransformInverse; }
};



//================================================================================
// DEFINE
//================================================================================
#define ef						else if																		///< else if �ȗ��p�}�N��

#define toF(V)					((Float)(V))																///< Float�^�ւ̃L���X�g�}�N��
#define toI(V)					((Sint32)(V))																///< Sint32�^�ւ̃L���X�g�}�N��
#define F(V)					toF(V)
#define L(V)					toI(V)

#define PI						(3.141592653589793238462643383279f)											///< ��
#define PI2						(6.283185307179586476925286766559f)											///< 2��
#define REV(V)					toF(1.0f/toF(V))															///< �t���Z�o�}�N��

#define SAFE_RELEASE(V)			if ( (V) != NULL ) { (V)->Release(); (V) = NULL; }							///< COM���S����}�N��
#define SAFE_DELETE(V)			if ( (V) != NULL ) { delete (V); (V) = NULL; }								///< new���������S���
#define SAFE_DELETES(V)			if ( (V) != NULL ) { delete [] (V); (V) = NULL; }							///< new[]���������S���

#define MIN(N1,N2)				((N1 < N2) ? (N1) : (N2))													///< �ŏ��l�擾�}�N��
#define MAX(N1,N2)				((N1 > N2) ? (N1) : (N2))													///< �ő�l�擾�}�N��
#define SWAP(N1,N2)				{ N1 = N2 - N1; N2 -= N1; N1 += N2; }										///< �l�����}�N��

#define SIN_TABLE_BIT			(16)																		///< �T�C���e�[�u���̃r�b�g��
#define SIN_TABLE_SIZE			(1 << SIN_TABLE_BIT)														///< �T�C���e�[�u���̃T�C�Y
#define SIN_TABLE_MASK			(SIN_TABLE_SIZE - 1)														///< �T�C���e�[�u���̃A�N�Z�X�p�}�X�N
#define ARCTAN_TABLE_SIZE		(SIN_TABLE_SIZE >> 3)														///< �A�[�N�^���W�F���g�e�[�u���̃T�C�Y
#define ARCTAN_POS_1			(ARCTAN_TABLE_SIZE << 1)													///< �A�[�N�^���W�F���g�̑�P�ی�
#define ARCTAN_POS_2			(ARCTAN_POS_1 + ARCTAN_POS_1)												///< �A�[�N�^���W�F���g�̑�Q�ی�
#define ARCTAN_POS_3			(ARCTAN_POS_1 + ARCTAN_POS_2)												///< �A�[�N�^���W�F���g�̑�R�ی�
#define ARCTAN_POS_4			(ARCTAN_POS_1 + ARCTAN_POS_3)												///< �A�[�N�^���W�F���g�̑�S�ی�
#define ARCTAN_POS_SHIFT		(SIN_TABLE_BIT - 3)															///< �A�[�N�^���W�F���g�̈ʒu�V�t�g��
#define ARCTAN_SCALE(V)			(toF(V) * toF(1 << ARCTAN_POS_SHIFT))										///< �A�[�N�^���W�F���g�̊g�嗦

#define TEXTURE_STAGE_MAX		(4)																			///< �e�N�X�`���X�e�[�W�ő吔
#define LUNA_BONE_MAX			(48)																		///< �ЂƂ̃��b�V���Ŏg�p�\�ȍő�{�[����
#define LUNA_THREAD_MAX			(32)																		///< �X���b�h�̍ő吔

#define NORMALIZE_ANGLE(A)		((A) & SIN_TABLE_MASK)														///< �p�x�̐��K���i0�`65535�ցj
#define GET_ANGLE(A)			toI(toF(A) * toF(SIN_TABLE_SIZE) / toF(360))								///< ��p�p�x�̎Z�o
#define GET_ANGLE_PI(A)			toI(toF(A) * toF(SIN_TABLE_SIZE) / toF(PI2))								///< ���W�A�������p�p�x�̎Z�o

#define PRIMITIVE_Z_MAX			(65535)																		///< �v���~�e�B�u�p�y�ő�l
#define INV_PRIMITIVE_Z_MAX		REV(PRIMITIVE_Z_MAX)														///< �v���~�e�B�u�p�y�l�Z�o�p�f�[�^
#define PRIMITIVE_Z_CENTER		(PRIMITIVE_Z_MAX / 2)														///< �v���~�e�B�u�y���S�ʒu
#define Z_TO_SORT_VALUE(Z)		(toI(Z) >> 3)																///< �y�l����y�\�[�g�p��l�Z�o�p
#define SORT_Z_MAX				Z_TO_SORT_VALUE(PRIMITIVE_Z_MAX)											///< �y�\�[�g�p�y�ő�l

#define MemoryClear(PD,S)		::FillMemory((PD),(S),0x00)													///< �������N���A
#define MemoryFill(PD,PS,S)		::FillMemory((PD),(S),(PS))													///< �������h��Ԃ�
#define MemoryMove(PD,PS,S)		::MoveMemory((PD),(PS),(S))													///< �������ړ�
#define MemoryCopy(PD,PS,S)		::CopyMemory((PD),(PS),(S))													///< �������R�s�[

#define MemoryAlloc(size)		::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, size )										///< HeapAlloc�������m�ۃ}�N��
#define MemoryFree(pointer)		if ( (pointer) != NULL ) { ::HeapFree( ::GetProcessHeap(), 0, pointer ); (pointer) = NULL; }	///< HeapAlloc����������}�N��

#define CHECK_GUID(S,D)			(stricmp( (S).Data, (D) ) == 0)												///< �V�X�e���R�[���o�b�N��GUID�`�F�b�N

#define COLOR_BASE				(D3DCOLOR_XRGB(0xFF,0xFF,0xFF))												///< �J���[��`�F��{�F
#define COLOR_WHITE				(D3DCOLOR_XRGB(0xFF,0xFF,0xFF))												///< �J���[��`�F��
#define COLOR_BLACK				(D3DCOLOR_XRGB(0x00,0x00,0x00))												///< �J���[��`�F��
#define COLOR_RED				(D3DCOLOR_XRGB(0xFF,0x00,0x00))												///< �J���[��`�F��
#define COLOR_GREEN				(D3DCOLOR_XRGB(0x00,0xFF,0x00))												///< �J���[��`�F��
#define COLOR_BLUE				(D3DCOLOR_XRGB(0x00,0x00,0xFF))												///< �J���[��`�F��
#define COLOR_ALPHA(A)			(D3DCOLOR_ARGB(A,0xFF,0xFF,0xFF))											///< �J���[��`�F�A���t�@
#define COLOR_BRIGHT(B)			(D3DCOLOR_XRGB(B,B,B))														///< �J���[��`�F���x

#define LZSS_RING_LENGTH		4096																		///< ��o�b�t�@�̑傫��
#define LZSS_RING_MASK			(LZSS_RING_LENGTH-1)														///< ��o�b�t�@�̃}�X�N
#define LZSS_LONGEST_MATCH		16																			///< �Œ���v��
#define NIL						LZSS_RING_LENGTH															///< �؂̖��[

#define COLORKEY_DISABLE		(D3DCOLOR_ARGB(0x00,0x00,0x00,0x00))										///< �e�N�X�`���ǂݍ��ݎ��J���[�L�[�s�v
#define COLORKEY_BLACK			(D3DCOLOR_ARGB(0xFF,0x00,0x00,0x00))										///< �e�N�X�`���ǂݍ��ݎ��J���[�L�[���ݒ�
#define COLORKEY_WHITE			(D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0xFF))										///< �e�N�X�`���ǂݍ��ݎ��J���[�L�[���ݒ�
#define COLORKEY_RED			(D3DCOLOR_ARGB(0xFF,0xFF,0x00,0x00))										///< �e�N�X�`���ǂݍ��ݎ��J���[�L�[�Ԑݒ�
#define COLORKEY_GREEN			(D3DCOLOR_ARGB(0xFF,0x00,0xFF,0x00))										///< �e�N�X�`���ǂݍ��ݎ��J���[�L�[�ΐݒ�
#define COLORKEY_BLUE			(D3DCOLOR_ARGB(0xFF,0x00,0x00,0xFF))										///< �e�N�X�`���ǂݍ��ݎ��J���[�L�[�ݒ�

#define LIGHT_MAX				(4)																			///< ���C�g�ő吔

#define PADLAYER_MAX			(256)																		///< �p�b�h�p���C���[�ő吔
#define JOYSTICK_MAX			(16)																		///< �W���C�X�e�B�b�N���ő吔
#define KEY_BUFFER_MAX			(32)																		///< �L�[�o�b�t�@�p�o�b�t�@�T�C�Y
#define ANIMATION_MAX			(256)																		///< �A�j���[�V�����ő吔

#define WM_SOCKET				(WM_USER + 1)																///< Socket�C�x���g��M�p���b�Z�[�W
#define WM_GRAPHNOTIFY			(WM_USER + 2)																///< ���[�r�[�C�x���g��M�p���b�Z�[�W

#define THREAD_SYSTEM			(0xFFFFFFFF)																///< �V�X�e���p�X���b�h��\���萔

#define RENDER_STATE_TBL_MAX	(210)
#define TEXTURE_STATE_TBL_MAX	(33)
#define SAMPLER_STATE_TBL_MAX	(14)

#define FILE_OPEN_READ(name)				::CreateFile( name, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_OPEN_WRITE(name)				::CreateFile( name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_OPEN_READ_WRITE(name)			::CreateFile( name, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_CLOSE(handle)					::CloseHandle( handle )
#define FILE_GET_SIZE(handle)				::GetFileSize( handle, NULL )
#define FILE_READ(handle,ptr,size)			{Uint32 ReadBytes; ::ReadFile( handle, ptr, size, &ReadBytes, NULL);}
#define FILE_WRITE(handle,ptr,size)			{Uint32 WriteBytes; ::WriteFile( handle, ptr, size, &WriteBytes, NULL);}
#define FILE_SEEK_BEGIN(handle,pos)			::SetFilePointer( handle, pos, NULL, FILE_BEGIN )
#define FILE_SEEK_CURRENT(handle,pos)		::SetFilePointer( handle, pos, NULL, FILE_CURRENT )
#define FILE_SEEK_END(handle,pos)			::SetFilePointer( handle, pos, NULL, FILE_END )
#define FILE_SET_TIME(handle,ft0,ft1,ft2)	::SetFileTime( handle, ft0, ft1, ft2 )
#define FILE_GET_TIME(handle,ft0,ft1,ft2)	::GetFileTime( handle, ft0, ft1, ft2 )


//================================================================================
// OBJECT HANDLE
//================================================================================
typedef enum { INVALID_CAMERA		= -1 } LCAMERA;				///< �J�����n���h��
typedef enum { INVALID_MODEL		= -1 } LMODEL;				///< ���f���n���h��
typedef enum { INVALID_ANIMATION	= -1 } LANIMATION;			///< �A�j���[�V�����n���h��
typedef enum { INVALID_SOUND		= -1 } LSOUND;				///< �T�E���h�n���h��
typedef enum { INVALID_MUSIC		= -1 } LMUSIC;				///< �~���[�W�b�N�n���h��
typedef enum { INVALID_FIELD		= -1 } LFIELD;				///< �t�B�[���h�n���h��
typedef enum { INVALID_MEDIA		= -1 } LMEDIA;				///< ���f�B�A�n���h��


typedef struct ___LSURFACE___      { void *pData; } *LSURFACE;
typedef struct ___LTEXTURE___      { void *pData; } *LTEXTURE;
typedef struct ___LSHEET___        { void *pData; } *LSHEET;
typedef struct ___LVMR9___         { void *pData; } *LVMR9;
typedef struct ___LSCENECONTROL___ { void *pData; } *LSCENECONTROL;
typedef struct ___LPOINT___        { void *pData; } *LPOINT;
typedef struct ___LPOINT3D___      { void *pData; } *LPOINT3D;
typedef struct ___LLINE___         { void *pData; } *LLINE;
typedef struct ___LLINE3D___       { void *pData; } *LLINE3D;
typedef struct ___LPRIMITIVE___    { void *pData; } *LPRIMITIVE;
typedef struct ___LPRIMITIVE3D___  { void *pData; } *LPRIMITIVE3D;
typedef struct ___LSPRITE___       { void *pData; } *LSPRITE;
typedef struct ___LSPRITE3D___     { void *pData; } *LSPRITE3D;
typedef struct ___LFONT___         { void *pData; } *LFONT;
typedef struct ___LFONTSPRITE___   { void *pData; } *LFONTSPRITE;
typedef struct ___LFONTSPRITE3D___ { void *pData; } *LFONTSPRITE3D;
typedef struct ___LMODELEX___      { void *pData; } *LMODELEX;
typedef struct ___LSHADERFX___     { void *pData; } *LSHADERFX;


const LSURFACE			INVALID_SURFACE			= NULL;
const LTEXTURE			INVALID_TEXTURE			= NULL;
const LSHEET			INVALID_SHEET			= NULL;
const LVMR9				INVALID_VMR9			= NULL;
const LSCENECONTROL		INVALID_SCENECONTROL	= NULL;
const LPOINT			INVALID_POINT			= NULL;
const LPOINT3D			INVALID_POINT3D			= NULL;
const LLINE				INVALID_LINE			= NULL;
const LLINE3D			INVALID_LINE3D			= NULL;
const LPRIMITIVE		INVALID_PRIMITIVE		= NULL;
const LPRIMITIVE3D		INVALID_PRIMITIVE3D		= NULL;
const LSPRITE			INVALID_SPRITE			= NULL;
const LSPRITE3D			INVALID_SPRITE3D		= NULL;
const LFONT				INVALID_FONT			= NULL;
const LFONTSPRITE		INVALID_FONTSPRITE		= NULL;
const LFONTSPRITE3D		INVALID_FONTSPRITE3D	= NULL;
const LMODELEX			INVALID_MODELEX			= NULL;
const LSHADERFX			INVALID_SHADERFX		= NULL;


//================================================================================
// ENUM
//================================================================================

/**
	@brief	�T�[�t�F�C�X�t�H�[�}�b�g��`

	�e��T�[�t�F�C�X�y�уe�N�X�`���t�H�[�}�b�g�̒�`�B
*/
enum eSurfaceFormat
{
	FORMAT_FROM_FILE,					///< �t�@�C������

	FORMAT_DEPTH16,						///< 16Bit�[�x�o�b�t�@
	FORMAT_DEPTH32,						///< 32Bit�[�x�o�b�t�@
	FORMAT_DEPTHSTENCIL,				///< �X�e���V���[�x�o�b�t�@

	FORMAT_DXT1,						///< DXT1���k�t�H�[�}�b�g�e�N�X�`��
	FORMAT_DXT3,						///< DXT3���k�t�H�[�}�b�g�e�N�X�`��
	FORMAT_DXT5,						///< DXT5���k�t�H�[�}�b�g�e�N�X�`��

	FORMAT_BACKBUFFER,					///< �o�b�N�o�b�t�@�[�ɏ���
	FORMAT_TARGET16,					///< 16Bit�����_�����O�^�[�Q�b�g
	FORMAT_TARGET32,					///< 32Bit�����_�����O�^�[�Q�b�g
	FORMAT_TARGETFloat,					///< ���������_�����_�����O�^�[�Q�b�g

	FORMAT_ALPHAONLY,					///< �A���t�@�p�e�N�X�`��

	FORMAT_TEXTURE32,					///< 32Bit�e�N�X�`���t�H�[�}�b�g�ɏ���
	FORMAT_TEXTURE16,					///< 16Bit�e�N�X�`���t�H�[�}�b�g�ɏ���

	FORMAT_TEXTURE_2D,					///< 2D�p�ėp�e�N�X�`���t�H�[�}�b�g
	FORMAT_TEXTURE_3D,					///< 3D�p�ėp�e�N�X�`���t�H�[�}�b�g
};

/**
	@brief	���_�t�H�[�}�b�g��`

	���LunaSprite�N���X�Ŏg�p����钸�_��`�B
*/
enum eVertexPrimitiveType
{
	PRIM_VERTEX_UV0,					///< �e�N�X�`���X�e�[�W���O�̒��_�f�[�^
	PRIM_VERTEX_UV1,					///< �e�N�X�`���X�e�[�W���P�̒��_�f�[�^
	PRIM_VERTEX_UV2,					///< �e�N�X�`���X�e�[�W���Q�̒��_�f�[�^
	PRIM_VERTEX_UV3,					///< �e�N�X�`���X�e�[�W���R�̒��_�f�[�^
	PRIM_VERTEX_UV4,					///< �e�N�X�`���X�e�[�W���S�̒��_�f�[�^
};


/**
	@brief	�A���t�@�u�����f�B���O���[�h��`

	�e��A���t�@�u�����f�B���O���[�h�̒�`�B
*/
enum eBlendType
{
	BLEND_NONE,							///< �A���t�@�u�����h����
	BLEND_NORMAL,						///< �ʏ�u�����f�B���O
	BLEND_ADD,							///< ���Z�u�����f�B���O
	BLEND_ADD_NOALPHA,					///< ���Z�u�����f�B���O�i�A���t�@�e���Ȃ�
	BLEND_SUB,							///< ���Z�u�����f�B���O
	BLEND_SUB_NOALPHA,					///< ���Z�u�����f�B���O�i�A���t�@�e���Ȃ�
	BLEND_MUL,							///< ��Z�u�����f�B���O
	BLEND_REVERSE,						///< ���]�u�����f�B���O
};


//================================================================================
// STRUCTURE
//================================================================================
/**
	@brief	�T�[�t�F�C�X�p�f�o�C�X�X�e�[�g
*/
struct MATERIALSTATE
{
	Uint32		SamplerState[TEXTURE_STAGE_MAX][SAMPLER_STATE_TBL_MAX];
	Uint32		TextureState[TEXTURE_STAGE_MAX][TEXTURE_STATE_TBL_MAX];
	eBlendType	BlendType;
	Bool		IsColorKey;
	Bool		IsBilinear;
	Bool		IsZBuffer;
	Bool		IsZWrite;
};


/**
	@brief	�_�f�[�^

	Luna�Ŏg�p�����_�\���p�̍\���́B
*/
typedef struct CLunaPoint
{
	Float Px;					///< �w���W
	Float Py;					///< �x���W

	/**
		@brief �l�ݒ�
		�l���ȗ��I�ɐݒ肷�邽�߂̊֐��B

		@param px		[in] �w���W
		@param py		[in] �x���W
	*/
	void Set( Float px, Float py )
	{
		Px = px;
		Py = py;
	}
}
LUNAPOINT;

/**
	@brief	��`�f�[�^

	Luna�Ŏg�p������`�\���p�̍\���́B
*/
typedef struct CLunaRect
{
	Float Px;					///< �w�n�_���W
	Float Py;					///< �x�n�_���W
	Float Sx;					///< �w�T�C�Y
	Float Sy;					///< �x�T�C�Y

	/**
		@brief �l�ݒ�
		�l���ȗ��I�ɐݒ肷�邽�߂̊֐��B

		@param px		[in] �w�n�_���W
		@param py		[in] �x�n�_���W
		@param sx		[in] �w�T�C�Y
		@param sy		[in] �x�T�C�Y
	*/
	void Set( Float px, Float py, Float sx, Float sy )
	{
		Px = px;
		Py = py;
		Sx = sx;
		Sy = sy;
	}

	/**
		@brief �l�ݒ�
		�l���ȗ��I�ɐݒ肷�邽�߂̊֐��B

		@param px		[in] �w�n�_���W
		@param py		[in] �x�n�_���W
		@param sx		[in] �w�T�C�Y
		@param sy		[in] �x�T�C�Y
		@param scale	[in] �g��k����
	*/
	void SetCenter( Float px, Float py, Float sx, Float sy, Float scale = 1.0f )
	{
		Px = px - (sx * 0.5f) * scale;
		Py = py - (sy * 0.5f) * scale;
		Sx = sx * scale;
		Sy = sy * scale;
	}
}
LUNARECT;

/**
	@brief	�N���b�s���O�̈�

	�N���b�s���O�p�̋�`�f�[�^
*/
struct CClipRect
{
	Sint32 x1;					///< �w�ʒu�n�_
	Sint32 y1;					///< �x�ʒu�n�_
	Sint32 x2;					///< �w�ʒu�I�_
	Sint32 y2;					///< �x�ʒu�I�_
};

/**
	@brief	�t�H���g�`���`

	�t�H���g�`��p�̃N���b�s���O���`��p��`�f�[�^
*/
struct CFontDrawRect
{
	Sint32 x1;					///< �w�n�_���W
	Sint32 y1;					///< �x�n�_���W
	Sint32 x2;					///< �w�I�_���W
	Sint32 y2;					///< �x�I�_���W
	Sint32 Pitch;					///< �t�H���g�摜�̃s�b�`
	void *pBits;				///< �t�H���g�̃s�N�Z���f�[�^�̐擪�|�C���^
};

/**
	@brief	�R�c�f�o�C�X���

	Luna3D�N���X�Ŏg�p����A�f�o�C�X�̏���S��
	�i�[���Ă������߂̍\���́B
*/
struct DEVICEINFORMATION
{
	Bool IsPureDevice;							///< �s���A�f�o�C�X���T�|�[�g���Ă邩�ǂ���
	Bool IsHardwareTnL;							///< �n�[�h�E�F�A�s���k���T�|�[�g���Ă邩�ǂ���
	Bool IsSoftwareTnL;							///< �\�t�g�E�F�A�s���k���T�|�[�g���Ă邩�ǂ���

	D3DDEVTYPE DeviceType;						///< �f�o�C�X�^�C�v

	Bool IsAnisotropyMIN;						///< �ٕ����t�B���^�����O���T�|�[�g���Ă邩�ۂ�
	Bool IsAnisotropyMAG;						///< �ٕ����t�B���^�����O���T�|�[�g���Ă邩�ۂ�
	Bool IsDither;								///< �f�B�U���T�|�[�g���Ă邩�ۂ�
	Bool IsDepthBias;							///< �[�x�o�C�A�X���T�|�[�g���Ă邩�ۂ�
	Bool IsWBuffer;								///< �v�o�b�t�@���T�|�[�g���Ă邩�ۂ�
	Bool IsAutoMipMap;							///< �~�b�v�}�b�v�����������T�|�[�g���Ă��邩�ۂ�

	Bool IsZCmpAlways;							///< ALWAYS�[�x��r���T�|�[�g���Ă��邩�ۂ�
	Bool IsZCmpEqual;							///< EQUAL�[�x��r���T�|�[�g���Ă��邩�ۂ�
	Bool IsZCmpGreater;							///< GREATER�[�x��r���T�|�[�g���Ă��邩�ۂ�
	Bool IsZCmpGreaterEqual;					///< GREATEREQUAL�[�x��r���T�|�[�g���Ă��邩�ۂ�
	Bool IsZCmpLess;							///< LESS�[�x��r���T�|�[�g���Ă��邩�ۂ�
	Bool IsZCmpLessEqual;						///< LESSEQUAL�[�x��r���T�|�[�g���Ă��邩�ۂ�
	Bool IsZCmpNever;							///< NEVER�[�x��r���T�|�[�g���Ă��邩�ۂ�
	Bool IsZCmpNotEqual;						///< NOTEQUAL�[�x��r���T�|�[�g���Ă��邩�ۂ�

	Bool IsSrcBlendFactor;						///< �\�[�X�Ƀu�����h�t�@�N�^�[���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcBothInvSrc;						///< �\�[�X��BOTHINVSRC�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcBothSrc;							///< �\�[�X��BOTHSRC�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcDestAlpha;						///< �\�[�X��DESTALPHA�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcDestColor;						///< �\�[�X��DESTCOLOR�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcInvDestAlpha;						///< �\�[�X��INVDESTALPHA�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcInvDestColor;						///< �\�[�X��INVDESTCOLOR�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcInvSrcAlpha;						///< �\�[�X��INVSRCALPHA�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcInvSrcColor;						///< �\�[�X��INVSRCCOLOR�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcOne;								///< �\�[�X��ONE�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcSrcAlpha;							///< �\�[�X��SRCALPHA�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcSrcAphaSat;						///< �\�[�X��SRCALPHASAT�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcSrcColor;							///< �\�[�X��SRCCOLOR�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsSrcZero;								///< �\�[�X��SERO�u�����h���T�|�[�g���Ă��邩�ۂ�

	Bool IsDstBlendFactor;						///< �f�X�e�B�l�[�V�����Ƀ\�[�X�Ƀu�����h�t�@�N�^�[���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstBothInvSrc;						///< �f�X�e�B�l�[�V������BOTHINVSRC�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstBothSrc;							///< �f�X�e�B�l�[�V������BOTHSRC�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstDestAlpha;						///< �f�X�e�B�l�[�V������DESTALPHA�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstDestColor;						///< �f�X�e�B�l�[�V������DESTCOLOR�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstInvDestAlpha;						///< �f�X�e�B�l�[�V������INVDESTALPHA�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstInvDestColor;						///< �f�X�e�B�l�[�V������INVDESTCOLOR�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstInvSrcAlpha;						///< �f�X�e�B�l�[�V������INVSRCALPHA�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstInvSrcColor;						///< �f�X�e�B�l�[�V������INVSRCCOLOR�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstOne;								///< �f�X�e�B�l�[�V������ONE�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstSrcAlpha;							///< �f�X�e�B�l�[�V������SRCALPHA�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstSrcAphaSat;						///< �f�X�e�B�l�[�V������SRCALPHASAT�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstSrcColor;							///< �f�X�e�B�l�[�V������SRCCOLOR�u�����h���T�|�[�g���Ă��邩�ۂ�
	Bool IsDstZero;								///< �f�X�e�B�l�[�V������ZERO�u�����h���T�|�[�g���Ă��邩�ۂ�

	Bool IsCubeTexture;							///< �L���[�u�e�[�N�X�`�����T�|�[�g���Ă��邩�ۂ�
	Bool IsMipmapTexture;						///< �~�b�v�}�b�v�e�N�X�`�����T�|�[�g���Ă��邩�ۂ�
	Bool IsPerspective;							///< �p�[�X�y�N�e�B�u�R���N�g���T�|�[�g���Ă��邩�ۂ�
	Bool IsPow2;								///< �Q�ׂ̂���ȊO�̃T�C�Y�̃e�N�X�`�����T�|�[�g���Ă��邩�ۂ�
	Bool IsSquareOnly;							///< �����`�ȊO�̃e�N�X�`�����T�|�[�g���Ă��邩�ۂ�

	Bool IsTextureBorder;						///< BORDER�e�N�X�`�����[�h���T�|�[�g���Ă邩�ۂ�
	Bool IsTxtureClamp;							///< CLAMP�e�N�X�`�����[�h���T�|�[�g���Ă邩�ۂ�
	Bool IsTextureIndependent;					///< INDEPENDENT�e�N�X�`�����[�h���T�|�[�g���Ă邩�ۂ�
	Bool IsTextureMirror;						///< MIRROR�e�N�X�`�����[�h���T�|�[�g���Ă邩�ۂ�
	Bool IsTextureMirrorRonce;					///< MIRRORRONCE�e�N�X�`�����[�h���T�|�[�g���Ă邩�ۂ�
	Bool IsTextureWrap;							///< WRAP�e�N�X�`�����[�h���T�|�[�g���Ă邩�ۂ�

	Uint32 MaxAnisotropy;						///< �ٕ����t�B���^����
	Uint32 MaxTextureWidth;						///< �ő�e�N�X�`������
	Uint32 MaxTextureHeight;					///< �ő�e�N�X�`���c��
	Uint32 MaxTextureRepeat;					///< �ő�e�N�X�`�����s�[�g��
	Uint32 MaxTextureAspectRatio;				///< �ő�e�N�X�`���A�X�y�N�g�l

	Bool IsStencilKeep;							///< KEEP�X�e���V��������T�|�[�g���Ă邩�ۂ�
	Bool IsStencilZero;							///< ZERO�X�e���V��������T�|�[�g���Ă邩�ۂ�
	Bool IsStencilReplace;						///< REPLACE�X�e���V��������T�|�[�g���Ă邩�ۂ�
	Bool IsStencilIncRsat;						///< INCRSAT�X�e���V��������T�|�[�g���Ă邩�ۂ�
	Bool IsStencilDecRsat;						///< DECRSAT�X�e���V��������T�|�[�g���Ă邩�ۂ�
	Bool IsStencilInvert;						///< INVERT�X�e���V��������T�|�[�g���Ă邩�ۂ�
	Bool IsStencilIncR;							///< INCR�X�e���V��������T�|�[�g���Ă邩�ۂ�
	Bool IsStencilDecR;							///< DECR�X�e���V��������T�|�[�g���Ă邩�ۂ�
	Bool IsStencilTwoSided;						///< ���ʃX�e���V���������\���ǂ���

	Float MaxVertexW;							///< �ő咸�_�v�l
	Float GuardBandLeft;						///< �K�[�h�o���h�N���b�s���O���ʒu
	Float GuardBandTop;							///< �K�[�h�o���h�N���b�s���O��ʒu
	Float GuardBandRight;						///< �K�[�h�o���h�N���b�s���O�E�ʒu
	Float GuardBandBottom;						///< �K�[�h�o���h�N���b�s���O���ʒu

	Float MaxPointSize;							///< �ő�|�C���g�X�v���C�g�T�C�Y

	Uint32 MaxPrimitiveCount;					///< �ő�ꊇ�`��\�|���S����
	Uint32 MaxVertexIndex;						///< �ő�ꊇ�`��\���_�C���f�b�N�X��

	Uint32 MaxTextureBlendStages;				///< �ő�e�N�X�`���u�����f�B���O�X�e�[�W��
	Uint32 MaxSimultaneousTextures;				///< �ő�e�N�X�`���X�e�[�W��

	Uint32 MaxActiveLights;						///< �ő�n�[�h�E�F�A���C�g��

	Uint32 MaxVertexBlendMatrices;				///< ���_�u�����h�ő吔
	Uint32 MaxVertexBlendMatrixIndex;			///< ���_�E�F�C�g�ő吔

	Uint32 VertexShaderVersion;					///< ���_�V�F�[�_�[�o�[�W����
	Uint32 PixelShaderVersion;					///< �s�N�Z���V�F�[�_�[�o�[�W����
	Uint32 MaxVertexShaderConst;				///< �ő咸�_�V�F�[�_�[�萔���W�X�^��

	Uint32 DynamicFlowControlDepth;				///< ���_�V�F�[�_�[�ł̓��I�t���[����ő�l�X�g��
	Uint32 StaticFlowControlDepth;				///< ���_�V�F�[�_�[�ł̐ÓI�t���[����ő�l�X�g��
};

/**
	@brief	���k�f�[�^�w�b�_

	LunaCompres�N���X�Ŏg�p����A���k�f�[�^�̃w�b�_�B
*/
struct LZSSHEADER
{
	char Chunk[4];					///< ��p�̃t�@�C���ł��邱�Ƃ����߂����ʎq�B���'L''Z''S''S'
	Uint32 DecodeSize;				///< �W�J��̃f�[�^�T�C�Y
	Uint32 Reserved[2];				///< �\��̈�i��ɂO�j
};

/**
	@brief	16Bit�s�N�Z���f�[�^

	16Bit�s�N�Z���t�H�[�}�b�g�̍\���́B
*/
struct PIXELDATA16
{
	Uint16 a : 4;				///< �A���t�@����
	Uint16 r : 4;				///< �Ԑ���
	Uint16 g : 4;				///< �ΐ���
	Uint16 b : 4;				///< ����
};

/**
	@brief	32Bit�s�N�Z���f�[�^

	32Bit�s�N�Z���t�H�[�}�b�g�̍\���́B
*/
struct PIXELDATA32
{
	Uint8 b;				///< ����
	Uint8 g;				///< �ΐ���
	Uint8 r;				///< �Ԑ���
	Uint8 a;				///< �A���t�@����
};

/**
	@brief	64Bit�s�N�Z���f�[�^

	64Bit�s�N�Z���t�H�[�}�b�g�̍\���́B
*/
struct PIXELDATA64
{
	Uint16 b;				///< ����
	Uint16 g;				///< �ΐ���
	Uint16 r;				///< �Ԑ���
	Uint16 a;				///< �A���t�@����
};

/**
	@brief	Float�^�s�N�Z���f�[�^

	���������_�s�N�Z���t�H�[�}�b�g�̍\���́B
*/
struct PIXELDATAFloat
{
	Float b;						///< ����
	Float g;						///< �ΐ���
	Float r;						///< �Ԑ���
	Float a;						///< �A���t�@����
};

/**
	@brief	�v���~�e�B�u�p�_���

	�Q�c�v���~�e�B�u�̃����_�����O�L���[��
	�f�[�^��ǉ����鎞�Ɏg�p����ėp���_�f�[�^�B
*/
typedef struct CPrimitivePoint2D
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	Float w;							///< �v�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P
	Float u2;							///< �t�u�X�e�[�W�Q
	Float v2;							///< �t�u�X�e�[�W�Q
	Float u3;							///< �t�u�X�e�[�W�R
	Float v3;							///< �t�u�X�e�[�W�R
	Float u4;							///< �t�u�X�e�[�W�S
	Float v4;							///< �t�u�X�e�[�W�S
}
PRIMITIVEPOINT, PRIMITIVEPOINT2D;

/**
	@brief	�R�c�v���~�e�B�u�p�_���

	�R�c�v���~�e�B�u�̃����_�����O�L���[��
	�f�[�^��ǉ����鎞�Ɏg�p����ėp���_�f�[�^�B
*/
typedef struct CPrimitivePoint3D
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P
	Float u2;							///< �t�u�X�e�[�W�Q
	Float v2;							///< �t�u�X�e�[�W�Q
	Float u3;							///< �t�u�X�e�[�W�R
	Float v3;							///< �t�u�X�e�[�W�R
	Float u4;							///< �t�u�X�e�[�W�S
	Float v4;							///< �t�u�X�e�[�W�S
}
PRIMITIVEPOINT3D;

/**
	@brief	�Q�c�|���S��

	�ʏ�̃V���v���ȂQ�c�`����s�����Ɏg�p����钸�_�f�[�^�\���́B
*/
typedef struct CVertex2D
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	Float w;							///< �v�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u;							///< �t�u
	Float v;							///< �t�u

	/**
		CVertex2D���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
}
VERTEX2D;

/**
	@brief	�v���~�e�B�u���_

	�e�N�X�`���t�u���S�X�e�[�W���܂񂾃v���~�e�B�u�p���_
*/
struct PRIMVERTEX0
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	Float w;							///< �v�ʒu
	D3DCOLOR c;							///< ���_�F

	/**
		PRIMVERTEX0���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
	};
};


/**
	@brief	�v���~�e�B�u���_

	�e�N�X�`���t�u���P�X�e�[�W���܂񂾃v���~�e�B�u�p���_
*/
struct PRIMVERTEX1
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	Float w;							///< �v�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P

	/**
		PRIMVERTEX1���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
};

/**
	@brief	�v���~�e�B�u���_

	�e�N�X�`���t�u���Q�X�e�[�W���܂񂾃v���~�e�B�u�p���_
*/
struct PRIMVERTEX2
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	Float w;							///< �v�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P
	Float u2;							///< �t�u�X�e�[�W�Q
	Float v2;							///< �t�u�X�e�[�W�Q

	/**
		PRIMVERTEX2���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2)
	};
};

/**
	@brief	�v���~�e�B�u���_

	�e�N�X�`���t�u���R�X�e�[�W���܂񂾃v���~�e�B�u�p���_
*/
struct PRIMVERTEX3
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	Float w;							///< �v�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P
	Float u2;							///< �t�u�X�e�[�W�Q
	Float v2;							///< �t�u�X�e�[�W�Q
	Float u3;							///< �t�u�X�e�[�W�R
	Float v3;							///< �t�u�X�e�[�W�R

	/**
		PRIMVERTEX3���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX3)
	};
};

/**
	@brief	�v���~�e�B�u���_

	�e�N�X�`���t�u���S�X�e�[�W���܂񂾃v���~�e�B�u�p���_
*/
struct PRIMVERTEX4
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	Float w;							///< �v�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P
	Float u2;							///< �t�u�X�e�[�W�Q
	Float v2;							///< �t�u�X�e�[�W�Q
	Float u3;							///< �t�u�X�e�[�W�R
	Float v3;							///< �t�u�X�e�[�W�R
	Float u4;							///< �t�u�X�e�[�W�S
	Float v4;							///< �t�u�X�e�[�W�S

	/**
		PRIMVERTEX4���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX4)
	};
};

/**
	@brief	�R�c�v���~�e�B�u���_

	�e�N�X�`���t�u���܂܂Ȃ��R�c�v���~�e�B�u�p���_
*/
struct PRIMVERTEX3D0
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	D3DCOLOR c;							///< ���_�F

	/**
		PRIMVERTEX3D0���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE)
	};
};

/**
	@brief	�R�c�v���~�e�B�u���_

	�e�N�X�`���t�u���P�X�e�[�W���܂񂾂R�c�v���~�e�B�u�p���_
*/
struct PRIMVERTEX3D1
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P

	/**
		PRIMVERTEX3D1���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
};

/**
	@brief	�R�c�v���~�e�B�u���_

	�e�N�X�`���t�u���Q�X�e�[�W���܂񂾂R�c�v���~�e�B�u�p���_
*/
struct PRIMVERTEX3D2
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P
	Float u2;							///< �t�u�X�e�[�W�Q
	Float v2;							///< �t�u�X�e�[�W�Q

	/**
		PRIMVERTEX3D2���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2)
	};
};

/**
	@brief	�R�c�v���~�e�B�u���_

	�e�N�X�`���t�u���R�X�e�[�W���܂񂾂R�c�v���~�e�B�u�p���_
*/
struct PRIMVERTEX3D3
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P
	Float u2;							///< �t�u�X�e�[�W�Q
	Float v2;							///< �t�u�X�e�[�W�Q
	Float u3;							///< �t�u�X�e�[�W�R
	Float v3;							///< �t�u�X�e�[�W�R

	/**
		PRIMVERTEX3D3���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX3)
	};
};

/**
	@brief	�R�c�v���~�e�B�u���_

	�e�N�X�`���t�u���S�X�e�[�W���܂񂾂R�c�v���~�e�B�u�p���_
*/
struct PRIMVERTEX3D4
{
	Float x;							///< �w�ʒu
	Float y;							///< �x�ʒu
	Float z;							///< �y�ʒu
	D3DCOLOR c;							///< ���_�F
	Float u1;							///< �t�u�X�e�[�W�P
	Float v1;							///< �t�u�X�e�[�W�P
	Float u2;							///< �t�u�X�e�[�W�Q
	Float v2;							///< �t�u�X�e�[�W�Q
	Float u3;							///< �t�u�X�e�[�W�R
	Float v3;							///< �t�u�X�e�[�W�R
	Float u4;							///< �t�u�X�e�[�W�S
	Float v4;							///< �t�u�X�e�[�W�S

	/**
		PRIMVERTEX3D4���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX4)
	};
};

/**
	@brief	�V�F�[�_�[���������p

	�V�F�[�_�[��I������Ƃ��Ɏg�p����f�[�^�\���́B
*/
struct SHADERCREATE
{
	Uint32 BoneWeightCount;		///< �{�[���E�F�C�g��
	Uint32 ShaderVersion;		///< �V�F�[�_�[�o�[�W����
	Bool IsSoftwareVP;					///< �\�t�g�E�F�A�������ۂ�
};

/**
	@brief	�Q������̓_

	LunaCollision�N���X�Ŏg����_�f�[�^�\���́B
*/
struct POINT2D
{
	Float Px;							///< �w�ʒu
	Float Py;							///< �x�ʒu
};

/**
	@brief	�Q������̉~

	LunaCollision�N���X�Ŏg����~�f�[�^�\���́B
*/
struct CIRCLE2D
{
	POINT2D Center;						///< �~�̒��S
	Float Radius;						///< �~�̔��a
};

/**
	@brief	�Q������̎l�p

	LunaCollision�N���X�Ŏg����l�p�`�f�[�^�\���́B
*/
struct RECT2D
{
	Float Sx;							///< ����w���W
	Float Sy;							///< ����x���W
	Float Ex;							///< �E���w���W
	Float Ey;							///< �E���x���W
};

/**
	@brief	�Q������̑��p�`

	LunaCollision�N���X�Ŏg���鑽�p�`�f�[�^�\���́B
*/
struct POLYGON2D
{
	Sint32 Count;							///< �|�C���g�z��̃|�C���g��
	POINT2D *pPts;						///< �|���S����\�����߂̃|�C���g�z��̃|�C���^
};

/**
	@brief	�Q������̐�

	LunaCollision�N���X�Ŏg������f�[�^�\���́B
*/
struct LINE2D
{
	POINT2D Pt0;						///< �����n�_�ʒu
	POINT2D Pt1;						///< �����I�_�ʒu
};

/**
	@brief	�R������̓_
*/
struct POINT3D
{
	Float Px;							///< �w�ʒu
	Float Py;							///< �x�ʒu
	Float Pz;							///< �y�ʒu

	POINT3D(){}														///< �R���g���N�^
	POINT3D( Float x, Float y, Float z ){ Px = x; Py = y; Pz = z; }	///< �R���g���N�^
	POINT3D( POINT3D &pt ) { Px = pt.Px; Py = pt.Py; Pz = pt.Pz; }	///< �R���g���N�^
};

/**
	@brief	�R������̉~�i��

	LunaCollision�N���X�Ŏg�p����鋅�f�[�^�\���́B
*/
struct SPHERE3D
{
	POINT3D Center;						///< ���̒��S
	Float Radius;						///< ���̔��a

	SPHERE3D(){}															///< �R���X�g���N�^
	SPHERE3D( POINT3D &pt, Float radius ){ Center = pt; Radius = radius; }	///< �R���X�g���N�^
};

/**
	@brief	�R������̐�

	LunaCollision�N���X�Ŏg������f�[�^�\���́B
*/
struct LINE3D
{
	POINT3D Pt0;						///< �����n�_�ʒu
	POINT3D Pt1;						///< �����I�_�ʒu

	LINE3D(){}																///< �R���X�g���N�^
	LINE3D( POINT3D &pt0, POINT3D &pt1 ) { Pt0 = pt0; Pt1 = pt1; }			///< �R���X�g���N�^
};

/**
	@brief	�R������̖�

	LunaCollision�N���X�Ŏg����ʃf�[�^�\���́B
*/
struct PLANE3D
{
	Float a;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� a �W�� 
	Float b;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� b �W�� 
	Float c;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� c �W�� 
	Float d;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� d �W�� 
};

/**
	@brief	�R������̔�

	LunaCollision�N���X�Ŏg���锠�f�[�^�\���́B
*/
struct BOX3D
{
	POINT3D Points[8];					///< ���̊e�p��\�����_�f�[�^
	PLANE3D Planes[6];					///< ���̊e�ʂ�\���ʃf�[�^
};

/**
	@brief	�V�F�[�_�[�p���C�g�f�[�^

    �V�F�[�_�[�p�̃��C�e�B���O�f�[�^��
	�i�[���邽�߂̍\���́B
*/
struct SHADERLIGHTDATA
{
	BOOL IsActive[LIGHT_MAX];			///< ���C�g���g�p���邩�ۂ�
	BOOL IsDirection[LIGHT_MAX];		///< �f�B���N�V���i�����C�g���ۂ�
	Float Attenuation[LIGHT_MAX];		///< ���C�g������
	D3DXVECTOR4 Position[LIGHT_MAX];	///< ���C�g�ʒu
	D3DXVECTOR4 Direction[LIGHT_MAX];	///< ���C�g����
	D3DCOLORVALUE Color[LIGHT_MAX];		///< ���C�g�F
	D3DCOLORVALUE Specular;				///< ���ˌ�
	D3DCOLORVALUE Ambient;				///< ����
};

/**
	@brief	���f���p���_

	�{�[���������_�x�[�X���_�\���́B<BR>
	�Œ�@�\�ŏ����\�ȃ{�[���������_�`���̍\���́B
*/
struct BASEVERTEX
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u

	/**
		BASEVERTEX���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
};

/**
	@brief	�{�[�����f���p���_

	�{�[���L�蒸�_�x�[�X���_�\���́B<BR>
	�Œ�@�\�ŏ����\�ȃ{�[���L�蒸�_�`���̍\���́B
*/
struct BASEBONEVERTEX
{
	D3DXVECTOR3 Pos;					///< �ʒu
	Float Weight[3];					///< �E�F�C�g
	Uint8 Index[4];				///< �{�[���C���f�b�N�X
	D3DXVECTOR3 Norm;					///< �@��
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u

	/**
		BASEBONEVERTEX���_�p�e�u�e��`
	*/
	enum {
		/// �e�u�e�t�H�[�}�b�g��`
		FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
};

/**
	@brief	�S�f�[�^�ۗL���_

	�S���_�f�[�^�ۗL�p���_�f�[�^�\���́B
	�ǂݍ��܂ꂽ���f���[�f�[�^�͕K�����̌`����
	���_�f�[�^��ۗL���Ă��܂��B
*/
struct VERTEXALL
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	D3DXVECTOR3 PosMorph;				///< �^�[�Q�b�g���_
	D3DXVECTOR3 NormMorph;				///< �^�[�Q�b�g�@��
	Float Weight[3];					///< �E�F�C�g
	Uint8 Index[4];				///< �{�[���C���f�b�N�X
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u
};

/**
	@brief	�ʏ풸�_

	�ʏ�̓����ϊ��p�̒��_�\���́B
*/
struct VERTEXNORMAL
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u
};

/**
	@brief	���[�t�B���O�p���_

	���[�t�B���O�������\�Ȓ��_�̍\���́B
*/
struct VERTEXMORPH
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	D3DXVECTOR3 PosMorph;				///< �^�[�Q�b�g�ʒu
	D3DXVECTOR3 NormMorph;				///< �^�[�Q�b�g�@��
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u
};

/**
	@brief	�{�[���Q�E�F�C�g���_

	�ő�Q�{�̃{�[���̉e�����󂯂钸�_�̍\���́B
*/
struct VERTEXBONE2
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	Float Weight[1];					///< �E�F�C�g
	Uint8 Index[4];				///< �{�[���C���f�b�N�X
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u
};

/**
	@brief	�{�[���R�E�F�C�g���_

	�ő�R�{�̃{�[���̉e�����󂯂钸�_�̍\���́B
*/
struct VERTEXBONE3
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	Float Weight[2];					///< �E�F�C�g
	Uint8 Index[4];				///< �{�[���C���f�b�N�X
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u 
};

/**
	@brief	�{�[���S�E�F�C�g���_

	�ő�S�{�̃{�[���̉e�����󂯂钸�_�̍\���́B
*/
struct VERTEXBONE4
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	Float Weight[3];					///< �E�F�C�g
	Uint8 Index[4];				///< �{�[���C���f�b�N�X
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u
};

/**
	@brief	�{�[���Q�E�F�C�g���[�t�B���O���_

	�ő�Q�{�̃{�[���̉e�����󂯂郂�[�t�B���O�L�蒸�_�̍\���́B
*/
struct VERTEXBONE2MORPH
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	D3DXVECTOR3 PosMorph;				///< �^�[�Q�b�g���_
	D3DXVECTOR3 NormMorph;				///< �^�[�Q�b�g�@��
	Float Weight[1];					///< �E�F�C�g
	Uint8 Index[4];				///< �{�[���C���f�b�N�X
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u
};

/**
	@brief	�{�[���R�E�F�C�g���[�t�B���O���_

	�ő�R�{�̃{�[���̉e�����󂯂郂�[�t�B���O�L�蒸�_�̍\���́B
*/
struct VERTEXBONE3MORPH
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	D3DXVECTOR3 PosMorph;				///< �^�[�Q�b�g���_
	D3DXVECTOR3 NormMorph;				///< �^�[�Q�b�g�@��
	Float Weight[2];					///< �E�F�C�g
	Uint8 Index[4];				///< �{�[���C���f�b�N�X
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u
};

/**
	@brief	�{�[���S�E�F�C�g���[�t�B���O���_

	�ő�S�{�̃{�[���̉e�����󂯂郂�[�t�B���O�L�蒸�_�̍\���́B
*/
struct VERTEXBONE4MORPH
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	D3DXVECTOR3 PosMorph;				///< �^�[�Q�b�g���_
	D3DXVECTOR3 NormMorph;				///< �^�[�Q�b�g�@��
	Float Weight[3];					///< �E�F�C�g
	Uint8 Index[4];				///< �{�[���C���f�b�N�X
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u
};

/**
	@brief	�o���v�}�b�v�p���_

	�o���v�}�b�v����̓����ϊ��p�̒��_�\���́B
*/
struct VERTEXBUMPMAP
{
	D3DXVECTOR3 Pos;					///< �ʒu
	D3DXVECTOR3 Norm;					///< �@��
	D3DXVECTOR3 Tangent;				///< �ڐ�
	D3DXVECTOR3 BiNorm;					///< �]�@��
	D3DCOLOR Color;						///< ���_�F
	D3DXVECTOR2 Tex;					///< �e�N�X�`���t�u
};

/**
	@brief	�z�X�g���

	�\�P�b�g�g�p���Ƀz�X�g�����i�[���邽�߂Ɏg���\���́B
*/
struct HOSTINFO
{
	char Name[256];						///< �z�X�g��
	char Alias[16][256];				///< �z�X�g�ʖ��e�[�u��
	char Address[16][64];				///< IP�A�h���X�e�[�u��
	Sint32 Type;						///< �f�[�^�^�C�v
	Sint32 Length;						///< �f�[�^�T�C�Y
	Sint32 AliasCount;					///< �G�C���A�X��
	Sint32 AddressCount;				///< IP�A�h���X��
};

/**
	@brief	�\�P�b�g�p���M�f�[�^��`

	�\�P�b�g�g�p���Ƀf�[�^�𑗐M����ۂɎg�p�����f�[�^�\���́B
*/
struct SOCKETSENDDATA
{
	Uint32 Send;					///< ���M�ς݃f�[�^�T�C�Y
	Uint32 Size;					///< ���M���v�T�C�Y
	Uint8 *pData;					///< ���M�f�[�^
};

/**
	@brief	�\�P�b�g�ڑ����

	�\�P�b�g�ł̐ڑ����̐ڑ�����<BR>
	�i�[���Ă������߂̍\���̂ł�
*/
struct CONNECTCLIENTDATA
{
	SOCKET Socket;							///< �\�P�b�g�f�[�^
	SOCKADDR_IN SockAddr;					///< �\�P�b�g�A�h���X
	HOSTINFO HostInfo;						///< �z�X�g���
	char IPAddress[64];						///< �h�o�A�h���X
	char Buffer[1024];						///< �o�b�t�@
	Sint32 Length;							///< �o�b�t�@����

	Bool IsWriteEnable;						///< �������݂n�j�t���O
	Bool IsReadEnable;						///< �ǂݍ��݂n�j�t���O

	SOCKETSENDDATA SendData;				///< ���M�f�[�^

	CONNECTCLIENTDATA *pNext;				///< ���̐ڑ����ւ̃|�C���^
};

/**
	@brief	�񓯊�IO�p�I�[�o�[���b�v�\����

	�񓯊�IO��p�������������鎞��<BR>
	�g�������i�[���邽�߂̍\���̂ł��B
*/
struct OVERLAPEDDATA
{
	Bool			IsRequest;				///< ����M���N�G�X�g�����ۂ�
	Sint32			RequestCode;			///< ���N�G�X�g���ʃR�[�h
	WSAOVERLAPPED	Overlap;				///< ����M���N�G�X�g�p�f�[�^
	WSABUF			Buffer;					///< ���M�o�b�t�@
};

/**
	@brief	�t�@�C���Ǘ��p�f�[�^��`

	LunaFile�N���X�ŗp������t�@�C���Ǘ��֌W�̍\���́B
*/
struct FILEDATA
{
	HANDLE hFile;						///< �t�@�C���n���h��
	BOOL IsPack;						///< �p�b�N�t�@�C�����ۂ�
	Uint32 Start;						///< �t�@�C���J�n�ʒu
	Uint32 Size;						///< �t�@�C���I���ʒu
	FILETIME CreationTime;				///< �쐬����
	FILETIME LastAccessTime;			///< �ŏI�A�N�Z�X����
	FILETIME LastWriteTime;				///< �ŏI�X�V����
	char FileName[MAX_PATH];					///< �t�@�C����
};

//=============================================================================
// DEFINE
//=============================================================================
#define SOCKET_LOG_LINE_MAX				(256)


//=============================================================================
// WORK ENUM
//=============================================================================

/**
	@brief	�����R�[�h��`

	LunaFontSprite�N���X�Ŏg�p�����<BR>
	S-JIS�����R�[�h�\�̃C���f�b�N�X�Z�o�p��`�ł�
*/
enum
{
	CODE_ASCII_START		= 0x0000,
	CODE_ASCII_END			= 0x00FF,

	CODE_SJIS_A_START		= 0x8140,
	CODE_SJIS_A_END			= 0x9FFF,

	CODE_SJIS_B_START		= 0xE040,
	CODE_SJIS_B_END			= 0xEEFF,

	CODE_SJIS_C_START		= 0xF8A0,
	CODE_SJIS_C_END			= 0xFC4F,

	CODE_TABLE_SIZE			= (CODE_ASCII_END - CODE_ASCII_START) + (CODE_SJIS_A_END - CODE_SJIS_A_START) + (CODE_SJIS_B_END - CODE_SJIS_B_START) + (CODE_SJIS_C_END - CODE_SJIS_C_START),	///< �ŏI�I�ȃe�[�u���T�C�Y

	SHEET_MAX				= 32,		///< LunaFontSprite�N���X�Ŏg�p����V�[�g�ő吔
};

/**
	@brief	�V�[�g�T�C�Y��`

	CSheet�N���X�Ŏg�p�����V�[�g�̊e���`�ł�
*/
enum {
	SHEET_X_MAX		= 16,			///< �w�����̃V�[�g�ő吔
	SHEET_Y_MAX		= 16,			///< �x�����̃V�[�g�ő吔

	SHEET_SIZE_X	= 256,			///< �V�[�g�̂w�����ő�T�C�Y
	SHEET_SIZE_Y	= 256,			///< �V�[�g�̂x�����ő�T�C�Y
};

/**
	@brief	�G�t�F�N�g�p�����[�^�[�n���h����`

	LunaModelEx�N���X�Ŏg�p�����G�t�F�N�g�n���h���̊e���`�ł�
*/
enum {
	FX_HANDLE_mTransform,			///< �����ϊ��p�s��
	FX_HANDLE_mWorld,				///< ���[���h�ϊ��s��
	FX_HANDLE_mWorldView,			///< �J������Ԃւ̕ϊ��s��

	FX_HANDLE_mBoneMatrixArray,		///< �{�[���p�s��
	FX_HANDLE_BoneWeightCount,		///< �{�[���E�F�C�g��

	FX_HANDLE_LightIsUse,			///< ���C�g�F�g�p�L���t���O
	FX_HANDLE_LightIsDirectional,	///< ���C�g�F���s�����t���O�itrue:���s����/false:�_�����j
	FX_HANDLE_LightAttenuation,		///< ���C�g�F�X�|�b�g���C�g������
	FX_HANDLE_LightColor,			///< ���C�g�F�F
	FX_HANDLE_LightParameter,		///< ���C�g�F����or�ʒu�i�������ʒu����LightIsDirectional�Ɉˑ��j

	FX_HANDLE_MaterialDiffuse,		///< �}�e���A���F�f�B�t�[�Y
	FX_HANDLE_MaterialAmbient,		///< �}�e���A���F�A���r�G���g

	FX_HANDLE_vCameraPos,			///< �J�����ʒu
	FX_HANDLE_SlideTextureU,		///< �e�N�X�`���t�X���C�h�l
	FX_HANDLE_SlideTextureV,		///< �e�N�X�`���u�X���C�h�l
	FX_HANDLE_VertexExtrusion,		///< ���_�����o���l
	FX_HANDLE_MorphWeight,			///< ���[�t�B���O�E�F�C�g

	FX_HANDLE_FogParameter,			///< �t�H�O�F�v�Z�p
	FX_HANDLE_FogTransform,			///< �t�H�O�F�y�l�Z�o�p

	FX_HANDLE_TextureStage0,		///< �e�N�X�`���F�X�e�[�W�O
	FX_HANDLE_TextureStage1,		///< �e�N�X�`���F�X�e�[�W�P
	FX_HANDLE_TextureStage2,		///< �e�N�X�`���F�X�e�[�W�Q
	FX_HANDLE_TextureStage3,		///< �e�N�X�`���F�X�e�[�W�R

	FX_HANDLE_MAX,
};

/**
	@brief	���_�^�C�v��`

	LunaModelEx�Ŏg�p����钸�_�t�H�[�}�b�g��`�B
*/
enum eVertexType
{
	VX_NORMAL,						///< �ʏ�̓����ϊ��p
	VX_MORPH,						///< ���[�t�B���O�L�蓧���ϊ��p
	VX_BONE2,						///< �Q�{�[���e���{�[���ϊ�
	VX_BONE3,						///< �R�{�[���e���{�[���ϊ�
	VX_BONE4,						///< �S�{�[���e���{�[���ϊ�
	VX_BONE2MORPH,					///< �Q�{�[���e���{�[���ϊ��{���[�t�B���O
	VX_BONE3MORPH,					///< �R�{�[���e���{�[���ϊ��{���[�t�B���O
	VX_BONE4MORPH,					///< �S�{�[���e���{�[���ϊ��{���[�t�B���O

	VX_UNKNOW,
};


//=============================================================================
// WORK STRUCT
//=============================================================================

/**
	@brief	LFD�t�@�C���w�b�_

	LFD�t�@�C���p�̃t�@�C���w�b�_�\���́B
*/
struct LFDHEADER
{
	char Guid[4];						///< �t�@�C�����ʏ��i��� 'L' 'F' 'D' '\0'
	Uint8 FontSize;						///< �t�H���g�T�C�Y
	Uint8 SheetMax;						///< �V�[�g�ő吔
	Uint16 SheetWidth;					///< �V�[�g����
	Uint16 SheetHeight;					///< �V�[�g�c��
	Uint16 FontMax;						///< �t�H���g�ő吔
	Uint16 IndexTbl[CODE_TABLE_SIZE];	///< �C���f�b�N�X�e�[�u��
};

/**
	@brief	��{�I�u�W�F�N�g

	�e�I�u�W�F�N�g�̊�{�ƂȂ�\���̂ł�
*/
struct OBJECTBASE
{
	Bool IsUse;							///< �g�p�t���O
	Uint32 RefCount;					///< �Q�ƃJ�E���^
};

/**
	@brief	��{�I�u�W�F�N�g�t�@�C��

	�e�t�@�C���I�u�W�F�N�g�̊�{�ƂȂ�\���̂ł�
*/
struct OBJECTFILE : public OBJECTBASE
{
	char FileName[MAX_PATH];				///< �t�@�C����
};

/**
	@brief	�A�_�v�^�[���

	DirectXGraphics�Ŏg�p�����A�_�v�^�[��<BR>
	�����i�[���Ă������߂̍\���̂ł�
*/
struct ADAPTERDATA
{
	Sint32 ModeCount;						///< ��ʃ��[�h��
	D3DDISPLAYMODE Mode[128];				///< ��ʃ��[�h

	Sint32 DepthCount;						///< �[�x�t�H�[�}�b�g��
	D3DFORMAT DepthFormats[16];				///< �[�x�t�H�[�}�b�g

	Sint32 TextureCount;					///< �e�N�X�`���t�H�[�}�b�g��
	D3DFORMAT TextureFormats[128];			///< �e�N�X�`���t�H�[�}�b�g

	Sint32 TargetCount;						///< �����_�����O�^�[�Q�b�g�t�H�[�}�b�g��
	D3DFORMAT TargetFormats[32];			///< �����_�����O�^�[�Q�b�g�t�H�[�}�b�g
};

/**
	@brief	�T�E���h�f�[�^

	LunaSound�N���X�Ŏg�p�����A�T�E���h�f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct SOUNDDATA : public OBJECTFILE
{
	IDirectSoundBuffer *pBuffer;
	Uint32 PausePos;
	Bool IsLoop;
	Bool IsPause;

	FILEDATA *pFile;						///< �t�@�C���n���h��
	class CAyame *pAyame;					///< �h���C�o�[

	// ����p
	struct {
		Float fStart;
		Float fEnd;
		Sint32 Time;
		Sint32 TimeAll;
		Bool IsCtrl;
	} Volume, Pan;
};

/**
	@brief	���f�B�A�I�u�W�F�N�g

	LunaMedia�N���X�Ŏg�p�����A���f�B�A�֌W�̏���<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct MEDIADATA : public OBJECTFILE
{
	IGraphBuilder	*pGB;			///< DirectShow�C���^�[�t�F�[�X
	IMediaSeeking	*pMS;			///< DirectShow�C���^�[�t�F�[�X
	IMediaEventEx	*pME;			///< DirectShow�C���^�[�t�F�[�X
	IVideoWindow	*pVW;			///< DirectShow�C���^�[�t�F�[�X
	IMediaControl	*pMC;			///< DirectShow�C���^�[�t�F�[�X
	IBasicAudio		*pBA;			///< DirectShow�C���^�[�t�F�[�X
	Sint64			StartPos;		///< �J�n�ʒu
	Sint64			EndPos;			///< �I���ʒu
	Bool			IsPlay;			///< �Đ��t���O
	Bool			IsLoop;			///< ���[�v�t���O
	Bool			IsPause;		///< �ꎞ��~�t���O
	Bool			IsTemp;			///< �ꎞ�t�@�C������̓ǂݍ��݂��ۂ�
};

/**
	@brief	�~���[�W�b�N�f�[�^

	LunaMusic�N���X�Ŏg�p�����A�V�[�P���X�f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct MUSICDATA : public OBJECTFILE
{
	IDirectMusicPerformance8 *pPerformance;	///< �p�t�H�[�}���X�I�u�W�F�N�g
	IDirectMusicSegment8 *pSegment;			///< �Z�O�����g�I�u�W�F�N�g
	IDirectMusicSegmentState *pState;		///< �Z�O�����g�X�e�[�^�X�I�u�W�F�N�g

	void *pMusicData;						///< �p�b�N�t�@�C������̃f�[�^

	Bool IsPlay;							///< �Đ������ۂ�
	Bool IsPause;							///< �ꎞ��~�����ۂ�
};

/**
	@brief	�L�[�t���[���f�[�^

	LunaAnimation�N���X�Ŏg�p�����A�A�j���[�V������<BR>
	�L�[�t���[���̏����i�[���邽�߂̍\���̂ł�
*/
struct KEYFRAMEDATA
{
	Float fTime;							///< �L�[����
	Float fParam;							///< �L�[�l
	Bool IsIn;								///< �X�v���C������IN�W����萔�ɂ��邩�ǂ���
	Bool IsOut;								///< �X�v���C������OUT�W����萔�ɂ��邩�ǂ���
	Float fIn;								///< IN�W���̒萔
	Float fOut;								///< OUT�W���̒萔

	KEYFRAMEDATA *pPrev;					///< �O���L�[�t���[���f�[�^�|�C���^
	KEYFRAMEDATA *pNext;					///< ����L�[�t���[���f�[�^�|�C���^
};

/**
	@brief	�T�E���h�f�[�^

	LunaAnimation�N���X�Ŏg�p�����A�A�j���[�V������<BR>
	�f�[�^���Ǘ����邽�߂̍\���̂ł�
*/
struct ANIMATIONDATA : public OBJECTBASE
{
	Float *pNewtonWork0;					///< �j���[�g����ԗp���[�N
	Float *pNewtonWork1;					///< �j���[�g����ԗp���[�N
	KEYFRAMEDATA *pKeys;					///< �L�[�t���[���f�[�^�|�C���^
	Uint32 KeyMax;					///< �L�[�t���[����
	Float fTimeFirst;						///< �J�n����
	Float fTimeLast;						///< �I������
};

/**
	@brief	�V�F�[�_�[�]���p�f�[�^

	LunaModelEx�N���X�Ŏg�p�����A�����_�����O����<BR>
	�V�F�[�_�[�ւ̓]���f�[�^���Ǘ����邽�߂̍\���̂ł�
*/
struct SHADERDATA
{
	CMatrix mWorld;							///< ���[���h�s��
	CMatrix mCamera;						///< �J�����s��
	CMatrix mTransform;						///< �g�����X�I�[���s��
	CMatrix mWorldView;						///< ���[���h�r���[�s��
	CMatrix mInvRotateWorld;				///< ��]�t�s��
	CMatrix mInvWorld;						///< ���[���h�t�s��

	Float fVertexExtrusion;					///< ���_�����o����
	Float fMorphWeight;						///< ���[�t�B���O�E�F�C�g
	Float fSlideTextureU;					///< �t�}�b�v�X���C�h��
	Float fSlideTextureV;					///< �u�}�b�v�X���C�h��
};

/**
	@brief	�J�����f�[�^

	LunaCamera�N���X�Ŏg�p�����A�J�����f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct LUNACAMERADATA : public OBJECTBASE
{
	CMatrix mProjection;					///< �v���W�F�N�V�����s��
	CMatrix mView;							///< �r���[�s��
	CMatrix mCamera;						///< �J�����s��
	CVector3D vPosition;						///< �ʒu

	CStyle Style;							///< �p��������

	Float fFov;								///< �J�����e�n�u
	Float fAspect;							///< �J�����A�X�y�N�g
	Float fNearZ;							///< �ŋߕ���
	Float fFarZ;							///< �ŉ�����
};

/**
	@brief	�}�C�N���X���b�h�f�[�^

	LunaMicroThread�N���X�Ŏg�p�����A<BR>
	�X���b�h�f�[�^���Ǘ����邽�߂̍\���̂ł�
*/
struct MICROTHREADDATA
{
	PMICROTHREADPROC pProcMain;							///< �X���b�h���C���֐�
	PMICROTHREADPROC pProcTerminate;						///< �X���b�h�I���֐�

	Sint32 StackSize;									///< �X�^�b�N�T�C�Y

	Uint32 NextThreadNo;						///< ���̃X���b�h�̔ԍ�
	Uint32 PrevThreadNo;						///< �O�̃X���b�h�̔ԍ�
	unsigned int ThreadId;							///< �X���b�h�̂h�c
	HANDLE hThread;									///< �X���b�h�̃n���h��
	HANDLE hSemaphore;								///< �X���b�h�̊Ǘ��p�Z�}�t�H

	Sint64 StartTime;								///< �v���J�n����
	Sint64 EndTime;								///< �v���I������
	Float CPUTime;									///< �b�o�t����

	Bool IsActive;									///< �A�N�e�B�u���ۂ�
};

/**
	@brief	�t�@�C�o�[�f�[�^

	LunaFiber�N���X�Ŏg�p�����A<BR>
	�t�@�C�o�[�f�[�^���Ǘ����邽�߂̍\���̂ł�
*/
struct FIBERDATA
{
	PFIBERPROC pProcMain;					///< �X���b�h�p�R�[���o�b�N�֐��̃|�C���^
	Uint32 StackSize;				///< �X�^�b�N�T�C�Y
	Bool IsActive;							///< �A�N�e�B�u���ۂ�
	Bool IsBoot;							///< �N�������ۂ�
	Bool IsSuspend;							///< �T�X�y���h�����ۂ�

	Uint64 StartTime;						///< �J�n����
	Uint64 EndTime;						///< �I������
	Float CPUTime;							///< �b�o�t�g�p���ԁi���j

	void *pFiber;							///< �t�@�C�o�[�̃|�C���^
	void *pNextFiber;						///< ���̃t�@�C�o�[�̃|�C���^
};

/**
	@brief	�G�t�F�N�g�f�[�^

	LunaShaderFx�N���X�Ŏg�p�����A�G�t�F�N�g���f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct SHADERFXDATA : public OBJECTFILE
{
	ID3DXEffect *pEffect;
	Uint16 Major;
	Uint16 Minor;
};

/**
	@brief	���f���f�[�^

	LunaModel�N���X�Ŏg�p�����A���f�����f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct MODELDATA : public OBJECTFILE
{
	ID3DXAnimationController *pAnimController;	///< �A�j���[�V�����R���g���[���[
	D3DXFRAME *pFrameRoot;						///< �t���[���f�[�^�ւ̃|�C���^

	Sint32 MeshCount;								///< ���b�V����
	D3DXMESHCONTAINER **ppMeshTbl;				///< ���b�V���A�N�Z�X�e�[�u��

	Float fObjectRadius;						///< �o�E���f�B���O�X�t�B�A�̔��a
	CVector3D vObjectCenter;						///< �o�E���f�B���O�X�t�B�A�̒��S
	CVector3D vBBMin;							///< �o�E���f�B���O�{�b�N�X�ŏ��l
	CVector3D vBBMax;							///< �o�E���f�B���O�{�b�N�X�ő�l

	Float fSx;									///< �w�����g��k��
	Float fSy;									///< �x�����g��k��
	Float fSz;									///< �y�����g��k��

	CStyle Style;								///< �p��������
	CMatrix mWorld;								///< ���[���h�s��
};

/**
	@brief	�}�e���A���f�[�^

	LunaModelEx�N���X�Ŏg�p�����A�}�e���A���f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct LMATERIAL
{
	D3DMATERIAL9 Mat;						///< �}�e���A���f�[�^
	LTEXTURE lTex[4];						///< �e�N�X�`���n���h��
	Uint32 VertexStart;						///< ���_�J�n�ʒu
	Uint32 VertexCount;						///< ���_��
	Uint32 IndexStart;						///< �C���f�b�N�X�J�n�ʒu
	Uint32 FaceCount;						///< �C���f�b�N�X��
};


/**
	@brief	�t�B�[���h�}�e���A���f�[�^

	�N�I�[�h�c���[�\�z�p�}�e���A���f�[�^
*/
struct LFIELDMATERIAL
{
	Sint32 IndexStart;
	Sint32 IndexCount;
};

/**
	@brief	�t�B�[���h���b�V���f�[�^

	�N�I�[�h�c���[�\�z�p���b�V���f�[�^
*/
struct LFIELDMESH
{
	CVector3D BBMin;							///< �o�E���f�B���O�{�b�N�X�ŏ��_
	CVector3D BBMax;							///< �o�E���f�B���O�{�b�N�X�ő�_

	IDirect3DVertexDeclaration9 *pVD;		///< ���_��`
	IDirect3DVertexBuffer9 *pVB;			///< ���_�o�b�t�@
	IDirect3DIndexBuffer9 *pIB;				///< �C���f�b�N�X�o�b�t�@

	void *pVertexData;						///< ���_�f�[�^
	void *pIndexData;						///< �C���f�b�N�X�f�[�^
	Uint32 VertexCount;						///< ���_��
	Uint32 IndexCount;						///< �C���f�b�N�X��

	CVector3D *pNormals;						///< �e�ʂ̖@��

	LFIELDMATERIAL *pMaterial;				///< �}�e���A���f�[�^
};

/**
	@brief	�t�B�[���h�t���[���f�[�^

	�N�I�[�h�c���[�\�z�p�t���[���f�[�^
*/
struct LFIELDFRAME
{
	LFIELDFRAME *pChild[4];					///< �q���t���[���ւ̃|�C���^
	Sint32 MeshNo;							///< �֘A�t�����Ă��郁�b�V���ԍ�

	CVector3D BBMin;							///< �o�E���f�B���O�{�b�N�X�ŏ��_
	CVector3D BBMax;							///< �o�E���f�B���O�{�b�N�X�ő�_

	BOX3D Box;								///< �o�E���f�B���O�{�b�N�X
};

/**
	@brief	�t�B�[���h�f�[�^

	LunaField�N���X�Ŏg�p�����A�t�B�[���h�f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct LUNAFIELDDATA : public OBJECTFILE
{
	Sint32 AreaCount;							///< �G���A��
	LFIELDMESH *pMeshData;					///< ���b�V���f�[�^
	Bool *pIsDrawList;						///< �`��f�[�^���X�g

	Bool IsBumpMap;							///< �o���v�}�b�v�̗L��

	LFIELDFRAME *pFrameRoot;				///< �t���[���̗L��

	LMATERIAL *pMaterial;					///< �}�e���A���f�[�^�|�C���^
	Uint32 MaterialCount;			///< �}�e���A����

	Uint16 Major;					///< �V�F�[�_�[���W���[�o�[�W����
	Uint16 Minor;					///< �V�F�[�_�[�}�C�i�[�o�[�W����

	D3DXHANDLE FxHandle[FX_HANDLE_MAX];		///< �G�t�F�N�g�n���h��
	LSHADERFX lShaderFx;					///< �G�t�F�N�g�n���h��
	Uint32 EffectSendData;			///< �G�t�F�N�g���M�f�[�^
};


//=============================================================================
// NAMESPACE
//=============================================================================
namespace LibLuna {}
using namespace LibLuna;




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�A�v���P�[�V�����Ǘ��N���X

	Windows�֘A�̊�{�������Ǘ�����N���X�ł��B
	�E�B���h�E�̐�������A���b�Z�[�W�����A
	�^�C�}�[�����A���b�Z�[�W�{�b�N�X�\���Ȃǂ�
	�E�B���h�E�A�v���̊�{�������Ǘ����Ă��܂�
*/
class Luna
{
#ifndef __TOOL_MODE__
	friend int main( int argc, char *argv[] );													///< �R���\�[���A�v�����C���֐�
	friend int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrev, LPSTR Cmd, INT Show );			///< �E�B���h�E�A�v�����C���֐�
#endif // __TOOL_MODE__

protected:
	// �A�v���P�[�V�������
	static HINSTANCE m_hInstance;				///< �C���X�^���X�n���h��
	static HANDLE m_hMutex;						///< �~���[�e�b�N�X�n���h��
	static MSG m_Message;						///< ���b�Z�[�W
	static char m_ApplicationName[MAX_PATH];	///< �A�v���P�[�V������
	static Uint64 m_NowTime;					///< ���݃t���[������
	static Uint64 m_OldTime;					///< �O�t���[������
	static Uint64 m_BeforeTime;					///< �t���[����������
	static Bool m_IsInit;						///< �������t���O
	static Bool m_IsClipMouse;					///< �}�E�X�N���b�v�t���O
	// �E�B���h�E���
	static char m_CurrentDirectry[MAX_PATH];	///< �J�����g�f�B���N�g��
	static HWND m_hWindow;						///< �E�B���h�E�n���h��
	static Sint32 m_ScreenWidth;				///< ��ʉ���
	static Sint32 m_ScreenHeight;				///< ��ʏc��
	static Bool m_IsWindowMode;					///< �E�B���h�E���[�h���ۂ�
	static Bool m_IsActive;						///< �A�N�e�B�u���ۂ�
	static Bool m_IsActiveWindow;				///< �E�B���h�E���A�N�e�B�u���ۂ�
	static Sint32 m_VirtualScreenWidth;			///< ���z��ʉ���
	static Sint32 m_VirtualScreenHeight;		///< ���z��ʏc��
	static Float m_Virtual2RealX;				///< ���z��ʂ���X�N���[����ʂւ̕ϊ�
	static Float m_Virtual2RealY;				///< ���z��ʂ���X�N���[����ʂւ̕ϊ�
	static Float m_BackUpVirtual2RealX;			///< ���z��ʂ���X�N���[����ʂւ̕ϊ��p�����[�^�o�b�N�A�b�v
	static Float m_BackUpVirtual2RealY;			///< ���z��ʂ���X�N���[����ʂւ̕ϊ��p�����[�^�o�b�N�A�b�v
	// ���j���[�֌W
	static HMENU m_hMenu;						///< ���j���[�n���h��
	static char m_MenuName[MAX_PATH];			///< ���j���[��
	// �������֌W
	static void (*m_pCallbackInit)( void );		///< ������������R�[���o�b�N�֐�
	static Uint32 m_UseLunaFlag;				///< �g�p�I�v�V����
	static Bool m_IsDrawMouse;					///< �}�E�X�`�悷�邩�ۂ�
	static Bool m_IsDrawTitleInfo;				///< �^�C�g���ɏ���`�悷�邩�ۂ�
	static Bool m_IsAllowMultiBoot;				///< ���d�N���������邩�ۂ�
	// �t���[�����
	static Uint32 m_SyncCount;					///< ���t���[����
	static Uint32 m_FrameRate;					///< �t���[�����[�g
	static Uint32 m_FPS;						///< �b�ԃt���[����
	static Uint32 m_OldFPS;						///< �b�ԃt���[�����o�b�N�A�b�v
	static Uint32 m_PPS;						///< �b�ԃ|���S����
	static Uint32 m_OldPPS;						///< �b�ԃ|���S�����o�b�N�A�b�v
	static Uint32 m_PPS3D;						///< �b�ԂR�c�|���S����
	static Uint32 m_OldPPS3D;					///< �b�ԂR�c�|���S�����o�b�N�A�b�v
	static Uint32 m_PPF;						///< �t���[���|���S����
	static Uint32 m_OldPPF;						///< �t���[���|���S�����o�b�N�A�b�v
	static Uint32 m_PPF3D;						///< �t���[���R�c�|���S����
	static Uint32 m_OldPPF3D;					///< �t���[���R�c�|���S�����o�b�N�A�b�v
	static Float m_fFrameTime;					///< �t���[������
	// ��
	static FILE *m_fpLogFile;					///< ���O�t�@�C���p�t�@�C���|�C���^
	static char m_DebugFileName[MAX_PATH];		///< �f�o�b�O�t�@�C����
	static Bool m_IsLogoutConsole;				///< ���O���R���\�[���֏o�͂��邩�ۂ�
	static Bool m_IsExit;						///< �I�����邩�ۂ�
	static CRITICAL_SECTION m_CriticalSection;	///< �N���e�B�J���Z�N�V����
	static Bool m_IsExitBlock;					///< �I���u���b�N
	static Bool m_IsExitCode;					///< �I���`�F�b�N

protected:

#ifndef __TOOL_MODE__
	static LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );		///< �E�B���h�E���b�Z�[�W�R�[���o�b�N�֐�
	static int WINAPI Boot( HINSTANCE hInst, Sint32 argc, char *argv[] );						///< Luna�̋N��
	static Bool RegisterWindowClass( void );													///< �E�B���h�E�N���X�̓o�^
	static Bool InitWindow( void );																///< �E�B���h�E�̏�����
	static void ResizeWindow( void );															///< �E�B���h�E�̃��T�C�Y
#endif // __TOOL_MODE__
	static Bool InitSystem( void );																///< �V�X�e���̏�����

public:

#ifdef __TOOL_MODE__
	static LRESULT CALLBACK MsgToolMode( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );	///< �E�B���h�E���b�Z�[�W�R�[���o�b�N�֐�
	static Bool InitToolMode( HWND hWnd, Uint32 Flags );										///< MFC����������
	static Bool StartToolMode( Uint32 ScreenWidth = 0, Uint32 ScreenHeight = 0 );				///< MFC�����J�n
	static void UninitToolMode( void );															///< MFC�����I��
	static void WaitForMsgLoop( void );															///< ���b�Z�[�W���[�v����
#else // __TOOL_MODE__
	static Bool Init( void );																	///< �V�X�e���̏�����
	static void Exit( void );																	///< �A�v���P�[�V�����̏I��
	static void Main( Sint32 ArgNum, char *ArgStr[] );											///< ���C���֐�
	static Bool MessageProc( Sint32 Msg, Sint32 wParam, Sint32 lParam );						///< ���b�Z�[�W��M
	static Bool WaitForMsgLoop( Bool IsFullActive = false );									///< ���b�Z�[�W���[�v����
	static void SyncFrame( void );																///< �t���[�������p
#endif // __TOOL_MODE__

	// �K�{
	static Bool Start( void );																	///< �V�X�e���̊J�n
	static void End( void );																	///< �V�X�e���̏I��
	// �⏕�֐�
	static void MsgBox( Uint32 Flag, const char *pTitle, const char *pStr,... );				///< ���b�Z�[�W�{�b�N�X�\��
	static Bool SelectBox( const char *pTitle, const char *pStr,... );							///< �I�������b�Z�[�W�{�b�N�X�\��
	// �����ݒ�֘A
	static void SetInitCallback( void (*pCallback)( void ) );									///< ��������R�[���o�b�N�֐��ݒ�
	static void SetUseOption( Uint32 Flags );													///< �g�p�N���X��ݒ�
	static void SetApplicationName( const char *pName );										///< �A�v���P�[�V��������ݒ�
	static void SetScreenInfo( Sint32 Width, Sint32 Height, Bool IsWindow );					///< ��ʏ���ݒ�
	static void SetMenu( const char *pMenuName );												///< ���j���[��ݒ�
	static void SetFrameRate( Sint32 FrameRate );												///< �t���[�����[�g�ݒ�
	static void SetDrawMouse( void );															///< �}�E�X�`��n�m
	static void SetDrawTitleInfo( void );														///< �^�C�g���o�[�ɏ��`��n�m
	static void SetLogFileName( const char *pFileName, const char *pExt = "html" );				///< ���O�t�@�C�����ݒ�
	static void AllowMultiBoot( void );															///< ���d�N���n�m
	static void SetVirtualScreenSize( Sint32 RealWidth, Sint32 RealHeight , Sint32 VirtualWidth, Sint32 VirtualHeight );	///< ���z��̉�ʃT�C�Y�ݒ�
	static void SetMouseClip( Bool IsClip );													///< �}�E�X�N���b�v�ݒ�
	// �擾�n
	static HINSTANCE GetInstanceHandle( void );													///< �C���X�^���X�n���h���擾
	static HWND GetWindowHandle( void );														///< �E�B���h�E�n���h���擾
	static Sint32 GetFPS( void );																///< �b�ԃt���[�����擾
	static Sint32 GetPPS( void );																///< �b�ԕ`��|���S�������
	static Sint32 GetPPF( void );																///< �t���[���ԕ`��|���S�������
	static Sint32 GetPPS3D( void );																///< �b�ԕ`��|���S�������
	static Sint32 GetPPF3D( void );																///< �t���[���ԕ`��|���S�������
	static void GetAbsPath( const char *pAbsPath );												///< ��΃p�X�擾
	static void GetApplicationName( char *pAppName );											///< �A�v���P�[�V�������擾
	static void GetScreenData( Sint32 *pWidth, Sint32 *pHeight, Bool *pIsWindow );				///< ��ʏ��擾
	static void GetVirtualScreenSize( Sint32 *pWidth, Sint32 *pHeight );						///< ���z��̉�ʃT�C�Y�擾
	static Float Virtual2RealX( Float Pos );													///< �X�N���[����ł̎��ۂ̂w���W���擾���܂�
	static Float Virtual2RealY( Float Pos );													///< �X�N���[����ł̎��ۂ̂x���W���擾���܂�
	// ���̑��e��
#ifndef __TOOL_MODE__
	static void ChangeScreenSize( Sint32 Width, Sint32 Height, Bool IsChange );					///< ��ʃT�C�Y�ύX
	static void ChangeScreenMode( void );														///< ��ʃ��[�h�ύX
#endif // __TOOL_MODE__
	static void DefaultCurrentDirectory( void );												///< �J�����g�f�B���N�g���ݒ�
	static void ResetCurrentDirectory( void );													///< �J�����g�f�B���N�g��������
	static void DrawPolygon( Sint32 Cnt );														///< �`��|���S�����ʒB
	static void DrawPolygon3D( Sint32 Cnt );													///< �`��R�c�|���S�����ʒB
	static void SetWindowCenter( HWND hWnd, HWND hWndParent );									///< ��ʂ̒����ɃE�B���h�E���ړ�����
	static void SetVirtualScreenEnable( Bool Flag );											///< ���z��ʗL���ݒ�
	// �^�C�}�[�n
	static Uint64 GetSystemTime( void );														///< �p�t�H�[�}���X�J�E���^�[���擾
	static Uint64 GetSystemTimeSecondCount( void );													///< �p�t�H�[�}���X�J�E���^�[��b�Ԃ̃J�E���g�����擾
	static Float GetFrameTime( void );															///< �t���[�����Ԏ擾
	static Uint32 GetSyncCounter( void );														///< �Q�[���̑��t���[���擾
	static Uint32 GetFrameRate( void );															///< �t���[�����[�g�擾
	// ���O�֌W
	static void LogoutConsole( void );															///< ���O���R���\�[���Ɏ����o��
	static void LogoutStart();																	///< ���O�o�͊J�n
	static void LogoutEnd();																	///< ���O�o�͏I��
	static void LogoutMainCategory( const char *pStr );											///< ���C���J�e�S���̏o��
	static void LogoutKeyword( const char *pStr,... );											///< �L�[���[�h�̏o��
	static void LogoutError( const char *pStr,... );											///< �G���[�̏o��
	static void LogoutOK( const char *pStr,... );												///< ���������o��
	static void LogoutStrong( const char *pStr,... );											///< �����o��
	static void Logout( const char *pStr,... );													///< ���O�o��
	static void LogoutNextLine( void );															///< ���O���s
	static Bool IsFullScreenMode( void );

	static void EnterCriticalSection( void );													///< �N���e�B�J���Z�N�V�����ɓ���
	static void LeaveCriticalSection( void );													///< �N���e�B�J���Z�N�V��������o��
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// ENUM
//=============================================================================
/**
	@brief	�A�j���[�V�����^�C�v��`

	LunaAnimation�N���X�Ŏg�p�����A�j���[�V�����̕��@��\����`�B
*/
enum eAnimationType
{
	ANIM_TYPE_STEP,						///< �X�e�b�v���
	ANIM_TYPE_LINEAR,					///< ���`���
	ANIM_TYPE_NEWTON,					///< �j���[�g�����
	ANIM_TYPE_TCB,						///< �s�b�a�X�v���C�����
};


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�A�j���[�V�����Ǘ��N���X

	�A�j���[�V�������Ǘ����邽�߂̃N���X�ł��B
	���`��Ԃ���s�b�a�X�v���C���܂ŁA
	�F�X�ȕ�Ԃ��T�|�[�g���Ă��܂��B
	�������̃L�[�t���[�����w�肷�邾����
	���Ԃ��Ƃ̕�Ԃ������I�ɍs���悤�ɂȂ��Ă��܂��B
*/
class LunaAnimation
{
protected:
	static ANIMATIONDATA *m_pAnimation;													///< �A�j���[�V�����f�[�^�|�C���^
	static Uint32 m_AnimMax;															///< �A�j���[�V�����f�[�^�ő吔

protected:
	static LANIMATION GetFreeHandle( void );											///< ���g�p�n���h���̎擾
	static Bool Delete( LANIMATION lAnim );												///< �폜
	static void *GetKeyData( void *pData, Float fTime, Sint32 KeyMax );					///< �L�[�f�[�^�擾
	static void Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 );	///< �G���~�[�g�֐�
	static Float InComing( void *pData0, void *pData1 );								///< ��Ԑ�[�v�Z
	static Float OutGoing( void *pData0, void *pData1 );								///< ��ԏI�[�v�Z

public:
	static Bool Initialize( void );														///< ������
	static void Finalize( void );														///< ���

	static void SetMax( Uint32 Max );													///< �ő吔�ݒ�
	static LANIMATION Create( Sint32 KeyMax );											///< �A�j���[�V�����I�u�W�F�N�g����
	static void Release( LANIMATION lAnim );											///< �I�u�W�F�N�g���
	static void SetKey( LANIMATION lAnim, Sint32 KeyNo, Float fTime, Float fParam, Bool IsIn = false, Bool IsOut = false, Float fIn = 0.0f, Float fOut = 0.0f );		///< �A�j���[�V�����L�[�w���Ĕ�
	static Float GetParameter( LANIMATION lAnim, Float fTime, eAnimationType Type, Float fDefault );	///< �p�����[�^�[�擾
	static void Optimize( LANIMATION lAnim );											///< �A�j���[�V�����f�[�^�œK��

	static Float FlatSpeed( Float fStart, Float fEnd, Float fAll, Float fNow );			///< �����^�����s���܂�
	static Float AddSpeed( Float fStart, Float fEnd, Float fAll, Float fNow );			///< �����^�����s���܂�
	static Float SubSpeed( Float fStart, Float fEnd, Float fAll, Float fNow );			///< �����^�����s���܂�
	static Float Bezier( Float p1, Float p2, Float p3, Float t );						///< Bezier��Ԃ��s���܂�
	static Float Neville( Float p1, Float p2, Float p3, Float t );						///< Neville��Ԃ��s���܂�
};




//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
typedef class INSTANCEID
{
private:
	char m_String[32];

public:
	INSTANCEID( const char *pGuid );
	~INSTANCEID( void );
	Bool operator==( const INSTANCEID &Instance ) const;
}
INSTANCEID;


//=============================================================================
/**
*/
//=============================================================================
class CBaseObject
{
	friend class CBaseList;

protected:
	CBaseObject		*m_pPrev;
	CBaseObject		*m_pNext;
	CBaseObject		*m_pParent;
	CBaseObject		*m_pChild;
	CBaseObject		*m_pSibling;

	Uint32			m_RefCount;
	Uint32			m_ChildCount;

	char			m_Name[MAX_PATH];

public:
	CBaseObject();
	virtual ~CBaseObject();

	Uint32 AddRef( void );
	Uint32 Release( void );

	Uint32 GetRefCount( void );
	Uint32 GetChildCount( void );

	CBaseObject *GetPrev( void );
	CBaseObject *GetNext( void );
	CBaseObject *GetChild( void );
	CBaseObject *GetParent( void );
	CBaseObject *GetSibling( void );

	void AddChild( CBaseObject *pChild );

	void SetName( const char *pName );
	void GetName( char *pName );
	const char *GetNamePointer( void ) const;

	virtual Bool GetInstanceByIndex( Uint32 Index, INSTANCEID &InstanceId, CBaseObject **ppInstance );
	virtual Bool GetInstanceByName( const char *pName, INSTANCEID &InstanceId, CBaseObject **ppInstance );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CBaseList : public CBaseObject
{
protected:
	CBaseObject	*m_pTop;
	CBaseObject	*m_pEnd;
	Uint32		m_Count;

public:
	CBaseList();
	virtual ~CBaseList();

	void Init( void );
	void InsertTop( CBaseObject *pObj );
	void InsertEnd( CBaseObject *pObj );
	void Erase( CBaseObject *pObj );
	CBaseObject *GetTop( void );
	CBaseObject *GetEnd( void );
	CBaseObject *GetPrev( CBaseObject *pObj );
	CBaseObject *GetNext( CBaseObject *pObj );
	Uint32 GetCount( void );
	CBaseObject *SearchFromName( const char *pName );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CBaseMgr : public CBaseList
{
protected:
	IDirect3DDevice9 *m_pD3DDevice;

public:
	CBaseMgr( IDirect3DDevice9 *pDevice );
	virtual ~CBaseMgr();

	virtual Bool GetDevice( IDirect3DDevice9 **ppDev );
	virtual IDirect3DDevice9 *GetDevicePtr( void ) const;
	virtual HWND GetWindow( void ) const;

public:
	virtual void Reset( void ){}
	virtual void Restore( void ){}
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CDeviceObject : public CBaseObject
{
protected:
	CBaseMgr *m_pManager;

public:
	CDeviceObject( CBaseMgr *pMgr );
	virtual ~CDeviceObject();

public:
	virtual void Reset( void )		= 0;
	virtual void Restore( void )	= 0;

public:
	virtual HRESULT SetTexture( Sint32 Stage, class CTexture *pTex );
	virtual char *GetError( HRESULT hr );
	virtual IDirect3DDevice9 *GetDevice( void ) const { return m_pManager->GetDevicePtr(); }
	virtual HWND GetWindow( void ) const { return m_pManager->GetWindow(); }
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CDeviceObjectMgr : public CBaseMgr
{
public:
	CDeviceObjectMgr( IDirect3DDevice9 *pDevice );
	virtual ~CDeviceObjectMgr();

	virtual void Reset( void );
	virtual void Restore( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CCollisionBuffer : public CBaseObject
{
protected:
	Uint32		m_PointMax;
	Uint32		m_PointCount;
	CVector3D	*m_pPositionLocal;
	CVector3D	*m_pPositionWorld;
	CVector3D	*m_pNormalLocal;
	CVector3D	*m_pNormalWorld;

public:
	CCollisionBuffer( Uint32 Max );
	virtual ~CCollisionBuffer();

	virtual void Reset( void );
	virtual Bool SetData( CVector3D &vPosLocal, CVector3D &vPosWorld, CVector3D &vNormLocal, CVector3D &vNormWorld );
	virtual Bool GetData( Uint32 No, CVector3D *pPosLocal, CVector3D *pPosWorld, CVector3D *pNormLocal, CVector3D *pNormWorld );
	virtual Uint32 GetCount( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
extern const INSTANCEID IID_MATERIAL;


//=============================================================================
/**
*/
//=============================================================================
class CMaterial : public CBaseObject
{
protected:
	Bool			m_IsUseMaterialState;
	MATERIALSTATE	m_State;
	D3DMATERIAL9	m_Material;
	LTEXTURE		m_lTexture[TEXTURE_STAGE_MAX];
	char			m_TextureName[TEXTURE_STAGE_MAX][MAX_PATH];

public:
	CMaterial();
	virtual ~CMaterial();

	virtual void SetMaterial( D3DMATERIAL9 *pMaterial );
	virtual void SetTexture( Uint32 Stage, LTEXTURE lTex );
	virtual void SetMaterialAlpha( Float fAlpha );
	virtual void SetTextureName( Uint32 Stage, const char *pName );
	virtual void GetTextureName( Uint32 Stage, char *pName );

	virtual Uint32 Rendering( Uint32 Flag, LSHADERFX lShader, D3DXATTRIBUTERANGE *pAttr );

	virtual void SetMateriaStateEnable( Bool IsEnable );
	virtual void SetTextureState( Uint32 Stage, D3DTEXTURESTAGESTATETYPE State, Uint32 Param );
	virtual void SetSamplerState( Uint32 Stage, D3DSAMPLERSTATETYPE State, Uint32 Param );
	virtual void SetBlendingType( eBlendType BlendType );
	virtual void SetFilterEnable( Bool Flag );
	virtual void SetColorkeyEnable( Bool Flag );
	virtual void SetZBufferEnable( Bool Flag );
	virtual void SetZWriteEnable( Bool Flag );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CVertexBuffer : public CBaseObject
{
protected:
	Uint32						m_VertexCount;
	VERTEXALL					*m_pVertex;
	IDirect3DVertexBuffer9		*m_pVertexBuffer;
	IDirect3DVertexDeclaration9	*m_VertexDeclaration;
	eVertexType					m_VertexType;
	Uint16						m_VxShaderMajor;
	Uint16						m_VxShaderMinor;

public:
	CVertexBuffer( Uint32 VertexCount );
	virtual ~CVertexBuffer();

	virtual void Reset( void );
	virtual void Restore( void );

	virtual Bool Update( Uint16 MajorVersion, Uint16 MinorVersion, eVertexType Type );
	virtual VERTEXALL *GetPointer( void );
	virtual Uint32 GetCount( void );

	virtual void SetDevice( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CMeshIndex : public CBaseObject
{
protected:
	Uint32					m_IndexCount;
	Uint16					*m_pIndex;
	IDirect3DIndexBuffer9	*m_pIndexBuffer;
	Uint16					m_VxShaderMajor;
	Uint16					m_VxShaderMinor;

public:
	CMeshIndex( Uint32 IndexCount );
	virtual ~CMeshIndex();

	virtual void Reset( void );
	virtual void Restore( void );

	virtual Bool Update( Uint16 MajorVersion, Uint16 MinorVersion );
	virtual Uint16 *GetPointer( void );
	virtual Uint32 GetCount( void );

	virtual void SetDevice( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
enum eShaderBaseType
{
	SHADER_TRANSFORM_NORMAL		= (1 <<  0),
	SHADER_TRANSFORM_MORPH		= (1 <<  1),
	SHADER_TRANSFORM_BONE		= (1 <<  2),

	SHADER_LIGHT0				= (1 <<  3),
	SHADER_LIGHT1				= (1 <<  4),
	SHADER_LIGHT2				= (1 <<  5),
	SHADER_LIGHT3				= (1 <<  6),
	SHADER_LIGHT4				= (1 <<  7),

	SHADER_TEXTURE_BASE			= (1 <<  9),
	SHADER_TEXTURE_LIGHT		= (1 << 10),
	SHADER_TEXTURE_REFLECT		= (1 << 11),
	SHADER_TEXTURE_PROJECT		= (1 << 12),

	SHADER_TECHNIQUE_PASS1		= (1 << 13),
	SHADER_TECHNIQUE_PASS2		= (1 << 14),
};


//=============================================================================
/**
*/
//=============================================================================
class CShader : public CBaseObject
{
protected:
	ID3DXEffect *m_pEffect;

public:
	CShader();
	virtual ~CShader();

	virtual void Reset( void );
	virtual void Restore( void );

	virtual Bool Create( Uint32 TypeFlag, Uint32 BoneWeightCount, Uint32 BoneMatrixCoun, Uint32 *pSendFlag );
	virtual Bool CreateFromFile( const char *pFileName );
	virtual Bool CreateFromMemory( const char *pShader, Uint32 Size );

	virtual Bool Begin( Uint32 *pPassMax, Uint32 Flag = D3DXFX_DONOTSAVESHADERSTATE );
	virtual void End( void );
	virtual void BeginPass( Uint32 Pass );
	virtual void EndPass( void );
	virtual void UpdateParameter( void );

	virtual D3DXHANDLE GetParameterByName( const char *pName );
	virtual D3DXHANDLE GetParameterBySemantic( const char *pSemantic );

	virtual void SetBool( D3DXHANDLE pHandle, BOOL Param );
	virtual void SetBoolArray( D3DXHANDLE pHandle, BOOL *pParam, Sint32 Num );
	virtual void SetFloat( D3DXHANDLE pHandle, Float Param );
	virtual void SetFloatArray( D3DXHANDLE pHandle, Float *pParam, Sint32 Num );
	virtual void SetInt( D3DXHANDLE pHandle, Sint32 Param );
	virtual void SetIntArray( D3DXHANDLE pHandle, Sint32 *pParam, Sint32 Num );
	virtual void SetMatrix( D3DXHANDLE pHandle, D3DXMATRIX *pMatrix );
	virtual void SetMatrixArray( D3DXHANDLE pHandle, D3DXMATRIX *pMatrix, Sint32 Num );
	virtual void SetMatrixTranspose( D3DXHANDLE pHandle, D3DXMATRIX *pMatrix );
	virtual void SetMatrixTransposeArray( D3DXHANDLE pHandle, D3DXMATRIX *pMatrix, Sint32 Num );
	virtual void SetString( D3DXHANDLE pHandle, const char *pStr );
	virtual void SetTexture( D3DXHANDLE pHandle, CTexture *pTex );
	virtual void SetVector( D3DXHANDLE pHandle, D3DXVECTOR4 *pVec );
	virtual void SetVectorArray( D3DXHANDLE pHandle, D3DXVECTOR4 *pVec, Sint32 Num );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CFont : public CDeviceObject
{
	friend class CFontMgr;

protected:
	HDC m_hDC;									///< �f�o�C�X�R���e�L�X�g�n���h��
	HFONT m_hFont;								///< �t�H���g�n���h��
	HFONT m_hFontOld;							///< �O�̃t�H���g�n���h��
	TEXTMETRIC m_TextMetric;					///< �t�H���g���g���b�N
	Sint32 m_FontSize;							///< �t�H���g�T�C�Y
	CTexture *m_pTarget;						///< �^�[�Q�b�g�n���h��
	char *m_pBuffer;							///< �o�b�t�@�|�C���^
	Bool m_IsBegin;								///< �t�H���g�`��\��Ԃ��ǂ���
	Bool m_IsAlpha;								///< �A���t�@�`�����l���L�����ǂ���
	Bool m_IsUpdate;							///< �`���Ƀe�N�X�`�����X�V���邩�ǂ���

protected:
	CFont( CBaseMgr *pMgr );
	virtual ~CFont();

	virtual void Reset( void ) {}
	virtual void Restore( void ) {}

protected:
	virtual Bool Create( const char *pFontFace, Sint32 FontSize, Bool IsItalic = false, Bool IsBold = false );	///< �t�H���g�I�u�W�F�N�g����

	virtual Sint32 GetFontBuffer( HDC hDC, Uint16 Code, GLYPHMETRICS *pGM, char **ppData, Bool Alpha );	///< �t�H���g�o�b�t�@�擾
	virtual Bool LockTarget( void **ppBits, Sint32 *pPitch, D3DFORMAT *pFormat, Sint32 *pWidth, Sint32 *pHeight );	///< �`��^�[�Q�b�g���b�N
	virtual void UnlockTarget( void );															///< �`��^�[�Q�b�g���b�N����
	virtual void DrawPixel1555( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< �T�[�t�F�C�X�ɕ����`��
	virtual void DrawPixel565( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< �T�[�t�F�C�X�ɕ����`��
	virtual void DrawPixel4444( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< �T�[�t�F�C�X�ɕ����`��
	virtual void DrawPixel8888( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< �T�[�t�F�C�X�ɕ����`��
	virtual void DrawPixel4444AA( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< �T�[�t�F�C�X�ɕ����`��
	virtual void DrawPixel8888AA( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< �T�[�t�F�C�X�ɕ����`��
	virtual Bool Clip( CFontDrawRect *pDst, CFontDrawRect *pSrc, Sint32 Width, Sint32 Height );			///< �N���b�s���O

public:
	virtual void SetDestination( CTexture *pTarget = NULL );								///< �`���ݒu
	virtual void DrawChar( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );									///< �����`��
	virtual void DrawCharAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );								///< �A���`�G�C���A�X�t�������`��
	virtual Sint32 DrawText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< �e�L�X�g�`��
	virtual Sint32 DrawTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< �A���`�G�C���A�X�t���e�L�X�g�`��
	virtual Sint32 DrawPText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< �v���|�[�V���i���e�L�X�g�`��
	virtual Sint32 DrawPTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );					///< �A���`�G�C���A�X�t���v���|�[�V���i���e�L�X�g�`��
	virtual void GetFontData( Uint16 Code, ABC *pABC );												///< �t�H���g�f�[�^�擾

	virtual void Begin( Bool IsUpdate = true );														///< �t�H���g�����J�n
	virtual void End( void );																					///< �t�H���g�����I��

	virtual Sint32 GetTextWidth( const char *pStr );												///< ������̍ő剡���擾
	virtual Sint32 GetFontSize( void );																	///< �t�H���g�T�C�Y�擾
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CFontMgr : public CBaseMgr
{
protected:
	Sint32	m_StackMax;
	Sint32	m_StackCount;
	CFont	**m_pFontStackTbl;

public:
	CFontMgr( IDirect3DDevice9 *pDevice, Sint32 StackMax );
	virtual ~CFontMgr();

	virtual CFont *Create( const char *pFontFace, Sint32 FontSize, Bool IsItalic = false, Bool IsBold = false );

	virtual void Begin( CFont *pFont, Bool IsUpdate = true );													///< �t�H���g�����J�n
	virtual void End( void );																					///< �t�H���g�����I��

	virtual void DrawChar( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );									///< �����`��
	virtual void DrawCharAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );								///< �A���`�G�C���A�X�t�������`��
	virtual Sint32 DrawText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< �e�L�X�g�`��
	virtual Sint32 DrawTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );					///< �A���`�G�C���A�X�t���e�L�X�g�`��
	virtual Sint32 DrawPText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< �v���|�[�V���i���e�L�X�g�`��
	virtual Sint32 DrawPTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );					///< �A���`�G�C���A�X�t���v���|�[�V���i���e�L�X�g�`��
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
struct CFontSheetData
{
	Uint8 SheetNo;		///< �V�[�g�ԍ�
	Uint8 abcA;			///< ABC��
	Uint8 abcB;			///< ABC��
	Uint8 abcC;			///< ABC��
	Uint16 x1;			///< UV�f�[�^
	Uint16 y1;			///< UV�f�[�^
	Uint16 x2;			///< UV�f�[�^
	Uint16 y2;			///< UV�f�[�^
};

//=============================================================================
/**
*/
//=============================================================================
class CBaseFontSheet : public CDeviceObject
{
protected:
	CFont *m_pFont;
	CFontSheetData *m_pSheetTbl;					///< �t�H���g�V�[�g�f�[�^�|�C���^
	CTexture *m_pTextures[SHEET_MAX];				///< �e�N�X�`���n���h��
	Uint16 m_IndexTbl[CODE_TABLE_SIZE];				///< �C���f�b�N�X�e�[�u��

	Sint32 m_SheetWidth;							///< �V�[�g����
	Sint32 m_SheetHeight;							///< �V�[�g�c��
	Sint32 m_SheetCount;							///< �V�[�g��
	Sint32 m_FontSize;								///< �t�H���g�T�C�Y
	Sint32 m_FontMax;								///< �t�H���g��

	Bool m_IsAlpha;									///< ���`�����l�����g�����ۂ�
	Bool m_IsAntialias;								///< �A���`�G�C���A�X���g�����ۂ�

protected:
	CBaseFontSheet( CBaseMgr *pMgr );
	virtual ~CBaseFontSheet();

	virtual Uint16 Code2Index( Uint16 Code );																///< �����R�[�h����C���f�b�N�X�ւ̕ϊ�

public:
	virtual Bool CreateSheetTable( const char *pBuffer, CFont *pFont, Bool IsAntialias );					///< �t�H���g�I�u�W�F�N�g����
	virtual Bool CreateSheetTableFromFile( const char *pFileName, const char *pExt );						///< �t�H���g�I�u�W�F�N�g��LFD���琶��
	virtual Bool CreateSheetTableFromMemory( void *pData, const char *pExt );								///< �t�H���g�I�u�W�F�N�g��LFD���琶��

	virtual Bool ReCreateSheetTable( const char *pBuffer );													///< �t�H���g�I�u�W�F�N�g����

	virtual Bool GetWidth( const char *pStr, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight );
	virtual void GetHeight( Sint32 *pHeight );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
struct CSortPrimitive
{
	Uint8 Data[sizeof(PRIMVERTEX4[3])];
	CSortPrimitive *pNext;
};

//=============================================================================
/**
*/
//=============================================================================
class CPrimitive2DBase : public CDeviceObject
{
	friend class CPrimitive2DBaseMgr;

protected:
	IDirect3DVertexBuffer9 *m_pVertexBuffer;
	CSortPrimitive **m_ppSortTop;
	Uint8 *m_pVertexData;
	eVertexPrimitiveType m_VertexType;

	Uint32 m_VertexFVF;
	Uint32 m_VertexDataSize;
	Uint32 m_VertexSize;
	Uint32 m_VertexMax;
	Uint32 m_VertexCount;
	Uint32 m_VertexOffset;
	Uint32 m_RequestedVertexCount;

	Bool m_IsSortZ;
	Bool m_IsPers;
	Bool m_IsZoom;
	Bool m_IsScissoring;

	D3DXVECTOR4 m_PerseCenter;
	D3DXVECTOR4 m_ZoomCenter;
	Float m_ScissorX1;
	Float m_ScissorY1;
	Float m_ScissorX2;
	Float m_ScissorY2;

protected:
	CPrimitive2DBase( CBaseMgr *pMgr );
	virtual ~CPrimitive2DBase();

protected:
	void SetVertexLinear( CPrimitivePoint2D *pPtIn1, CPrimitivePoint2D *pPtIn2, CPrimitivePoint2D *pPtOut, Float Ave );

public:
	virtual void Reset( void );
	virtual void Restore( void );

	virtual Bool Push( CPrimitivePoint2D *pPoint, Uint32 Count )	= 0;
	virtual void Begin( void )										= 0;
	virtual void End( void )										= 0;
	virtual void Render( void )										= 0;

public:
	virtual Sint32 GetRequestedVertexCount( void );
	virtual void SetScissoring( RECT *pRect );
	virtual void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );
	virtual void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPrimitive2DBaseMgr : public CDeviceObjectMgr
{
public:
	CPrimitive2DBaseMgr( IDirect3DDevice9 *pDevice );
	virtual ~CPrimitive2DBaseMgr();

	virtual void SetScissoring( RECT *pRect );
	virtual void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );
	virtual void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPrimitive3DBase : public CDeviceObject
{
	friend class CPrimitive3DBaseMgr;

protected:
	IDirect3DVertexBuffer9 *m_pVertexBuffer;
	Uint8 *m_pVertexData;
	eVertexPrimitiveType m_VertexType;
	Uint32 m_VertexFVF;
	Uint32 m_VertexDataSize;
	Uint32 m_VertexSize;
	Uint32 m_VertexMax;
	Uint32 m_VertexCount;
	Uint32 m_VertexOffset;
	Uint32 m_RequestedVertexCount;

protected:
	CPrimitive3DBase( CBaseMgr *pMgr );
	virtual ~CPrimitive3DBase();

public:
	virtual void Reset( void );
	virtual void Restore( void );

	virtual Bool Push( CPrimitivePoint3D *pPoint, Uint32 Count )	= 0;
	virtual void Begin( void )										= 0;
	virtual void End( void )										= 0;
	virtual void Render( void )										= 0;

public:
	virtual Sint32 GetRequestedVertexCount( void );
};

}




//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPrimitive3DBaseMgr : public CDeviceObjectMgr
{
public:
	CPrimitive3DBaseMgr( IDirect3DDevice9 *pDevice );
	virtual ~CPrimitive3DBaseMgr();
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPoint2D : public CPrimitive2DBase
{
	friend class CPoint2DMgr;

protected:
	CPoint2D( CBaseMgr *pMgr );
	virtual ~CPoint2D( void );

	virtual void EffectPolygon( CPrimitivePoint2D *pDst, CPrimitivePoint2D *pSrc );

public:
	virtual Bool Create( Uint32 VertexMax );

	virtual Bool Push( CPrimitivePoint2D *pPoint, Uint32 Count );
	virtual void Render( void );
	virtual void Begin( void );
	virtual void End( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPoint2DMgr : public CPrimitive2DBaseMgr
{
protected:

public:
	CPoint2DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CPoint2DMgr();

	virtual CPoint2D *Create( Uint32 VertexMax );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPoint3D : public CStyle, public CPrimitive3DBase
{
	friend class CPoint3DMgr;

protected:
	CPoint3D( CBaseMgr *pMgr );
	virtual ~CPoint3D();

public:
	virtual Bool Create( Uint32 VertexMax );

	virtual Bool Push( CPrimitivePoint3D *pPoint, Uint32 Count );
	virtual void Render( void );
	virtual void Begin( void );
	virtual void End( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPoint3DMgr : public CPrimitive3DBaseMgr
{
protected:

public:
	CPoint3DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CPoint3DMgr();

	virtual CPoint3D *Create( Uint32 VertexMax );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPrimitive2D : public CPrimitive2DBase
{
	friend class CPrimitive2DMgr;

protected:
	virtual Uint32 ScissorPolygon( CPrimitivePoint2D *pDst, CPrimitivePoint2D *pSrc );
	virtual Uint32 ScissorPolygonLeft( CPrimitivePoint2D *pPtIn, CPrimitivePoint2D *pPtOut, Uint32 VxNum );
	virtual Uint32 ScissorPolygonTop( CPrimitivePoint2D *pPtIn, CPrimitivePoint2D *pPtOut, Uint32 VxNum );
	virtual Uint32 ScissorPolygonRight( CPrimitivePoint2D *pPtIn, CPrimitivePoint2D *pPtOut, Uint32 VxNum );
	virtual Uint32 ScissorPolygonBottom( CPrimitivePoint2D *pPtIn, CPrimitivePoint2D *pPtOut, Uint32 VxNum );
	virtual void EffectPolygon( CPrimitivePoint2D *pDst, CPrimitivePoint2D *pSrc );

protected:
	CPrimitive2D( CBaseMgr *pMgr );
	virtual ~CPrimitive2D();

public:
	virtual Bool Create( Uint32 VertexMax, eVertexPrimitiveType VertexType, Bool IsSortZ );
	virtual Bool Resize( Uint32 Count );

	virtual Bool Push( CPrimitivePoint2D *pPoint, Uint32 Count );
	virtual void Begin( void );
	virtual void End( void );
	virtual void Render( void );
};

}




//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPrimitive2DMgr : public CPrimitive2DBaseMgr
{
public:
	CPrimitive2DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CPrimitive2DMgr();

	virtual CPrimitive2D *Create( Uint32 VertexMax, eVertexPrimitiveType VertexType, Bool IsSortZ );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPrimitive3D : public CStyle, public CPrimitive3DBase
{
	friend class CPrimitive3DMgr;

protected:
	CPrimitive3D( CBaseMgr *pMgr );
	virtual ~CPrimitive3D();

public:
	virtual Bool Create( Uint32 VertexMax, eVertexPrimitiveType VertexType );

	virtual Bool Push( CPrimitivePoint3D *pPoint, Uint32 Count );
	virtual void Render( void );
	virtual void Begin( void );
	virtual void End( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CPrimitive3DMgr : public CPrimitive3DBaseMgr
{
protected:

public:
	CPrimitive3DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CPrimitive3DMgr();

	virtual CPrimitive3D *Create( Uint32 VertexMax, eVertexPrimitiveType VertexType );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CSprite2D : public CPrimitive2D
{
	friend class CSprite2DMgr;

protected:
	CTexture *m_pTexture[TEXTURE_STAGE_MAX];

protected:
	CSprite2D( CBaseMgr *pMgr );
	virtual ~CSprite2D();

public:
	virtual void AttatchTexture( Uint32 Stage, CTexture *pTex );

	virtual void Render( void );

	virtual void DrawSquare( CLunaRect *pDstRect, Float Pz, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 UvCount );
	virtual void DrawSquareRotate( CLunaRect *pDstRect, Float Pz, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 Angle, Uint32 UvCount, Float fCx = 0.0f, Float fCy = 0.0f );
	virtual void DrawSquareRotateXYZ( CLunaRect *pDstRect, Float Pz, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ, Uint32 UvCount );
	virtual void DrawSquareMatrix( CMatrix *pMatrix, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 UvCount );

	virtual void DrawRing( Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Float Wrap, Uint32 UvCount );
	virtual void DrawRingRotate( Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 Angle, Float Wrap, Uint32 UvCount );
	virtual void DrawRingRotateXYZ( Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ, Float Wrap, Uint32 UvCount );

	virtual void DrawRingEx( Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Float Wrap, Uint32 UvCount );
	virtual void DrawRingExRotate( Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 Angle, Float Wrap, Uint32 UvCount );
	virtual void DrawRingExRotateXYZ( Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ, Float Wrap, Uint32 UvCount );

	virtual void DrawRotate( CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 Angle, Sint32 UvCount );
	virtual void DrawRotateXYZ( CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ, Sint32 UvCount );

	virtual void DrawList( Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );
};

}




//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CSprite2DMgr : public CPrimitive2DBaseMgr
{
protected:

public:
	CSprite2DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CSprite2DMgr();

	virtual CSprite2D *Create( Uint32 VertexMax, eVertexPrimitiveType VertexType, Bool IsSortZ );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CSprite3D : public CPrimitive3D
{
	friend class CSprite3DMgr;

protected:
	CTexture *m_pTexture[TEXTURE_STAGE_MAX];

protected:
	CSprite3D( CBaseMgr *pMgr );
	virtual ~CSprite3D();

public:
	virtual Bool Create( Uint32 VertexMax, eVertexPrimitiveType VertexType );
	virtual void AttatchTexture( Uint32 Stage, CTexture *pTex );

	virtual void Render( void );

	virtual void DrawSquare( CStyle *pStyle, Float Px, Float Py, Float Pz, Float fSx, Float fSy, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 UvCount );
	virtual void DrawRing( CStyle *pStyle, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );
	virtual void DrawRingEx( CStyle *pStyle, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );

	virtual void DrawListXY( Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );
	virtual void DrawListYZ( Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );
	virtual void DrawListZX( Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CSprite3DMgr : public CPrimitive3DBaseMgr
{
protected:

public:
	CSprite3DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CSprite3DMgr();

	virtual CSprite3D *Create( Uint32 VertexMax, eVertexPrimitiveType VertexType );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CFontSprite2D : public CBaseFontSheet
{
	friend class CFontSprite2DMgr;

protected:
	Bool m_IsSortZ;
	Bool m_IsSizeHalf;
	Sint32 m_Space;
	CSprite2D *m_pSprites[SHEET_MAX];

protected:
	CFontSprite2D( CBaseMgr *pMgr );
	virtual ~CFontSprite2D();

	virtual void Reset( void ) {}
	virtual void Restore( void ) {}

public:
	virtual Bool Create( const char *pBuffer, Uint32 Num, CFont *pFont, Bool IsSortZ = false, Bool IsAntialias = true );
	virtual Bool CreateFromFile( const char *pFileName, const char *pExt, Uint32 Num, Bool IsSortZ = false );

	virtual void DisableHankakuSizeHalf( void );

	virtual void BufferResize( Uint32 Count );
	virtual Bool ReCreateStringBuffer( const char *pBuffer, Uint32 Num );

	virtual void Begin( Sint32 Space );
	virtual void End( void );
	virtual void Render( void );

	virtual void DrawString( const char *pStr, Sint32 Px, Sint32 Py, Float Pz, D3DCOLOR Color );
	virtual void DrawStringP( const char *pStr, Sint32 Px, Sint32 Py, Float Pz, D3DCOLOR Color );
	virtual Sint32 DrawChara( const char *pStr, CLunaRect *pDst, Float Pz, D3DCOLOR Color );
	virtual Sint32 DrawCharaRotate( const char *pStr, CLunaRect *pDst, Float Pz, D3DCOLOR Color, Sint32 Angle );
	virtual Sint32 DrawCharaRotateXYZ( const char *pStr, CLunaRect *pDst, Float Pz, D3DCOLOR Color, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );

	virtual POINT GetStringLastPos( const char *pStr, Sint32 Px, Sint32 Py );
	virtual POINT GetStringLastPosP( const char *pStr, Sint32 Px, Sint32 Py );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CFontSprite2DMgr : public CBaseMgr
{
public:
	CFontSprite2DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CFontSprite2DMgr();

	virtual CFontSprite2D *Create( const char *pBuffer, Uint32 Num, CFont *pFont, Bool IsSortZ = false, Bool IsAntialias = true );
	virtual CFontSprite2D *CreateFromFile( const char *pFileName, const char *pExt, Uint32 Num, Bool IsSortZ = false );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CFontSprite3D : public CBaseFontSheet
{
	friend class CFontSprite3DMgr;

protected:
	CSprite3D *m_pSprites[SHEET_MAX];

protected:
	CFontSprite3D( CBaseMgr *pMgr );
	virtual ~CFontSprite3D();

	virtual void Reset( void ) {}
	virtual void Restore( void ) {}

	virtual Sint32 GetWidth( const char *pStr );

public:
	virtual Bool Create( const char *pBuffer, Uint32 Num, CFont *pFont, Bool IsAntialias = true );
	virtual Bool CreateFromFile( const char *pFileName, const char *pExt, Uint32 Num );

	virtual Bool ReCreateStringBuffer( const char *pBuffer, Uint32 Num );

	virtual void Begin( void );
	virtual void End( void );
	virtual void Render( void );

	virtual void DrawString( const char *pStr, CStyle *pStyle, Float fScale, D3DCOLOR Color );
	virtual void DrawStringP( const char *pStr, CStyle *pStyle, Float fScale, D3DCOLOR Color );
};
}




//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CFontSprite3DMgr : public CBaseMgr
{
public:
	CFontSprite3DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CFontSprite3DMgr();

	virtual CFontSprite3D *Create( const char *pBuffer, Uint32 Num, CFont *pFont, Bool IsAntialias = true );
	virtual CFontSprite3D *CreateFromFile( const char *pFileName, const char *pExt, Uint32 Num );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CAnimation : public CBaseObject
{
	friend class CModelLoader;

protected:
	LANIMATION		m_lAnimTransX;
	LANIMATION		m_lAnimTransY;
	LANIMATION		m_lAnimTransZ;
	LANIMATION		m_lAnimScaleX;
	LANIMATION		m_lAnimScaleY;
	LANIMATION		m_lAnimScaleZ;
	LANIMATION		m_lAnimQuatNo;

	CQuaternion		*m_pQuaternionTbl;

public:
	CAnimation();
	~CAnimation();

	void ComputeAnimationMatrix( CMatrix &mOut, Float fTime, eAnimationType Type, CVector3D &vPos, CVector3D &vScale, CMatrix &mRot );
	void ComputeAnimationData( CVector3D &vOutPos, CVector3D &vOutScale, CQuaternion &qOutRot, Float fTime, eAnimationType Type, CVector3D &vPos, CVector3D &vScale, CMatrix &mRot );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
extern const INSTANCEID IID_ANIMATIONSET;


//=============================================================================
/**
*/
//=============================================================================
class CAnimationSet : public CBaseObject
{
protected:
	Uint32 m_TimeMax;

public:
	CAnimationSet();
	virtual ~CAnimationSet();

	virtual void SetTimeMax( Uint32 Max );
	virtual Uint32 GetTimeMax( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CBaseFrame : public CBaseObject
{
protected:
	static long m_SpaceCount;

protected:
	CMatrix		m_TransformMatrix;
	CVector3D	m_vTransmformPosition;
	CVector3D	m_vTransmformScale;
	CMatrix		m_mTransmformRotate;

	CMatrix		m_LocalMatrix;
	CMatrix		m_WorldMatrix;

public:
	CBaseFrame();
	virtual ~CBaseFrame();

public:
	static void SetSpace( long Cnt );
	static long GetSpace( void );

public:
	virtual CMatrix *GetWorldMatrixPointer( void );

public:
	virtual void UpdateTransform( CMatrix &Matrix, CMatrix &MatrixRoot ) = 0;
	virtual void UpdateAnimation( Float fTimeA, Float fTimeB, eAnimationType Type ) = 0;
	virtual Uint32 Rendering( void ) = 0;
	virtual void LogoutName( void ) = 0;
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
extern const INSTANCEID IID_BASEMESH;
class CFrame;

//=============================================================================
/**
*/
//=============================================================================
class CBaseMesh : public CBaseFrame
{
protected:
	CVertexBuffer		*m_pVertexBuffer;
	CMeshIndex			*m_pIndexBuffer;
	CShader				*m_pShader;
	CCollisionBuffer	*m_pCollisionBuff;
	eVertexType			m_VertexType;
	CVector3D			m_vBBMin;
	CVector3D			m_vBBMax;
	CVector3D			m_vCenter;
	Float				m_fRadius;
	BOX3D				m_Box;
	Uint32				m_ShaderSendFlag;
	Float				m_fSlideTextureU;
	Float				m_fSlideTextureV;
	Float				m_fVertexExtrusion;
	Float				m_fMorphWeight;
	CMaterial			**m_ppMaterialList;
	Uint32				m_MaterialCount;
	Uint16				m_VxShaderMajor;
	Uint16				m_VxShaderMinor;
	Uint8				m_RenderFlag;

protected:
	HRESULT Optimize( ID3DXMesh *pMesh );
	virtual void UpdateCollisionBuffer( void );
	virtual void ComputeMeshNormal( void );

public:
	CBaseMesh( Uint16 ShaderVersionMajor, Uint16 ShaderVersionMinor );
	virtual ~CBaseMesh();

	virtual Bool GetInstanceByIndex( Uint32 Index, const INSTANCEID &InstanceId, CBaseObject **ppInstance );
	virtual Bool GetInstanceByName( const char *pName, const INSTANCEID &InstanceId, CBaseObject **ppInstance );

	virtual void Reset( void );
	virtual void Restore( void );
	virtual void UpdateMaterialList( void );
	virtual void SetShader( CShader *pShader, Uint32 Flag );
	virtual void SetVertexExtrusion( Float fParam );
	virtual void SetSlideTextureU( Float fParam );
	virtual void SetSlideTextureV( Float fParam );
	virtual void SetMorphWeight( Float fParam );
	virtual void SetTexture( Uint32 Stage, LTEXTURE lTex, Sint32 MeshNo );
	virtual void SetMaterialAlpha( Float fAlpha, Sint32 MaterialNo );
	virtual void SetMorphTarget( CBaseMesh *pMesh );
	virtual void UpdateAnimation( Float fTimeA, Float fTimeB, eAnimationType Type );
	virtual void GetBoundingSphere( CVector3D *pCenter, Float *pRadius );
	virtual void GetBoundingBox( CVector3D *pBBMin, CVector3D *pBBMax, BOX3D *pBox );
	virtual void GetWorldMatrix( CMatrix *pMatrix );
	virtual Bool CollisionRay( CVector3D &vStart, CVector3D &vEnd, Bool IsBackFace, Bool IsNormal );
	virtual Bool GetCollisionInfo( Uint32 PointNo, CVector3D *pPositionLocal, CVector3D *pPositionWorld, CVector3D *pNormalLocal, CVector3D *pNormalWorld );
	virtual Uint32 GetCollisionInfoCount( void );
	virtual Uint32 GetMaterialCount( void );
	virtual Uint32 GetMaterialIndexByName( const char *pName );
	virtual Bool IsMorph( void );

public:
	virtual void UpdateBoneConnect( CFrame **ppFrameList, Sint32 FrameCount ) = 0;
	virtual Bool GenerateMeshData( ID3DXMesh *pMesh, ID3DXSkinInfo *pSkinInfo, Uint32 *pAdjacency ) = 0;
	virtual void UpdateTransform( CMatrix &Matrix, CMatrix &MatrixRoot ) = 0;
	virtual Uint32 Rendering( void ) = 0;
	virtual Bool IsSkinned( void ) = 0;
	virtual Uint32 GetWeightCount( void ) = 0;
	virtual Uint32 GetBoneCount( void ) = 0;

	virtual void SetRenderFlag( Uint8 Flag, Uint8 Mask = 0xff );
	virtual Uint8 GetRenderFlag( void ) const;

	virtual void LogoutName( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CBoneMesh : public CBaseMesh
{
protected:
	CMatrix			*m_pBoneOffsetMatrix;
	Uint32			m_BoneMax;
	Uint32			m_FaceInflCount;
	Uint32			m_BoneCombinationCount;
	ID3DXBuffer		*m_pBoneCombination;
	ID3DXSkinInfo	*m_pSkinInfo;
	D3DXMATRIX		**m_ppBoneMatrixTbl;

protected:
	virtual Bool ConstructionBuffer( ID3DXMesh *pMesh, D3DXATTRIBUTERANGE *pAttrTbl, Uint32 AttrCnt );
	virtual void UpdateBoneConnect( CFrame **ppFrameList, Sint32 FrameCount );
	virtual void SendToShaderConstant( void );

public:
	CBoneMesh( Uint16 ShaderVersionMajor, Uint16 ShaderVersionMinor );
	virtual ~CBoneMesh();

	Bool GenerateMeshData( ID3DXMesh *pMesh, ID3DXSkinInfo *pSkinInfo, Uint32 *pAdjacency );

	virtual void UpdateTransform( CMatrix &Matrix, CMatrix &MatrixRoot );
	virtual Uint32 Rendering( void );
	virtual void ConnectAnimation( CAnimationSet *pAnimSet );
	virtual Bool IsSkinned( void );
	virtual Uint32 GetWeightCount( void );
	virtual Uint32 GetBoneCount( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
enum eSurfaceType
{
	SURFACE_TYPE_RENDERTARGET,
	SURFACE_TYPE_DEPTHSTENCIL,
	SURFACE_TYPE_TEXTURE,
};


//=============================================================================
/**
*/
//=============================================================================
class CBaseSurface : public CDeviceObject
{
protected:
	D3DXIMAGE_INFO		m_ImageInfo;
	D3DFORMAT			m_Format;
	Uint32				m_Width;
	Uint32				m_Height;
	Bool				m_IsLock;
	eSurfaceType		m_SurfaceType;

protected:
	virtual HRESULT LoadImageToBaseSurface( IDirect3DSurface9 *pSurface, void *pData, Uint32 Size, Uint32 Width, Uint32 Height, D3DCOLOR KeyColor );

public:
	CBaseSurface( CBaseMgr *pMgr );
	virtual ~CBaseSurface();

	virtual Bool GetImageInfoFromMemory( void *pData, Uint32 Size );

	virtual Uint32 GetImageWidth( void );
	virtual Uint32 GetImageHeight( void );
	virtual Uint32 GetWidth( void );
	virtual Uint32 GetHeight( void );
	virtual D3DFORMAT GetFormat( void );

public:
	virtual void Reset( void ) = 0;
	virtual void Restore( void ) = 0;
	virtual Bool SetRenderTarget( void ) = 0;
	virtual Bool SetDepthStencil( void ) = 0;
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CCriticalSection
{
protected:
	CRITICAL_SECTION m_CriticalSection;

public:
	CCriticalSection();
	virtual ~CCriticalSection();

	void Enter( void );
	void Leave( void );
};
}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CEvent
{
protected:
	HANDLE *m_pEventHandle;
	Uint32 m_HandleCount;

public:
	CEvent( Bool IsSignal = false, Uint32 Count = 1 );
	virtual ~CEvent();

	virtual void Set( Uint32 No = 0 );
	virtual void Reset( Uint32 No = 0 );
	virtual Bool IsSignal( Uint32 No = 0 );
	virtual Sint32 Wait( Uint32 MilliSeconds = INFINITE );
};
}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
extern const INSTANCEID IID_FRAME;


//=============================================================================
/**
*/
//=============================================================================
class CFrame : public CBaseFrame
{
protected:
	CBaseMesh	*m_pMesh;
	Uint32		m_AnimationCount;
	CAnimation	**m_ppAnimationTbl;
	CBaseList	m_ListFrame;
	Uint32 m_MotionIndexA;
	Uint32 m_MotionIndexB;
	Float m_fMotionWeight;

protected:

public:
	CFrame();
	virtual ~CFrame();

	virtual void UpdateFrameList( CFrame **ppFrameList, Sint32 &Cnt );
	virtual void UpdateMeshList( CBaseMesh **ppMeshList, Sint32 &Cnt );

	virtual Bool GetInstanceByIndex( Uint32 Index, const INSTANCEID &InstanceId, CBaseObject **ppInstance );
	virtual Bool GetInstanceByName( const char *pName, const INSTANCEID &InstanceId, CBaseObject **ppInstance );

	virtual Uint32 GetAnimationIndexByName( const char *pName );

	virtual void SetAnimationWeight( Uint32 IndexA, Uint32 IndexB, Float fWeight );
	virtual void AddFrame( CFrame *pFrame );
	virtual void AddMesh( CBaseMesh *pMesh );
	virtual void SetTransformMatrix( D3DXMATRIX *pMatrix );
	virtual void UpdateTransform( CMatrix &Matrix, CMatrix &MatrixRoot );
	virtual void UpdateAnimation( Float fTimeA, Float fTimeB, eAnimationType Type );
	virtual Uint32 Rendering( void );
	virtual void SetAnimationCount( Uint32 Count );
	virtual void ConnectAnimation( Uint32 No, CAnimationSet *pAnimSet );

	virtual void LogoutName( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
enum eLagFormat
{
	LAGFMT_A4R4G4B4,					///< 16Bit�t�H�[�}�b�g
	LAGFMT_A8R8G8B8,					///< 32Bit�t�H�[�}�b�g
	LAGFMT_A16R16G16B16,				///< 64Bit�t�H�[�}�b�g
	LAGFMT_Float,						///< ���������_�^�t�H�[�}�b�g

	LAGFMT_COMPRESS_A4R4G4B4,			///< ���k16Bit�t�H�[�}�b�g
	LAGFMT_COMPRESS_A8R8G8B8,			///< ���k32Bit�t�H�[�}�b�g
	LAGFMT_COMPRESS_A16R16G16B16,		///< ���k64Bit�t�H�[�}�b�g
	LAGFMT_COMPRESS_Float,				///< ���k���������_�^�t�H�[�}�b�g
};

//=============================================================================
/**
*/
//=============================================================================
class CLagLoader
{
protected:
	PIXELDATA32 *m_pBits;		///< �摜�̃s�N�Z���f�[�^��32BitARGB�^�Ŋi�[�����
	Sint32 m_Width;				///< �摜�̉������i�[�����
	Sint32 m_Height;			///< �摜�̏c�����i�[�����
	Sint32 m_Pitch;				///< �摜�̃s�b�`���i�[�����

protected:
	virtual Sint32 GetDitherColor5( Sint32 Color,  Sint32 Px, Sint32 Py );																///< 4Bit�F�f�B�U�擾
	virtual Sint32 GetDitherColor4( Sint32 Color,  Sint32 Px, Sint32 Py );																///< 5Bit�F�f�B�U�擾
	virtual void ConvertFormat( Sint32 Width, Sint32 Height, eLagFormat SrcFormat, void *pSrc, eLagFormat DstFormat, void *pDest );		///< �摜�t�H�[�}�b�g�R���o�[�g

	virtual Sint32 LoadLAG( const char *pFileName, const char *pName, Sint32 *pWidth, Sint32 *pHeight, void **ppData, eLagFormat *Format );	///< LAG�t�@�C���ǂݍ���
	virtual Sint32 GetLAGDataSize( Sint32 Width, Sint32 Height, eLagFormat Format );														///< LAG�f�[�^�T�C�Y�擾
	virtual Bool IsCompress( eLagFormat Format );																							///< ���k�t�H�[�}�b�g���ۂ�

	virtual Bool Decode( const Uint8 *pSrc, Uint8 **ppDst, Uint32 DstSize );																///< �摜�f�[�^�f�R�[�h

public:
	CLagLoader();																											///< �R���X�g���N�^
	virtual ~CLagLoader();																											///< �f�X�g���N�^

	virtual const char *Load( const char *pFileName, const char *pDataName );														///< �ǂݍ���
	virtual void Release( void );																									///< ���

	virtual void GetPixelData( void **ppBits, Sint32 *ppitch );																		///< �s�N�Z���f�[�^�擾
	virtual void GetGraphicSize( Sint32 *pWidth, Sint32 *pHeight );																	///< �摜�T�C�Y�擾

	virtual Uint32 GetDataSize( void );																								///< �摜�f�[�^�T�C�Y
	virtual void *GetDataAddress( void );																							///< �摜�f�[�^�A�h���X�擾

	virtual Bool CopyToSurface( void *pDst, Sint32 Pitch, D3DFORMAT Format );																	///< �T�[�t�F�C�X�ɃR�s�[
	virtual Bool CopyToSurface( Sint32 Dx, Sint32 Dy, Sint32 Px, Sint32 Py, Sint32 Sx, Sint32 Sy, void *pDst, Sint32 Pitch, D3DFORMAT Format );	///< �g��@�\�t���T�[�t�F�C�X�R�s�[
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CLine2D : public CPrimitive2DBase
{
	friend class CLine2DMgr;

protected:
	CLine2D( CBaseMgr *pMgr );
	virtual ~CLine2D();

protected:
	virtual Uint32 ScissorPolygon( CPrimitivePoint2D *pDst, CPrimitivePoint2D *pSrc );
	virtual Uint32 ScissorPolygonLeft( CPrimitivePoint2D *pPtIn, CPrimitivePoint2D *pPtOut, Uint32 VxNum );
	virtual Uint32 ScissorPolygonTop( CPrimitivePoint2D *pPtIn, CPrimitivePoint2D *pPtOut, Uint32 VxNum );
	virtual Uint32 ScissorPolygonRight( CPrimitivePoint2D *pPtIn, CPrimitivePoint2D *pPtOut, Uint32 VxNum );
	virtual Uint32 ScissorPolygonBottom( CPrimitivePoint2D *pPtIn, CPrimitivePoint2D *pPtOut, Uint32 VxNum );
	virtual void EffectPolygon( CPrimitivePoint2D *pDst, CPrimitivePoint2D *pSrc );

public:
	virtual Bool Create( Uint32 VertexMax );

	virtual Bool Push( CPrimitivePoint2D *pPoint, Uint32 Count );
	virtual void Render( void );
	virtual void Begin( void );
	virtual void End( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CLine2DMgr : public CPrimitive2DBaseMgr
{
public:
	CLine2DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CLine2DMgr();

	virtual CLine2D *Create( Uint32 VertexMax );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CLine3D : public CStyle, public CPrimitive3DBase
{
	friend class CLine3DMgr;

protected:
	CLine3D( CBaseMgr *pMgr );
	virtual ~CLine3D();

public:
	virtual Bool Create( Uint32 VertexMax );

	virtual Bool Push( CPrimitivePoint3D *pPoint, Uint32 Count );
	virtual void Render( void );
	virtual void Begin( void );
	virtual void End( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CLine3DMgr : public CPrimitive3DBaseMgr
{
protected:

public:
	CLine3DMgr( IDirect3DDevice9 *pDevice );
	virtual ~CLine3DMgr();

	virtual CLine3D *Create( Uint32 VertexMax );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CMesh : public CBaseMesh
{
protected:
	Uint32				m_AttributeCnt;
	D3DXATTRIBUTERANGE	*m_pAttributeTbl;

protected:
	virtual Bool ConstructionBuffer( ID3DXMesh *pMesh, D3DXATTRIBUTERANGE *pAttrTbl, Uint32 AttrCnt );
	virtual void UpdateBoneConnect( CFrame **ppFrameList, Sint32 FrameCount );
	virtual void SendToShaderConstant( CMatrix &mWorld );

public:
	CMesh( Uint16 ShaderVersionMajor, Uint16 ShaderVersionMinor );
	virtual ~CMesh();

	virtual Bool GenerateMeshData( ID3DXMesh *pMesh, ID3DXSkinInfo *pSkinInfo, Uint32 *pAdjacency );

	virtual void UpdateTransform( CMatrix &Matrix, CMatrix &MatrixRoot );
	virtual Uint32 Rendering( void );
	virtual void ConnectAnimation( CAnimationSet *pAnimSet ){}
	virtual Bool IsSkinned( void );
	virtual Uint32 GetWeightCount( void );
	virtual Uint32 GetBoneCount( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
struct FIELDCOLOR
{
	Float a;
	Float r;
	Float g;
	Float b;
};

//=============================================================================
/**
*/
//=============================================================================
struct FIELDVERTEX
{
	Float Px, Py, Pz;
	Float Nx, Ny, Nz;
	Float Tx, Ty, Tz;
	Float Bx, By, Bz;
	FIELDCOLOR Color;
	Float Tu, Tv;
};

//=============================================================================
/**
*/
//=============================================================================
struct FIELDFACE
{
	Sint32 SurfaceNo;
	FIELDVERTEX Vx[3];
};

//=============================================================================
/**
*/
//=============================================================================
struct FIELDSURFACE
{
	Sint32 IndexStart;
	Sint32 IndexCount;
};

//=============================================================================
/**
*/
//=============================================================================
struct FIELDMESH
{
	Float MinX, MinY, MinZ;
	Float MaxX, MaxY, MaxZ;

	Sint32 SurfaceCount;
	FIELDSURFACE *pSurface;

	Sint32 VertexCount;
	FIELDVERTEX *pVertex;

	Sint32 IndexCount;
	Uint16 *pIndex;
};

//=============================================================================
/**
*/
//=============================================================================
class CMeshDivider
{
protected:
	Sint32 m_AreaCount;
	Bool **m_ppRenderingTabl;
	Float m_fEpsilon;
	Sint32 m_MeshCount;
	FIELDMESH *m_pMeshData;

	virtual void VertexLinear( FIELDVERTEX *pIn0, FIELDVERTEX *pIn1, FIELDVERTEX *pOut, Float fRate );
	virtual Sint32 ScissorPolygonLeft( FIELDVERTEX *pPtIn, FIELDVERTEX *pPtOut, Sint32 VxNum, Float fClip );
	virtual Sint32 ScissorPolygonRight( FIELDVERTEX *pPtIn, FIELDVERTEX *pPtOut, Sint32 VxNum, Float fClip );
	virtual Sint32 ScissorPolygonTop( FIELDVERTEX *pPtIn, FIELDVERTEX *pPtOut, Sint32 VxNum, Float fClip );
	virtual Sint32 ScissorPolygonBottom( FIELDVERTEX *pPtIn, FIELDVERTEX *pPtOut, Sint32 VxNum, Float fClip );
	virtual void ScissorMesh( FIELDMESH *pMesh, FIELDFACE *pFaceOrg, Sint32 FaceCountOrg, Float sx, Float sz, Float ex, Float ez );
	virtual void OptimizeMesh( FIELDMESH *pMesh, FIELDFACE *pFace, Sint32 FaceCount);

public:
	CMeshDivider();
	virtual ~CMeshDivider();

	virtual Float ConvertToHightField( FIELDFACE *pTriList, Sint32 Count, Sint32 CellCount, Sint32 Scale = -1 );

	virtual Sint32 GetAreaCount( void );
	virtual FIELDMESH *GetAreaMesh( Sint32 x, Sint32 z );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
enum eAutoCreateShaderType
{
	AUTO_SHADER_NORMAL_NOLIGHT,
	AUTO_SHADER_REFLECTION_NOLIGHT,

	AUTO_SHADER_NORMAL,
	AUTO_SHADER_REFLECTION,
	AUTO_SHADER_PROJECT,

	AUTO_SHADER_TOON,
};

//=============================================================================
/**
*/
//=============================================================================
enum eCollisionType
{
	COLLISION_SPHERE,					///< �����蔻������ōs��
	COLLISION_AABB,						///< �����蔻���AABB�ōs��
	COLLISION_OBB,						///< �����蔻���OBB�ōs��
};


//=============================================================================
/**
*/
//=============================================================================
class CModel : public CDeviceObject, public CStyle
{
	friend class CModelLoader;
	friend class CModelMgr;

protected:
	Uint32			m_FrameCount;
	CFrame			**m_ppFrameList;
	Uint32			m_MeshCount;
	CBaseMesh		**m_ppMeshList;
	Uint32			m_AnimationCount;
	CAnimationSet	**m_ppAnimationList;
	CBaseList		m_ListFrame;

protected:
	virtual CFrame *GetRootFrame( void );
	virtual void UpdateFrameList( Sint32 FrameCount );
	virtual void UpdateMeshList( Sint32 MeshCount );
	virtual void SetAnimationSet( CBaseList &List );
	virtual void UpdateAnimationSet( void );

protected:
	CModel( CBaseMgr *pMgr );
	virtual ~CModel();

	virtual void Reset( void );
	virtual void Restore( void );

public:
	virtual void AddFrame( CFrame *pFrame );

	virtual Bool IsSkiinedMesh( Uint32 MeshNo );
	virtual Uint32 GetAnimationTimeMax( Uint32 Index );
	virtual Uint32 GetAnimationTrackMax( void );
	virtual Sint32 GetFrameIndexByName( const char *pName );
	virtual Sint32 GetMeshIndexByName( const char *pName );
	virtual Sint32 GetAnimationIndexByName( const char *pName );
	virtual Uint32 GetMeshCount( void );
	virtual Uint32 GetFrameCount( void );
	virtual CBaseMesh **GetMeshArray( void ) const;

	virtual void SetMateriaStateEnable( Bool IsEnable, Sint32 MeshNo, Sint32 MaterialNo );
	virtual void AutoCreateShader( eAutoCreateShaderType Type, Sint32 MeshNo );
	virtual void SetShader( CShader *pShader, Sint32 MeshNo, Uint32 Flag );
	virtual void SetTexture( Uint32 Stage, LTEXTURE lTex, Sint32 MeshNo, Sint32 MaterialNo );
	virtual void SetMaterialAlpha( Float fAlpha, Sint32 MeshNo, Sint32 MaterialNo );
	virtual void SetVertexExtrusion( Float fParam, Sint32 MeshNo );
	virtual void SetSlideTextureU( Float fParam, Sint32 MeshNo );
	virtual void SetSlideTextureV( Float fParam, Sint32 MeshNo );
	virtual void SetMorphWeight( Float fParam, Sint32 MeshNo );
	virtual void SetMorphTarget( Sint32 DstMeshNo, CModel *pModelSrc, Sint32 SrcMeshNo );

	virtual void UpdateTransform( CMatrix &Matrix );
	virtual void UpdateAnimation( Float fTimeA, Float fTimeB, eAnimationType Type );
	virtual Uint32 Rendering( void );

	virtual void SetStyle( CStyle &Style );
	virtual void GetStyle( CStyle &Style );

	virtual void SetRenderFlag( Uint8 Flag, Uint8 Mask = 0xff, Sint32 MeshNo = -1 );
	virtual Uint8 GetRenderFlag( Sint32 MeshNo ) const;

	virtual void SetTextureState( Uint32 Stage, D3DTEXTURESTAGESTATETYPE State, Uint32 Param, Sint32 MeshNo, Sint32 MaterialNo );
	virtual void SetSamplerState( Uint32 Stage, D3DSAMPLERSTATETYPE State, Uint32 Param, Sint32 MeshNo, Sint32 MaterialNo );
	virtual void SetBlendingType( eBlendType BlendType, Sint32 MeshNo, Sint32 MaterialNo );
	virtual void SetFilterEnable( Bool Flag, Sint32 MeshNo, Sint32 MaterialNo );
	virtual void SetColorkeyEnable( Bool Flag, Sint32 MeshNo, Sint32 MaterialNo );
	virtual void SetZBufferEnable( Bool Flag, Sint32 MeshNo, Sint32 MaterialNo );
	virtual void SetZWriteEnable( Bool Flag, Sint32 MeshNo, Sint32 MaterialNo );

	virtual Bool GetInstanceByIndex( Uint32 Index, const INSTANCEID &InstanceId, CBaseObject **ppInstance );
	virtual Bool GetInstanceByName( const char *pName, const INSTANCEID &InstanceId, CBaseObject **ppInstance );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CModelLoader : public CBaseObject
{
protected:
	Uint16		m_ShaderVersionMajor;
	Uint16		m_ShaderVersionMinor;
	CModel		*m_pModel;
	CBaseList	m_AnimationSetList;
	Sint32		m_FrameCount;
	Sint32		m_MeshCount;

protected:
	virtual Bool EnumObjectFromXFile( ID3DXFileEnumObject *pDxFileEnumObj );
	virtual Bool LoadFrame( ID3DXFileData *pDxFileData, CFrame *pFrame );
	virtual Bool LoadTransformMatrix( ID3DXFileData *pDxFileData, CFrame *pFrame );
	virtual Bool LoadMesh( ID3DXFileData *pDxFileData, CFrame *pFrame );
	virtual Bool LoadAnimationSet( ID3DXFileData *pDxFileData, CAnimationSet *pAnimSet );
	virtual Bool LoadAnimation( ID3DXFileData *pDxFileData, CAnimation *pAnim, CAnimationSet *pAnimSet );
	virtual Bool ConvertMaterial( CBaseMesh *pMesh, Uint32 Count, ID3DXBuffer *pMtrl );
	virtual Bool ComputeModelNormal( ID3DXMesh **ppMesh );
	virtual void UpdateBoneConnect( void );

public:
	CModelLoader();
	virtual ~CModelLoader();

	virtual Bool CreateFromFile( const char *pFileName, Uint16 ShaderVersionMajor, Uint16 ShaderVersionMinor, CBaseMgr *pMgr );
	virtual Bool CreateFromMemory( void *pData, Uint32 Size, Uint16 ShaderVersionMajor, Uint16 ShaderVersionMinor, CBaseMgr *pMgr );
	virtual Bool GetModel( CModel **ppModel );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CModelMgr : public CDeviceObjectMgr
{
protected:

public:
	CModelMgr( IDirect3DDevice9 *pDevice );
	virtual ~CModelMgr();

	virtual CModel *CreateFromMemory( void *pData, Uint32 Size, Uint16 ShaderVersionMajor = 2, Uint16 ShaderVersionMinor = 0, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );
	virtual CModel *CreateFromFile( const char *pFileName, Uint16 ShaderVersionMajor = 2, Uint16 ShaderVersionMinor = 0, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
struct CTextureSheet
{
	Sint32 Px;
	Sint32 Py;
	Sint32 Sx;
	Sint32 Sy;
	CTexture *pTex;
	CVertex2D Vx[4];
};

//=============================================================================
/**
*/
//=============================================================================
class CSheet : public CDeviceObject
{
	friend class CSheetMgr;

protected:
	CTextureSheet **m_ppSheets;
	Sint32 m_CountX;
	Sint32 m_CountY;
	Sint32 m_Width;
	Sint32 m_Height;

protected:
	virtual void CreateSheetData( Float fPx, Float fPy, D3DCOLOR Color );
	virtual void DrawSheetData( void );
	virtual Bool LoadFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor );

protected:
	CSheet( CBaseMgr *pMgr );
	virtual ~CSheet();

	virtual void Reset( void ) {}
	virtual void Restore( void ) {}

public:
	virtual Bool CreateFromFile( const char *pFileName, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );
	virtual Bool CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );
	virtual Bool CreateFromLAG( const char *pFileName, const char *pDataName, eSurfaceFormat Format );

	virtual Sint32 GetWidth( void );
	virtual Sint32 GetHeight( void );

	virtual void Draw( Float Px, Float Py, D3DCOLOR Color );
	virtual void DrawScale( Float fPx, Float fPy, Float fScale, D3DCOLOR Color, Float fCx = 0.0f, Float fCy = 0.0f );
	virtual void DrawRotate( Float fPx, Float fPy, Sint32 Angle, D3DCOLOR Color, Float fCx = 0.0f, Float fCy = 0.0f );
	virtual void DrawRotateScale( Float fPx, Float fPy, Sint32 Angle, Float fScale, D3DCOLOR Color, Float fCx = 0.0f, Float fCy = 0.0f );
};
}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CSheetMgr : public CBaseMgr
{
protected:

public:
	CSheetMgr( IDirect3DDevice9 *pDevice );
	virtual ~CSheetMgr();

	virtual CSheet *SearchInstance( const char *pFileName );

	virtual CSheet *CreateFromFile( const char *pFileName, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );
	virtual CSheet *CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );
	virtual CSheet *CreateFromLAG( const char *pFileName, const char *pDataName, eSurfaceFormat Format );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CSurface : public CBaseSurface
{
	friend class CSurfaceMgr;

protected:
	CBaseMgr *m_pManager;
	eSurfaceFormat m_BaseFormat;
	IDirect3DSurface9 *m_pSurface;
	IDirect3DSurface9 *m_pBaseSurface;
	D3DFORMAT m_Format;
	Bool m_IsRenderTarget;
	Bool m_IsDepthBuffer;

protected:
	CSurface( CBaseMgr *pMgr );
	virtual ~CSurface();

	virtual void Reset( void );
	virtual void Restore( void );

	virtual Bool Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
	virtual Bool CreateFromFile( const char *pFileName, eSurfaceFormat Format );
	virtual Bool CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
	virtual Bool CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format );

public:
	virtual Bool SetDepthStencil( void );
	virtual Bool SetRenderTarget( void );

	virtual Bool Copy( RECT *pDstRect, CSurface *pSrc, RECT *pSrcRect );
	virtual HDC GetDC( void );
	virtual void ReleaseDC( HDC hDC );

	virtual void GetInstance( IDirect3DSurface9 **ppSurface );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CSurfaceMgr : public CDeviceObjectMgr
{
protected:

public:
	CSurfaceMgr( IDirect3DDevice9 *pDevice );
	virtual ~CSurfaceMgr();

	virtual CSurface *Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
	virtual CSurface *CreateFromFile( const char *pFileName, eSurfaceFormat Format );
	virtual CSurface *CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
	virtual CSurface *CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CTexture : public CBaseSurface
{
	friend class CTextureMgr;

protected:
	IDirect3DTexture9	*m_pTexture;
	IDirect3DTexture9	*m_pBaseTexture;
	D3DPOOL				m_Pool;

protected:
	CTexture( CBaseMgr *pMgr );
	virtual ~CTexture();

	virtual Bool Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
	virtual Bool CreateEx( Uint32 Width, Uint32 Height, Uint32 Levels, Uint32 Usage, D3DFORMAT Format, D3DPOOL Pool );
	virtual Bool CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
	virtual Bool CreateFromRenderTarget( CTexture &Texture );
	virtual Bool CreateFromLAG( const char *pFileName, const char *pDataName, eSurfaceFormat Format );
	virtual Bool CreateFromFile( const char *pFileName, eSurfaceFormat Format, D3DCOLOR KeyColor );
	virtual Bool CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor );

	virtual Bool LoadImageFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor );
	virtual Bool LoadImageFromFile( const char *pFileName, eSurfaceFormat Format, D3DCOLOR KeyColor );
	virtual Bool CreateTextureFromImageInfo( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor );

public:
	virtual Bool LockRect( RECT *pRect, void **ppBites, Uint32 *pPitch, Uint32 *pWidth, Uint32 *pHeight, D3DFORMAT *pFormat );
	virtual void UnLockRect( void );
	virtual Bool StretchRect( RECT *pDstRect, CTexture *pSrcTex, RECT *pSrcRect, Bool IsUvToTexel = false );

	virtual void Reset( void );
	virtual void Restore( void );
	virtual Bool SetRenderTarget( void );
	virtual Bool SetDepthStencil( void );

	virtual Bool DownloadRenderTarget( void );
	virtual void ColorFill( D3DCOLOR Color );

	virtual bool GetDC( HDC *pDC );
	virtual void ReleaseDC( HDC hDC );

	virtual void UpdateTexture( void );
	virtual void GetSurface( IDirect3DSurface9 **ppSurface );
	virtual void GetBaseSurface( IDirect3DSurface9 **ppSurface );
	virtual void GetInstance( IDirect3DTexture9 **ppTexture );
	virtual void GetBaseInstance( IDirect3DTexture9 **ppTexture );

	virtual Float PixelToTexelU( Float fParam );
	virtual Float PixelToTexelV( Float fParam );

	virtual Bool SaveToFile( const char *pFileName, D3DXIMAGE_FILEFORMAT Format );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CTextureMgr : public CDeviceObjectMgr
{
protected:
	Float m_fOffsetUV;

public:
	CTextureMgr( IDirect3DDevice9 *pDevice );
	virtual ~CTextureMgr();

	CTexture *SearchInstance( const char *pFileName );
	void SetOffsetUV( Float fOffset );
	Float GetOffsetUV( void );

	virtual CTexture *Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
	virtual CTexture *CreateEx( Uint32 Width, Uint32 Height, Uint32 Levels, Uint32 Usage, D3DFORMAT Format, D3DPOOL Pool );
	virtual CTexture *CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
	virtual CTexture *CreateFromRenderTarget( CTexture &Texture );
	virtual CTexture *CreateFromLAG( const char *pFileName, const char *pDataName, eSurfaceFormat Format );
	virtual CTexture *CreateFromFile( const char *pFileName, eSurfaceFormat Format, D3DCOLOR KeyColor );
	virtual CTexture *CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor );
};
}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CVMRTexture : public CTexture
{
	enum { TEXTURE_CHACHE_MAX = 1 };

protected:
	Sint32				m_CachePos;
	IDirect3DTexture9	*m_pTextureCache[TEXTURE_CHACHE_MAX];

protected:
	CVMRTexture( CBaseMgr *pMgr );
	virtual ~CVMRTexture();

public:
	virtual void Reset( void );
	virtual void Restore( void );

	virtual void AddCachePointer( void );

	virtual void GetSurface( IDirect3DSurface9 **ppSurface );
	virtual void GetInstance( IDirect3DTexture9 **ppTexture );

	virtual Bool CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CVMR9Allocator : public CVMRTexture, public IVMRSurfaceAllocator9, private IVMRImagePresenter9
{
private:
	Uint32						m_SurfaceNum;
	IVMRSurfaceAllocatorNotify9	*m_pIVMRSurfAllocNotify;
	IDirect3DSurface9			**m_ppSurfaces;
	Uint32						m_MovieWidth;
	Uint32						m_MovieHeight;

protected:
	void DeleteSurfaces();
	HRESULT PresentHelper( VMR9PresentationInfo *lpPresInfo );

public:
	CVMR9Allocator( CBaseMgr *pMgr );
	virtual ~CVMR9Allocator();

	virtual HRESULT STDMETHODCALLTYPE InitializeDevice( DWORD_PTR dwUserID, VMR9AllocationInfo *pAllocInfo, DWORD *pNumBuffers );
	virtual HRESULT STDMETHODCALLTYPE TerminateDevice( DWORD_PTR dwID );
	virtual HRESULT STDMETHODCALLTYPE GetSurface( DWORD_PTR dwUserID, Uint32 SurfaceIndex, Uint32 SurfaceFlags, IDirect3DSurface9 **lplpSurface );
	virtual HRESULT STDMETHODCALLTYPE AdviseNotify( IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify );
	virtual HRESULT STDMETHODCALLTYPE StartPresenting( DWORD_PTR dwUserID );
	virtual HRESULT STDMETHODCALLTYPE StopPresenting( DWORD_PTR dwUserID );
	virtual HRESULT STDMETHODCALLTYPE PresentImage( DWORD_PTR dwUserID, VMR9PresentationInfo *lpPresInfo );
	virtual HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** ppvObject );

	virtual ULONG STDMETHODCALLTYPE AddRef( void );
	virtual ULONG STDMETHODCALLTYPE Release( void );

	virtual Uint32 GetMovieWidth( void );
	virtual Uint32 GetMovieHeight( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CVMR9 : public CDeviceObject
{
	friend class CVMR9Mgr;

private:
	CBaseMgr			*m_pManager;
	CBaseMgr			*m_pAllocatorMgr;
	IGraphBuilder		*m_pGraph;
	IBaseFilter			*m_pFilter;
	IMediaControl		*m_pMediaControl;
	CVMR9Allocator		*m_pAllocator;

protected:
	CVMR9( CBaseMgr *pMgr );
	virtual ~CVMR9();

	void Reset( void );
	void Restore( void );

	HRESULT SetAllocatorPresenter( IBaseFilter *pFilter, HWND hWnd );

public:
	virtual Bool LoadFromFile( const char *pFile );
	virtual Bool Play( void );
	virtual void Stop( void );
	virtual Bool IsPlay( void );
	virtual void Render( CLunaRect *pDst = NULL, Bool IsLoop = false );
	virtual CTexture *GetTexture( void );
};

}



//=============================================================================
// INCLUDE
//=============================================================================


namespace LibLuna
{
//=============================================================================
/**
*/
//=============================================================================
class CVMR9Mgr : public CDeviceObjectMgr
{
protected:

public:
	CVMR9Mgr( IDirect3DDevice9 *pDevice );
	virtual ~CVMR9Mgr();

	virtual CVMR9 *CreateFromFile( const char *pFile );
};

}



//====================================================================
// INCLUDE
//====================================================================


//====================================================================
// DEFINE
//====================================================================
#define LOOP_INFINITY	(0xFFFFFFFF)


//====================================================================
// TYPEDEF
//====================================================================
typedef void *(*AYAME_MEMORY_ALLOC_PROC)( unsigned long Size, const char *pFileName, unsigned long Line );										///< �������m�ۗp�R�[���o�b�N�֐�
typedef void (*AYAME_MEMORY_FREE_PROC)( void *pData );																							///< ����������p�R�[���o�b�N�֐�

typedef Bool (*AYAME_INITIALIZE_PROC)( HWND hWnd, void **ppDirectSound, AYAME_MEMORY_ALLOC_PROC pAllocProc, AYAME_MEMORY_FREE_PROC pFreeProc );	///< �h���C�o�[������
typedef void (*AYAME_UNINITIALIZE_PROC)( void );																								///< �h���C�o�[���
typedef Bool (*AYAME_GETERROR_PROC)( char *pErrStr );																							///< �h���C�o�[����̃G���[���擾
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_PROC)( const char *pFileName, Bool IsGlobal );													///< �h���C�o�[����I�u�W�F�N�g�擾
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_EX_PROC)( const char *pFileName, unsigned long Start, unsigned long Size, Bool IsGlobal );		///< �h���C�o�[����I�u�W�F�N�g�擾
typedef class CAyame *(*AYAME_CREATE_FROM_MEMORY_PROC)( void *pData, unsigned long Size, Bool IsGlobal );										///< �h���C�o�[����I�u�W�F�N�g�擾


//====================================================================
/**
	@brief	OggVorbis�Đ��p�N���X

	DLL�p�ɏ������z�֐������̒��g�̂Ȃ��N���X�ł�
*/
//====================================================================
typedef class CAyame
{
public:
	virtual Bool __stdcall IsPlay( void )																		= 0;	///< �Đ��`�F�b�N
	virtual Bool __stdcall Play( unsigned long nLoopCount= 0, unsigned long nLoopInSample = 0 )					= 0;	///< �Đ�
	virtual Bool __stdcall Loop( unsigned long nLoopCount = LOOP_INFINITY, unsigned long nLoopInSample = 0 )	= 0;	///< ���[�v�Đ�
	virtual Bool __stdcall Stop( void )																			= 0;	///< ��~
	virtual Bool __stdcall Pause( void )																		= 0;	///< �ꎞ��~
	virtual Bool __stdcall SetVolume( Float fParam )															= 0;	///< �{�����[���ݒ�
	virtual Bool __stdcall SetPan( Float fParam )																= 0;	///< �p���ݒ�
	virtual Bool __stdcall Release( void )																		= 0;	///< ���
	virtual Bool __stdcall AddRef( void )																		= 0;	///< �Q�ƃJ�E���g�C���N�������g
	virtual void __stdcall WaitEvent( void )																	= 0;	///< �C�x���g�I���҂�
}
COggVorbis, *PCOggVorbis;




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
/**
*/
//=============================================================================
class Luna3D
{
protected:
	static Sint32 m_SceneCount;										///< �V�[�������J�E���^
	static HINSTANCE m_hDllD3D9;									///< DLL�n���h��
	static IDirect3D9 *m_pDirect3D;									///< Direct3D�I�u�W�F�N�g
	static IDirect3DDevice9 *m_pDevice;								///< �f�o�C�X�I�u�W�F�N�g
	static IDirect3DSurface9 *m_pRenderTarget;						///< �����_�����O�^�[�Q�b�g
	static IDirect3DQuery9 *m_pQuery[2];							///< �f�o�C�X�₢���킹�p
	static D3DVIEWPORT9 m_Viewport;									///< �r���[�|�[�g

	static char m_AdapterName[128];									///< �A�_�v�^�[��
	static char m_AdapterDriver[128];								///< �A�_�v�^�[�h���C�o�[��
	static char m_AdapterVersion[128];								///< �A�_�v�^�[�o�[�W������

	static DEVICEINFORMATION m_DeviceInfo;							///< �f�o�C�X���

	static D3DDISPLAYMODE m_WindowMode;								///< �E�B���h�E���[�h�̃f�B�X�v���C���[�h
	static D3DDISPLAYMODE m_FullScreenMode[2];						///< �t���N���[�����[�h�̃f�B�X�v���C���[�h

	static ADAPTERDATA m_AdapterData;								///< �A�_�v�^�[�f�[�^

	static D3DPRESENT_PARAMETERS m_PresentParams[2];				///< �v���[���e�[�V�����p�����[�^�[

	static LCAMERA m_lCamera;										///< �A�N�e�B�u�J�����n���h��
	static LTEXTURE m_lTexTarget;									///< �A�N�e�B�u�^�[�Q�b�g�e�N�X�`���n���h��
	static LSURFACE m_lSurfTarget;									///< �A�N�e�B�u�^�[�Q�b�g�T�[�t�F�C�X�n���h��
	static LSURFACE m_lSurfDepthStencil;							///< �A�N�e�B�u�[�x�o�b�t�@�n���h��

	static LTEXTURE m_lTexActive[TEXTURE_STAGE_MAX];				///< �A�N�e�B�u�e�N�X�`���n���h��

	static Uint32 m_RenderState[RENDER_STATE_TBL_MAX];							///< �����_�����O�X�e�[�g
	static Uint32 m_SamplerState[TEXTURE_STAGE_MAX][SAMPLER_STATE_TBL_MAX];		///< �T���v���[�X�e�|�g
	static Uint32 m_TextureState[TEXTURE_STAGE_MAX][TEXTURE_STATE_TBL_MAX];		///< �e�N�X�`���X�e�[�g

	static eSurfaceFormat m_SurfaceFormatTbl[2][16];				///< �T�[�t�F�C�X�t�H�[�}�b�g�����e�[�u��
	static Uint32 m_SurfaceFormatCount[2];							///< �T�[�t�F�C�X�t�H�[�}�b�g��

	static Uint32 m_MaxVertexShaderVersion;							///< �g�p���钸�_�V�F�[�_�[�ő�o�[�W����

	static HFONT m_hFont;											///< �t�H���g�n���h��
	static HFONT m_hOldFont;										///< �O�̃t�H���g�n���h��
	static HDC m_hDC;												///< �f�o�C�X�R���e�L�X�g�n���h��

	static Float m_FogNear;											///< �t�H�O�J�n�X
	static Float m_FogFar;											///< �t�H�O�I���_
	static D3DCOLOR m_FogColor;										///< �t�H�O�F

	static Bool m_IsWaitBlank;										///< ���������҂�
	static Bool m_IsFullColor;										///< �t���J���[���[�h
	static Bool m_IsEmulationMode;									///< �G�~�����[�V�����N���t���O
	static Bool m_IsLocked;											///< �o�b�N�o�b�t�@���b�N�t���O
	static Bool m_IsCheckingFillRate;								///< �t�B�����[�g�`�F�b�N���t���O
	static Bool m_IsNVPerfHUD;										///< NVPerfHUD�ł̉�͂��g�����ۂ�

	static void (*m_pCallbackReset)( void );						///< ���Z�b�g���R�[���o�b�N�֐�
	static void (*m_pCallbackRestore)( void );						///< ���X�g�A���R�[���o�b�N�֐�

	static MATERIALSTATE m_DefaultState;							///< �f�t�H���g�̃}�e���A���X�e�[�g

protected:
	static Bool InitAdapter( void );																	///< �A�_�v�^�[������
	static Bool CreateDirect3DObject( void );															///< Direct3DObject����
	static Bool CheckAdapterInformation( void );														///< �A�_�v�^�[���擾
	static Bool CheckDeviceInformation( void );															///< �f�o�C�X���擾
	static void GetDeviceCaps( D3DCAPS9 *pCaps, DEVICEINFORMATION *pDevInfo );							///< �f�o�C�X���\�擾
	static Sint32 GetDeviceTypeNo( void );																///< �f�o�C�X�^�C�v�ԍ��擾
	static D3DPRESENT_PARAMETERS MakePresentParameters( HWND hWnd, Bool IsWindow, Bool IsFullColor );	///< �v���[���e�[�V�����p�����[�^�[�쐬
	static void InitializeDeviceSetteing( void );														///< �f�o�C�X�ݒ菉����
	static void ResetDeviceSetteing( void );															///< �f�o�C�X�ݒ菉����
	static Bool CreateDeviceByNVPerfHUD( HWND hWindow, D3DPRESENT_PARAMETERS *pPresentParam );			///< �f�o�C�X�ݒ菉����

public:
	static Bool Initialize( void );															///< �N���X������
	static void Finalize( void );															///< �N���X���

	static void ResetDevice( Bool IsChange );												///< �f�o�C�X���Z�b�g

	static Uint32 GetRestVRAM( void );														///< �g�p�\�Ȑ���e�N�X�`���������e�ʂ��擾
	static char *GetPixelFormat( D3DFORMAT Format, char *pStr = NULL );						///< �s�N�Z���t�H�[�}�b�g�𕶎���Ŏ擾
	static D3DFORMAT GetFormat( eSurfaceFormat Format, D3DFORMAT OrgFmt );					///< �w��t�H�[�}�b�g����Direct3D�t�H�[�}�b�g���擾
	static char *GetError( HRESULT hr );													///< �G���[�擾

	static Bool Start( HWND hWindow, Bool IsWindow );										///< �R�c�֌W�̃f�o�C�X���N��
	static void GetDeviceInformation( DEVICEINFORMATION *pInfo );							///< �f�o�C�X���擾
	static Bool CopyToRenderTarget( RECT *pDstRect, LSURFACE lSurf, RECT *pSrcRect );

	static Bool CheckPixelShaderSupport( Uint16 Major, Uint16 Minor );						///< �s�N�Z���V�F�[�_�[�̃T�|�[�g�`�F�b�N
	static void EnableEmulationMode( void );												///< �G�~�����[�V�������[�h���g�p
	static void EnableFullColorMode( void );												///< �t���J���[���[�h���g�p
	static void EnableWaitVBlank( void );													///< ����������҂�
	static void EnableNVPerfHUD( void );													///< NVPerfHUD�ł̉�͂��g��

	static HMONITOR GetAdapterMonitor( void );												///< ���j�^�[�n���h���擾
	static IDirect3DDevice9 *GetDevice( void );												///< �f�o�C�X�擾

	static void SetMaxVertexShaderVersion( Uint16 Major, Uint16 Minor );					///< �g�p���钸�_�V�F�[�_�[�̍ō��o�[�W������ݒ�
	static void SetVertexProccessing( Uint16 Major, Uint16 Minor );							///< �g�p���钸�_�V�F�[�_�[�̃o�[�W������ݒ�
	static Bool GetVertexProccessing( Uint16 Major, Uint16 Minor );							///< �w�肵���o�[�W�����̒��_�V�F�[�_�[���g�p�\���`�F�b�N����

	static Bool SetDepthStencilSurface( LSURFACE lSurf );									///< �[�x�X�e���V���o�b�t�@��ݒ�
	static Bool SetRenderTargetSurface( LSURFACE lSurf );									///< �����_�����O�^�[�Q�b�g�T�[�t�F�C�X��ݒ�
	static Bool SetRenderTargetTexture( LTEXTURE lTex );									///< �����_�����O�^�[�Q�b�g�e�N�X�`����ݒ�
	static Bool ResetRenderTarget( void );													///< �����_�����O�^�[�Q�b�g�������l��
	static Bool ResetDepthStencil( void );													///< �[�x�X�e���V���o�b�t�@�������l��

	static void SetLight( Sint32 No, Bool IsActive );																	///< ���C�g�̗L����ݒ�

	static void SetFogParameter( Float fNear, Float fFar, D3DCOLOR Color );												///< �t�H�O�p�f�[�^�ݒ�
	static void GetFogParameter( Float *pfNear, Float *pfFar, D3DCOLOR *pColor );										///< �t�H�O�p�f�[�^�擾

	static Bool Clear( Uint32 ClearFlags = D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, D3DCOLOR Color = 0x00000000, Float Depth = 1.0f, Uint32 Stencil = 0, RECT *pDst = NULL );	///< �o�b�t�@�N���A
	static void ColorFill( RECT *pDst, D3DCOLOR Color );																///< ��ʓh��Ԃ�
	static Bool BeginScene( void );																						///< �V�[���J�n
	static void EndScene( void );																						///< �V�[���I��
	static void Refresh( HWND hWnd = NULL );																			///< ��ʍX�V

	static void FillRateCheckStart( void );																				///< �t�B�����[�g�`�F�b�N�̊J�n
	static Uint32 FillRateCheckEnd( void );																				///< �t�B�����[�g�`�F�b�N�̏I��
	static Bool BlockForEndRendering( void );																			///< �����_�����O�̏I����҂�

	static Bool Clip( RECT *pDst, RECT *pSrc );																			///< �N���b�s���O�̈�ݒ�

	static void SetCamera( LCAMERA lCam );																				///< �J�����ݒ�
	static void SetViewport( RECT *pRect );																				///< �r���[�|�[�g�ݒ�
	static void GetViewport( RECT *pRect );																				///< �r���[�|�[�g�擾

	static void SetTexture( Uint32 Stage, LTEXTURE lTex );																///< �e�N�X�`���ݒ�

	static void SetRenderState( D3DRENDERSTATETYPE State, Uint32 Param );												///< �����_�����O�X�e�[�g�ݒ�
	static void SetTextureState( Uint32 Stage, D3DTEXTURESTAGESTATETYPE State, Uint32 Param );							///< �e�N�X�`���X�e�[�g�ݒ�
	static void SetSamplerState( Uint32 Stage, D3DSAMPLERSTATETYPE State, Uint32 Param );								///< �T���v�����O�X�e�[�g�ݒ�
	static void SetBlendingType( eBlendType BlendType );																///< �u�����f�B���O�^�C�v�ݒ�
	static void SetFilterEnable( Bool Flag );																			///< �o�C���j�A�t�B���^�L���ݒ�
	static void SetColorkeyEnable( Bool Flag );																			///< �J���[�L�[�L���ݒ�
	static void SetZBufferEnable( Bool Flag );																			///< �[�x�o�b�t�@�L���ݒ�
	static void SetZWriteEnable( Bool Flag );																			///< Z�������ݗL���ݒ�
	static void SetWireFrameEnable( Bool Flag );																		///< ���C���t���[�������_�����O�L���ݒ�

	static Bool FontBegin( const char *pFontFace, Sint32 FontSize );													///< �t�H���g�`��J�n
	static void FontDraw( Sint32 Px, Sint32 Py, COLORREF FontColor, COLORREF BackColor, const char *pStr,... );			///< �t�H���g�`��
	static void FontEnd( void );																						///< �t�H���g�`��I��

	static Bool LockBackBuffer( void **ppBits, Sint32 *pPitch, D3DFORMAT *pFormat, Sint32 *pWidth, Sint32 *pHeight );	///< �o�b�N�o�b�t�@���b�N
	static void UnlockBackBuffer( void );																				///< �o�b�N�o�b�t�@���b�N����

	static void SetScissoring( Bool IsUse, RECT *pRect );																///< �V�U�����O�̈��ݒ�
	static void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );									///< �p�[�X�␳���x����ݒ�
	static void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );										///< �Y�[�����x����ݒ�
	static void WorldToScreen( CVector3D *pWorldPos, CVector3D *pScreenPos );											///< ���[���h���W����X�N���[�����W���擾
	static void ScreenToWorld( CVector3D *pWorldPos, CVector3D *pScreenPos );											///< �X�N���[�����W���烏�[���h���W���擾
	static void ScreenToView( CVector3D *pViewPos, CVector3D *pScreenPos );												///< �X�N���[�����W����r���[���W���擾

	static Sint32 GetScreenModeCount( Bool IsFullColor );																///< ��ʃ��[�h���擾
	static void GetScreenMode( Bool IsFullColor, Sint32 No, Sint32 *pWidth, Sint32 *pHeight );							///< ��ʃ��[�h�擾
	static Sint32 GetRenderTargetTextureSizeCount( void );																///< �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y���擾
	static void GetRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight );								///< �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y�擾

	static void GetAdapterName( char *pName );																			///< �A�_�v�^�[���擾
	static void GetAdapterDriver( char *pName );																		///< �A�_�v�^�[�h���C�o�[���擾
	static void GetAdapterVersion( char *pName );																		///< �A�_�v�^�[�o�[�W�����擾

	static void SetDialogMode( Bool IsMode );																			///< �_�C�A���O���[�h�̗L��

	static void SetCallbackDeviceReset( void (*pCallback)( void ) );													///< ���Z�b�g���R�[���o�b�N�֐�
	static void SetCallbackDeviceRestore( void (*pCallback)( void ) );													///< ���X�g�A���R�[���o�b�N�֐�

	static void SetSurfaceFormatTblFor2D( eSurfaceFormat FmtTbl[], Uint32 Count );										///< 2D�p�T�[�t�F�C�X�t�H�[�}�b�g�����e�[�u���ݒ�
	static void SetSurfaceFormatTblFor3D( eSurfaceFormat FmtTbl[], Uint32 Count );										///< 3D�p�T�[�t�F�C�X�t�H�[�}�b�g�����e�[�u���ݒ�

	static void GetDefaultMateriaState( MATERIALSTATE *pState );														///< �f�t�H���g�}�e���A���X�e�[�g�擾
	static void SetMateriaRenderState( MATERIALSTATE *pState );															///< �}�e���A���X�e�[�g���f�o�C�X�ɐݒ�
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�J��������N���X

	�R�c��ԓ��̃J���������݂ɑ��邽�߂̃N���X�ł��B
	��{�I�Ȏp�������CStyle�N���X�������Ă���A
	���f���N���X�Ɠ��l�̕��@�Ŏp�����䂷�邱�Ƃ�
	�o���܂����A���ڈʒu�Ǝ��_���w�肷����@�Ȃǂ�
	�g���܂��B
*/
class LunaCamera
{
	friend class Luna3D;

protected:
	static CMatrix m_mProjection;					///< �v���W�F�N�V�����s��
	static CMatrix m_mView;							///< �r���[�s��
	static CMatrix m_mCamera;						///< �J�����s��
	static CMatrix m_mCameraInv;					///< �J�����t�s��
	static CVector3D m_vPosition;					///< �J�����ʒu

	static D3DXVECTOR3 m_FrustumPoint[8];			///< �r���[�t���X�^���p���_�f�[�^
	static D3DXPLANE m_FrustumPlane[6];				///< �r���[�t���X�^���p�ʃf�[�^

	static BOX3D m_Box;								///< �r���[�t���X�^���̃o�E���f�B���O�{�b�N�X

	static LUNACAMERADATA *m_pCamera;				///< �J�����f�[�^�|�C���^
	static Uint32 m_CameraMax;						///< �J�����ő吔

protected:
	static void Init( LCAMERA lCamera );													///< �J�����f�[�^�̏�����
	static Bool Delete( LCAMERA lCamera );													///< �J�����f�[�^�̍폜
	static void SetDevice( LCAMERA lCam );													///< �f�o�C�X�ɐݒ�

public:
	static Bool Initialize( void );															///< �J�����N���X�̏�����
	static void Finalize( void );															///< �J�����N���X�̉��

	static void SetMatrixDirect( CMatrix *pProjection, CMatrix *pView );					///< �J�����}�g���b�N�X�𒼐ڐݒ�
	static void GetMatrixDirect( CMatrix *pProjection, CMatrix *pView, CMatrix *pCamera, CMatrix *pCameraInv = NULL );	///< �J�����}�g���b�N�X�𒼐ڎ擾

	static LCAMERA Create( void );															///< �쐬
	static void AddRef( LCAMERA lCam );														///< �Q�ƃJ�E���^�C���N�������g
	static void Release( LCAMERA lCam );													///< ���

	static void GetProjectionMatrix( LCAMERA lCam, CMatrix *pMat );							///< �v���W�F�N�V�����}�g���b�N�X�擾
	static void GetViewMatrix( LCAMERA lCam, CMatrix *pMat );								///< �r���[�}�g���b�N�X�擾
	static void GetCameraMatrix( LCAMERA lCam, CMatrix *pMat );								///< �J�����}�g���b�N�X�擾
	static void GetPosition( LCAMERA lCam, CVector3D *pPos );								///< �J�����ʒu�擾

	static void CreateProjection( LCAMERA lCam, Float fFovY, Float fNearZ, Float fFarZ, Float fAspect );	///< �����ϊ��p�s�񐶐�
	static void CreateOrtho( LCAMERA lCam, Float Width, Float Height, Float fNearZ, Float fFarZ );			///< ���ˉe�s�񐶐�

	static void TransformUpdate( LCAMERA lCam );											///< �J�����ϊ��X�V
	static void TransformInit( LCAMERA lCam );												///< �J�����ϊ�������

	static void Heading( LCAMERA lCam, Sint32 Rot );										///< �J�����w�b�f�B���O
	static void Pitching( LCAMERA lCam, Sint32 Rot );										///< �J�����s�b�`���O
	static void Rolling( LCAMERA lCam, Sint32 Rot );										///< �J�������[�����O
	static void RotationX( LCAMERA lCam, Sint32 Rot );										///< �J�����w����]
	static void RotationY( LCAMERA lCam, Sint32 Rot );										///< �J�����x����]
	static void RotationZ( LCAMERA lCam, Sint32 Rot );										///< �J�����y����]
	static void Translation( LCAMERA lCam, Float fPx, Float fPy, Float fPz );				///< �J�����ړ�
	static void LookAt( LCAMERA lCam, CVector3D *pEye, CVector3D *pAt, CVector3D *pUp );		///< �J������C�ӂ̓_����C�ӂ̓_�𒍎�����悤�ɂ���

	static Bool ViewfrustumCulling( BOX3D *pBox );											///< �r���[�t���X�^���J�����O���s

	static Sint32 GetAngleX( LCAMERA lCam );												///< �w�p�x�擾
	static Sint32 GetAngleY( LCAMERA lCam );												///< �x�p�x�擾
	static Sint32 GetAngleZ( LCAMERA lCam );												///< �y�p�x�擾

	static void SetFront( LCAMERA lCam, CVector3D *pVec );									///< �J�����̎p���f�[�^�̂�O�����x�N�g���ݒ�
	static void SetRight( LCAMERA lCam, CVector3D *pVec );									///< �J�����̎p���f�[�^�̂��E�����x�N�g���ݒ�
	static void SetUp( LCAMERA lCam, CVector3D *pVec );										///< �J�����̎p���f�[�^�̂�������x�N�g���ݒ�
	static void GetFront( LCAMERA lCam, CVector3D *pVec );									///< �J�����̎p���f�[�^�̂�O�����x�N�g���擾
	static void GetRight( LCAMERA lCam, CVector3D *pVec );									///< �J�����̎p���f�[�^�̂��E�����x�N�g���擾
	static void GetUp( LCAMERA lCam, CVector3D *pVec	);										///< �J�����̎p���f�[�^�̂�������x�N�g���擾
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// STRUCT
//=============================================================================
/**
	@brief	CD�g���b�N�f�[�^

	LunaCDDA�N���X�Ŏg�p�����ACD�g���b�N�f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct TRACKDATA
{
	Uint32 TrackStart;				///< �g���b�N�J�n�ʒu
	Uint32 TrackLength;				///< �g���b�N�I���ʒu
};


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	CDDA�Đ��N���X

	�l�b�h��p����CDDA���Đ����邽�߂̃N���X�ł��B
	��{�I�Ȏw��g���b�N�Đ�����A���[�v�Đ��A�ꎞ��~
	�Ȃǂ��T�|�[�g���Ă��܂��B
*/
class LunaCDDA
{
protected:
	static TRACKDATA *m_pTrackData;								///< �g���b�N�f�[�^	
	static Uint32 m_TrackMax;									///< �g���b�N�ő吔

	static Uint32 m_StartPos;									///< �Đ��J�n�ʒu
	static Uint32 m_EndPos;										///< �Đ��I���ʒu
	static Uint32 m_CurrenrPos;									///< ���݈ʒu�i�ꎞ��~�p�j
	static Sint32 m_StartTrack;									///< �J�n�g���b�N�ԍ�
	static Sint32 m_EndTrack;									///< �ŏI�g���b�N�ԍ�

	static Uint32 m_DeviceID;									///< �f�o�C�XID
	static char m_DeviceName[32];								///< �f�o�C�X���iA:�Ƃ�B:�Ƃ�C:�Ƃ��j

	static Bool m_IsOpen;										///< �f�o�C�X�I�[�v�������ۂ�
	static Bool m_IsPlay;										///< �Đ������ۂ�
	static Bool m_IsPause;										///< �ꎞ��~�����ۂ�
	static Bool m_IsLoop;										///< ���[�v�����ۂ�

public:
	static Bool Initialize( void );											///< �N���X������
	static void Finalize( void );											///< �N���X���
	static Bool Replay( WPARAM wParam, LPARAM lParam );						///< ���v���C�����p

	static Bool Eject( Bool IsEject );										///< CD�r�o

	static Bool Open( const char *pDeviceName );							///< �f�o�C�X�I�[�v��
	static void Close( void );												///< �f�o�C�X�N���[�Y

	static Bool Stop( void );												///< ��~
	static Bool Pause( void );												///< �ꎞ��~
	static Bool Replay( void );												///< ���v���C
	static Bool Play( Bool IsLoop = false );								///< �S�̍Đ�
	static Bool Play( Sint32 Track, Bool IsLoop = false );					///< ��ȍĐ�
	static Bool Play( Sint32 Track1, Sint32 Track2, Bool IsLoop = false );	///< �Ȏw��Đ�
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�����֘A�N���X

	��{�I�ȕ����񑀍�֘A�̃N���X�ł��B
	�����R�[�h�̎擾�A���p����S�p�ւ̕ϊ��A
	�����񒆂��琔���A������̎擾�ȂǁA
	�e��T�|�[�g�֐����p�ӂ���Ă��܂��B
*/
class LunaChara
{
public:
	static void Code2Str( Uint16 Code, char *pStr );														///< �����R�[�h���當�����擾����
	static Uint16 GetCharCode( const unsigned char *pStr );													///< �w�蕶�����當���R�[�h���擾����
	static Sint32 GetCharCodeEx( const unsigned char *pStr, Uint16 *pCode );								///< �����񂩂當���R�[�h���擾
	static Bool IsKanji( unsigned char Chara );																///< �S�p���������ׂ�
	static Bool IsKana( unsigned char Chara );																///< ���p�J�i�����ׂ�
	static Sint32 GetString( char Chara, const unsigned char *pSrc, unsigned char *pDst );					///< �����񂩂�"�ň͂܂ꂽ��������擾
	static Sint32 GetString( char Chara1, char Chara2, const unsigned char *pSrc, unsigned char *pDst );	///< �����񂩂�w�蕶���Ɉ͂܂ꂽ��������擾
	static Sint32 GetNumber( const unsigned char *pSrc, Sint32 *pNum );										///< �����񂩂琔�����擾
	static Sint32 Hankaku2Zenkaku( const unsigned char *pSrc, unsigned char *pDst );						///< �w�蔼�p������S�p�����ɕϊ�
	static void Hankaku2ZenkakuStr( const unsigned char *pSrc, unsigned char *pDst );						///< �����񒆂̔��p��S�p�ɕϊ�
	static void Euc2Jis( unsigned char *pDst, const unsigned char *pSrc );									///< Euc  -> Jis  �ϊ�
	static void Jis2Euc( unsigned char *pDst, const unsigned char *pSrc );									///< Jis  -> Euc  �ϊ�
	static void Jis2SJis( unsigned char *pDst, const unsigned char *pSrc );									///< Jis  -> SJis �ϊ�
	static void SJis2Jis( unsigned char *pDst, const unsigned char *pSrc );									///< Sjis -> Jis  �ϊ�
	static void Euc2SJis( unsigned char *pDst, const unsigned char *pSrc );									///< Euc  -> SJis �ϊ�
	static void SJis2Euc( unsigned char *pDst, const unsigned char *pSrc );									///< SJis -> Euc  �ϊ�
	static void CopyUpper( unsigned char *pDst, const unsigned char *pSrc );								///< ��������啶���ɕϊ����R�s�[
	static void CutAfterStr( char *pDst, const char *pSrc, char c );										///< �w�蕶���ȉ��؎̂ăR�s�[
};





//======================================================================
// INCLUDE
//======================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�����蔻��N���X

	��{�I�ȓ����蔻�菈�����s���N���X�ł��B
	�Q�c�֘A�̓����蔻��͑S�ē��삵�܂����A
	�R�c�֘A�̓����蔻��͖������̂��̂�����܂��B
*/
class LunaCollision
{
public:
	// �Q�c
	static Bool Point_Point( POINT2D *pPt1, POINT2D *pPt2 );												///< �_�Ɛ�
	static Bool Point_Line( POINT2D *pPt, LINE2D *pLine );													///< �_�Ɛ�
	static Bool Point_Rect( POINT2D *pPt, RECT2D *pRect );													///< �_�Ǝl�p
	static Bool Point_Circle( POINT2D *pPt, CIRCLE2D *pCir );												///< �_�Ɖ~
	static Bool Point_Polygon( POINT2D *pPt, POLYGON2D *pPoly );											///< �_�Ƒ��p�`
	static Bool Rect_Rect( RECT2D *pRect1, RECT2D *pRect2 );												///< �l�p�Ǝl�p
	static Bool Rect_Circle( RECT2D *pRect, CIRCLE2D *pCir );												///< �l�p�Ɖ~
	static Bool Rect_Line( RECT2D *pRect, LINE2D *pLine );													///< �l�p�Ɛ�
	static Bool Rect_Polygon( RECT2D *pRect, POLYGON2D *pPoly );											///< �l�p�Ƒ��p�`
	static Bool Circle_Circle( CIRCLE2D *pCir1, CIRCLE2D *pCir2 );											///< �~�Ɖ~
	static Bool Circle_Line( CIRCLE2D *pCir, LINE2D *pLine );												///< �~�Ɛ�
	static Bool Circle_Polygon( CIRCLE2D *pCir, POLYGON2D *pPoly );											///< �~�Ƒ��p�`
	static Bool Line_Line( LINE2D *pLine1, LINE2D *pLine2 );												///< ���Ɛ�
	static Bool Line_Polygon( LINE2D *pLine, POLYGON2D *pPoly );											///< ���Ƒ��p�`
	static Bool Polygon_Polygon( POLYGON2D *pPoly1, POLYGON2D *pPoly2 );									///< ���p�`�Ƒ��p�`
	// �R�c
	static Bool Point_Point_3D( POINT3D *pPt1, POINT3D *pPt2 );												///< �_�Ɠ_
	static Bool Point_Sphere_3D( POINT3D *pPt, SPHERE3D *pSph );											///< �_�Ƌ�
	static Bool Point_Line_3D( POINT3D *pPt, LINE3D *pLine );												///< �_�Ɛ�
	static Bool Point_Plane_3D( POINT3D *pPt, PLANE3D *pPlane );											///< �_�Ɩ�
	static Bool Point_Box_3D( POINT3D *pPt, BOX3D *pBox );													///< �_�Ɣ�
	static Bool Sphere_Sphere_3D( SPHERE3D *pSph1, SPHERE3D *pSph2 );										///< ���Ƌ�
	static Bool Sphere_Line_3D( SPHERE3D *pSph, LINE3D *pLine );											///< ���Ɛ�
	static Bool Sphere_Plane( SPHERE3D *pSph, PLANE3D *pPlane );											///< ���Ɩ�
	static Bool Sphere_Box_3D( SPHERE3D *pSph, BOX3D *pBox );												///< ���Ɣ�
	static Bool Line_Plane_3D( LINE3D *pLine, PLANE3D *pPlane, POINT3D *pPoints, POINT3D *pPos );			///< ���Ɩ�
	static Bool Line_Box_3D( LINE3D *pLine, BOX3D *pBox );													///< ���Ɣ�
	static Bool Line_Triangle_3D( LINE3D* pLine, POINT3D Points[], Float *pT, Float *pU, Float *pV );		///< ���ƎO�p�`
	static Bool Box_Box_3D( BOX3D *pBox1, BOX3D *pBox2 );													///< ���Ɣ�
	static Bool FrustumCulling( BOX3D *pFrustum, BOX3D *pBox );												///< �r���[�t���X�^���Ɣ�
	static Bool Plane_Plane_3D( PLANE3D *pPlane1, PLANE3D *pPlane2, POINT3D Points1[], POINT3D Points2[] );	///< ���ʓ��m�̔���

	// �R���W�����f�[�^�쐬�֐�
	static void CreateBox( BOX3D *pOut, POINT3D *pMinPt, POINT3D *pMaxPt, CMatrix *pMatrix );				///< ������
	static void CreateBoxProjection( BOX3D *pOut, POINT3D *pMinPt, POINT3D *pMaxPt, CMatrix *pMatrix );		///< ������
	static void CreatePlaneFromPoint( PLANE3D *pOut, POINT3D *pPt0, POINT3D *pPt1, POINT3D *pPt2 );			///< ���ʐ���
	static void CreatePlane( PLANE3D *pOut, POINT3D *pPt, POINT3D *pNormal );								///< ���ʐ���

	static Bool PlaneIntersectLine( POINT3D *Intersection, PLANE3D *pPlane, POINT3D *pEdge0, POINT3D *pEdge1 );	///< ���ʂƒ����̌�_
	static Bool EdgeIntersectsQuad( POINT3D* pEdges, POINT3D* pFacePoints, PLANE3D* pPlane, POINT3D *pHitPos );	///< �S�_�ō\������镽�ʂƐ����̌�������
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�R���\�[���Ǘ��N���X

	�R���\�[�����Ǘ����邽�߂̃N���X�ł��B
	�f�o�b�O�����Ȃǂ����ȈՓI�ɍs����悤��
	�Ȃ��Ă��܂��B
*/
class LunaConsole
{
protected:
	static Bool m_IsInit;											///< �������t���O
	static HANDLE m_hConsole;										///< �R���\�[���n���h��

public:
	static Bool Initialize( void );									///< �N���X�̏�����
	static void Finalize( void );									///< �N���X�̏I��

	static Bool Create( void );										///< �R���\�[������
	static void Release( void );									///< �R���\�[�����

	static void Clear( void );										///< ��ʃN���A
	static void Locate( Sint32 x, Sint32 y );						///< �ʒu�w��
	static void Print( const char *pStr,... );						///< �o��
	static void Print( Sint32 x, Sint32 y, const char *pStr,... );	///< �ʒu�w��t���o��
	static void SetColor( Uint16 Attributes );						///< �F�ݒ�
	static void CursorOff( void );									///< �J�[�\���I�t
	static void CursorOn( void );									///< �J�[�\���I��
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�f�o�b�O�⍲�N���X

	�f�o�b�O���T�|�[�g����N���X�ł��B
	��p�̃f�o�b�O�E�B���h�E���J���Ă�
	���O�\����A�u�b�{�{�̃f�o�b�O�E�B���h�E�ւ�
	������`��Ȃǂ��s�����Ƃ��o���܂��B
*/
class LunaDebug
{
protected:
	static HWND m_hListWnd;							///< �f�o�b�O�p�E�B���h�E�̃E�B���h�E�n���h��

public:
	static Bool Initialize( void );					///< �N���X������
	static void Finalize( void );					///< �N���X���

	static void OutputString( char *pStr,... );		///< ��������u�b�̃f�o�b�O�E�C���h�E�ɕ\��

	static Bool OpenWindow( void );					///< �f�o�b�O�E�C���h�E�I�[�v��
	static void CloseWindow( void );				///< �f�o�b�O�E�C���h�E�N���[�Y
	static void DrawString( const char *pStr,... );	///< �f�o�b�O�E�C���h�E�ɕ�����`��
	static void Clear( void );						///< �����o�b�t�@�N���A
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�v���~�e�B�u�G�t�F�N�g�N���X

	LunaPrimitive�̃��b�p�[�N���X�ł��B
	�P���ȃ|���S�������`��ł��Ȃ�LunaPrimitive
	�N���X�ɑ΂��ėl�X�Ȍ`��̃|���S����
	�`����T�|�[�g���郉�b�p�[�ɂȂ��Ă��܂��B
*/
class LunaEffect
{
public:
	static void FillRotate( LPRIMITIVE lPrim, CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 Angle );																		///< ��]�\�|���S���`��
	static void FillRotateXYZ( LPRIMITIVE lPrim, CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );									///< �R����]�\�|���S���`��

	static void FillTriangle( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color );																						///< ���O�p�`�`��
	static void FillTriangleRotate( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color, Uint32 Angle );																	///< ��]�\���O�p�`�`��
	static void FillTriangleRotateXYZ( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );									///< �R����]�\���O�p�`�`��

	static void FillSquare( LPRIMITIVE lPrim, CLunaRect *pDstRect, Float fPosZ, D3DCOLOR Color );																									///< �l�p�`�`��
	static void FillSquareRotate( LPRIMITIVE lPrim, CLunaRect *pDstRect, Float fPosZ, D3DCOLOR Color, Uint32 Angle );																				///< ��]�\�l�p�`�`��
	static void FillSquareRotateXYZ( LPRIMITIVE lPrim, CLunaRect *pDstRect, Float fPosZ, D3DCOLOR Color, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );												///< �R����]�\�l�p�`�`��

	static void FillPolygon( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color, Sint32 Num );																			///< �����p�`�`��
	static void FillPolygonRotate( LPRIMITIVE lPrim, Float Px, Float Py, Float Radiust, Float fPosZ, D3DCOLOR Color, Sint32 Num, Uint32 Angle );													///< ��]�\�����p�`�`��
	static void FillPolygonRotateXYZ( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );						///< �R����]�\�����p�`�`��

	static void FillRing( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num );										///< �y�������O�`��
	static void FillRingRotate( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 Angle );					///< ��]�\�y�������O�`��
	static void FillRingRotateXYZ( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );	///< �R����]�\�y�������O�`��

	static void FillRingEx( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num );																///< �x�������O�`��
	static void FillRingExRotate( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 Angle );											///< ��]�\�x�������O�`��
	static void FillRingExRotateXYZ( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );			///<�@�R����]�\�x�������O�`��

	static void CircleFade( LPRIMITIVE lPrim, LTEXTURE lTex, CLunaRect *pSrc, Sint32 Divide, Sint32 Side, Sint32 Alpha, Bool IsSmooth );																///< �~��t�F�[�h�`��
	static void CircleRoundFade( LPRIMITIVE lPrim, LTEXTURE lTex, CLunaRect *pSrc, Sint32 Divide, Sint32 Side, Sint32 Alpha, Bool IsSmooth );														///< �~���]�t�F�[�h�`��
};




//==========================================================================
// INCLUDE
//==========================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�e�d�o�֘A�N���X

	FEP�𑀍삷��N���X�ł��B
	OS�Ŏg�p���Ă���FEP��p����
	��{�I�ȓ��͏������T�|�[�g���Ă��܂�
*/
class LunaFEP
{
	enum { FEP_BUFFER_SIZE = 2048 };

protected:
	static HWND				m_hWnd;							///< �E�B���h�E�n���h��
	static HIMC				m_hImc;							///< FEP�n���h��
	static CANDIDATELIST	*m_pCandidateList;				///< �������X�g�|�C���^
	static char				m_String[FEP_BUFFER_SIZE];		///< ���͕�����i�[�o�b�t�@
	static Sint32			m_Position;						///< �J�[�\���ԍ�
	static char				m_IsLastChara;					///< �ŏI����
	static char				m_StrTbl[5][1024];				///< ������o�b�t�@

public:
	static Bool Initialize( void );							///< �N���X������
	static void Finalize( void );							///< �N���X���

	static Bool IsOpen( void );										///< �e�d�o�I�[�v�������ۂ�
	static void BackChara( void );									///< �ŏI�����폜
	static void AddChara( Uint32 Chara );							///< �����ǉ�
	static Sint32 GetConvertPos( void );							///< �ϊ��ʒu�擾
	static Sint32 GetCursorCount( void );							///< �J�[�\���ʒu�擾
	static Sint32 GetCountCandidate( void );						///< ���������񐔎擾
	static Sint32 GetCandidateStart( void );						///< �����J�n�ʒu�擾
	static Sint32 GetCandidateCount( void );						///< �����f�[�^���擾
	static Sint32 GetCandidateIndex( void );						///< �����C���f�b�N�X�擾
	static void GetCandidateString( char *pStr, Sint32 Index );		///< �Y�����������擾
	static Bool GetStatus( char *pStr );							///< ��Ԏ擾
	static void GetConvertString( char *pStr );						///< �ϊ���������擾
	static void GetInputString( char *pStr );						///< ���͍ςݕ�����擾
	static void ClearInputString( void );							///< ���͍ςݕ�����o�b�t�@������
	static Bool LunaFEP::Notify( Uint32 Action, Uint32 Index, Uint32 Value );	///< ���̓R���e�L�X�g�̏�ԕύX�Ɋւ������ IME �ɒm�点�܂�

	static void RefreshStatus( void );								///< ��ԍX�V
	static Bool GetStringTbl( char *pStatus, char *pInput1, char *pConvert1, char *pConvert2, char *pInput2 );	///< ������e�[�u���擾

	static HIMC GetHandle( void );									///< �h�l�b�n���h���擾
};



//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
#ifndef __TOOL_MODE__

/**
	@brief	�t�@�C�o�[�N���X

	�X���b�h�����y���e�Ղɕ��񏈗��������ł��܂��B
*/
class LunaFiber
{
private:
	static void UpdateFiberList( void );					///< �t�@�C�o�[���X�g�X�V

public:
	static Bool Initialize( void );							///< �N���X������
	static void Finalize( void );							///< �N���X���

	static Bool Start( void );								///< �t�@�C�o�[�����X�^�[�g

	static Bool Switch( Uint32 FiberId );					///< �t�@�C�o�[�؂�ւ�

	static Bool Create( Uint32 FiberId, PFIBERPROC pProcMain, Uint32 StackSize );	///< �t�@�C�o�[����
	static Bool Exit( Uint32 FiberId );						///< �t�@�C�o�[�I��

	static void Suspend( Uint32 FiberId );					///< �t�@�C�o�[�ꎞ��~
	static void Resume( Uint32 FiberId );					///< �t�@�C�o�[�ĊJ

	static Float GetCPUTime( Uint32 FiberId );				///< �b�o�t�g�p���Ԏ擾
};

#endif



//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�n�C�g�t�B�[���h�N���X

	���O�^�}�b�v���Ǘ����邽�߂̃n�C�g�t�B�[���h�N���X�ł��B
	�Ƃ����Ă����ۂɂ͍����}�b�v����̐����ł͂Ȃ��A
	�w�t�@�C������̃N�I�[�h�c���[�^�t�B�[���h�Ǘ��N���X�ł��B
*/
class LunaField
{
protected:
	static LUNAFIELDDATA *m_pField;																						///< �t�B�[���h�f�[�^�|�C���^
	static Uint32 m_FieldMax;																							///< �t�B�[���h�ő吔

protected:
	static void Init( LFIELD lField );																					///< �t�B�[���h�f�[�^������
	static Bool Delete( LFIELD lField );																				///< �t�B�[���h�f�[�A�폜
	static void DeleteFrame( void *pData );																				///< �t���[���폜
	static void DeleteMesh( void *pData );																				///< ���b�V���폜
	static LFIELD GetFreeHandle( void );																				///< ���g�p�I�u�W�F�N�g�n���h���擾

	static void MeshInit( void *pData );																				///< ���b�V��������
	static void FrameInit( void *pData );																				///< �t���[��������

	static void RenderingFrame( LFIELD lField, void *pData );															///< �t���[�������_�����O
	static Sint32 SearchMeshNoFromPoint( void *pFrame, LFIELD lField, CVector3D *pPos );									///< �C�ӂ̓_���ǂ̃��b�V�����ɂ��邩������
	static void CreateQuadTree( void *pFrame, LFIELD lField, Sint32 Px, Sint32 Pz, Sint32 Count );						///< �N�I�[�h�c���[�̍쐬
	static void CullQuadTree( void *pFrame, LFIELD lField );															///< �N�I�[�h�c���[�̃J�����O
	static Bool UpdateVertexIndexBuffer( LFIELD lField );																///< ���_�E�C���f�b�N�X�o�b�t�@�X�V
	static Bool ConvertMeshToField( LFIELD lField, ID3DXMesh *pMesh, Sint32 TreeDepth, Sint32 ZoomSize );				///< ���b�V���f�[�^���t�B�[���h�f�[�^�ɃR���o�[�g
	static void SendToShaderConstant( void *pData0, void *pData1 );														///< �V�F�[�_�[�Ƀf�[�^��]��

	static LFIELD LoadFromMemory( void *pData, Uint32 Size, Sint32 TreeDepth, Sint32 ZoomSize, eSurfaceFormat Format, Bool IsBumpMap, D3DCOLOR KeyColor );	///< ����������f�[�^��ǂݍ���

public:
	static Bool Initialize( void );																						///< �t�B�[���h�V�X�e��������
	static void Finalize( void );																						///< �t�B�[���h�V�X�e�����
	static void Reset( void );																							///< �t�B�[���h�f�[�^���Z�b�g
	static void Restore( void );																						///< �t�B�[���h�f�[�^���X�g�A
	static void SetMax( Uint32 Max );																					///< �ő�t�B�[���h�g�p�ʐݒ�
	static void Release( LFIELD lField );																				///< �t�B�[���h�f�[�^���

	static void SetEffectHandle( LFIELD lField, LSHADERFX lShaderFx );													///< �G�t�F�N�g�t�@�C�����t�B�[���h�ɐݒ�
	static void SetEffectSendData( LFIELD lField, Uint32 SendData );													///< �G�t�F�N�g�t�@�C���ւ̑��M�f�[�^
	static void ChangeShaderVersion( LFIELD lField, Uint16 Major, Uint16 Minor );										///< �g�p����V�F�[�_�[�̃o�[�W������ύX
	static void SetTexture( LFIELD lField, Uint32 Stage, LTEXTURE lTex, Sint32 MateriaNo = -1 );						///< �t�B�[���h�փe�N�X�`���ݒ�

	static LFIELD CreateFromMemory( void *pData, Uint32 Size, Sint32 TreeDepth, Sint32 ZoomSize = -1, eSurfaceFormat Format = FORMAT_TEXTURE_3D, Bool IsBumpMap = false, D3DCOLOR KeyColor = COLORKEY_DISABLE );	///< ����������f�[�^��ǂݍ���
	static LFIELD CreateFromFile( const char *pFileName, Sint32 TreeDepth, Sint32 ZoomSize = -1, eSurfaceFormat Format = FORMAT_TEXTURE_3D, Bool IsBumpMap = false, D3DCOLOR KeyColor = COLORKEY_DISABLE );			///< �t�@�C������t�B�[���h�f�[�^�𐶐�

	static void ViewfrustumCulling( LFIELD lField );																	///< �r���[�t���X�^���J�����O
	static Sint32 Rendering( LFIELD lField );																			///< �t�B�[���h�����_�����O
	static Float RenderingTimer( LFIELD lField );																		///< �t�B�[���h�����_�����O
	static Sint32 GetCellCount( LFIELD lField );																		///< �Z�����擾
	static Bool IsDrawCell( LFIELD lField, Sint32 Px, Sint32 Pz );														///< �Z���`��L���擾

	static Bool CheckCrossLine( LFIELD lField, CVector3D *pPos0, CVector3D *pPos1, CVector3D *pOut );						///< �Q�_�����Ԑ����ƃ|���S���̌�������
	static Sint32 SearchMeshNoFromPoint( LFIELD lField, CVector3D *pPos );												///< �C�ӂ̓_���ǂ̃��b�V�����ɂ��邩������
	static Bool GetHeightFromPoint( LFIELD lField, CVector3D *pPos, CVector3D *pOut, CVector3D *pNorm = NULL, Float *pDistance = NULL );///< �C�ӂ̓_����C�ӕ����ł̃t�B�[���h���̍��������߂�
	static Bool GetNearPointFromPoint( LFIELD lField, CVector3D *pPos, CVector3D *pDir, CVector3D *pOut, CVector3D *pNorm = NULL, Float *pDistance = NULL );///< �C�ӂ̓_����C�ӕ����ł̃t�B�[���h���̍ŋߓ_�����߂�
};




//=============================================================================
// INCLUDE
//=============================================================================



//=============================================================================
// DEFINE
//=============================================================================
#define FILE_SEARCH_MAX		(16)


//=============================================================================
// STRUCT
//=============================================================================
struct FILE_SEARCH_LIST
{
	char FileRootPath[MAX_PATH];
	char FilePackName[MAX_PATH];
};

/**
	@brief	�t�@�C���V�[�N��`

	LunaFile�N���X�Ŏg�p�����t�@�C���V�[�N�̕��@��\����`�B
*/
enum eSeekFlag
{
	SEEK_FILE_CURRENT,					///< �J�����g�ʒu
	SEEK_FILE_START,					///< �擪�ʒu
	SEEK_FILE_END,						///< �I�[�ʒu
};

//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�t�@�C���Ǘ��N���X

	�t�@�C�����Ǘ����邽�߂̃N���X�ł��B
	�W���Ή��c�[���ł���ALLZSS�ALPACK�����
	�ǂݏo���̃T�|�[�g�����Ă��܂��B
*/
class LunaFile
{
protected:
	static char m_CurrentDirectory[MAX_PATH];
	static FILE_SEARCH_LIST m_FileSearchList[FILE_SEARCH_MAX];

protected:
	static Bool GetFileAddress( HANDLE hFile, const char *pFile, Uint32 *pAddress, Uint32 *pSize, Uint32 *pCrc );	///< �t�@�C���A�h���X�̎擾
	static Bool DecodeData( void **ppData, Uint32 *pSize );															///< �f�[�^�̃f�R�[�h

public:
	static Bool Initialize( void );																					///< �t�@�C���N���X������
	static void Finalize( void );																					///< �t�@�C���N���X���

	static Bool IsFileExistInPack( const char *pFile );																///< �p�b�N���t�@�C�����݃`�F�b�N

	static Bool Load( const char *pFile, void **ppData, Uint32 *pSize );											///< �t�@�C����ǂݍ���
	static Bool LoadFromFile( const char *pFile, void **ppData, Uint32 *pSize );									///< �t�@�C����ǂݍ���
	static Bool LoadFromPack( const char *pFile, const char *pPack, void **ppData, Uint32 *pSize );					///< �p�b�N�t�@�C������Y���t�@�C����ǂݍ���
	static Bool LoadFromResource( const char *pFile, const char *pResource, void **ppData, Uint32 *pSize );			///< ���\�[�X����t�@�C����ǂݍ���

	static FILEDATA *FileOpen( const char *pFile, Bool ReadOnly = false );											///< �w��t�@�C���̃t�@�C���n���h�����擾
	static FILEDATA *FileOpenFromFile( const char *pFile, Bool ReadOnly = false );									///< �w��t�@�C���̃t�@�C���n���h�����擾
	static FILEDATA *FileOpenFromPack( const char *pFile, const char *pPack, Bool ReadOnly = false );				///< �p�b�N�t�@�C�����̂��ăt�@�C���̃t�@�C���n���h�����擾
	static void FileClose( FILEDATA *pFile );																		///< �t�@�C���N���[�Y
	static Uint32 FileGetSize( FILEDATA *pFile );																	///< �t�@�C���T�C�Y�擾
	static Uint32 FileGetPosition( FILEDATA *pFile );																///< �t�@�C���ʒu�擾

	static Uint32 FileWrite( FILEDATA *pFile, Uint32 Size, void *pData );											///< �t�@�C����������
	static Uint32 FileRead( FILEDATA *pFile, Uint32 Size, void *pData );											///< �t�@�C���ǂݍ���
	static Bool FileSeek( FILEDATA *pFile, Uint32 Offset, eSeekFlag Flag );											///< �t�@�C���V�[�N

	static Uint32 GetCRC( Uint8 Data[], Sint32 Size );																///< �f�[�^��CRC32���擾

	static void SetCurrentDirectory( char *pCurrentDir );															///< �Ǎ���J�����g�f�B���N�g����ݒ�
	static void SetRootPath( Uint32 Priority, const char *pRootPath, const char *pPackFile );						///< �Ǎ���̃��[�g

	static Bool GetFilePath( char *pFilePath, const char *pSrcFile );												///< �f�[�^���Ƃ̃p�X�擾
	static Bool CopyFileToTempDir( const char *pSrcFile, char *pFilePath );											///< �e���|�����f�B���N�g���Ƀp�b�N�̒��g���R�s�[
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�t�H���g�֘A�N���X

	�P���ȃt�H���g�`����T�|�[�g����N���X�ł��B
	�o�b�N�o�b�t�@�A�e�N�X�`���A�I�t�X�N���[��
	�T�[�t�F�C�X�ւ̃t�H���g�`�揈�����T�|�[�g���܂��B
*/
class LunaFont
{
protected:
	static LibLuna::CFontMgr *m_pFontMgr;

public:
	static Bool Initialize( void );																				///< �N���X������
	static void Finalize( void );																				///< �N���X���

	static LFONT Create( const char *pFontFace, Sint32 FontSize, Bool IsItalic = false, Bool IsBold = false );	///< �t�H���g�I�u�W�F�N�g����
	static void Release( LFONT lFont );																			///< �t�H���g�I�u�W�F�N�g���

	static Sint32 GetFontSize( LFONT lFont );																	///< �t�H���g�T�C�Y�擾
	static Sint32 GetTextWidth( LFONT lFont, const char *pStr );												///< ������̍ő剡���擾
	static void GetFontData( LFONT lFont, Uint16 Code, ABC *pABC );												///< �t�H���g�f�[�^�擾
	static Bool GetWidth( LFONT lFont, const char *pStr, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight );	///< �������擾
	static void SetDestination( LFONT lFont, LTEXTURE lTarget = INVALID_TEXTURE );								///< �`���ݒu

	static void Begin( LFONT lFont, Bool IsUpdate = true );														///< �t�H���g�����J�n
	static void End( void );																					///< �t�H���g�����I��
	static void DrawChar( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );									///< �����`��
	static void DrawCharAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );								///< �A���`�G�C���A�X�t�������`��
	static Sint32 DrawText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< �e�L�X�g�`��
	static Sint32 DrawTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< �A���`�G�C���A�X�t���e�L�X�g�`��
	static Sint32 DrawPText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< �v���|�[�V���i���e�L�X�g�`��
	static Sint32 DrawPTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );					///< �A���`�G�C���A�X�t���v���|�[�V���i���e�L�X�g�`��
	static Sint32 DrawTextDirect( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< �e�L�X�g�`��
	static Sint32 DrawTextDirectAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< �A���`�G�C���A�X�t���e�L�X�g�`��
	static Sint32 DrawPTextDirect( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< �v���|�[�V���i���e�L�X�g�`��
	static Sint32 DrawPTextDirectAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );					///< �A���`�G�C���A�X�t���v���|�[�V���i���e�L�X�g�`��
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�t�H���g�X�v���C�g�Ǘ��N���X

	�X�v���C�g�`���̃t�H���g�`��N���X�ł��B
	���O�Ƀe�N�X�`���Ƀt�H���g��~���l�߁A
	UV�e�[�u�����쐬���Ă����A�e�[�u���A�N�Z�X����A
	�C�ӂ̕������e�N�X�`������؂�o���ĕ`��
	����悤�ȍ\���ɂȂ��Ă��܂��B
	������A�P���ȕ����`����������ɏ����ł��A
	�G�t�F�N�g�Ȃǂ��e�Ղɂ����܂����A
	�S�Ă̕������e�N�X�`���ɓW�J���Ă������߁A
	�g�p�������͑����Ă��܂��܂��B
*/
class LunaFontSprite
{
protected:
	static LibLuna::CFontSprite2DMgr *m_pFontSprMgr;

public:
	static Bool Initialize( void );															///< �N���X������
	static void Finalize( void );															///< �N���X���

	static LFONTSPRITE Create( const char *pBuffer, Bool IsAlpha, Uint32 Num, LFONT lFont, Bool IsSortZ = false, Bool IsAntialias = true );	///<�t�H���g�I�u�W�F�N�g����
	static LFONTSPRITE CreateFromFile( const char *pFileName, const char *pExt, Bool IsAlpha, Uint32 Num, Bool IsSortZ = false );		///< �t�H���g�I�u�W�F�N�g��LFD���琶��

	static void DisableHankakuSizeHalf( LFONTSPRITE lFontSpr );															///< ���p�����̃T�C�Y��1/2�ɂ���̂��~�߂�

	static Bool ReCreateStringBuffer( LFONTSPRITE lFontSpr, const char *pBuffer, Uint32 Num );			///<�t�H���g�I�u�W�F�N�g�Đ���

	static void Release( LFONTSPRITE lFontSpr );											///< �t�H���g�I�u�W�F�N�g���
	static void BufferResize( LFONTSPRITE lFontSpr, Uint32 Count );							///< �o�b�t�@�T�C�Y�Đݒ�

	static Bool GetWidth( LFONTSPRITE lFontSpr, const char *pStr, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight );	///< �������擾
	static void GetHeight( LFONTSPRITE lFontSpr, Sint32 *pHeight );							///< �t�H���g�����擾
	static void ResetBuffer( LFONTSPRITE lFontSpr, Sint32 Space = 0 );							///< �t�H���g�o�b�t�@������
	static void UpdateBuffer( LFONTSPRITE lFontSpr );										///< �t�H���g�o�b�t�@�X�V
	static void Rendering( LFONTSPRITE lFontSpr );											///< �t�H���g�o�b�t�@�����_�����O

	static void DrawString( LFONTSPRITE lFontSpr, const char *pStr, Sint32 Px, Sint32 Py, Float Pz, D3DCOLOR Color );		///< �e�L�X�g�`��
	static void DrawStringP( LFONTSPRITE lFontSpr, const char *pStr, Sint32 Px, Sint32 Py, Float Pz, D3DCOLOR Color );		///< �v���|�[�V���i���t�H���g�e�L�X�g�`��
	static Sint32 DrawChara( LFONTSPRITE lFontSpr, const char *pStr, CLunaRect *pDst, Float Pz, D3DCOLOR Color );			///< �����`��
	static Sint32 DrawCharaRotate( LFONTSPRITE lFontSpr, const char *pStr, CLunaRect *pDst, Float Pz, D3DCOLOR Color, Sint32 Angle );	///< ��]�����`��
	static Sint32 DrawCharaRotateXYZ( LFONTSPRITE lFontSpr, const char *pStr, CLunaRect *pDst, Float Pz, D3DCOLOR Color, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );	///< �R����]�����`��

	static POINT GetStringLastPos( LFONTSPRITE lFontSpr, const char *pStr, Sint32 Px, Sint32 Py );	///< �`�掞�ŏI�ʒu�擾
	static POINT GetStringLastPosP( LFONTSPRITE lFontSpr, const char *pStr, Sint32 Px, Sint32 Py );	///< �v���|�[�V���i���t�H���g�`�掞�ŏI�ʒu�擾
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�t�H���g�X�v���C�g�Ǘ��N���X

	�X�v���C�g�`���̃t�H���g�`��N���X�ł��B
	���O�Ƀe�N�X�`���Ƀt�H���g��~���l�߁A
	UV�e�[�u�����쐬���Ă����A�e�[�u���A�N�Z�X����A
	�C�ӂ̕������e�N�X�`������؂�o���ĕ`��
	����悤�ȍ\���ɂȂ��Ă��܂��B
	������A�P���ȕ����`����������ɏ����ł��A
	�G�t�F�N�g�Ȃǂ��e�Ղɂ����܂����A
	�S�Ă̕������e�N�X�`���ɓW�J���Ă������߁A
	�g�p�������͑����Ă��܂��܂��B
*/
class LunaFontSprite3D
{
protected:
	static LibLuna::CFontSprite3DMgr *m_pFontSprMgr;

public:
	static Bool Initialize( void );												///< �N���X������
	static void Finalize( void );												///< �N���X���

	static LFONTSPRITE3D Create( const char *pBuffer, Bool IsAlpha, Uint32 Num, LFONT lFont, Bool IsAntialias = true );	///<�t�H���g�I�u�W�F�N�g����
	static LFONTSPRITE3D CreateFromFile( const char *pFileName, const char *pLagName, Bool IsAlpha, Uint32 Num );		///< �t�H���g�I�u�W�F�N�g��LFD���琶��

	static Bool ReCreateStringBuffer( LFONTSPRITE3D lFontSpr, const char *pBuffer, Uint32 Num );			///<�t�H���g�I�u�W�F�N�g�Đ���

	static void BufferResize( LFONTSPRITE3D lFontSpr, Uint32 Count );							///< �o�b�t�@�T�C�Y�Đݒ�
	static void Release( LFONTSPRITE3D lFontSpr );											///< �t�H���g�I�u�W�F�N�g���

	static void ResetBuffer( LFONTSPRITE3D lFontSpr );										///< �t�H���g�o�b�t�@������
	static void UpdateBuffer( LFONTSPRITE3D lFontSpr );										///< �t�H���g�o�b�t�@�X�V
	static void Rendering( LFONTSPRITE3D lFontSpr );										///< �t�H���g�o�b�t�@�����_�����O

	static void DrawString( LFONTSPRITE3D lFontSpr, const char *pStr, CStyle *pStyle, Float fScale, D3DCOLOR Color );	///< ������`��
	static void DrawStringP( LFONTSPRITE3D lFontSpr, const char *pStr, CStyle *pStyle, Float fScale, D3DCOLOR Color );	///< �v���|�[�V���i���t�H���g�e�L�X�g�`��
};





//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// ENUM
//=============================================================================
/**
	@brief	POV�p�x�萔
*/
enum ePOV
{
	POV_0		= 0,
	POV_45		= 45,
	POV_90		= 90,
	POV_135		= 135,
	POV_180		= 180,
	POV_225		= 225,
	POV_270		= 270,
	POV_315		= 315,
	POV_N		= POV_0,
	POV_NE		= POV_45,
	POV_E		= POV_90,
	POV_SE		= POV_135,
	POV_S		= POV_180,
	POV_SW		= POV_225,
	POV_W		= POV_270,
	POV_NW		= POV_315,
};

/**
	@brief	�L�[�X�e�[�^�X��`

	LunaPad�N���X�Ŏg�p�����L�[�̊e���Ԓ�`�B
*/
enum eKeyState
{
	KEY_STATE_FREE,						///< �L�[�̓t���[���
	KEY_STATE_PULL,						///< �L�[�͗����ꂽ�u��
	KEY_STATE_PUSH,						///< �L�[�͉����ꂽ�u��
	KEY_STATE_HOLD,						///< �L�[�͉����ꑱ���Ă���
};

/**
	@brief �}�E�X�{�^����Ԓ�`

	�e��{�^���̏�Ԓ�`�B
*/
enum eMouseState
{
	MOUSE_FREE,							///< �}�E�X�{�^���͉�����Ă��Ȃ�
	MOUSE_PULL,							///< �}�E�X�{�^���͗����ꂽ
	MOUSE_PUSH,							///< �}�E�X�{�^���͉����ꂽ
	MOUSE_HOLD,							///< �}�E�X�{�^���͉�����Â��Ă���
};

/**
	@brief	�p�b�h�X�e�[�g��`

	LunaPad�N���X�Ŏg�p�����p�b�h�̊e���Ԓ�`�B
*/
enum ePadState
{
	PAD_STATE_PUSH,						///< �������u�Ԏ擾�p
	PAD_STATE_PULL,						///< �������u�Ԏ擾�p
	PAD_STATE_HOLD,						///< ���������擾�p
	PAD_STATE_REPEAT,					///< ���s�[�g�擾�p

	PAD_STATE_MAX,
};

/**
	@brief	�p�b�h�p�e��{�^����`

	LunaPad�N���X�Ŏg�p�����e��{�^���̒�`�B
*/
enum ePadSort
{
	PAD_DIR_UP,							///< ������w��
	PAD_DIR_DOWN,						///< �������w��
	PAD_DIR_LEFT,						///< �������w��
	PAD_DIR_RIGHT,						///< �E�����w��

	PAD_BUTTON_01,						///< �{�^���P�w��
	PAD_BUTTON_02,						///< �{�^���Q�w��
	PAD_BUTTON_03,						///< �{�^���R�w��
	PAD_BUTTON_04,						///< �{�^���S�w��
	PAD_BUTTON_05,						///< �{�^���T�w��
	PAD_BUTTON_06,						///< �{�^���U�w��
	PAD_BUTTON_07,						///< �{�^���V�w��
	PAD_BUTTON_08,						///< �{�^���W�w��
	PAD_BUTTON_09,						///< �{�^���X�w��
	PAD_BUTTON_10,						///< �{�^���P�O�w��
	PAD_BUTTON_11,						///< �{�^���P�P�w��
	PAD_BUTTON_12,						///< �{�^���P�Q�w��
	PAD_BUTTON_13,						///< �{�^���P�R�w��
	PAD_BUTTON_14,						///< �{�^���P�S�w��
	PAD_BUTTON_15,						///< �{�^���P�T�w��
	PAD_BUTTON_16,						///< �{�^���P�U�w��

	PAD_SORT_MAX,

	PAD_SORT_NONE,						///< ����

	PAD_BUTTON_MAX	= (PAD_BUTTON_16 - PAD_BUTTON_01),
};


//=============================================================================
// STRUCT
//=============================================================================
/**
	@brief	���f�[�^

	LunaInput�N���X�Ŏg�p�����A���̓f�o�C�X�̎���<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct AXISDATA
{
	Sint32 Ax;								///< �w��
	Sint32 Ay;								///< �x��
	Sint32 Az;								///< �y��
};

/**
	@brief	�p�b�h���f�[�^

	LunaPad�N���X�Ŏg�p�����A�p�b�h���f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct PADSTATUS
{
	Sint32 KeyState[PAD_STATE_MAX];			///< �L�[��ԃf�[�^
};

/**
	@brief	�p�b�h�f�[�^�w�b�_

	LunaPad�N���X�Ŏg�p�����A�p�b�h�ۑ��p�f�[�^�̃w�b�_<BR>
	�\���̂ł�
*/
struct PADSAVEHEADER
{
	char Guid[4];								///< �t�@�C�����ʗp
	Sint32 LayerMax;							///< ���C���[��
	Sint32 FrameMax;							///< �t���[����
};

/**
	@brief	�}�E�X�f�[�^

	�}�E�X�f�[�^���i�[���邽�߂̍\���́B
*/
struct MOUSEDATA
{
	Sint32 X;							///< �w�ʒu
	Sint32 Y;							///< �x�ʒu
	Sint32 W;							///< �y�ʒu

	Sint32 Mx;							///< �w�ړ���
	Sint32 My;							///< �x�ړ���

	Bool ClickL;						///< ���N���b�N
	Bool ClickR;						///< �E�N���b�N
	Bool ClickW;						///< �z�C�[���N���b�N

	Bool DoubleClickL;					///< �E�_�u���N���b�N
	Bool DoubleClickR;					///< ���_�u���N���b�N
	Bool DoubleClickW;					///< �z�C�[���_�u���N���b�N

	eMouseState StateL;					///< ���{�^�����
	eMouseState StateR;					///< �E�{�^�����
	eMouseState StateW;					///< �z�C�[���{�^�����
};

/**
	@brief	�L�[�{�[�h�f�[�^

	�L�[�{�[�h�f�[�^����M���邽�߂̍\����
*/
struct KEYBOARDDATA
{
	char Key[256];						///< ��
};

/**
	@brief	�W���C�X�e�B�b�N�f�[�^

	�W���C�X�e�B�b�N�p�f�[�^���i�[���Ă������߂̍\���́B
*/
struct JOYSTICKDATA
{
	Sint32 Px, Py, Pz;					///< ��
	Sint32 Rx, Ry, Rz;					///< ��]��
	Sint32 Vx, Vy, Vz;					///< ���̑��x
	Sint32 VRx, VRy, VRz;				///< ���̊p���x
	Sint32 Ax, Ay, Az;					///< ���̉����x
	Sint32 ARx, ARy, ARz;				///< ���̊p�����x
	Sint32 Fx, Fy, Fz;					///< ���̃t�H�[�X
	Sint32 FRx, FRy, FRz;				///< ���̃g���N
	Sint32 Slider[2];					///< �X���C�_�[
	Sint32 Pov[4];						///< POV
	char Button[PAD_BUTTON_MAX];		///< �{�^��
};

/**
	@brief	�W���C�X�e�B�b�N�f�[�^�f�[�^

	LunaInput�N���X�Ŏg�p�����A�W���C�X�e�B�b�N�f�[�^��<BR>
	�Ǘ����邽�߂̍\���̂ł�
*/
struct JOYSTICKWORK
{
	JOYSTICKDATA Data;						///< �W���C�X�e�B�b�N�f�[�^
	AXISDATA Center;						///< �����S��`
	AXISDATA Max;							///< ���ő�l
	AXISDATA RotCenter;						///< ��]�����S��`
	AXISDATA RotMax;						///< ��]���ő�l
	IDirectInputDevice8 *pDevice;			///< �f�o�C�X

	Bool IsPolling;							///< �|�[�����O�����邩�ۂ�
	Bool IsForceFeedback;					///< �t�H�[�X�t�B�[�h�o�b�N�ɑΉ����Ă��邩�ۂ�

	Sint32 LockKey;							///< ���b�N����L�[
	Sint32 KeyState[PAD_STATE_MAX];			///< �L�[���
	Sint32 KeyStateWork[2];					///< �L�[���擾�p���[�N
	Sint32 KeyRepeatCounter[PAD_SORT_MAX];	///< �L�[���s�[�g�J�E���^�[
	Sint32 PadMap[PAD_SORT_MAX];				///< �p�b�h�}�b�s���O���
	Sint32 KeyAlias[PAD_SORT_MAX];			///< �L�[�{�[�h�}�b�s���O�p

	Bool IsUsePOVDirection;					///< POV ������L�[�Ɏg�p���邩�ǂ���
};


//=============================================================================
// CLASS
//=============================================================================
class LunaInput
{
#ifdef __TOOL_MODE__
	friend void Luna::WaitForMsgLoop( void );
#else // __TOOL_MODE__
	friend Bool Luna::WaitForMsgLoop( Bool IsFullActive );
#endif // __TOOL_MODE__
	friend class LunaPad;

protected:
	static IDirectInput8			*m_pDirectInput;				///< DirectInput�I�u�W�F�N�g
	static IDirectInputDevice8		*m_pDevKeyboard;				///< �L�[�{�[�h�f�o�C�X
	static Uint32					m_JoystickMax;					///< �W���C�X�e�B�b�N�ő吔
	static Uint32					m_JoystickCount;				///< �W���C�X�e�B�b�N��
	static KEYBOARDDATA				m_KeyboardData;					///< �L�[�{�[�h�f�[�^
	static MOUSEDATA				m_MouseData;					///< �}�E�X�f�[�^
	static JOYSTICKWORK				*m_pJoystickData;				///< �W���C�X�e�B�b�N�f�[�^�|�C���^
	static DIDEVICEOBJECTDATA		m_KeyBuffer[KEY_BUFFER_MAX];	///< �L�[�o�b�t�@
	static Uint32					m_KeyBufferCount;				///< �L�[�o�b�t�@�J�E���g
	static Uint32					m_KeyBufferMax;					///< �L�[�o�b�t�@�ő吔
	static Bool						m_DoubleClickL;					///< ���_�u���N���b�N�t���O
	static Bool						m_DoubleClickR;					///< �E�_�u���N���b�N�t���O
	static Bool						m_DoubleClickW;					///< �z�C�[���_�u���N���b�N�t���O

protected:
	static BOOL CALLBACK EnumAxisCallback( const DIDEVICEOBJECTINSTANCE* pdidoi, void *pContext );		///< ���񋓗p�R�[���o�b�N�֐�
	static BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, void* pContext );	///< �p�b�h�񋓗p�R�[���o�b�N�֐�
	static Bool InitKeyboard( void );								///< �L�[�{�[�h������
	static Bool InitJoystick( void );								///< �W���C�X�e�B�b�N������

	static Sint32 AdjustAxis( Sint32 axisSource, Sint32 axisCenter, Sint32 axisMax, Sint32 axisRange, Float deadZone );	///< ���̃A�W���X�g

	static void RefreshMouse( void );								///< �}�E�X���X�V
	static void RefreshKeyboard( void );							///< �L�[�{�[�h���X�V
	static void RefreshKeyboardBuffer( void );						///< �L�[�{�[�h�o�b�t�@�X�V
	static void RefreshJoystick( void );							///< �W���C�X�e�B�b�N�X�V

	static void Refresh( void );									///< �f�o�C�X���X�V

public:
	static Bool Initialize( void );									///< �N���X������
	static void Finalize( void );									///< �N���X���

	static void SetCursorPos( POINT Pt );							///< �}�E�X�ʒu��ݒ�

	static void SetMouseWheel( Sint16 w );							///< �z�C�[���ړ��l�ݒ�
	static void SetDoubleClickL( void );							///< ���_�u���N���b�N�ݒ�
	static void SetDoubleClickR( void );							///< �E�_�u���N���b�N�ݒ�
	static void SetDoubleClickM( void );							///< �z�C�[���_�u���N���b�N�ݒ�

	static void KeyBufferFlush( void );								///< �L�[�o�b�t�@�t���b�V��
	static Bool KeyBufferLoop( Uint32 *pKey );						///< �L�[�o�b�t�@�擾���[�v
	static Bool GetKeyData( Uint32 Key );							///< �L�[�f�[�^�擾
	static void GetMouseData( MOUSEDATA *pMouse );					///< �}�E�X�f�[�^�擾
	static Bool GetJoystickData( Sint32 No, JOYSTICKDATA *pJoy );	///< �W���C�X�e�B�b�N�f�[�^�擾
};


/**
	@brief	�p�b�h�ȈՑ���N���X

	LunaInput�����e�ՂɈ�����悤�ɂ���
	���b�p�[�N���X�ł��B
	�e������{�^����LunaInput�̃L�[��{�^����
	�}�b�s���O���邱�ƂŁA�L�[�R���t�B�O�Ȃǂ�
	���₷���A�e�{�^���̏ڍׂȃf�[�^���擾�o��
	��悤�ɂȂ��Ă��܂��B
*/
class LunaPad
{
#ifdef __TOOL_MODE__
	friend void Luna::WaitForMsgLoop( void );
#else // __TOOL_MODE__
	friend Bool Luna::WaitForMsgLoop( Bool IsFullActive );
#endif // __TOOL_MODE__
	friend class LunaInput;

protected:
	static Bool						m_IsUseAlias;					///< �p�b�h�ʖ���`�t���O
	static Sint32					m_UseMapPadMax;					///< �g�p�\��ő�p�b�h��
	static Sint32					m_KeyRepeatTime;				///< �L�[���s�[�g����
	static Sint32					m_KeyRepeatInterval;			///< �L�[���s�[�g�Ԋu

protected:
	static void Refresh( void );																				///< �p�b�h��Ԃ̍X�V

public:
	static void Initialize( Sint32 PadMax, Bool IsUseAlias, Sint32 KeyRepeatTime, Sint32 KeyRepeatInterval );	///< �p�b�h�V�X�e���̏�����
	static void SetButton( Sint32 PadNo, ePadSort PadSort, Sint32 Button );										///< �{�^����`�ݒ�
	static void SetAlias( Sint32 PadNo, ePadSort PadSort, Sint32 KeyNo );										///< �{�^���L�[�{�[�h����U��ݒ�

	static void UsePOVDirection( Sint32 PadMax, Bool IsUse );													///< POV �����L�[�g�p�ېݒ�
	static Bool IsUsePOVDirection( Sint32 PadMax );																///< POV �����L�[���g�p���邩�ۂ�

	static Bool IsPushAnyKey( Sint32 PadNo );																	///< �{�^�����b�N
	static Bool GetState( Sint32 PadNo, ePadState PadState, ePadSort PadSort );									///< �{�^����Ԏ擾
	static void SetState( Sint32 PadNo, ePadState PadState, ePadSort PadSort );									///< �{�^����Ԑݒ�
	static void SetLock( Sint32 PadNo, ePadSort PadSort );														///< �{�^�����b�N
	static void SetUnlock( Sint32 PadNo, ePadSort PadSort );													///< �{�^�����b�N

	static ePadSort CursorWrapUpDown( Sint32 PadNo, Sint32 *pCursor, Sint32 Max );								///< ���b�v���㉺�J�[�\������
	static ePadSort CursorWrapLeftRight( Sint32 PadNo, Sint32 *pCursor, Sint32 Max );							///< ���b�v�����E�J�[�\������
	static ePadSort CursorClampUpDown( Sint32 PadNo, Sint32 *pCursor, Sint32 Max );								///< �N�����v���㉺�J�[�\������
	static ePadSort CursorClampLeftRight( Sint32 PadNo, Sint32 *pCursor, Sint32 Max );							///< �N�����v�����E�J�[�\������
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// ENUM
//=============================================================================
/**
	@brief	���C�g�^�C�v��`

	���C�g�̎�ޒ�`�B
*/
enum eLightType
{
	LIGHT_DIRECTION,					///< ���s�������C�g
	LIGHT_POINT,						///< �_�������C�g
};


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	���C�g�N���X

	�R�c��ԏ�ɐݒu���郉�C�g�𑀍삷�邽�߂̃N���X�ł��B
	Luna�ł͎d�l��ő�S�̃f�B���N�V���i�����C�g��
	�|�C���g���C�g���T�|�[�g���Ă��܂��B
	�܂������̃��C�g�͒��_�V�F�[�_�[2.0����T�|�[�g���ꂽ
	���򖽗߂ɂ��؂�ւ��̃R�X�g�͔������܂���B
*/
class LunaLight
{
	friend class Luna3D;

protected:
	static D3DLIGHT9 m_Lights[LIGHT_MAX];			///< ���C�g�f�[�^
	static Bool m_IsActiveLights[LIGHT_MAX];		///< ���C�g�g�p�t���O
	static D3DCOLORVALUE m_Ambient;					///< �A���r�G���g

protected:
	static void SetDevice( Sint32 No, Bool IsActive );				///< �f�o�C�X�ɐݒ�

public:
	static Bool Initialize( void );									///< �N���X������
	static void Finalize( void );									///< �N���X���

	static void SetAmbient( Float r, Float g, Float b );			///< �����ݒ�

	static void SetLightType( Sint32 No, eLightType Type );			///< ���C�g�^�C�v�ݒ�
	static void SetPosition( Sint32 No, CVector3D *pPos );			///< ���C�g�ʒu�ݒ�
	static void SetDirection( Sint32 No, CVector3D *pDir );			///< ���C�g�����ݒ�
	static void SetDiffuse( Sint32 No, Float r, Float g, Float b );	///< ���C�g�f�B�t���[�Y�ݒ�
	static void SetSpecular( Sint32 No, Float r, Float g, Float b );	///< ���C�g�X�y�L�����ݒ�
	static void SetAttenuation( Sint32 No, Float Attenuation );		///< ���C�g�������ݒ�

	static void GetLightDataForShader( SHADERLIGHTDATA *pData );	///< �V�F�[�_�[�p���C�g�f�[�^�擾
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	���C���`��N���X

	�Q�c��ɒP���ȃ��C����`�悷�邽�߂̃N���X�ł��B
	�@�\�I�ɂ͂������������������̒P���Ȃ��̂�
	���̃N���X�ɑ΂��郉�b�p�[�͂܂�����܂���B
*/
class LunaLine
{
	friend class Luna3D;

protected:
	static LibLuna::CLine2DMgr *m_pLineMgr;

protected:
	static void SetScissoring( Bool IsUse, RECT *pRect );								///< �V�U�����O�̈�ݒ�
	static void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );	///< �p�[�X�⊮�f�[�^�ݒ�
	static void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );		///< �g��k���ݒ�

public:
	static Bool Initialize( void )	;													///< �N���X������
	static void Finalize( void );														///< �N���X���
	static void Reset( void );															///< ���Z�b�g
	static void Restore( void );														///< ����

	static LLINE Create( Uint32 VertexMax );											///< ���C���I�u�W�F�N�g����

	static void Release( LLINE lLine );													///< ���C���I�u�W�F�N�g���

	static void Rendering( LLINE lLine );												///< �o�b�t�@�����_�����O
	static void ResetBuffer( LLINE lLine );												///< �o�b�t�@���Z�b�g
	static void UpdateBuffer( LLINE lLine );											///< �o�b�t�@�X�V

	static Bool PushRenderBuffer( LLINE lLine, CPrimitivePoint2D *pPoint, Uint32 Count );	///< �o�b�t�@�ɕ`��f�[�^�ǉ�
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�R�c���C���`��N���X

	�R�c��ԓ��Ƀ��C����`�悷�邽�߂̃N���X�ł��B
	���̃N���X�͒P���ɐ�����`�悷�邾���ł���A
	���b�p�[���܂��p�ӂ���Ă܂���B
*/
class LunaLine3D
{
	friend class Luna3D;

protected:
	static LibLuna::CLine3DMgr *m_pLineMgr;

public:
	static Bool Initialize( void );																///< �N���X������
	static void Finalize( void );																///< �N���X���
	static void Reset( void );																	///< ���Z�b�g
	static void Restore( void );																///< ����

	static LLINE3D Create( Uint32 VertexMax );													///< ���C���I�u�W�F�N�g����

	static void Release( LLINE3D lLine3D );														///< ���C���I�u�W�F�N�g���

	static void TransformInit( LLINE3D lLine3D );												///< �ϊ�������
	static void TransformUpdate( LLINE3D lLine3D );												///< �ϊ��X�V

	static void Heading( LLINE3D lLine3D, Sint32 Rot );											///< �w�b�f�B���O
	static void Pitching( LLINE3D lLine3D, Sint32 Rot );										///< �s�b�`���O
	static void Rolling( LLINE3D lLine3D, Sint32 Rot );											///< ���[�����O
	static void RotationX( LLINE3D lLine3D, Sint32 Rot );										///< �w����]
	static void RotationY( LLINE3D lLine3D, Sint32 Rot );										///< �x����]
	static void RotationZ( LLINE3D lLine3D, Sint32 Rot );										///< �y����]
	static void Translation( LLINE3D lLine3D, Float fPx, Float fPy, Float fPz );				///< �ړ�
	static void LookAt( LLINE3D lLine3D, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );		///< ����

	static void Rendering( LLINE3D lLine3D );													///< �o�b�t�@�����_�����O
	static void ResetBuffer( LLINE3D lLine3D );													///< �o�b�t�@���Z�b�g
	static void UpdateBuffer( LLINE3D lLine3D );												///< �o�b�t�@�X�V
	static Bool PushRenderBuffer( LLINE3D lLine3D, CPrimitivePoint3D *pPoint, Uint32 Count );	///< �o�b�t�@�ɕ`��f�[�^�ǉ�
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	LZSS�Ǘ��N���X

	LZSS�Ɋւ��鏈�����s�����߂̃N���X�ł��B
*/
class LunaLzss
{
protected:
	static Sint32 m_Dad[LZSS_RING_LENGTH+1];										///< ���k�𓀗p���[�N�f�[�^�|�C���^
	static Sint32 m_LSon[LZSS_RING_LENGTH+1];										///< ���k�𓀗p���[�N�f�[�^�|�C���^
	static Sint32 m_RSon[LZSS_RING_LENGTH+257];										///< ���k�𓀗p���[�N�f�[�^�|�C���^
	static Sint32 m_MatchPos;														///< �Œ���v�ʒu
	static Sint32 m_MatchLen;														///< �Œ���v��
	static Uint8 m_Text[LZSS_RING_LENGTH + LZSS_LONGEST_MATCH - 1];					///< �e�L�X�g�f�[�^�|�C���^

protected:
	static void InitTree( void );													///< �؂̏�����
	static void InsertNode( Sint32 r );												///< �m�[�h��؂ɑ}��
	static void DeleteNode( Sint32 p );												///< �m�[�h��؂���폜

public:
	static Sint32 GetOriginalSize( void *pSrc );									///< �f�R�[�h��̃I���W�i���T�C�Y�擾
	static Bool Decode( void *pSrc, void *pDst );									///< LZSS����̃f�R�[�h
	static Bool Encode( void *pSrc, void *pDst, Uint32 SrcSize, Uint32 *pDstSize );	///< LZSS�ւ̃G���R�[�h
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�Z�p�N���X

	��ʓI�Ɏg�p����ł��낤�A�Z�p������
	�܂Ƃ߂��N���X�ł��B
	�T�C���A�R�T�C���A�A�[�N�^���W�F���g�̃e�[�u������
	�g���₷�����ꂽ�����擾�ւ��Ȃǂ��p�ӂ���Ă��܂��B
*/
class LunaMath
{
protected:
	static Float m_fSinTable[SIN_TABLE_SIZE];							///< �T�C���e�[�u��
	static Uint32 m_fArcTanTable[ARCTAN_TABLE_SIZE+1];					///< �A�[�N�^���W�F���g�e�[�u��

public:
	static Float Sin( Sint32 Angle );									///< �T�C���擾
	static Float Cos( Sint32 Angle );									///< �R�T�C���擾
	static void SinCos( Sint32 Angle, Float *pfSin, Float *pfCos );		///< �T�C���E�R�T�C���擾
	static Sint32 Atan( Sint32 Dx, Sint32 Dy );							///< �A�[�N�^���W�F���g�擾
	static Sint32 Atan( Float Dx, Float Dy );							///< �A�[�N�^���W�F���g�擾

	static void RotationPoint( CLunaPoint *pPoint, Sint32 Angle );		///< �C�ӂ̃|�C���g����]������
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	���f�B�A�Đ��N���X

	DirectShow��p���ă��f�B�A���Đ����邽�߂̃N���X�ł��B
*/
class LunaMedia
{
protected:
	static MEDIADATA *m_pMedia;											///< ���f�B�A�p�I�u�W�F�N�g
	static Uint32 m_MediaMax;											///< �I�u�W�F�N�g�ő吔

protected:
	static LMEDIA GetFreeHandle( void );								///< ���g�p�n���h���擾
	static void Init( LMEDIA lMedia );									///< �I�u�W�F�N�g������
	static Bool Delete( LMEDIA lMedia );								///< �I�u�W�F�N�g�폜

public:
	static Bool Initialize( void );										///< �N���X������
	static void Finalize( void );										///< �N���X���

	static void HandleGraphEvent( void );								///< �C�x���g�n���h��

	static void AddRef( LMEDIA lMedia );								///< �Q�ƃJ�E���^�C���N�������g
	static LMEDIA SearchHandle( const char *pFileName );				///< ����t�@�C������

	static LMEDIA CreateFromAudio( const char *pFileName );				///< ���f�B�A�I�u�W�F�N�g�̐���

	static void Release( LMEDIA lMedia );								///< �I�u�W�F�N�g���

	static void Play( LMEDIA lMedia, Bool bLoop = false );				///< �Đ�
	static void Stop( LMEDIA lMedia );									///< ��~
	static void Pause( LMEDIA lMedia );									///< �ꎞ��~
	static void SetVolume( LMEDIA lMedia, Float fParam );				///< �{�����[���ύX
	static void SetPan( LMEDIA lMedia, Float fParam );					///< �p���ړ�
	static void SetSpeed( LMEDIA lMedia, Float fParam );				///< �{�����[���ύX
	static Bool IsPlay( LMEDIA lMedia );								///< �Đ��`�F�b�N
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�������Ǘ��N���X

	�������Ǘ����s�����߂̃N���X�ł��B
	���������ɂn�r����g�p����S��������
	�ꊇ�Ŋm�ۂ��A���̗̈悩��؂�����
	�g�p����\���ɂȂ��Ă��܂��B
	�������̋��E�I�[�o�[�`�F�b�N��
	����Y��Ȃǂ��`�F�b�N���A�t�@�C�����Ƃ���
	�s�ԍ����o�͂��邱�Ƃ��ł��܂��B
	�������̃R���p�N�V�����͍s���܂���̂ŁA
	�A�v���P�[�V�����ɂ���Ă͎v��ʃ�����
	�m�ۃG���[�������N�����\��������܂��B
*/
class LunaMemory
{
protected:
	static CRITICAL_SECTION m_CriticalSection;			///< �N���e�B�J���Z�N�V����
	static void *m_pDataAddr;							///< �f�[�^�A�h���X
	static void *m_pDataAddrAligned;					///< �A���C�����g��f�[�^�A�h���X
	static Uint32 m_MaxSize;							///< �ő�T�C�Y
	static Uint32 m_UseMemory;							///< �g�p���̃T�C�Y
	static Uint32 m_MaxUseMemory;						///< �ő�g�p������
	static Uint32 m_LastAllocMemorySize;				///< �Ō�Ɋm�ۂ��悤�Ƃ����������T�C�Y
	static Uint64 m_BaseGuid;							///< �I�[�`�F�b�N�p���ʎq
	static Bool m_IsDebugMode;							///< �f�o�b�O���[�h���ۂ�
	static Bool m_IsFastAlloc;							///< �������[�h���ۂ�
	static Uint32 m_ListFree;							///< ���g�p�G���A���X�g

protected:
	static void FreeListInsert( void *pAlloc );															///< ���g�p�G���A���X�g�֑}��
	static void FreeListErase( void *pAlloc );															///< ���g�p�G���A���X�g����폜
	static void Optimize( void *pData );																///< �w�胁�����̑O����œK��
	static void *SearchFreeArea( Uint32 Size );															///< ���g�p��������Ԃ�����
	static void *ComputeAddress( void *pAlloc, Uint32 Size, Uint32 RealSize );							///< ���g�p��������Ԃ���g�p�\�ȃ�������Ԃ̃A�h���X���擾

public:
	static Bool Initialize( void );																		///< �������N���X�̏�����
	static void Finalize( void );																		///< �������N���X�̉��

	static Bool SetWorkArea( Uint32 Size, Bool IsDebugMode );											///< �g�p��������Ԃ�ݒ�
	static void SetTerminateGuid( Uint64 Guid );														///< �g�p���̃�������Ԃ̏I�[���ʎq��ݒ�

	static void *Alloc( Uint32 Size, const char *pFile, Sint32 Line );									///< �������m��
	static void *AllocLog( Uint32 Size, const char *pFile, Sint32 Line );								///< ���O�o�͗p�������m��
	static void *ClearAlloc( Uint32 Size, const char *pFile, Sint32 Line );								///< �O�N���A�ς݃������m��
	static void *ClearAllocLog( Uint32 Size, const char *pFile, Sint32 Line );							///< ���O�o�͗p�O�N���A�ς݃������m��
	static void *ReAlloc( void *pOld, Uint32 Size, const char *pFile, Sint32 Line );					///< �������Ċm��
	static void *ReAllocLog( void *pOld, Uint32 Size, const char *pFile, Sint32 Line );					///< ���O�o�͗p�������Ċm��

	static void Free( void *pAddr );																	///< ���������
	static void FreeLog( void *pAddr );																	///< ���O�o�͗p���������

	static void SetAllocMode( Bool IsFastMode );														///< �������m�ۃ��[�h
	static Uint32 GetRest( void );																		///< �c�胁�����e�ʎ擾
	static Bool CheckOverAccess( void );																///< �������A�N�Z�X�G���[���`�F�b�N
	static void Optimize( void );																		///< �������̈�̍œK��

	static Uint32 GetAllocLastSize( void );																///< �Ō�Ɋm�ۂ��悤�Ƃ����������T�C�Y

	static void RenderMap( LPRIMITIVE lPrim, Sint32 Px, Sint32 Py, Sint32 Width, Sint32 Height, D3DCOLOR Col1, D3DCOLOR Col2 );	///< �������g�p�󋵂������_�����O

	static void PrintAlloc( void );																		///< �m�ۗ̈���o��
};


#ifndef __TOOL_MODE__

//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�}�C�N���X���b�h�N���X

	�ʏ�̃X���b�h���}�C�N���X���b�h����
	�������̂ł��B
	�����͕��ʂ̃X���b�h�����ȒP�ł����A
	�g�������ד��Ȃ̂Ŗ�肪���邩������܂���B
*/
class LunaMicroThread
{
protected:
	static MICROTHREADDATA	*m_pThreadData;			///< �X���b�h�p�f�[�^
	static PMICROTHREADPROC	m_pLoadProc;			///< ���[�_�[�֐�
	static unsigned int		m_ThreadId;				///< �X���b�hID
	static HANDLE			m_Handle;				///< �X���b�h�n���h��
	static Bool				m_IsSuccess;			///< ��������
	static Sint64			m_ThreadAllTimeOld;		///< �S�X���b�h��������
	static Float			m_ThreadAllTime;		///< �S�X���b�h��������
	static void				*m_pThreadProcTbl[32];	///< �X���b�h�p�֐�

protected:
	static void UpdateThreadList( void );								///< �}�C�N���X���b�h���X�g�X�V
	static void Terminate( Uint32 ThreadId );							///< �}�C�N���}�C�N���X���b�h�I��

	static unsigned int __stdcall ThreadProc00( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc01( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc02( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc03( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc04( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc05( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc06( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc07( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc08( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc09( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc10( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc11( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc12( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc13( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc14( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc15( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc16( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc17( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc18( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc19( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc20( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc21( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc22( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc23( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc24( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc25( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc26( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc27( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc28( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc29( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc30( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProc31( void *pParam );			///< �X���b�h�Ǘ��p�֐�
	static unsigned int __stdcall ThreadProcLoader( void *pParam );		///< �X���b�h�p�֐�

public:
	static Bool Initialize( void );																					///< �}�C�N���X���b�h�N���X������
	static void Finalize( void );																					///< �}�C�N���X���b�h�N���X�I��

	static void Start( void );																						///< �}�C�N���}�C�N���X���b�h�n��
	static void End( void );																						///< �}�C�N���}�C�N���X���b�h�I��
	static Bool StartLoadThread( PMICROTHREADPROC pLoadProc, void *pParam, Uint32 StackSize, Uint32 Priority = THREAD_PRIORITY_LOWEST );	///< �f�[�^�ǂݍ��ݗp�}�C�N���}�C�N���X���b�h
	static Bool IsEndLoadThread( void );																			///< �f�[�^�ǂݍ��݃}�C�N���}�C�N���X���b�h�I���`�F�b�N
	static Bool IsSuccessLoadThread( void );																		///< �f�[�^�ǂݍ��݃}�C�N���}�C�N���X���b�h�����`�F�b�N
	static void Exit( Uint32 ThreadId );																			///< �}�C�N���}�C�N���X���b�h�I��
	static Bool Create( Uint32 ThreadId, PMICROTHREADPROC pProcMain, PMICROTHREADPROC pProcTerminate, void *pParam, Uint32 StackSize );	///< �}�C�N���}�C�N���X���b�h����
	static void Switch( Uint32 ThreadId );																			///< �}�C�N���}�C�N���X���b�h�؂�ւ�

	static Float GetRateCPU( Uint32 ThreadId = THREAD_SYSTEM );														///< �}�C�N���}�C�N���X���b�h�������Ԏ擾
};

#endif



//======================================================================
// INCLUDE
//======================================================================


//=============================================================================
// STRUCT
//=============================================================================
/**
	@brief	�g���t���[���N���X

	LunaModel�N���X�p�̃T�|�[�g�N���X�ł��B
	�w�t�@�C���ǂݍ��ݎ��̃t���[�����`���Ă��܂��B
	���[�U�[�����̃N���X�𒼐ڎQ�Ƃ��邱�Ƃ͂���܂���B
*/
struct LUNAFRAME : public D3DXFRAME
{
    D3DXMATRIX CombinedTransformationMatrix;
};


/**
	@brief	�g�����b�V���R���e�i�N���X

	LunaModel�N���X�p�̃T�|�[�g�N���X�ł��B
	�w�t�@�C���ǂݍ��ݎ��̃��b�V�����`���Ă��܂��B
	���[�U�[�����̃N���X�𒼐ڎQ�Ƃ��邱�Ƃ͂���܂���B
*/
struct LUNAMESH : public D3DXMESHCONTAINER
{
	// �X�L�����b�V�����
	ID3DXMesh			*pMeshOriginal;

	D3DXATTRIBUTERANGE	*pAttributeTable;
	Uint32				NumAttributeGroups;

	D3DXMATRIX			**ppBoneMatrixPtr;
	D3DXMATRIX			*pBoneMatrix;
	D3DXMATRIX			*pBoneOffsetMatrix;
	Uint32				BoneMatrixMax;

	// �A�v���P�[�V�������
	LTEXTURE			*plTexture;
	Float				fObjectRadius;
	CVector3D			vObjectCenter;
	CVector3D			vBBMin;
	CVector3D			vBBMax;

	BOX3D				Box;

	Uint32				VertexCount;
	Uint32				PolygonCount;

	D3DXMATRIX			mTransform;
};


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	���f���A���P�[�V�����N���X

	LunaModel�łw�t�@�C����ǂݍ��ގ��Ɏg����A
	���[�_�[�N���X�ł��B
	�����I�ɂ��̃N���X�̊e���\�b�h���Ă΂��`�ŁA
	�t�@�C���̓ǂݍ��݂��s���悤�ɂȂ��Ă��܂��B
	���[�U�[�����̃N���X�𒼐ڎQ�Ƃ��邱�Ƃ͂���܂���B
*/
class CModelAlloc : public ID3DXAllocateHierarchy
{
	Uint32 m_FrameCount;																		///< �t���[����
	Uint32 m_MeshCount;																			///< ���b�V����
	eSurfaceFormat m_Format;
	D3DCOLOR m_KeyColor;
	Bool m_IsMipmap;

public:
	CModelAlloc() {};																			///< �R���X�g���N�^
	CModelAlloc( eSurfaceFormat Format, D3DCOLOR KeyColor );						///< �R���X�g���N�^
	virtual ~CModelAlloc() {}																	///< �f�X�g���N�^

	Uint32 GetMeshCount( void );																///< ���b�V�����擾
	Uint32 GetFrameCount( void );																///< �t���[�����擾

	Bool CopyName( char **ppDstName, const char *pSrcName );									///< ���O�R�s�[

    virtual HRESULT __stdcall DestroyFrame( D3DXFRAME *pFrameToFree );							///< �t���[���f�[�^���
    virtual HRESULT __stdcall DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerBase );	///< ���b�V���f�[�^���
    virtual HRESULT __stdcall CreateFrame( LPCTSTR pName, D3DXFRAME **ppNewFrame );				///< �t���[���f�[�^����
    virtual HRESULT __stdcall CreateMeshContainer(												///< ���b�V���f�[�^����
										LPCSTR pName,
										CONST D3DXMESHDATA *pMeshData,
										CONST D3DXMATERIAL *pMaterials,
										CONST ::D3DXEFFECTINSTANCE *pEffectInstances,
										unsigned long NumMaterials,
										CONST unsigned long *pAdjacency,
										LPD3DXSKININFO pSkinInfo,
										LPD3DXMESHCONTAINER *ppNewMeshContainer );
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	���f���N���X

	DirectX�p�̃��f���t�@�C���ł���w�t�@�C����
	�������邽�߂̃N���X�ł��B
	�e��L�[�t���[���A�j���[�V��������X�L�����b�V����
	�����܂ł��T�|�[�g���܂����A��{�I�ɏ�����
	�S�ă\�t�g�E�F�A�ōs���A�Â������o�Ȃǂɂ͌����܂��񂪁A
	DirectX�̌Œ�V�F�[�_�[�@�\�ŏ�������邽�߁A������
	�m���ȓ��삪���҂ł��܂��B
*/
class LunaModel
{
protected:
	static CMatrix m_mBase;
	static MODELDATA *m_pModel;								///< ���f���f�[�^�|�C���^
	static Uint32 m_ModelMax;								///< ���f���f�[�^�ő吔

protected:
	static void Init( LMODEL lModel );						///< ���f���I�u�W�F�N�g������
	static Bool Delete( LMODEL lModel );					///< ���f���I�u�W�F�N�g�폜
	static LMODEL GetFreeHandle( void );					///< ���g�p�n���h���擾
	static void RenderingMesh( D3DXMESHCONTAINER *pMeshContainerBase, D3DXFRAME *pFrameBase );				///< ���b�V�������_�����O
	static void RenderingFrame( D3DXFRAME *pFrame );														///< �t���[�������_�����O
	static void FrameUpdate( D3DXFRAME *pFrameBase, D3DXMATRIX *pParentMatrix, D3DXMATRIX *pRootMatrix );	///< �t���[���X�V
	static Bool SetupBoneMatrixPointers( LMODEL lModel, D3DXFRAME *pFrame );								///< �{�[���s��|�C���^�[�ݒ�
	static Bool SetupBoneMatrixPointersOnMesh( LMODEL lModel, D3DXMESHCONTAINER *pMeshContainerBase );		///< ���b�V���̃{�[���s��|�C���^�[�ݒ�

	static LMODEL LoadFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor );			///< ����������w�t�@�C����ǂݍ���
	static Bool MeshDataConvert( LUNAMESH *pMeshContainer, Float fScale );									///< ���b�V���f�[�^�R���o�[�g

	static Sint32 CreateMeshList( D3DXFRAME *pFrame, D3DXMESHCONTAINER **ppList, Sint32 Count );			/// ���b�V�����X�g����

public:
	static Bool Initialize( void );																			///< �N���X������
	static void Finalize( void );																			///< �N���X���
	static void Reset( void );																				///< �f�o�C�X�f�[�^���Z�b�g
	static void Restore( void );																			///< �f�o�C�X�f�[�^���X�g�A
	static void SetMax( Uint32 Max );																		///< �I�u�W�F�N�g�ő吔�ݒ�
	static void Release( LMODEL lModel );																	///< �I�u�W�F�N�g���

	static LMODEL CreateFromFile( const char *pFileName, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );		///< �t�@�C�����琶��
	static LMODEL CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );	///< ���������琶��

	static LMODEL CreateCube( Float fSizeX, Float fSizeY, Float fSizeZ, D3DCOLORVALUE Color );				///< �L���[�u�쐬
	static LMODEL CreateSphere( Float fRadius, Sint32 Slices, Sint32 Stacks, D3DCOLORVALUE Color );			///< �X�t�B�A����
	static LMODEL CreatePolygon( Float fLength, Sint32 Sides, D3DCOLORVALUE Color );						///< �|���S���쐬
	static LMODEL CreateText( const char *pFontFace, const char *pText, Float fDeviation, Float fExtrusion, Float fScale, D3DCOLORVALUE Color );	///< �e�L�X�g����

	static void TransformInit( LMODEL lModel );																///< �ϊ�������
	static void TransformUpdate( LMODEL lModel, Float fTime = 0.0f );										///< �ϊ��X�V

	static void Scale( LMODEL lModel, Float fSx, Float fSy, Float fSz );									///< �X�P�[�����O
	static void Heading( LMODEL lModel, Sint32 Rot );														///< �w�b�f�B���O
	static void Pitching( LMODEL lModel, Sint32 Rot );														///< �s�b�`���O
	static void Rolling( LMODEL lModel, Sint32 Rot );														///< ���[�����O
	static void RotationX( LMODEL lModel, Sint32 Rot );														///< �w����]
	static void RotationY( LMODEL lModel, Sint32 Rot );														///< �x����]
	static void RotationZ( LMODEL lModel, Sint32 Rot );														///< �y����]
	static void RotationQuaternion( LMODEL lModel, CQuaternion *pQuat );									///< �N�H�[�^�j�I���ŉ�]
	static void Translation( LMODEL lModel, Float fPx, Float fPy, Float fPz );								///< �ړ�
	static void LookAt( LMODEL lModel, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );						///< �C�ӓ_����C�ӓ_�ւ̒���
	static Bool SetStyleToModel( LMODEL lModel, CStyle *pStyle );											///< �p���f�[�^�����f���ɐݒ�
	static Bool GetStyleFromModel( LMODEL lModel, CStyle *pStyle );											///< �p���f�[�^�����f������擾

	static void Rendering( LMODEL lModel );																	///< �����_�����O

	static void SetTexture( LMODEL lModel, Uint32 Stage, LTEXTURE lTex, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );	///< ���f���փe�N�X�`���ݒ�
	static void SetMaterialAlpha( LMODEL lModel, Uint8 Alpha, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );				///< ���f���̃}�e���A���A���t�@��ݒ�

	static Bool SphereBoundProbe( LMODEL lModel, CVector3D *pRayPosition, CVector3D *pRayDirection );			///< �����Ƃ̓��蔻��
	static Bool CheckSphereBound( LMODEL lModel1, LMODEL lModel2 );											///< ���P�ʂ̓��蔻��
	static void GetModelSphere( LMODEL lModel, CVector3D *pvCenter, Float *pRadius );						///< �o�E���f�B���O�X�t�B�A���擾

	static Uint32 GetTrackCount( LMODEL lModel );															///< �g���b�N�����擾
	static Bool SetTrackEnable( LMODEL lModel, Sint32 Track, Bool IsEnable );								///< �g���b�N�̎g�p�̗L����ݒ�
	static Bool SetTrackSpeed( LMODEL lModel, Sint32 Track, Float fSpeed );									///< �g���b�N�̑��x�ݒ�
	static Bool SetTrackWeight( LMODEL lModel, Sint32 Track, Float fWeight );								///< �g���b�N�̏d�ݐݒ�
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�ėp���f���N���X

	DirectX�p�̃��f���t�@�C���ł���w�t�@�C����
	�������߂̃N���X�ł��B
	LunaModel�N���X�ŃT�|�[�g���Ă���@�\��
	��ʂ肻�낦����ŁA���[�t�B���O��e�N�X�`������
	�Ȃǂ𒸓_�V�F�[�_�[2.0�ōs�����߁A�_��ȏ�����
	�\�ɂȂ��Ă��܂��B
	LunaModel�N���X�ɔ�ׂ�Ɠ������������G�ɂȂ��Ă��܂�
	�̂ŁA�ǂݍ��ݎ��ԂȂǂ͏��X������܂����A
	���[�U�[����莩�R�ȕ`�揈����I�����邱�Ƃ�
	�\�ł��B
*/
class LunaModelEx
{
protected:
	static LibLuna::CModelMgr *m_pModelMgr;

public:
	static Bool Initialize( void );																							///< ���f���V�X�e��������
	static void Finalize( void );																							///< ���f���V�X�e�����
	static void Reset( void );																								///< ���f���f�[�^���Z�b�g
	static void Restore( void );																							///< ���f���f�[�^���X�g�A
	static void Release( LMODELEX lModelEx );																				///< ���f���f�[�^���

	static LMODELEX CreateFromMemory( void *pData, Uint32 Size, Uint16 ShaderVersionMajor = 2, Uint16 ShaderVersionMinor = 0, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );	///< ����������f�[�^��ǂݍ���
	static LMODELEX CreateFromFile( const char *pFileName, Uint16 ShaderVersionMajor = 2, Uint16 ShaderVersionMinor = 0, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );			///< �t�@�C�����烂�f���f�[�^�𐶐�

	static void LoadEffectFromFile( LMODELEX lModelEx, const char *pShaderName, Uint32 SendFlag, Sint32 MeshNo );			///< �G�t�F�N�g��ݒ�
	static void SetEffectHandle( LMODELEX lModelEx, LSHADERFX lShaderFx, Uint32 SendFlag, Sint32 MeshNo );					///< �G�t�F�N�g��ݒ�
	static void AutoCreateShader( LMODELEX lModelEx, LibLuna::eAutoCreateShaderType Type, Sint32 MeshNo = -1 );						///< �����V�F�[�_�[����

	static void TransformInit( LMODELEX lModelEx );																			///< �ϊ�������
	static void TransformUpdate( LMODELEX lModelEx, Float fAnimeTime = 0.0f, Bool IsAnime = false, eAnimationType Type = ANIM_TYPE_LINEAR );						///< �ϊ��X�V
	static void TransformFromMatrix( LMODELEX lModelEx, CMatrix *pMatrix, Float fAnimeTime = 0.0f, Bool IsAnime = false, eAnimationType Type = ANIM_TYPE_LINEAR );	///< �ϊ��X�V
	static void TransformUpdateBlend( LMODELEX lModelEx, Float fAnimeTimeA, Float fAnimeTimeB, eAnimationType Type = ANIM_TYPE_LINEAR );
	static void TransformFromMatrixBlend( LMODELEX lModelEx, CMatrix *pMatrix, Float fAnimeTimeA, Float fAnimeTimeB, eAnimationType Type = ANIM_TYPE_LINEAR );

	static void SetAnimationTrackEnable( LMODELEX lModelEx, Sint32 Track );													///< �A�j���[�V�����g���b�N�ݒ�
	static void SetAnimationTrackBlend( LMODELEX lModelEx, Sint32 TrackA, Sint32 TrackB, Float fWeight, Sint32 FrameNo );	///< �A�j���[�V�����g���b�N�̃u�����h�ݒ�
	static Sint32 GetAnimationTrackMax( LMODELEX lModelEx );																///< �A�j���[�V�����g���b�N�����擾
	static Sint32 GetAnimationTrackNo( LMODELEX lModelEx, const char *pName );												///< �A�j���[�V�����g���b�N�ԍ��𖼑O����擾
	static Sint32 GetAnimationFrameMax( LMODELEX lModelEx, Sint32 Track );													///< �A�j���[�V�����g���b�N�̍ő�t���[�����擾

	static void Scaling( LMODELEX lModelEx, Float fSx, Float fSy, Float fSz );												///< �X�P�[�����O
	static void Heading( LMODELEX lModelEx, Sint32 Rot );																	///< �w�b�f�B���O
	static void Pitching( LMODELEX lModelEx, Sint32 Rot );																	///< �s�b�`���O
	static void Rolling( LMODELEX lModelEx, Sint32 Rot );																	///< ���[�����O
	static void RotationX( LMODELEX lModelEx, Sint32 Rot );																	///< �w����]
	static void RotationY( LMODELEX lModelEx, Sint32 Rot );																	///< �x����]
	static void RotationZ( LMODELEX lModelEx, Sint32 Rot );																	///< �y����]
	static void RotationQuaternion( LMODELEX lModelEx, CQuaternion *pQuat );												///< �N�H�[�^�j�I���ŉ�]
	static void Translation( LMODELEX lModelEx, Float fPx, Float fPy, Float fPz );											///< �ړ�
	static void LookAt( LMODELEX lModelEx, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );								///< �C�Ӎ��W�𒍎�

	static void GetBoundingBox( LMODELEX lModelEx, Uint32 MeshNo, BOX3D *pBox );											///< �o�E���f�B���O�{�b�N�X�f�[�^�擾

	static void RenderingBox( LMODELEX lModelEx, D3DCOLOR Color );															///< ���f�������_�����O
	static Sint32 Rendering( LMODELEX lModelEx = INVALID_MODELEX );															///< ���f�������_�����O
	static Float RenderingTimer( LMODELEX lModelEx = INVALID_MODELEX );														///< ���f�������_�����O

	static Sint32 GetMeshNoFromName( LMODELEX lModelEx, const char *pMeshName );											///< �Y�����閼�O�̃��b�V���̔ԍ����擾
	static Sint32 GetFrameNoFromName( LMODELEX lModelEx, const char *pFrameName );											///< �Y�����閼�O�̃t���[���̔ԍ����擾
	static void GetTransformMatrixFromMesh( LMODELEX lModelEx, CMatrix *pMatrix, Sint32 MeshNo );							///< ���b�V������ϊ��s����擾
	static void GetTransformMatrixFromFrame( LMODELEX lModelEx, CMatrix *pMatrix, Sint32 FrameNo );							///< �t���[���֕ϊ��s���ݒ�
	static void SetTransformMatrixToMesh( LMODELEX lModelEx, CMatrix *pMatrix, Sint32 MeshNo );								///< �t���[������ϊ��s����擾
	static void SetStyleToModel( LMODELEX lModelEx, CStyle *pStyle );														///< �p���f�[�^�����f���ɐݒ�
	static void GetStyleFromModel( LMODELEX lModelEx, CStyle *pStyle );														///< �p���f�[�^�����f������擾

	static Bool GetScreenPosition( LMODELEX lModelEx, CVector3D *pPos, Sint32 MeshNo );										///< �X�N���[�����W���擾

	static void SetVertexExtrusion( LMODELEX lModelEx, Float fOffset, Sint32 MeshNo = -1 );									///< ���_�����o���ʐݒ�
	static void SetMorphWeight( LMODELEX lModelEx, Float fOffset, Sint32 MeshNo = -1 );										///< ���[�t�B���O�����p�E�F�C�g�l�ݒ�
	static void SetSlideTextureU( LMODELEX lModelEx, Float fOffset, Sint32 MeshNo = -1 );									///< �e�N�X�`���t�u�̂t�̃X���C�h�l�ݒ�
	static void SetSlideTextureV( LMODELEX lModelEx, Float fOffset, Sint32 MeshNo = -1 );									///< �e�N�X�`���t�u�̂u�̃X���C�h�l�ݒ�
	static void SetTexture( LMODELEX lModelEx, Uint32 Stage, LTEXTURE lTex, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );	///< ���f���փe�N�X�`���ݒ�
	static void SetMaterialAlpha( LMODELEX lModelEx, Uint8 Alpha, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );				///< ���f���̃}�e���A���A���t�@��ݒ�
	static Bool SetMorphTarget( LMODELEX lDst, Sint32 DstNo, LMODELEX lSrc, Sint32 SrcNo );									///< ���[�t�B���O�p�^�[�Q�b�g���b�V���ݒ�
	static Sint32 GetMeshCount( LMODELEX lModelEx );																		///< ���b�V�����擾
	static Sint32 GetFrameCount( LMODELEX lModelEx );																		///< �t���[�����擾
	static Bool IsBoneMesh( LMODELEX lModelEx, Sint32 MeshNo );																///< ���b�V�����{�[�����胁�b�V�������擾���܂�
	static void SetRenderFlag( LMODELEX lModelEx, Uint8 Flag, Uint8 Mask = 0xff, Sint32 MeshNo = -1 );						///< �����_�����O�t���O�̐ݒ�
	static Uint8 GetRenderFlag( LMODELEX lModelEx, Sint32 MeshNo );															///< �����_�����O�t���O�̎擾

	// �X�e�[�g����
	static void SetMateriaStateEnable( LMODELEX lModelEx, Bool IsEnable, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );											///< �X�e�[�g�����t���O
	static void SetTextureState( LMODELEX lModelEx, Uint32 Stage, D3DTEXTURESTAGESTATETYPE State, Uint32 Param, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );	///< �e�N�X�`���X�e�[�g�ݒ�
	static void SetSamplerState( LMODELEX lModelEx, Uint32 Stage, D3DSAMPLERSTATETYPE State, Uint32 Param, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );		///< �T���v�����O�X�e�[�g�ݒ�
	static void SetBlendingType( LMODELEX lModelEx, eBlendType BlendType, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );											///< �u�����f�B���O�^�C�v�ݒ�
	static void SetFilterEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< �o�C���j�A�t�B���^�L���ݒ�
	static void SetColorkeyEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< �J���[�L�[�L���ݒ�
	static void SetZBufferEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< �[�x�o�b�t�@�L���ݒ�
	static void SetZWriteEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< Z�������ݗL���ݒ�
	static void SetWireFrameEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< ���C���t���[�������_�����O�L���ݒ�

	// �����蔻��
	static Bool CheckCollision( LibLuna::eCollisionType CollisionType, LMODELEX lModel1, Sint32 MeshNo1, LMODELEX lModel2, Sint32 MeshNo2, Float fScale = 1.0f );	///< �����蔻��`�F�b�N
	static Bool CollisionRay( LMODELEX lModelEx, Sint32 MeshNo, CVector3D *pvStart, CVector3D *pvEnd, Bool IsBackFace = false, Bool IsNormal = false );		///< �����Ƃ̌����`�F�b�N
	static Bool CollisionScreen( LMODELEX lModelEx, Sint32 MeshNo, CVector3D *pScreenPos, Bool IsBackFace = false, Bool IsNormal = false );					///< ��ʂƂ̌����`�F�b�N
	static Bool CollisionScreenFast( LMODELEX lModelEx, Sint32 MeshNo, CVector3D *pScreenPos );																///< ��ʂƂ̌����`�F�b�N
	static Bool GetCollisionInfo( LMODELEX lModelEx, Sint32 MeshNo, Sint32 PointNo, CVector3D *pPositionLocal, CVector3D *pPositionWorld, CVector3D *pNormalLocal, CVector3D *pNormalWorld );	///< �����蔻�茋�ʃ|���S���̏Փˏ��擾
	static Uint32 GetCollisionInfoCount( LMODELEX lModelEx, Sint32 MeshNo );												///< �Փ˃|�C���g���擾
	static void GetBoundingBox( LMODELEX lModelEx, Sint32 MeshNo, CVector3D *pMin, CVector3D *pMax );							///< �o�E���f�B���O�{�b�N�X�擾
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�~���[�W�b�N�N���X

	DirectMusic��e�ՂɈ�����悤�ɂ������b�p�[�ł��B
	Midi�̍Đ����T�|�[�g���A
	�p���̈ړ���{�����[���̕ύX�Ȃǂ��s�����Ƃ��o���܂��B
*/
class LunaMusic
{
protected:
	static IDirectSound *m_pDirectSound;					///< DirectSound�I�u�W�F�N�g
	static IDirectMusic *m_pDirectMusic;					///< DirectMusic�I�u�W�F�N�g
	static IDirectMusicLoader8 *m_pMusicLoader;				///< �~���[�W�b�N���[�_�[�I�u�W�g�N�g
	static MUSICDATA *m_pMusic;								///< �~���[�W�b�N�f�[�^�|�C���^
	static Uint32 m_MusicMax;								///< �~���[�W�b�N�f�[�^�ő吔

protected:
	static Bool Delete( LMUSIC lMusic );									///< �~���[�W�b�N�f�[�^�폜
	static void Init( LMUSIC lMusic );										///< �~���[�W�b�N�f�[�^������
	static LMUSIC GetFreeHandle( void );									///< ���g�p�~���[�W�b�N�f�[�^�擾

	static LMUSIC LoadFromMemoryMidi( void *pData, Uint32 Size, Uint32 DefaultPathType );	///< ���������̂l�h�c�h�f�[�^����I�u�W�F�N�g�𐶐�

public:
	static Bool Initialize( void );											///< �~���[�W�b�N�N���X������
	static void Finalize( void );											///< �~���[�W�b�N�N���X���

	static void SetMax( Uint32 Max );										///< �g�p�ő�~���[�W�b�N�N���X�ݒ�

	static LMUSIC SearchHandle( const char *pFileName );					///< ���ꖼ�̂̃~���[�W�b�N�n���h�����擾

	static LMUSIC CreateFromMidi( const char *pFileName, Uint32 DefaultPathType = DMUS_APATH_SHARED_STEREOPLUSREVERB );	///< �l�h�c�h����~���[�W�b�N�f�[�^���쐬���n���h�����擾

	static LMUSIC CreateFromMemoryMidi( void *pData, Uint32 Size, Uint32 DefaultPathType = DMUS_APATH_SHARED_STEREOPLUSREVERB );	///< ���������̂l�h�c�h�f�[�^����I�u�W�F�N�g�𐶐�

	static void AddRef( LMUSIC lMusic );									///< �Q�ƃJ�E���g���Z
	static void Release( LMUSIC lMusic );									///< �~���[�W�b�N���

	static void Play( LMUSIC lMusic, Uint32 LoopCount = 0 );				///< �Đ�
	static void Loop( LMUSIC lMusic );										///< ���[�v�Đ�
	static void Pause( LMUSIC lMusic );										///< �ꎞ��~
	static void Stop( LMUSIC lMusic );										///< ��~
	static void SetVolume( LMUSIC lMusic, Float fParam );					///< �{�����[���ݒ�
	static void SetPan( LMUSIC lMusic, Float fParam );						///< �p���ړ�
	static Bool IsPlay( LMUSIC lMusic, MUSIC_TIME* pOffset = NULL, Uint32* pRepeats = NULL );		///< �Đ���ԃ`�F�b�N
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�l�b�g���[�N�N���X

	WindowsSocket���������߂̃��b�p�[�N���X�ł��B
	WinSock2.0�̋@�\���g���Ă���A�񓯊������ɂ�
	�Ή����Ă��܂��B
	DirectPlay���g�����l�b�g���[�N�����Ƃ͈Ⴂ
	�l�b�g���[�N�Ȃ̂�Linux�Ȃǂ̂ق��̃v���b�g
	�t�H�[���Ƃ̒ʐM���e�Ղɍs���܂��B
*/
class LunaNetwork
{
public:
	/**
		@brief �N���C�A���g����
	*/
	class Client
	{
	protected:
		static SOCKET			m_Socket;													///< �����̃l�b�g���[�N
		static Bool				m_IsConnect;												///< �ڑ������ۂ�
		static OVERLAPEDDATA	m_OverlapSend;												///< ���M�p�I�[�o�[���b�v
		static OVERLAPEDDATA	m_OverlapRecv;												///< ��M�p�I�[�o�[���b�v

	private:
		static void __stdcall CompleteCallbackRecv( Uint32 Error, Uint32 Recv, WSAOVERLAPPED *pOver, Uint32 Flags );	///< �����������R�[���o�b�N�֐�
		static void __stdcall CompleteCallbackSend( Uint32 Error, Uint32 Send, WSAOVERLAPPED *pOver, Uint32 Flags );	///< �����������R�[���o�b�N�֐�

	public:
		static Bool Initialize( void );														///< �N���X������
		static void Finalize( void );														///< �N���X���

		static Bool ConnectServer( const char *pServerString, Uint16 PortNo );				///< �T�[�o�[�ւ̐ڑ�
		static void Shutdown( void );														///< �V���b�g�_�E��

		static Sint32 RequestSend( const void *pData, Uint32 Size );						///< �f�[�^���M
		static Sint32 RequestRecv( void *pData, Uint32 Size );								///< �f�[�^��M

		static Bool IsRequestEndSend( void );												///< ���N�G�X�g�����҂�
		static Bool IsRequestEndRecv( void );												///< ���N�G�X�g�����҂�

		static Sint32 GetRequestResultSend( void );											///< ���N�G�X�g���ʃR�[�h�擾
		static Sint32 GetRequestResultRecv( void );											///< ���N�G�X�g���ʃR�[�h�擾
	};

	/**
		@brief �T�[�o�[����
	*/
	class Server
	{
	protected:
		static Bool					m_IsConnect;								///< �ڑ������ۂ�
		static HWND					m_hWindow;									///< ��������E�B���h�E�̃E�B���h�E�n���h��
		static Uint32				m_Message;									///< �������郁�b�Z�[�W
		static HOSTINFO				m_HostInfo;									///< �z�X�g���
		static HOSTENT				m_HostEntry;								///< �z�X�g�G���g���[
		static SOCKET				m_Socket;									///< �����̃\�P�b�g
		static Sint32				m_ClientCount;								///< �N���C�A���g��
		static CONNECTCLIENTDATA	*m_pConnectionList;							///< �ڑ����[�U�[���X�g
		static CONNECTCLIENTDATA	m_ConnectClient;							///< �ŏI�ڑ��N���C�A���g
		static CONNECTCLIENTDATA	m_CloseClient;								///< �ŏI�ؒf�N���C�A���g
		static PCALLBACKSOCKETPROC	m_pCallBackAccept;							///< ��M��t���p�R�[���o�b�N�֐��̃|�C���^
		static PCALLBACKSOCKETPROC	m_pCallBackClose;							///< �ڑ��ؒf���p�R�[���o�b�N�֐��̃|�C���^
		static PCALLBACKSOCKETPROC	m_pCallBackRead;							///< �f�[�^��M���p�R�[���o�b�N�֐��̃|�C���^
		static PCALLBACKSOCKETPROC	m_pCallBackWrite;							///< �f�[�^���M���p�R�[���o�b�N�֐��̃|�C���^

	protected:
		static void List_Insert( CONNECTCLIENTDATA *pConnet );								///< ���X�g�Ƀf�[�^��}������
		static void List_Erase( CONNECTCLIENTDATA *pConnet );								///< ���X�g����f�[�^���폜����
		static void *List_Search( Sint32 No );												///< �ԍ����烊�X�g��������
		static void *List_Search( SOCKET Socket );											///< �\�P�b�g���烊�X�g��������

	public:
		static Bool Initialize( void );														///< �N���X������
		static void Finalize( void );														///< �N���X���

		static Bool CreateServer( Uint16 PortNo );											///< �T�[�o�[����
		static void Shutdown( void );														///< �V���b�g�_�E��

		static void SetAsynCallBackAccept( PCALLBACKSOCKETPROC pCallBack );					///< �ڑ���t���R�[���o�b�N�֐��̐ݒ�
		static void SetAsynCallBackConnect( PCALLBACKSOCKETPROC pCallBack );				///< �ڑ����R�[���o�b�N�֐��̐ݒ�
		static void SetAsynCallBackClose( PCALLBACKSOCKETPROC pCallBack );					///< �ؒf���R�[���o�b�N�֐��̐ݒ�
		static void SetAsynCallBackRead( PCALLBACKSOCKETPROC pCallBack );					///< �ǂݍ��ݎ��R�[���o�b�N�֐��̐ݒ�
		static void SetAsynCallBackWrite( PCALLBACKSOCKETPROC pCallBack );					///< �������ݎ��R�[���o�b�N�֐��̐ݒ�
		static void ReceiveMessage( HWND hWnd, WPARAM wParam, LPARAM lParam );				///< ��M���b�Z�[�W����

		static Bool ASyncAccept( void );													///< �񓯊��ڑ���t
		static Sint32 ASyncSend( const void *pData, Uint32 Size, Sint32 Id );				///< �񓯊��f�[�^���M
		static Sint32 ASyncRecv( void *pData, Uint32 Size, Sint32 Id );						///< �񓯊��f�[�^��M

		static void GetConnectClientInfo( HOSTINFO *pHostInfo, char *pAddr );				///< �ڑ����̃N���C�A���g�����擾����
		static void GetCloseClientInfo( HOSTINFO *pHostInfo, char *pAddr );					///< �ؒf���ꂽ�N���C�A���g�����擾����
		static Sint32 GetClientCount( void );												///< �ڑ����̃N���C�A���g�����擾����
		static void GetClientInfo( Sint32 No, char *pName, char *pAddress );				///< �ڑ����̃N���C�A���g�����擾����

		static Bool SetSendData( SOCKETSENDDATA *pSend, Sint32 Id );						///< ���M����f�[�^��ݒ肷��
	};

	friend class LunaNetwork::Client;
	friend class LunaNetwork::Server;

protected:
	static char			m_LastError[1024];													///< �G���[�i�[�p������
	static WSADATA		m_WsaData;															///< �\�P�b�g�f�[�^
	static HOSTINFO		m_HostInfo;															///< �z�X�g���
	static HOSTENT		m_HostEntry;														///< �z�X�g�G���g���[

	static void GetMakeError( Sint32 ErrorCode, char *pErrStr );							///< �G���[������̐���

public:
	static Bool Initialize( void );															///< �N���X������
	static void Finalize( void );															///< �N���X���

	static Bool GetLastError( char *pError );												///< �Ō�ɔ��������G���[���擾
	static Bool GetHostInfo( const char *pServerString, HOSTINFO *pHost );					///< �z�X�g���̎擾
	static void GetLocalHostName( char *pName );											///< ���[�J���z�X�g�����擾
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�|�C���g�`��N���X

	�Q�c��Ƀ|�C���g��`�悷�邾���ɃN���X�ł��B
	�P���ɓ_��`�悷�邾���̂��̂ŁA���̃N���X��
	���b�p�[�͑��݂��܂���B
*/
class LunaPoint
{
	friend class Luna3D;

protected:
	static LibLuna::CPoint2DMgr *m_pPointMgr;

public:
	static Bool Initialize( void );																	///< �N���X������
	static void Finalize( void );																	///< �N���X���
	static void Reset( void );																		///< �f�o�C�X�f�[�^���Z�b�g
	static void Restore( void );																	///< �f�o�C�X�f�[�^���X�g�A

	static LPOINT Create( Uint32 VertexMax );														///< ����

	static void Release( LPOINT lPt );																///< ���

	static void Rendering( LPOINT lPt );															///< �����_�����O
	static void ResetBuffer( LPOINT lPt );															///< �����_�����O�o�b�t�@���Z�b�g
	static void UpdateBuffer( LPOINT lPt );															///< �����_�����O�o�b�t�@�X�V

	static Bool PushRenderBuffer( LPOINT lPt, CPrimitivePoint2D *pPoint, Uint32 Count );				///< �����_�����O�o�b�t�@�Ƀf�[�^�ǉ�

	static Sint32 GetRequestedVertexCount( LPOINT lPrim );															///< ���ۂɃ��N�G�X�g�������_���擾

	static void SetScissoring( Bool IsUse, RECT *pRect );
	static void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );
	static void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�R�c�|�C���g�`��N���X

	�R�c��ԓ��Ƀ|�C���g��`�悷�邽�߂̃N���X�ł��B
	�w����W�ɓ_��`�悷�邾���̃N���X�ł���A
	���̃N���X�̃��b�p�[�͑��݂��܂���B
*/
class LunaPoint3D
{
protected:
	static LibLuna::CPoint3DMgr *m_pPointMgr;

public:
	static Bool Initialize( void );																///< �N���X������
	static void Finalize( void );																///< �N���X���
	static void Reset( void );																	///< �f�o�C�X�f�[�^���Z�b�g
	static void Restore( void );																///< �f�o�C�X�f�[�^���X�g�A

	static LPOINT3D Create( Uint32 VertexMax );													///< ����

	static void Release( LPOINT3D lPnt3D );														///< ���

	static void TransformInit( LPOINT3D lPnt3D );												///< �ϊ�������
	static void TransformUpdate( LPOINT3D lPnt3D );												///< �ϊ��X�V

	static void Heading( LPOINT3D lPnt3D, Sint32 Rot );											///< �w�b�f�B���O
	static void Pitching( LPOINT3D lPnt3D, Sint32 Rot );										///< �s�b�`���O
	static void Rolling( LPOINT3D lPnt3D, Sint32 Rot );											///< ���[�����O
	static void RotationX( LPOINT3D lPnt3D, Sint32 Rot );										///< �w����]
	static void RotationY( LPOINT3D lPnt3D, Sint32 Rot );										///< �x����]
	static void RotationZ( LPOINT3D lPnt3D, Sint32 Rot );										///< �y����]
	static void Translation( LPOINT3D lPnt3D, Float fPx, Float fPy, Float fPz );				///< �ړ�
	static void LookAt( LPOINT3D lPnt3D, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );	///< ����

	static void Rendering( LPOINT3D lPnt3D );													///< �����_�����O
	static void ResetBuffer( LPOINT3D lPnt3D );													///< �����_�����O�o�b�t�@���Z�b�g
	static void UpdateBuffer( LPOINT3D lPnt3D );												///< �����_�����O�o�b�t�@�X�V

	static Bool PushRenderBuffer( LPOINT3D lPnt3D, CPrimitivePoint3D *pPoint, Uint32 Count );	///< �����_�����O�o�b�t�@�Ƀf�[�^�ǉ�
};




//=============================================================================
// INCLUDE
//=============================================================================



//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�v���~�e�B�u�N���X

	�Q�c���ʏ�ɒP��̃|���S����`�悷�邽�߂̃N���X�ł��B
	���̃N���X���g�͒P���ȃ|���S����`�悷�邾���̂��̂ł����A
	LunaEffect�N���X��LunaSprite�N���X����舵���₷���悤��
	���b�p�[�ɂȂ��Ă���A���ڂ��̃N���X���g�p����̂�
	�Â����G�t�F�N�g���g�p�������Ƃ��Ȃǂ����ɂȂ�Ǝv���܂��B
*/
class LunaPrimitive
{
	friend class Luna3D;

protected:
	static LibLuna::CPrimitive2DMgr *m_pPrimMgr;

public:
	static Bool Initialize( void );																						///< �N���X������
	static void Finalize( void );																						///< �N���X�I��
	static void Reset( void );																							///< �f�o�C�X���Z�b�g
	static void Restore( void );																						///< �f�o�C�X���X�g�A

	static LPRIMITIVE Create( Uint32 VertexMax, eVertexPrimitiveType VertexType, Bool IsSortZ );						///< ����

	static void BufferResize( LPRIMITIVE lPrim, Uint32 Count );															///< �Đݒ�
	static void Release( LPRIMITIVE lPrim );																			///< ���

	static void Rendering( LPRIMITIVE lPrim );																			///< �����_�����O
	static void ResetBuffer( LPRIMITIVE lPrim );																		///< �����_�����O�o�b�t�@������
	static void UpdateBuffer( LPRIMITIVE lPrim );																		///< �����_�����O�o�b�t�@�X�V

	static Bool PushRenderBuffer( LPRIMITIVE lPrim, CPrimitivePoint2D *pPoint, Uint32 Count );								///< �����_�����O�o�b�t�@�ɒǉ�

	static Sint32 GetRequestedVertexCount( LPRIMITIVE lPrim );															///< ���ۂɃ��N�G�X�g�������_���擾

	static void SetScissoring( Bool IsUse, RECT *pRect );
	static void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );
	static void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�R�c�v���~�e�B�u�`��N���X

	�R�c��ԓ��̃v���~�e�B�u��`�悷�邽�߂̃N���X�ł��B
	���̃N���X���̂͒P���ȃ|���S���`�悵���ł��܂���B
	�܂����̃N���X�̃��b�p�[�͑��݂��܂���B
*/
class LunaPrimitive3D
{
	friend class Luna3D;

protected:
	static LibLuna::CPrimitive3DMgr *m_pPrimMgr;

public:
	static Bool Initialize( void );																///< �v���~�e�B�u�N���X������
	static void Finalize( void );																///< �v���~�e�B�u�N���X���
	static void Reset( void );																	///< �S�v���~�e�B�u���Z�b�g
	static void Restore( void );																///< �S�v���~�e�B�u���X�g�A

	static LPRIMITIVE3D Create( Uint32 VertexMax, eVertexPrimitiveType VertexType );			///< �v���~�e�B�u����

	static void Release( LPRIMITIVE3D lPrim3D );												///< �v���~�e�B�u���

	static void TransformInit( LPRIMITIVE3D lPrim3D );											///< �ϊ�������
	static void TransformUpdate( LPRIMITIVE3D lPrim3D );										///< �ϊ��X�V

	static void Heading( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< �w�b�f�B���O
	static void Pitching( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< �s�b�`���O
	static void Rolling( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< ���[�����O
	static void RotationX( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< �w����]
	static void RotationY( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< �x����]
	static void RotationZ( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< �y����]
	static void Translation( LPRIMITIVE3D lPrim3D, Float fPx, Float fPy, Float fPz );			///< �ړ�
	static void LookAt( LPRIMITIVE3D lPrim3D, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );	///< �w����W����
	static void Scaling( LPRIMITIVE3D lPrim3D, Float fSx, Float fSy, Float fSz );				///< ���[�����O

	static void Rendering( LPRIMITIVE3D lPrim3D );												///< �����_�����O
	static void ResetBuffer( LPRIMITIVE3D lPrim3D );											///< �o�b�t�@���Z�b�g
	static void UpdateBuffer( LPRIMITIVE3D lPrim3D );											///< �o�b�t�@�X�V

	static Bool PushRenderBuffer( LPRIMITIVE3D lPrim3D, CPrimitivePoint3D *pPoint, Uint32 Count );	///< �o�b�t�@�Ƀv���~�e�B�u�ǉ�

	static Sint32 GetRequestedVertexCount( LPRIMITIVE3D lPrim3D );									///< ���N�G�X�g���ꂽ���_�����擾
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	���������N���X

	�����Z���k�E�c�C�X�^���g�p�����[���������������N���X�ł��B
*/
class LunaRand
{
protected:
	static Uint32 GenerateInt32( void );				///< 32Bit��������

public:
	static void Seed( Uint32 Param );					///< �����̎��ݒ�
	static Uint32 GetInt32( void );						///< 32Bit�������擾
	static Uint64 GetInt64( void );						///< 64Bit�������擾
	static Float GetFloat32( void );					///< 32Bit���������_�������擾

	static Sint32 GetInt( Sint32 Min, Sint32 Max );		///< Min�`Max�͈͂̐����������擾
	static Float GetFloat( Float Min, Float Max );		///< Min�`Max�͈͂̕��������_�������擾
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	���W�X�g���[����N���X

	���W�X�g���𑀍삷�邽�߂̃��b�p�[�N���X�ł��B
	�L�[�̍쐬����A�o�C�i���A������A���l��
	�ǂݏ������o����悤�ȍ\���ɂȂ��Ă��܂��B
*/
class LunaRegistry
{
public:
	static Bool Create( const char *pKeyName );														///< ���W�X�g������
	static void Close( void );																		///< ���W�X�g������
	static Bool Delete( const char *pKeyName );														///< ���W�X�g���폜

	static Bool SetNumber( const char *pValue, Uint32 Data );										///< ���l����������
	static Bool SetString( const char *pValue, const char *pStr );									///< ���������������
	static Bool SetBinary( const char *pValue, const unsigned char *pData, Uint32 Size );			///< �o�C�i������������

	static Bool GetNumber( const char *pValue, Uint32 *pData );										///< ���l���擾
	static Bool GetString( const char *pValue, char *pStr, Uint32 Size );							///< ��������擾
	static Bool GetBinary( const char *pValue, Uint8 *pData, Uint32 Size );							///< �o�C�i�����擾
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CASS
//=============================================================================
/**
	@brief	�V�F�[�_�[�Ǘ��N���X

	�V�F�[�_�[�̊Ǘ����s�����߂̃N���X�ł��B
*/
class LunaShaderFx
{
protected:
	static LibLuna::CBaseList	m_ShaderList;																		///< �V�F�[�_�[�t�@�C���Ǘ����X�g
	static LSHADERFX			m_lCurrentShader;																	///< �J�����g�V�F�[�_�[

public:
	static Bool Initialize( void );																					///< �V�F�[�_�[�N���X�̏�����
	static void Finalize( void );																					///< �V�F�[�_�[�N���X�̉��
	static void Reset( void );																						///< �f�o�C�X���Z�b�g����
	static void Restore( void );																					///< �f�o�C�X���X�g�A����

	static void Release( LSHADERFX lShaderFx );																		///< �V�F�[�_�[���
	static void AddRef( LSHADERFX lShaderFx );																		///< �Q�ƃJ�E���^�C���N�������g

	static Bool Begin( LSHADERFX lShaderFx, Uint32 *pPassMax );														///< �V�F�[�_�[�J�n
	static void End( LSHADERFX lShaderFx );																			///< �V�F�[�_�[�I��
	static void BeginPass( LSHADERFX lShaderFx, Uint32 Pass );														///< �V�F�[�_�[�p�X�J�n�錾
	static void EndPass( LSHADERFX lShaderFx );																		///< �V�F�[�_�[�p�X�C���錾


	static LSHADERFX Create( Uint32 Type, Uint32 BoneWeightCount, Uint32 BoneMatrixCount, Uint32 *pSendFlag );		///< ��{�V�F�[�_�[����쐬
	static LSHADERFX CreateFromMemory( void *pData, Uint32 Size );													///< �V�F�[�_�[������������쐬
	static LSHADERFX CreateFromFile( const char *pFile );															///< �V�F�[�_�[���t�@�C������쐬

	static void UpdateParameter( LSHADERFX lShaderFx );																///< �ݒ肵���p�����[�^�[�̍X�V
	static void SetCurrentShader( LSHADERFX lShaderFx );															///< �����I�Ɏg�p����V�F�[�_�[

	static void SetBool( LSHADERFX lShaderFx, const char *pHandle, BOOL Param );									///< �u�[���l��ݒ肷��
	static void SetBoolArray( LSHADERFX lShaderFx, const char *pHandle, BOOL *pParam, Sint32 Num );					///< �u�[���l�̔z���ݒ肷��
	static void SetFloat( LSHADERFX lShaderFx, const char *pHandle, Float Param );									///< ���������_�l��ݒ肷��
	static void SetFloatArray( LSHADERFX lShaderFx, const char *pHandle, Float *pParam, Sint32 Num );				///< ���������_�l�̔z���ݒ肷��
	static void SetInt( LSHADERFX lShaderFx, const char *pHandle, Sint32 Param );									///< ������ݒ肷��
	static void SetIntArray( LSHADERFX lShaderFx, const char *pHandle, Sint32 *pParam, Sint32 Num );				///< �����̔z���ݒ肷 
	static void SetMatrix( LSHADERFX lShaderFx, const char *pHandle, D3DXMATRIX *pMatrix );							///< ��]�u�s���ݒ肷��
	static void SetMatrixArray( LSHADERFX lShaderFx, const char *pHandle, D3DXMATRIX *pMatrix, Sint32 Num );		///< ��]�u�s��̔z���ݒ肷��
	static void SetMatrixTranspose( LSHADERFX lShaderFx, const char *pHandle, D3DXMATRIX *pMatrix );				///< �]�u�s���ݒ肷��
	static void SetMatrixTransposeArray( LSHADERFX lShaderFx, const char *pHandle, D3DXMATRIX *pMatrix, Sint32 Num );///< �]�u�s��̔z���ݒ肷��
	static void SetString( LSHADERFX lShaderFx, const char *pHandle, const char *pStr );							///< �������ݒ肷��
	static void SetTexture( LSHADERFX lShaderFx, const char *pHandle, LTEXTURE lTex );								///< �e�N�X�`����ݒ肷��
	static void SetVector( LSHADERFX lShaderFx, const char *pHandle, D3DXVECTOR4 *pVec );							///< �x�N�g����ݒ肷��
	static void SetVectorArray( LSHADERFX lShaderFx, const char *pHandle, D3DXVECTOR4 *pVec, Sint32 Num );			///< �x�N�g���̔z���ݒ肷��

	static D3DXHANDLE GetParameterByName( LSHADERFX lShaderFx, const char *pName );									///< ���O����p�����[�^�[�n���h�����擾����
	static D3DXHANDLE GetParameterBySemantic( LSHADERFX lShaderFx, const char *pSemantic );							///< �Z�}���e�B�b�N����p�����[�^�[�n���h�����擾����
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�V�[�g�`��N���X

	���R�ȃT�C�Y�̃e�N�X�`����������悤�ɂ����N���X�ł��B
	�����I��256x256�̃e�N�X�`���Ɏ����������ĕ`�悵��
	���܂��̂ŁA�������x�I�ɂ͖�肪����܂����A�A�h�x���`���[
	�Q�[���ȂǂŎ��R�ȃT�C�Y�̃e�N�X�`����`�悵�����ꍇ�Ȃǂɂ�
	�L�����Ǝv���܂��B
*/
class LunaSheet
{
protected:
	static LibLuna::CSheetMgr *m_pSheetMgr;

public:
	static Bool Initialize( void );
	static void Finalize( void );

	static LSHEET CreateFromFile( const char *pFileName, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );							///< �t�@�C�����琶��
	static LSHEET CreateFromLAG( const char *pFileName, const char *pDataName, eSurfaceFormat Format );											///< �k�`�f�t�@�C�����琶��
	static LSHEET CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );					///< �������t�@�C�����琶��

	static void AddRef( LSHEET lSheet );																		///< �Q�ƃJ�E���g���Z
	static void Release( LSHEET lSheet );																		///< ���

	static Sint32 GetWidth( LSHEET lSheet );																	///< �I���W�i���̉����擾
	static Sint32 GetHeight( LSHEET lSheet );																	///< �I���W�i���̏c���擾

	static void Draw( LSHEET lSheet, Float Px, Float Py, D3DCOLOR Color );																				///< �`��
	static void DrawScale( LSHEET lSheet, Float fPx, Float fPy, Float fScale, D3DCOLOR Color, Float fCx = 0.0f, Float fCy = 0.0f );						///< �g��k���`��
	static void DrawRotate( LSHEET lSheet, Float fPx, Float fPy, Sint32 Angle, D3DCOLOR Color, Float fCx = 0.0f, Float fCy = 0.0f );					///< ��]�`��
	static void DrawRotateScale( LSHEET lSheet, Float fPx, Float fPy, Sint32 Angle, Float fScale, D3DCOLOR Color, Float fCx = 0.0f, Float fCy = 0.0f );	///< ��]�g��k���`��
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�ȈՕ`��N���X

	�P���ȃ|���S���̕`����ȈՓI�ɍs����N���X�ł��B
	���̊e��N���X�̂悤�Ƀo�b�t�@����Ȃ����߂�
	���������ɒP���ɂȂ��Ă��܂��B
*/
class LunaSimple
{
protected:
	static IDirect3DVertexBuffer9 *m_pVB;																															///< ���_�o�b�t�@

protected:
	static void DrawLine( Uint32 VertexCount );																														///< ���C���`��
	static void DrawPorygon( Uint32 VertexCount, LTEXTURE TexList[], Sint32 TexNum );																				///< �|���S���`��
	static void *LockVertexBuffer( Uint32 VertexCount, Uint32 VertexSize );																							///< ���_�o�b�t�@���b�N
	static void UnlockVertexBuffer( void );																															///< ���_�o�b�t�@�A�����b�N
	static void UpdateTextureUV( CPrimitivePoint2D TriPt[], Sint32 VxNum, LTEXTURE TexList[], Sint32 TexNum );														///< �e�N�X�`��UV�X�V

public:	
	static Bool Initialize( void );																																	///< �N���X������
	static void Finalize( void );																																	///< �N���X���

	static void Reset( void );																																		///< �f�o�C�X���Z�b�g������
	static void Restore( void );																																	///< �f�o�C�X���X�g�A������

	static void DrawLinePointList( CPrimitivePoint2D PointTbl[], Sint32 PointNum );																						///< �|�C���g���X�g���g���ă��C���`��
	static void LineTriangle( CVector2D *pPos, Float fScale, Sint32 Angle, D3DCOLOR Color );																		///< �O�p�`���C���`��
	static void LineSquare( CLunaRect *pDst, Sint32 Angle, D3DCOLOR Color );																						///< �l�p�`���C���`��
	static void LineCircle( CVector2D *pPos, Float fSx, Float fSy, D3DCOLOR Color );																				///< �~�`���C���`��

	static void DrawPolygonPointList( CPrimitivePoint2D PointTbl[], Sint32 PointNum, LTEXTURE TexList[], Sint32 TexNum );													///< �|�C���g���X�g�`��
	static void DrawTriangle( CVector2D *pPos, Float fScale, Sint32 Angle, CVector2D UvTbl[], D3DCOLOR Color, LTEXTURE TexList[], Sint32 TexNum );					///< �O�p�`�`��
	static void DrawSquare( CLunaRect *pDst, Sint32 Angle, CLunaRect SrcTbl[], D3DCOLOR Color, LTEXTURE TexList[], Sint32 TexNum, Sint32 Cx = 0, Sint32 Cy = 0 );	///< �l�p�`�`��
	static void DrawCircle( CVector2D *pPos, Float fSx, Float fSy, Sint32 Angle, CLunaRect SrcTbl[], D3DCOLOR Color, LTEXTURE TexList[], Sint32 TexNum );			///< �~�`�`��

	static void LineBox( CVector3D *pMin, CVector3D *pMax, CMatrix *pMatrix, D3DCOLOR Color );																		///< ���C���łR�c�{�b�N�X�`��
};



//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�T�E���h�Ǘ��N���X

	�T�E���h�h���C�o�[Ayame�̃��b�p�[�ł��B
	Ayame���o�R���ăT�E���h��炷�̂�
	OggVorbis�A�����kWave�A���kWave�̍Đ����\�ł��B
*/
class LunaSound
{
protected:
	static char								m_AyamePath[MAX_PATH];					///< Ayame�̃p�X
	static Bool								m_IsInitAyame;							///< Ayame�̏������L��
	static IDirectSound						*m_pDirectSound;						///< DirectSound�I�u�W�F�N�g
	static IDirectSound8					*m_pDirectSound8;						///< DirectSound�I�u�W�F�N�g
	static IDirectSoundBuffer				*m_pPrimaryBuffer;						///< �v���C�}���T�E���h�o�b�t�@
	static SOUNDDATA						*m_pSound;								///< �T�E���h�f�[�^�|�C���^
	static Uint32							m_SoundMax;								///< �T�E���h�ő吔
	static HINSTANCE						m_hAyame;								///< Ayame DLL�n���h��
	static AYAME_INITIALIZE_PROC			m_pAyameInitialize;						///< �h���C�o�[������
	static AYAME_UNINITIALIZE_PROC			m_pAyameUninitialize;					///< �h���C�o�[���
	static AYAME_CREATE_FROM_FILE_EX_PROC	m_pAyameCreateFromFileEx;				///< �h���C�o�[����I�u�W�F�N�g�擾
	static AYAME_CREATE_FROM_MEMORY_PROC	m_pAyameCreateFromMemory;				///< �h���C�o�[����I�u�W�F�N�g�擾
	static AYAME_GETERROR_PROC				m_pAyameGetError;						///< �G���[������

protected:
	static Bool Delete( LSOUND lSnd );												///< �I�u�W�F�N�g�폜
	static void Init( LSOUND lSnd );												///< �I�u�W�F�N�g������
	static LSOUND GetFreeHandle( void );											///< ���g�p�n���h���擾

	static Bool CreateSoundBuffer( IDirectSoundBuffer **ppBuffer, void *pMem, Uint32 Size );	///< �T�E���h�o�b�t�@����
	static void CheckDeviceInfo( void );											///< �f�o�C�X���`�F�b�N

	static Bool InitializeAyame( const char *pDllPath );							///< Ayame�V�X�e��������

public:
	static Bool Initialize( void );													///< �N���X������
	static void Finalize( void );													///< �N���X���

	static void Manager( void );													///< �}�l�[�W���[

	static void SetAyamePath( const char *pPath );									///< Ayame.dll�̃f�B���N�g���i�f�t�H���g��.\)
	static void GetSoundObject( IDirectSound8 **ppSound );							///< �T�E���h�I�u�W�F�N�g�擾

	static void SetMax( Uint32 Max );												///< �I�u�W�F�N�g�ő吔�ݒ�

	static LSOUND CreateFromFile( const char *pFileName, Bool IsNoStop, Bool IsAyame = true );				///< �t�@�C������I�u�W�F�N�g����
	static LSOUND CreateFromMemory( void *pData, Uint32 Size, Bool IsNoStop, Bool IsAyame = true  );		///< ����������I�u�W�F�N�g����

	static LSOUND SearchHandle( const char *pFileName );							///< �I�u�W�F�N�g�n���h������
	static void AddRef( LSOUND lSnd );												///< �Q�ƃJ�E���g���Z

	static void Release( LSOUND lSnd );												///< �I�u�W�F�N�g���

	static Bool IsPlay( LSOUND lSnd );												///< �Đ��`�F�b�N
	static void Play( LSOUND lSnd, Uint32 LoopCount = 0, Uint32 LoopInSample = 0 );	///< �Đ�
	static void Loop( LSOUND lSnd );												///< ���[�v�Đ�
	static void Pause( LSOUND lSnd );												///< �ꎞ��~
	static void Stop( LSOUND lSnd );												///< ��~
	static void SetVolume( LSOUND lSnd, Float fParam );								///< �{�����[���ݒ�
	static void SetPan( LSOUND lSnd, Float fParam );								///< �p���ړ�
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�Q�c�N���X
*/
class LunaSprite
{
protected:
	static LibLuna::CSprite2DMgr *m_pSprMgr;																																																							///< �X�v���C�g�f�[�^�|�C���^

public:
	static Bool Initialize( void );																																																										///< �N���X������
	static void Finalize( void );																																																										///< �N���X���

	static void Reset( void );																																																											///< �f�o�C�X���Z�b�g������
	static void Restore( void );																																																										///< �f�o�C�X���X�g�A������

	static LSPRITE Create( Uint32 VertexMax, eVertexPrimitiveType VertexType, Bool IsSortZ );																																											///< �X�v���C�g����
	static void AttatchTexture( LSPRITE lSpr, Uint32 Stage, LTEXTURE lTex );																																															///< �e�N�X�`����ڑ�

	static void BufferResize( LSPRITE lSpr, Uint32 Count );																																																				///< �o�b�t�@�T�C�Y�Đݒ�
	static void Release( LSPRITE lSpr );																																																								///< �X�v���C�g���

	static LPRIMITIVE GetPrimitive( LSPRITE lSpr );																																																						///< �v���~�e�B�u�n���h���擾

	static void SetScissoring( Bool IsUse, RECT *pRect );																																																				///< �V�U�����O�ݒ�
	static void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );																																														///< �g��k���ݒ�
	static void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );																																													///< �p�[�X�␳�ݒ�

	static void Rendering( LSPRITE lSpr );																																																								///< �����_�����O
	static void ResetBuffer( LSPRITE lSpr );																																																							///< �o�b�t�@���Z�b�g
	static void UpdateBuffer( LSPRITE lSpr );																																																							///< �o�b�t�@�X�V

	static void DrawSquare( LSPRITE lSpr, CLunaRect *pDstRect, Float Pz, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 UvCount = 1 );																																	///< �l�p�`�`��
	static void DrawSquareRotate( LSPRITE lSpr, CLunaRect *pDstRect, Float Pz, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 Angle, Uint32 UvCount = 1, Float fCx = 0.0f, Float fCy = 0.0f );																												///< �l�p�`��]�`��
	static void DrawSquareRotateXYZ( LSPRITE lSpr, CLunaRect *pDstRect, Float Pz, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ, Uint32 UvCount = 1 );																				///< �l�p�`�R����]�`��
	static void DrawSquareMatrix( LSPRITE lSpr, CMatrix *pMatrix, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 UvCount = 1 );

	static void DrawRing( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );															///< �����O��`��
	static void DrawRingRotate( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 Angle, Float Wrap, Uint32 UvCount = 1 );										///< �����O���]�`��
	static void DrawRingRotateXYZ( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ, Float Wrap, Uint32 UvCount = 1 );	///< �����O��R����]�`��

	static void DrawRingEx( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );																					///< �y�������O��`��
	static void DrawRingExRotate( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 Angle, Float Wrap, Uint32 UvCount = 1 );																///< �y�������O���]�`��
	static void DrawRingExRotateXYZ( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ, Float Wrap, Uint32 UvCount = 1 );							///< �y�������O��R����]�`��

	static void DrawRotate( LSPRITE lSpr, CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 Angle, Sint32 UvCount = 1 );																												///< ��]�`��
	static void DrawRotateXYZ( LSPRITE lSpr, CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ, Sint32 UvCount = 1 );																				///< �R����]�`��

	static void DrawList( LSPRITE lSpr, Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );																											///< ���X�g��`��
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�R�c�N���X
*/
class LunaSprite3D
{
protected:
	static LibLuna::CSprite3DMgr *m_pSprMgr;																																														///< �X�v���C�g�f�[�^�|�C���^

public:
	static Bool Initialize( void );																																																	///< �N���X������
	static void Finalize( void );																																																	///< �N���X���

	static void Reset( void );																																																		///< �f�o�C�X���Z�b�g������
	static void Restore( void );																																																	///< �f�o�C�X���X�g�A������

	static LSPRITE3D Create( Uint32 VertexMax, eVertexPrimitiveType VertexType );																																					///< �X�v���C�g����
	static void AttatchTexture( LSPRITE3D lSpr, Uint32 Stage, LTEXTURE lTex );																																						///< �e�N�X�`����ڑ�

	static void Release( LSPRITE3D lSpr );																																															///< �X�v���C�g���

	static void TransformInit( LSPRITE3D lSpr3D );																																													///< �ϊ�������
	static void TransformUpdate( LSPRITE3D lSpr3D );																																												///< �ϊ��X�V

	static void Heading( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< �w�b�f�B���O
	static void Pitching( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< �s�b�`���O
	static void Rolling( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< ���[�����O
	static void RotationX( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< �w����]
	static void RotationY( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< �x����]
	static void RotationZ( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< �y����]
	static void Translation( LSPRITE3D lSpr3D, Float fPx, Float fPy, Float fPz );																																					///< �ړ�
	static void LookAt( LSPRITE3D lSpr3D, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );																																		///< �w����W����
	static void Scaling( LSPRITE3D lSpr3D, Float fSx, Float fSy, Float fSz );																																						///< ���[�����O

	static LPRIMITIVE3D GetPrimitive( LSPRITE3D lSpr );																																												///< �v���~�e�B�u�n���h���擾

	static void Rendering( LSPRITE3D lSpr );																																														///< �����_�����O
	static void ResetBuffer( LSPRITE3D lSpr );																																														///< �o�b�t�@���Z�b�g
	static void UpdateBuffer( LSPRITE3D lSpr );																																														///< �o�b�t�@�X�V

	static void DrawSquare( LSPRITE3D lSpr, CStyle *pStyle, Float Px, Float Py, Float Pz, Float fSx, Float fSy, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 UvCount );																///< �l�p�`�`��
	static void DrawRing( LSPRITE3D lSpr, CStyle *pStyle, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );	///< �����O��`��
	static void DrawRingEx( LSPRITE3D lSpr, CStyle *pStyle, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );							///< �y�������O��`��

	static void DrawListXY( LSPRITE3D lSpr3D, Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );																	///< ���X�g�`��
	static void DrawListYZ( LSPRITE3D lSpr3D, Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );																	///< ���X�g�`��
	static void DrawListZX( LSPRITE3D lSpr3D, Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );																	///< ���X�g�`��
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�T�[�t�F�C�X�Ǘ��N���X
*/
class LunaSurface
{
protected:
	static LibLuna::CSurfaceMgr *m_pSurfMgr;															///< �T�[�t�F�C�X�Ǘ��p

public:
	static Bool Initialize( void );																		///< �N���X������
	static void Finalize( void );																		///< �N���X���
	static void Reset( void );																			///< �f�o�C�X���Z�b�g������
	static void Restore( void );																		///< �f�o�C�X���X�g�A������

	static LSURFACE Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );						///< ��̃T�[�t�F�C�X�𐶐�
	static LSURFACE CreateFromFile( const char *pFileName, eSurfaceFormat Format );					///< �摜�t�@�C������T�[�t�F�C�X�𐶐�
	static LSURFACE CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );			///< �����_�����O�^�[�Q�b�g�𐶐�
	static LSURFACE CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format );			///< �[�x�X�e���V���T�[�t�F�C�X�𐶐�

	static void AddRef( LSURFACE lSurf );																///< �Q�ƃJ�E���g���Z
	static void Release( LSURFACE lSurf );																///< �T�[�t�F�C�X�̉��

	static Bool Copy( LSURFACE lDstSurf, RECT *pDstRect, LSURFACE lSrcSurf, RECT *pSrcRect );			///< �T�[�t�F�C�X���R�s�[

	static HDC GetDC( LSURFACE lSurf );																	///< �f�o�C�X�R���e�L�X�g���擾
	static void ReleaseDC(  LSURFACE lSurf, HDC hDC );													///< �f�o�C�X�R���e�L�X�g�����
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�V�X�e���N���X

	���WindowsAPI���g�p���āAWindows�̊�{�I��
	�������s���ׂ̃N���X�ł��B
	��Ƀt�@�C������֘A�ƃR�����_�C�A���O�֘A��
	�����ɂȂ�܂��B
*/
class LunaSystem
{
public:
	static Bool CheckVolumeLabel( const char *pLabel, char *pPath );											///< CD-ROM�h���C�u�����̃��f�B�A�̃{�����[�����x�����`�F�b�N
	static Bool SetWallPaper( const char *pFile, Sint32 Type, Bool IsReboot );									///< �ǎ���ݒ�
	static Bool RunApplication( const char *pDir, const char *pAppName );										///< �A�v���P�[�V�������N��
	static void OpenBrowser( const char *pURL );																///< �u���E�U���I�[�v��
	static void GetWindowsDir( char *pDir );																	///< Windows�f�B���N�g�����擾
	static Bool CopyFile( const char *pSrc, char *pDst );														///< �t�@�C���R�s�[
	static void DeleteFile( const char *pSrc );																	///< �t�@�C���폜
	static Uint32 GetFileSize( const char *pSrc );																///< �t�@�C���T�C�Y�擾
	static Bool SaveData( const char *pFile, void *pData, Uint32 Size );										///< �f�[�^�Z�[�u
	static Bool LoadData( const char *pFile, void *pData, Uint32 Size );										///< �f�[�^���[�h
	static Bool FolderSelect( char *pDir );																		///< �t�H���_�I���_�C�A���O
	static Bool FileOpenDialog( char *pPath, const char *pTitle, const char *pFilter, const char *pExt );		///< �t�@�C���I���_�C�A���O
	static Bool FileSaveDialog( char *pPath, const char *pTitle, const char *pFilter, const char *pExt );		///< �t�@�C���ۑ��_�C�A���O
	static Bool CreateLinkFile( const char *pShortcutFile, const char *pDescription, const char *pTargetFile );	///< �V���[�g�J�b�g�쐬
	static Bool GetDesktopFolder( char *pPath );																///< �f�X�N�g�b�v�f�B���N�g���擾
	static void SetShowIME( Bool Flag );																		///< IME�\���ؑ�
	static Bool FileExist( const char *pFile );																	///< �t�@�C�����݊m�F
	static Bool CreateDirectory( const char *pPath );															///< �f�B���N�g������
	static void GetMemorySize( Uint32 *pTotalMem, Uint32 *pFreeMem );											///< �������e�ʎ擾
	static Bool OpenColorDialog( Sint32 *pR, Sint32 *pG, Sint32 *pB );											///< �F�I���_�C�A���O
	static void GetLocalTime( Sint32 *pYear, Sint32 *pMonth, Sint32 *pWeekDay, Sint32 *pDay, Sint32 *pHour, Sint32 *pMinute, Sint32 *pSecond, Sint32 *pMilliSecond );	///< ���[�J�����Ԏ擾
	static Sint32 DayOfMonth( Sint32 Year, Sint32 Month );														///< ���̓����擾
	static Sint32 DayOfWeek( Sint32 Year, Sint32 Month );														///< ���̊J�n�j�����擾
	static void KeyCheck( eKeyState *pKey, Uint32 KeyNo );														///< �L�[�{�[�h�̃L�[�`�F�b�N
	static void ChangeEndian( void *pData, Uint32 Bytes );														///< �G���f�B�A���ϊ�
	static void GetLongFullPathName( const char *pSrcPath, char *pDstPath );									///< �V���[�g�t�@�C�����������O�t�@�C�����ɕϊ�

	static void HostToNet( void *pData, Sint32 Size );															///< �z�X�g�o�C�g�I�[�_�[���l�b�g���[�N�o�C�g�I�[�_�[�ɕϊ�
	static void NetToHost( void *pData, Sint32 Size );															///< �l�b�g���[�N�o�C�g�I�[�_�[���z�X�g�o�C�g�I�[�_�[�ɕϊ�

	static void GetSocketError( Sint32 ErrorCode, char *pErrStr );												///< �\�P�b�g�̃G���[���擾���܂�
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�e�N�X�`���Ǘ��N���X
*/
class LunaTexture
{
	friend class Luna3D;

protected:
	static LibLuna::CTextureMgr	*m_pTexMgr;																												///< �e�N�X�`���Ǘ��p

public:
	static Bool Initialize( void );																														///< �N���X������
	static void Finalize( void );																														///< �N���X���
	static void Reset( void );																															///< �f�o�C�X���Z�b�g������
	static void Restore( void );																														///< �f�o�C�X���X�g�A������

	static void SetOffsetUV( Float offset );																											///< �e�N�X�`���I�t�Z�b�g�t�u�ݒ�
	static Float GetOffsetUV( void );																													///< �e�N�X�`���I�t�Z�b�g�t�u�擾

	static Sint32 GetWidth( LTEXTURE lTex );																											///< �e�N�X�`���̉��T�C�Y�擾
	static Sint32 GetHeight( LTEXTURE lTex );																											///< �e�N�X�`���̏c�T�C�Y�擾
	static Sint32 GetOriginalWidth( LTEXTURE lTex );																									///< ���摜�̉��T�C�Y�擾
	static Sint32 GetOriginalHeight( LTEXTURE lTex );																									///< ���摜�̏c�T�C�Y�擾

	static LTEXTURE Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );																		///< ��̃e�N�X�`������
	static LTEXTURE CreateEx( Uint32 Width, Uint32 Height, Uint32 Levels, Uint32 Usage, D3DFORMAT Format, D3DPOOL Pool );								///< ��̃e�N�X�`������
	static LTEXTURE CreateFromFile( const char *pFileName, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );								///< �t�@�C������e�N�X�`������
	static LTEXTURE CreateFromLAG( const char *pFileName, const char *pDataName, eSurfaceFormat Format );												///< �k�`�f�t�@�C������e�N�X�`������
	static LTEXTURE CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );															///< �����_�����O�^�[�Q�b�g�e�N�X�`������
	static LTEXTURE CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );							///< ����������e�N�X�`���𐶐�
	static LTEXTURE CreateFromRenderTarget( LTEXTURE lTex );																							///< �����_�����O�^�[�Q�b�g�̓��e���R�s�[�����e�N�X�`�����쐬

	static LTEXTURE SearchHandle( const char *pFileName );																								///< �w��t�@�C�����̃e�N�X�`���n���h���擾
	static void AddRef( LTEXTURE lTex );																												///< �Q�ƃJ�E���g���Z

	static void ColorFill( LTEXTURE lTex, D3DCOLOR Color );																								///< �w��F�ł̓h��Ԃ�
	static Bool Lock( LTEXTURE lTex, void **ppBits, Uint32 *pPitch, D3DFORMAT *pFormat, Uint32 *pWidth, Uint32 *pHeight, RECT *pLockRect = NULL );		///< �e�N�X�`�����b�N
	static void Unlock( LTEXTURE lTex, Bool IsUpdate = true );																							///< �e�N�X�`�����b�N����
	static void UpdateTexture( LTEXTURE lTex );																											///< �e�N�X�`���X�V

	static void Release( LTEXTURE lTex );																												///< �e�N�X�`�����

	static void Draw( LTEXTURE lTex, CLunaRect *pDstRect, CLunaRect *pSrcRect, D3DCOLOR Color );														///< �e�N�X�`���`��
	static void DrawRotate( LTEXTURE lTex, CLunaRect *pDstRect, CLunaRect *pSrcRect, D3DCOLOR Color, Uint32 Angle, Sint32 Cx = 0, Sint32 Cy = 0 );		///< �e�N�X�`����]�`��

	static void DrawMulti( LTEXTURE *plTexList, CLunaRect *pDstRect, CLunaRect *pSrcRectList, D3DCOLOR Color, Sint32 Num );								///< �}���`�e�N�X�`���`��

	static Float GetLastU( LTEXTURE lTex, Float fPos );																									///< �e�N�X�`���̍ŏI�I�Ȃt�l���擾
	static Float GetLastV( LTEXTURE lTex, Float fPos );																									///< �e�N�X�`���̍ŏI�I�Ȃu�l���擾

	static D3DFORMAT GetFormat( LTEXTURE lTex );																										///< �e�N�X�`���t�H�[�}�b�g���擾
	static void GetInstance( LTEXTURE lTex, IDirect3DTexture9 **ppTexture );																			///< �e�N�X�`���n���h������IDirect3DTexture9���擾
	static void GetBaseInstance( LTEXTURE lTex, IDirect3DTexture9 **ppTexture );																		///< �e�N�X�`���n���h������IDirect3DTexture9���擾

	static Bool StretchBlt( LTEXTURE lTexDst, RECT *pDstRect, LTEXTURE lTexSrc, RECT *pSrcRect, Bool IsUvToTexel = false );								///< �e�N�X�`������e�N�X�`���փR�s�[
	static Bool SaveToFile( LTEXTURE lTex, const char *pFile, D3DXIMAGE_FILEFORMAT Format );															///< �e�N�X�`�����t�@�C���ɕۑ�

	static HDC GetDC( LTEXTURE lTex );																													///< �f�o�C�X�R���e�L�X�g�擾
	static void ReleaseDC( LTEXTURE lTex, HDC hDC );																									///< �f�o�C�X�R���e�L�X�g���
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	�r�f�I�����_���[�Ǘ��N���X
*/
class LunaVMR9
{
protected:
	static LibLuna::CVMR9Mgr	*m_pVMRMgr;							///< VMR9���[�r�[�Ǘ��p

public:
	static Bool Initialize( void );									///< �N���X������
	static void Finalize( void );									///< �N���X���
	static void Reset( void );										///< �f�o�C�X���Z�b�g������
	static void Restore( void );									///< �f�o�C�X���X�g�A������

	static void AddRef( LVMR9 lVMR9 );								///< �Q�ƃJ�E���^�{�P
	static void Release( LVMR9 lVMR9 );								///< �Q�ƃJ�E���^�|�P

	static LVMR9 CreateFromFile( const char *pFile );				///< �t�@�C������ǂݍ���
	static Bool Play( LVMR9 lVMR9 );								///< �Đ�
	static void Stop( LVMR9 lVMR9 );								///< ��~
	static Bool IsPlay( LVMR9 lVMR9 );								///< �Đ������`�F�b�N

	static void Render( LVMR9 lVMR9 );								///< �o�b�N�o�b�t�@�Ƀ����_�����O
	static LTEXTURE GetTexture( LVMR9 lVMR9 );						///< �����_�����O��e�N�X�`���n���h���擾
};


#endif	// ___LUNA_DX9___
