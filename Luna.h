//==============================================================================//
//				DirectX9用汎用ライブラリ Luna									//
//==============================================================================//
//																				//
//	最新版の置いてあるURL														//
//																				//
//		TWINTAIL LOVERS.														//
//			http://www.twin-tail.jp/											//
//																				//
//	質問等発言場所																//
//																				//
//		BBS																		//
//			TWINTAIL LOVERS.内の掲示板											//
//																				//
// DirectX Library "Luna for DirectX 9.0c"										//
// Copyright (C) 2003-2005 葉迩倭												//
// All rights reserved.															//
//																				//
//==============================================================================//
#ifndef ___LUNA_DX9___
#define ___LUNA_DX9___


//================================================================================
// WARNING
//================================================================================
#pragma warning ( disable: 4127 )		// 定数の条件式
#pragma warning ( disable: 4100 )		// 未参照の変数
#pragma warning ( disable: 4514 )		// 未参照のインライン関数
#pragma warning ( disable: 4711 )		// 自動インライン展開
#pragma warning ( disable: 4201 )		// 構造体拡張ワーニング
#pragma warning ( disable: 4996 )		// 古い形式
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
#define DIRECTINPUT_VERSION		(0x0800)			///< DirectInputバージョン定義
#define _WIN32_WINNT			(0x0400)			///< Fiber用
#define WIN32_LEAN_AND_MEAN							///< 不要なヘッダの参照削除
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
typedef char					Sint8;								///< signed char 型の別定義
typedef short					Sint16;								///< signed short 型の別定義
typedef long					Sint32;								///< signed long 型の別定義
typedef __int64					Sint64;								///< signed __int64 型の別定義
typedef unsigned char			Uint8;								///< unsigned char 型の別定義
typedef unsigned short			Uint16;								///< unsigned short 型の別定義
typedef unsigned long			Uint32;								///< unsigned long 型の別定義
typedef unsigned __int64		Uint64;								///< unsigned __int64 型の別定義
typedef float					Float;								///< Float 型の別定義
typedef float					Float32;							///< Float 型の別定義
typedef double					Float64;							///< double 型の別定義
typedef long double				Float80;							///< long double 型の別定義
typedef bool					Bool;								///< Bool 型の別定義


typedef Bool (*PCALLBACKSOCKETPROC)( HWND hWnd, long Id );			///< ソケット処理用コールバック関数
typedef void (WINAPI *PFIBERPROC)( void *pParameter );				///< マイクロスレッド用コールバック関数
typedef Bool (*PMICROTHREADPROC)( void *pParameter );				///< スレッド用コールバック関数
typedef IDirect3D9 * (WINAPI *PDIRECT3DCREATE9)( unsigned int );	///< Direct3Dオブジェクト生成関数用


//================================================================================
// DEFINE
//================================================================================
static const Sint32 OPTION_DIRECTINPUT			= (1 <<  0);						///< DirectInputを使用してキー入力を行う
static const Sint32 OPTION_DIRECTSOUND			= (1 <<  1);						///< DirectSoundをを使用してサウンド再生を行う
static const Sint32 OPTION_DIRECTMUSIC			= (1 <<  2);						///< DirectMusicを使用してサウンド再生を行う
static const Sint32 OPTION_DIRECTSHOW			= (1 <<  3);						///< DirectShowを使用してムービーの再生をする
static const Sint32 OPTION_CDDA					= (1 <<  4);						///< MCIを使用してCDDAを使用する
static const Sint32 OPTION_FIBER				= (1 <<  5);						///< Fiberを使用してタスク処理をする


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
	@brief	ベクトル演算クラス

	ベクトル関連の処理をより容易にするためのクラスです。
	D3DXVECTOR2型からの派生なのでキャストすることなく
	そのまま同じように使うことが出来ます。

    @todo	------------------------
    @bug	------------------------
*/
//=============================================================================
class CVector2D : public D3DXVECTOR2
{
public:
	//==========================================================================
	/**	コンストラクタ
	*/
	//==========================================================================
	CVector2D()
	{
	}

	//==========================================================================
	/**	コンストラクタ

		@param v		[in] 初期化に使うベクトル
	*/
	//==========================================================================
	CVector2D( const CVector2D &v )
	{
		*this = v;
	}

	//==========================================================================
	/**	コンストラクタ

		@param fPx		[in] 初期化に使うＸ値
		@param fPy		[in] 初期化に使うＹ値
	*/
	//==========================================================================
	CVector2D( Float fPx, Float fPy )
	{
		x = fPx;
		y = fPy;
	}

	void Add( CVector2D *pIn1, CVector2D *pIn2 );					///< 指定したベクトルの加算を取得
	void Sub( CVector2D *pIn1, CVector2D *pIn2 );					///< 指定したベクトルの減算を取得
	void Set( Float fPx, Float fPy );							///< ベクトルを設定

	Float LengthSq( void );										///< 長さの二乗を取得
	Float Length( void );										///< 長さを取得
	Float DotProduct( CVector2D *pIn );							///< 指定ベクトルとの内積
	void Reflect( CVector2D *pIn1, CVector2D *pIn2 );				///< 指定ベクトルと反射ベクトルでの反射

	void Normalize( void );										///< 正規化
	Float CrossProduct( CVector2D *pIn1, CVector2D *pIn2 );		///< 指定ベクトルとの外積

	void Normalize( CVector2D *pIn );							///< 指定ベクトルからの無い席
	Float CrossProduct( CVector2D *pIn );						///< 指定ベクトルからの外積
	void Reflect( CVector2D *pIn );								///< 反射ベクトルでの反射

	void Scaling( Float sx, Float sy );							///< 拡大縮小
	void Translation( Float px, Float py );						///< 移動

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
	@brief	ベクトル演算クラス

	ベクトル関連の処理をより容易にするためのクラスです。
	D3DXVECTOR3型からの派生なのでキャストすることなく
	そのまま同じように使うことが出来ます。

    @todo	------------------------
    @bug	------------------------
*/
//=============================================================================
class CVector3D : public D3DXVECTOR3
{
public:
	//==========================================================================
	/**	コンストラクタ
	*/
	CVector3D()
	{
	}

	//==========================================================================
	/**	コンストラクタ

		@param v		[in] 初期化に使うベクトル
	*/
	CVector3D( const CVector3D &v )
	{
		*this = v;
	}

	//==========================================================================
	/**	コンストラクタ

		@param v		[in] 初期化に使うベクトル
	*/
	CVector3D( const D3DXVECTOR3 &v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	//==========================================================================
	/**	コンストラクタ

		@param fPx		[in] 初期化に使うＸ値
		@param fPy		[in] 初期化に使うＹ値
		@param fPz		[in] 初期化に使うＺ値
	*/
	CVector3D( Float fPx, Float fPy, Float fPz )
	{
		x = fPx;
		y = fPy;
		z = fPz;
	}

	void Add( CVector3D *pIn1, CVector3D *pIn2 );							///< ベクトル加算
	void Sub( CVector3D *pIn1, CVector3D *pIn2 );							///< ベクトル減算
	void Set( Float fPx, Float fPy, Float fPz );						///< ベクトル設定

	Float LengthSq( void );												///< 長さの二乗取得
	Float Length( void );												///< 長さ取得
	Float DotProduct( CVector3D *pIn );									///< 指定ベクトルとの内積取得

	void Normalize( void );												///< 正規化
	void CrossProduct( CVector3D *pIn1, CVector3D *pIn2 );				///< 指定された２ベクトルとの外積取得
	void Reflect( CVector3D *pIn1, CVector3D *pIn2 );						///< 指定された２ベクトルとの反射ベクトル取得
	void TransformNormal( CVector3D *pIn1, class CMatrix *pIn2 );		///< 指定ベクトルでの法線変換
	void TransformCoord( CVector3D *pIn1, class CMatrix *pIn2 );			///< 指定ベクトルでの座標変換
	void TransformProjection( CVector3D *pIn1, class CMatrix *pIn2 );	///< 指定ベクトルでの透視変換

	void Normalize( CVector3D *pIn );									///< 指定ベクトルを正規化
	void CrossProduct( CVector3D *pIn );									///< 指定ベクトルとの外積取得
	void Reflect( CVector3D *pIn );										///< 指定ベクトルでの反射ベクトルを取得
	void TransformNormal( class CMatrix *pIn );							///< 指定行列での法線変換
	void TransformCoord( class CMatrix *pIn );							///< 指定行列での座標変換
	void TransformProjection( class CMatrix *pIn );						///< 指定行列での透視変換

	void RotationX( Sint32 Angle );										///< Ｘ軸回転させる
	void RotationY( Sint32 Angle );										///< Ｙ軸回転させる
	void RotationZ( Sint32 Angle );										///< Ｚ軸回転させる
	void RotationAxis( Sint32 Angle, CVector3D *pAxis );					///< 任意軸回転させる
	void Rotation( Sint32 rotx, Sint32 roty, Sint32 rotz );					///< ３軸で回転させる
	void Scaling( Float sx, Float sy, Float sz );						///< スケーリングさせる
	void Translation( Float px, Float py, Float pz );					///< 移動させる

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
	@brief	行列クラス

	行列を容易に扱えるようにしたクラスです。
	Direct3DXの補助関数でSSEや3DNowでの演算を
	補佐するために内部的に16Byte単位で自動的に
	アライメントされます。
	そのため、メンバに直接アクセスできないなどの
	不便な点もあります。
*/
//=============================================================================
class CMatrix
{
	Uint8 Data[sizeof(D3DXMATRIX) + 16];															///< 行列用データ
	D3DXMATRIX *m_Ptr;																				///< 行列先頭アドレス

public:
	CMatrix();																						///< コンストラクタ
	CMatrix( CMatrix &Mat );																		///< コンストラクタ
	CMatrix( D3DMATRIX &Mat );																		///< コンストラクタ
	CMatrix( D3DXMATRIX &Mat );																		///< コンストラクタ
	CMatrix(																						///< コンストラクタ
		Float _11, Float _12, Float _13, Float _14,
		Float _21, Float _22, Float _23, Float _24,
		Float _31, Float _32, Float _33, Float _34,
		Float _41, Float _42, Float _43, Float _44 );
	~CMatrix(){}																					///< デストラクタ

	void Identity( void );																			///< 任意行列を単位化
	void Transpose( CMatrix *pIn );																	///< 任意行列を転置
	void Inverse( CMatrix *pIn );																	///< 任意行列を逆行列化
	void Normalize( CMatrix *pIn );																	///< 任意行列を正規化
	void Multiply( CMatrix *pIn1, CMatrix *pIn2 );													///< 任意行列を合成

	void Transpose( void );																			///< 転置
	void Inverse( void );																			///< 逆行列化
	void Normalize( void );																			///< 正規化
	void Multiply( CMatrix *pIn );																	///< 合成

	void RotationX( Sint32 Angle );																	///< Ｘ軸回転行列生成
	void RotationY( Sint32 Angle );																	///< Ｙ軸回転行列生成
	void RotationZ( Sint32 Angle );																	///< Ｚ軸回転行列生成
	void RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );								///< ３軸回転行列生成
	void RotationAxis( Sint32 Angle, CVector3D *pAxis );											///< 任意軸回転行列生成
	void Rotation( Sint32 rotx, Sint32 roty, Sint32 rotz );											///< ３軸回転行列生成
	void Scaling( Float sx, Float sy, Float sz );													///< 拡大縮小行列生成
	void Translation( Float px, Float py, Float pz );												///< 移動行列生成
	void RotateVector( CVector3D *pIn1, CVector3D *pIn2, CVector3D *pAxis = NULL );					///< 任意ベクトルから任意ベクトルへの回転行列生成

	void Perspective( Float fov, Float near_z, Float far_z, Float aspect );							///< 透視変換用行列の生成
	void Ortho( Float w, Float h, Float near_z, Float far_z );										///< 正射影行列生成

	void LookAt( CVector3D *pEye, CVector3D *pAt, CVector3D *pUp );									///< 注視用の行列を作る

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
	@brief	四元数クラス

	四元数を扱うためのクラスです。
*/
//=============================================================================
class CQuaternion : public D3DXQUATERNION
{
public:
	void Add( CQuaternion *pIn1, CQuaternion *pIn2 );						///< 加算
	void Sub( CQuaternion *pIn1, CQuaternion *pIn2 );						///< 減算
	void Mul( CQuaternion *pIn1, CQuaternion *pIn2 );						///< 乗算
	void Lerp( CQuaternion *pIn0, CQuaternion *pIn1, Float fRate );			///< 線形補完
	void Slerp( CQuaternion *pIn0, CQuaternion *pIn1, Float fRate );		///< 球面補完

	void Add( CQuaternion *pIn );											///< 加算
	void Sub( CQuaternion *pIn );											///< 減算
	void Mul( CQuaternion *pIn );											///< 乗算
	void Lerp( CQuaternion *pIn, Float fRate );								///< 線形補完
	void Slerp( CQuaternion *pIn, Float fRate );							///< 球面補完

	void Identity( void );													///< 正規化
	Float LengthSq( void );													///< 長さの二乗取得
	Float Length( void );													///< 長さ取得
	Float DotProduct( CQuaternion *pIn );									///< 内積
	void Conjugate( void );													///< 反転
};



//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
/**
	@brief	姿勢制御クラス

	３軸を表すベクトルを用いて姿勢制御を行う
	為のクラスです。
	基本的には各種３Ｄ関連のオブジェクトには
	このクラスが含まれており、統一された方法で
	姿勢の制御を行うことが出来るようになっています。
	ほとんどの場合、ラッパー上から操作することになりますので、
	直接このクラスを使用する機会は稀だと思います。

    @todo	------------------------
    @bug	------------------------
*/
//=============================================================================
class CStyle
{
protected:
	CMatrix m_mStyle;												///< 姿勢用行列
	CMatrix m_mStyleInverse;										///< 姿勢の逆行列
	CMatrix m_mTransform;											///< 変換行列
	CMatrix m_mTransformInverse;									///< 変換行列の逆行列
	CVector3D m_vUp;												///< 上方向ベクトル
	CVector3D m_vRight;												///< 右方向ベクトル
	CVector3D m_vFront;												///< 前方向ベクトル
	CVector3D m_vPosition;											///< 位置ベクトル
	CVector3D m_vScale;												///< 拡大縮小ベクトル

public:
	CStyle();														///< コンストラクタ
	CStyle( const CStyle &Style );									///< コンストラクタ

	void Set( CStyle *pStyle );										///< 姿勢データコピー
	void Get( CStyle *pStyle );										///< 姿勢データコピー

	void TransformInit( void );										///< 変換初期化
	void TransformUpdate( void );									///< 変換更新

	void RotationX( Uint32 Rot );									///< Ｘ軸回転
	void RotationY( Uint32 Rot );									///< Ｙ軸回転
	void RotationZ( Uint32 Rot );									///< Ｚ軸回転
	void Pitching( Uint32 Rot );									///< ピッチング
	void Heading( Uint32 Rot );										///< ヘッディング
	void Rolling( Uint32 Rot );										///< ローリング
	void RotationQuaternion( CQuaternion *pQuat );					///< クォータニオンで回転
	void Translation( Float fPx, Float fPy, Float fPz );			///< 移動
	void Scaling( Float fSx, Float fSy, Float fSz );				///< 拡大縮小
	void LookAt( CVector3D *pEye, CVector3D *pAt, CVector3D *pUp );	///< 任意座標を注視
	void FromMatrix( CMatrix *pMat );								///< 行列から生成
	Sint32 GetAngleX( void );										///< Ｘ角度取得
	Sint32 GetAngleY( void );										///< Ｙ角度取得
	Sint32 GetAngleZ( void );										///< Ｚ角度取得

	//==========================================================================
	/**	= 演算子

		@param In		[in] コピー元スタイル
	*/
	//==========================================================================
	CStyle &operator = ( const CStyle &In )			{ Set( (CStyle*)&In ); return *this; }

	//==========================================================================
	/**	位置設定

		@param pPos		[in] 設定元位置ベクトル
	*/
	//==========================================================================
	void SetPosition( CVector3D *pPos )			{ m_vPosition = *pPos; }

	//==========================================================================
	/**	前ベクトル設定

		@param pVec		[in] 設定元ベクトル
	*/
	//==========================================================================
	void SetFront( CVector3D *pVec )				{ m_vFront = *pVec; }

	//==========================================================================
	/**	右ベクトル設定

		@param pVec		[in] 設定元ベクトル
	*/
	//==========================================================================
	void SetRight( CVector3D *pVec )				{ m_vRight = *pVec; }

	//==========================================================================
	/**	上ベクトル設定

		@param pVec		[in] 設定元ベクトル
	*/
	//==========================================================================
	void SetUp( CVector3D *pVec )				{ m_vUp = *pVec; }

	//==========================================================================
	/**	位置取得

		@param pPos		[ous] 位置ベクトル格納先
	*/
	//==========================================================================
	void GetPosition( CVector3D *pPos )			{ *pPos = m_vPosition; }

	//==========================================================================
	/**	前ベクトル取得

		@param pVec		[ous] ベクトル格納先
	*/
	//==========================================================================
	void GetFront( CVector3D *pVec )				{ *pVec = m_vFront; }

	//==========================================================================
	/**	右ベクトル取得

		@param pVec		[ous] ベクトル格納先
	*/
	//==========================================================================
	void GetRight( CVector3D *pVec )				{ *pVec = m_vRight; }

	//==========================================================================
	/**	上ベクトル取得

		@param pVec		[ous] ベクトル格納先
	*/
	//==========================================================================
	void GetUp( CVector3D *pVec )				{ *pVec = m_vUp; }

	//==========================================================================
	/**	姿勢行列取得

		@param pMat		[ous] 行列格納先
	*/
	//==========================================================================
	void GetStyle( CMatrix *pMat )				{ *pMat = m_mStyle; }

	//==========================================================================
	/**	姿勢行列hの逆行列取得

		@param pMat		[ous] 行列格納先
	*/
	//==========================================================================
	void GetStyleInverse( CMatrix *pMat )		{ *pMat = m_mStyleInverse; }

	//==========================================================================
	/**	変換行列取得

		@param pMat		[ous] 行列格納先
	*/
	//==========================================================================
	void GetTransform( CMatrix *pMat )			{ *pMat = m_mTransform; }

	//==========================================================================
	/**	変換行列の逆行列取得

		@param pMat		[ous] 行列格納先
	*/
	//==========================================================================
	void GetTransformInverse( CMatrix *pMat )	{ *pMat = m_mTransformInverse; }
};



//================================================================================
// DEFINE
//================================================================================
#define ef						else if																		///< else if 簡略用マクロ

#define toF(V)					((Float)(V))																///< Float型へのキャストマクロ
#define toI(V)					((Sint32)(V))																///< Sint32型へのキャストマクロ
#define F(V)					toF(V)
#define L(V)					toI(V)

#define PI						(3.141592653589793238462643383279f)											///< π
#define PI2						(6.283185307179586476925286766559f)											///< 2π
#define REV(V)					toF(1.0f/toF(V))															///< 逆数算出マクロ

#define SAFE_RELEASE(V)			if ( (V) != NULL ) { (V)->Release(); (V) = NULL; }							///< COM安全解放マクロ
#define SAFE_DELETE(V)			if ( (V) != NULL ) { delete (V); (V) = NULL; }								///< newメモリ安全解放
#define SAFE_DELETES(V)			if ( (V) != NULL ) { delete [] (V); (V) = NULL; }							///< new[]メモリ安全解放

#define MIN(N1,N2)				((N1 < N2) ? (N1) : (N2))													///< 最小値取得マクロ
#define MAX(N1,N2)				((N1 > N2) ? (N1) : (N2))													///< 最大値取得マクロ
#define SWAP(N1,N2)				{ N1 = N2 - N1; N2 -= N1; N1 += N2; }										///< 値交換マクロ

#define SIN_TABLE_BIT			(16)																		///< サインテーブルのビット数
#define SIN_TABLE_SIZE			(1 << SIN_TABLE_BIT)														///< サインテーブルのサイズ
#define SIN_TABLE_MASK			(SIN_TABLE_SIZE - 1)														///< サインテーブルのアクセス用マスク
#define ARCTAN_TABLE_SIZE		(SIN_TABLE_SIZE >> 3)														///< アークタンジェントテーブルのサイズ
#define ARCTAN_POS_1			(ARCTAN_TABLE_SIZE << 1)													///< アークタンジェントの第１象限
#define ARCTAN_POS_2			(ARCTAN_POS_1 + ARCTAN_POS_1)												///< アークタンジェントの第２象限
#define ARCTAN_POS_3			(ARCTAN_POS_1 + ARCTAN_POS_2)												///< アークタンジェントの第３象限
#define ARCTAN_POS_4			(ARCTAN_POS_1 + ARCTAN_POS_3)												///< アークタンジェントの第４象限
#define ARCTAN_POS_SHIFT		(SIN_TABLE_BIT - 3)															///< アークタンジェントの位置シフト量
#define ARCTAN_SCALE(V)			(toF(V) * toF(1 << ARCTAN_POS_SHIFT))										///< アークタンジェントの拡大率

#define TEXTURE_STAGE_MAX		(4)																			///< テクスチャステージ最大数
#define LUNA_BONE_MAX			(48)																		///< ひとつのメッシュで使用可能な最大ボーン数
#define LUNA_THREAD_MAX			(32)																		///< スレッドの最大数

#define NORMALIZE_ANGLE(A)		((A) & SIN_TABLE_MASK)														///< 角度の正規化（0～65535へ）
#define GET_ANGLE(A)			toI(toF(A) * toF(SIN_TABLE_SIZE) / toF(360))								///< 専用角度の算出
#define GET_ANGLE_PI(A)			toI(toF(A) * toF(SIN_TABLE_SIZE) / toF(PI2))								///< ラジアンから専用角度の算出

#define PRIMITIVE_Z_MAX			(65535)																		///< プリミティブ用Ｚ最大値
#define INV_PRIMITIVE_Z_MAX		REV(PRIMITIVE_Z_MAX)														///< プリミティブ用Ｚ値算出用データ
#define PRIMITIVE_Z_CENTER		(PRIMITIVE_Z_MAX / 2)														///< プリミティブＺ中心位置
#define Z_TO_SORT_VALUE(Z)		(toI(Z) >> 3)																///< Ｚ値からＺソート用基準値算出用
#define SORT_Z_MAX				Z_TO_SORT_VALUE(PRIMITIVE_Z_MAX)											///< Ｚソート用Ｚ最大値

#define MemoryClear(PD,S)		::FillMemory((PD),(S),0x00)													///< メモリクリア
#define MemoryFill(PD,PS,S)		::FillMemory((PD),(S),(PS))													///< メモリ塗りつぶし
#define MemoryMove(PD,PS,S)		::MoveMemory((PD),(PS),(S))													///< メモリ移動
#define MemoryCopy(PD,PS,S)		::CopyMemory((PD),(PS),(S))													///< メモリコピー

#define MemoryAlloc(size)		::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, size )										///< HeapAllocメモリ確保マクロ
#define MemoryFree(pointer)		if ( (pointer) != NULL ) { ::HeapFree( ::GetProcessHeap(), 0, pointer ); (pointer) = NULL; }	///< HeapAllocメモリ解放マクロ

#define CHECK_GUID(S,D)			(stricmp( (S).Data, (D) ) == 0)												///< システムコールバックのGUIDチェック

#define COLOR_BASE				(D3DCOLOR_XRGB(0xFF,0xFF,0xFF))												///< カラー定義：基本色
#define COLOR_WHITE				(D3DCOLOR_XRGB(0xFF,0xFF,0xFF))												///< カラー定義：白
#define COLOR_BLACK				(D3DCOLOR_XRGB(0x00,0x00,0x00))												///< カラー定義：黒
#define COLOR_RED				(D3DCOLOR_XRGB(0xFF,0x00,0x00))												///< カラー定義：赤
#define COLOR_GREEN				(D3DCOLOR_XRGB(0x00,0xFF,0x00))												///< カラー定義：緑
#define COLOR_BLUE				(D3DCOLOR_XRGB(0x00,0x00,0xFF))												///< カラー定義：青
#define COLOR_ALPHA(A)			(D3DCOLOR_ARGB(A,0xFF,0xFF,0xFF))											///< カラー定義：アルファ
#define COLOR_BRIGHT(B)			(D3DCOLOR_XRGB(B,B,B))														///< カラー定義：明度

#define LZSS_RING_LENGTH		4096																		///< 環状バッファの大きさ
#define LZSS_RING_MASK			(LZSS_RING_LENGTH-1)														///< 環状バッファのマスク
#define LZSS_LONGEST_MATCH		16																			///< 最長一致長
#define NIL						LZSS_RING_LENGTH															///< 木の末端

#define COLORKEY_DISABLE		(D3DCOLOR_ARGB(0x00,0x00,0x00,0x00))										///< テクスチャ読み込み時カラーキー不要
#define COLORKEY_BLACK			(D3DCOLOR_ARGB(0xFF,0x00,0x00,0x00))										///< テクスチャ読み込み時カラーキー黒設定
#define COLORKEY_WHITE			(D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0xFF))										///< テクスチャ読み込み時カラーキー白設定
#define COLORKEY_RED			(D3DCOLOR_ARGB(0xFF,0xFF,0x00,0x00))										///< テクスチャ読み込み時カラーキー赤設定
#define COLORKEY_GREEN			(D3DCOLOR_ARGB(0xFF,0x00,0xFF,0x00))										///< テクスチャ読み込み時カラーキー緑設定
#define COLORKEY_BLUE			(D3DCOLOR_ARGB(0xFF,0x00,0x00,0xFF))										///< テクスチャ読み込み時カラーキー青設定

#define LIGHT_MAX				(4)																			///< ライト最大数

#define PADLAYER_MAX			(256)																		///< パッド用レイヤー最大数
#define JOYSTICK_MAX			(16)																		///< ジョイスティック数最大数
#define KEY_BUFFER_MAX			(32)																		///< キーバッファ用バッファサイズ
#define ANIMATION_MAX			(256)																		///< アニメーション最大数

#define WM_SOCKET				(WM_USER + 1)																///< Socketイベント受信用メッセージ
#define WM_GRAPHNOTIFY			(WM_USER + 2)																///< ムービーイベント受信用メッセージ

#define THREAD_SYSTEM			(0xFFFFFFFF)																///< システム用スレッドを表す定数

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
typedef enum { INVALID_CAMERA		= -1 } LCAMERA;				///< カメラハンドル
typedef enum { INVALID_MODEL		= -1 } LMODEL;				///< モデルハンドル
typedef enum { INVALID_ANIMATION	= -1 } LANIMATION;			///< アニメーションハンドル
typedef enum { INVALID_SOUND		= -1 } LSOUND;				///< サウンドハンドル
typedef enum { INVALID_MUSIC		= -1 } LMUSIC;				///< ミュージックハンドル
typedef enum { INVALID_FIELD		= -1 } LFIELD;				///< フィールドハンドル
typedef enum { INVALID_MEDIA		= -1 } LMEDIA;				///< メディアハンドル


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
	@brief	サーフェイスフォーマット定義

	各種サーフェイス及びテクスチャフォーマットの定義。
*/
enum eSurfaceFormat
{
	FORMAT_FROM_FILE,					///< ファイルから

	FORMAT_DEPTH16,						///< 16Bit深度バッファ
	FORMAT_DEPTH32,						///< 32Bit深度バッファ
	FORMAT_DEPTHSTENCIL,				///< ステンシル深度バッファ

	FORMAT_DXT1,						///< DXT1圧縮フォーマットテクスチャ
	FORMAT_DXT3,						///< DXT3圧縮フォーマットテクスチャ
	FORMAT_DXT5,						///< DXT5圧縮フォーマットテクスチャ

	FORMAT_BACKBUFFER,					///< バックバッファーに準拠
	FORMAT_TARGET16,					///< 16Bitレンダリングターゲット
	FORMAT_TARGET32,					///< 32Bitレンダリングターゲット
	FORMAT_TARGETFloat,					///< 浮動小数点レンダリングターゲット

	FORMAT_ALPHAONLY,					///< アルファ用テクスチャ

	FORMAT_TEXTURE32,					///< 32Bitテクスチャフォーマットに準拠
	FORMAT_TEXTURE16,					///< 16Bitテクスチャフォーマットに準拠

	FORMAT_TEXTURE_2D,					///< 2D用汎用テクスチャフォーマット
	FORMAT_TEXTURE_3D,					///< 3D用汎用テクスチャフォーマット
};

/**
	@brief	頂点フォーマット定義

	主にLunaSpriteクラスで使用される頂点定義。
*/
enum eVertexPrimitiveType
{
	PRIM_VERTEX_UV0,					///< テクスチャステージ数０の頂点データ
	PRIM_VERTEX_UV1,					///< テクスチャステージ数１の頂点データ
	PRIM_VERTEX_UV2,					///< テクスチャステージ数２の頂点データ
	PRIM_VERTEX_UV3,					///< テクスチャステージ数３の頂点データ
	PRIM_VERTEX_UV4,					///< テクスチャステージ数４の頂点データ
};


/**
	@brief	アルファブレンディングモード定義

	各種アルファブレンディングモードの定義。
*/
enum eBlendType
{
	BLEND_NONE,							///< アルファブレンド無効
	BLEND_NORMAL,						///< 通常ブレンディング
	BLEND_ADD,							///< 加算ブレンディング
	BLEND_ADD_NOALPHA,					///< 加算ブレンディング（アルファ影響なし
	BLEND_SUB,							///< 減算ブレンディング
	BLEND_SUB_NOALPHA,					///< 減算ブレンディング（アルファ影響なし
	BLEND_MUL,							///< 乗算ブレンディング
	BLEND_REVERSE,						///< 反転ブレンディング
};


//================================================================================
// STRUCTURE
//================================================================================
/**
	@brief	サーフェイス用デバイスステート
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
	@brief	点データ

	Lunaで使用される点表現用の構造体。
*/
typedef struct CLunaPoint
{
	Float Px;					///< Ｘ座標
	Float Py;					///< Ｙ座標

	/**
		@brief 値設定
		値を簡略的に設定するための関数。

		@param px		[in] Ｘ座標
		@param py		[in] Ｙ座標
	*/
	void Set( Float px, Float py )
	{
		Px = px;
		Py = py;
	}
}
LUNAPOINT;

/**
	@brief	矩形データ

	Lunaで使用される矩形表現用の構造体。
*/
typedef struct CLunaRect
{
	Float Px;					///< Ｘ始点座標
	Float Py;					///< Ｙ始点座標
	Float Sx;					///< Ｘサイズ
	Float Sy;					///< Ｙサイズ

	/**
		@brief 値設定
		値を簡略的に設定するための関数。

		@param px		[in] Ｘ始点座標
		@param py		[in] Ｙ始点座標
		@param sx		[in] Ｘサイズ
		@param sy		[in] Ｙサイズ
	*/
	void Set( Float px, Float py, Float sx, Float sy )
	{
		Px = px;
		Py = py;
		Sx = sx;
		Sy = sy;
	}

	/**
		@brief 値設定
		値を簡略的に設定するための関数。

		@param px		[in] Ｘ始点座標
		@param py		[in] Ｙ始点座標
		@param sx		[in] Ｘサイズ
		@param sy		[in] Ｙサイズ
		@param scale	[in] 拡大縮小率
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
	@brief	クリッピング領域

	クリッピング用の矩形データ
*/
struct CClipRect
{
	Sint32 x1;					///< Ｘ位置始点
	Sint32 y1;					///< Ｙ位置始点
	Sint32 x2;					///< Ｘ位置終点
	Sint32 y2;					///< Ｙ位置終点
};

/**
	@brief	フォント描画矩形

	フォント描画用のクリッピング＆描画用矩形データ
*/
struct CFontDrawRect
{
	Sint32 x1;					///< Ｘ始点座標
	Sint32 y1;					///< Ｙ始点座標
	Sint32 x2;					///< Ｘ終点座標
	Sint32 y2;					///< Ｙ終点座標
	Sint32 Pitch;					///< フォント画像のピッチ
	void *pBits;				///< フォントのピクセルデータの先頭ポインタ
};

/**
	@brief	３Ｄデバイス情報

	Luna3Dクラスで使用する、デバイスの情報を全て
	格納しておくための構造体。
*/
struct DEVICEINFORMATION
{
	Bool IsPureDevice;							///< ピュアデバイスをサポートしてるかどうか
	Bool IsHardwareTnL;							///< ハードウェアＴｎＬをサポートしてるかどうか
	Bool IsSoftwareTnL;							///< ソフトウェアＴｎＬをサポートしてるかどうか

	D3DDEVTYPE DeviceType;						///< デバイスタイプ

	Bool IsAnisotropyMIN;						///< 異方性フィルタリングをサポートしてるか否か
	Bool IsAnisotropyMAG;						///< 異方性フィルタリングをサポートしてるか否か
	Bool IsDither;								///< ディザをサポートしてるか否か
	Bool IsDepthBias;							///< 深度バイアスをサポートしてるか否か
	Bool IsWBuffer;								///< Ｗバッファをサポートしてるか否か
	Bool IsAutoMipMap;							///< ミップマップ自動生成をサポートしているか否か

	Bool IsZCmpAlways;							///< ALWAYS深度比較をサポートしているか否か
	Bool IsZCmpEqual;							///< EQUAL深度比較をサポートしているか否か
	Bool IsZCmpGreater;							///< GREATER深度比較をサポートしているか否か
	Bool IsZCmpGreaterEqual;					///< GREATEREQUAL深度比較をサポートしているか否か
	Bool IsZCmpLess;							///< LESS深度比較をサポートしているか否か
	Bool IsZCmpLessEqual;						///< LESSEQUAL深度比較をサポートしているか否か
	Bool IsZCmpNever;							///< NEVER深度比較をサポートしているか否か
	Bool IsZCmpNotEqual;						///< NOTEQUAL深度比較をサポートしているか否か

	Bool IsSrcBlendFactor;						///< ソースにブレンドファクターをサポートしているか否か
	Bool IsSrcBothInvSrc;						///< ソースにBOTHINVSRCブレンドをサポートしているか否か
	Bool IsSrcBothSrc;							///< ソースにBOTHSRCブレンドをサポートしているか否か
	Bool IsSrcDestAlpha;						///< ソースにDESTALPHAブレンドをサポートしているか否か
	Bool IsSrcDestColor;						///< ソースにDESTCOLORブレンドをサポートしているか否か
	Bool IsSrcInvDestAlpha;						///< ソースにINVDESTALPHAブレンドをサポートしているか否か
	Bool IsSrcInvDestColor;						///< ソースにINVDESTCOLORブレンドをサポートしているか否か
	Bool IsSrcInvSrcAlpha;						///< ソースにINVSRCALPHAブレンドをサポートしているか否か
	Bool IsSrcInvSrcColor;						///< ソースにINVSRCCOLORブレンドをサポートしているか否か
	Bool IsSrcOne;								///< ソースにONEブレンドをサポートしているか否か
	Bool IsSrcSrcAlpha;							///< ソースにSRCALPHAブレンドをサポートしているか否か
	Bool IsSrcSrcAphaSat;						///< ソースにSRCALPHASATブレンドをサポートしているか否か
	Bool IsSrcSrcColor;							///< ソースにSRCCOLORブレンドをサポートしているか否か
	Bool IsSrcZero;								///< ソースにSEROブレンドをサポートしているか否か

	Bool IsDstBlendFactor;						///< デスティネーションにソースにブレンドファクターをサポートしているか否か
	Bool IsDstBothInvSrc;						///< デスティネーションにBOTHINVSRCブレンドをサポートしているか否か
	Bool IsDstBothSrc;							///< デスティネーションにBOTHSRCブレンドをサポートしているか否か
	Bool IsDstDestAlpha;						///< デスティネーションにDESTALPHAブレンドをサポートしているか否か
	Bool IsDstDestColor;						///< デスティネーションにDESTCOLORブレンドをサポートしているか否か
	Bool IsDstInvDestAlpha;						///< デスティネーションにINVDESTALPHAブレンドをサポートしているか否か
	Bool IsDstInvDestColor;						///< デスティネーションにINVDESTCOLORブレンドをサポートしているか否か
	Bool IsDstInvSrcAlpha;						///< デスティネーションにINVSRCALPHAブレンドをサポートしているか否か
	Bool IsDstInvSrcColor;						///< デスティネーションにINVSRCCOLORブレンドをサポートしているか否か
	Bool IsDstOne;								///< デスティネーションにONEブレンドをサポートしているか否か
	Bool IsDstSrcAlpha;							///< デスティネーションにSRCALPHAブレンドをサポートしているか否か
	Bool IsDstSrcAphaSat;						///< デスティネーションにSRCALPHASATブレンドをサポートしているか否か
	Bool IsDstSrcColor;							///< デスティネーションにSRCCOLORブレンドをサポートしているか否か
	Bool IsDstZero;								///< デスティネーションにZEROブレンドをサポートしているか否か

	Bool IsCubeTexture;							///< キューブテークスチャをサポートしているか否か
	Bool IsMipmapTexture;						///< ミップマップテクスチャをサポートしているか否か
	Bool IsPerspective;							///< パースペクティブコレクトをサポートしているか否か
	Bool IsPow2;								///< ２のべき乗以外のサイズのテクスチャをサポートしているか否か
	Bool IsSquareOnly;							///< 正方形以外のテクスチャをサポートしているか否か

	Bool IsTextureBorder;						///< BORDERテクスチャモードをサポートしてるか否か
	Bool IsTxtureClamp;							///< CLAMPテクスチャモードをサポートしてるか否か
	Bool IsTextureIndependent;					///< INDEPENDENTテクスチャモードをサポートしてるか否か
	Bool IsTextureMirror;						///< MIRRORテクスチャモードをサポートしてるか否か
	Bool IsTextureMirrorRonce;					///< MIRRORRONCEテクスチャモードをサポートしてるか否か
	Bool IsTextureWrap;							///< WRAPテクスチャモードをサポートしてるか否か

	Uint32 MaxAnisotropy;						///< 異方性フィルタ次数
	Uint32 MaxTextureWidth;						///< 最大テクスチャ横幅
	Uint32 MaxTextureHeight;					///< 最大テクスチャ縦幅
	Uint32 MaxTextureRepeat;					///< 最大テクスチャリピート数
	Uint32 MaxTextureAspectRatio;				///< 最大テクスチャアスペクト値

	Bool IsStencilKeep;							///< KEEPステンシル操作をサポートしてるか否か
	Bool IsStencilZero;							///< ZEROステンシル操作をサポートしてるか否か
	Bool IsStencilReplace;						///< REPLACEステンシル操作をサポートしてるか否か
	Bool IsStencilIncRsat;						///< INCRSATステンシル操作をサポートしてるか否か
	Bool IsStencilDecRsat;						///< DECRSATステンシル操作をサポートしてるか否か
	Bool IsStencilInvert;						///< INVERTステンシル操作をサポートしてるか否か
	Bool IsStencilIncR;							///< INCRステンシル操作をサポートしてるか否か
	Bool IsStencilDecR;							///< DECRステンシル操作をサポートしてるか否か
	Bool IsStencilTwoSided;						///< 両面ステンシル処理が可能かどうか

	Float MaxVertexW;							///< 最大頂点Ｗ値
	Float GuardBandLeft;						///< ガードバンドクリッピング左位置
	Float GuardBandTop;							///< ガードバンドクリッピング上位置
	Float GuardBandRight;						///< ガードバンドクリッピング右位置
	Float GuardBandBottom;						///< ガードバンドクリッピング下位置

	Float MaxPointSize;							///< 最大ポイントスプライトサイズ

	Uint32 MaxPrimitiveCount;					///< 最大一括描画可能ポリゴン数
	Uint32 MaxVertexIndex;						///< 最大一括描画可能頂点インデックス数

	Uint32 MaxTextureBlendStages;				///< 最大テクスチャブレンディングステージ数
	Uint32 MaxSimultaneousTextures;				///< 最大テクスチャステージ数

	Uint32 MaxActiveLights;						///< 最大ハードウェアライト数

	Uint32 MaxVertexBlendMatrices;				///< 頂点ブレンド最大数
	Uint32 MaxVertexBlendMatrixIndex;			///< 頂点ウェイト最大数

	Uint32 VertexShaderVersion;					///< 頂点シェーダーバージョン
	Uint32 PixelShaderVersion;					///< ピクセルシェーダーバージョン
	Uint32 MaxVertexShaderConst;				///< 最大頂点シェーダー定数レジスタ数

	Uint32 DynamicFlowControlDepth;				///< 頂点シェーダーでの動的フロー制御最大ネスト数
	Uint32 StaticFlowControlDepth;				///< 頂点シェーダーでの静的フロー制御最大ネスト数
};

/**
	@brief	圧縮データヘッダ

	LunaCompresクラスで使用する、圧縮データのヘッダ。
*/
struct LZSSHEADER
{
	char Chunk[4];					///< 専用のファイルであることをしめす識別子。常に'L''Z''S''S'
	Uint32 DecodeSize;				///< 展開後のデータサイズ
	Uint32 Reserved[2];				///< 予約領域（常に０）
};

/**
	@brief	16Bitピクセルデータ

	16Bitピクセルフォーマットの構造体。
*/
struct PIXELDATA16
{
	Uint16 a : 4;				///< アルファ成分
	Uint16 r : 4;				///< 赤成分
	Uint16 g : 4;				///< 緑成分
	Uint16 b : 4;				///< 青成分
};

/**
	@brief	32Bitピクセルデータ

	32Bitピクセルフォーマットの構造体。
*/
struct PIXELDATA32
{
	Uint8 b;				///< 青成分
	Uint8 g;				///< 緑成分
	Uint8 r;				///< 赤成分
	Uint8 a;				///< アルファ成分
};

/**
	@brief	64Bitピクセルデータ

	64Bitピクセルフォーマットの構造体。
*/
struct PIXELDATA64
{
	Uint16 b;				///< 青成分
	Uint16 g;				///< 緑成分
	Uint16 r;				///< 赤成分
	Uint16 a;				///< アルファ成分
};

/**
	@brief	Float型ピクセルデータ

	浮動小数点ピクセルフォーマットの構造体。
*/
struct PIXELDATAFloat
{
	Float b;						///< 青成分
	Float g;						///< 緑成分
	Float r;						///< 赤成分
	Float a;						///< アルファ成分
};

/**
	@brief	プリミティブ用点情報

	２Ｄプリミティブのレンダリングキューに
	データを追加する時に使用する汎用頂点データ。
*/
typedef struct CPrimitivePoint2D
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	Float w;							///< Ｗ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１
	Float u2;							///< ＵＶステージ２
	Float v2;							///< ＵＶステージ２
	Float u3;							///< ＵＶステージ３
	Float v3;							///< ＵＶステージ３
	Float u4;							///< ＵＶステージ４
	Float v4;							///< ＵＶステージ４
}
PRIMITIVEPOINT, PRIMITIVEPOINT2D;

/**
	@brief	３Ｄプリミティブ用点情報

	３Ｄプリミティブのレンダリングキューに
	データを追加する時に使用する汎用頂点データ。
*/
typedef struct CPrimitivePoint3D
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１
	Float u2;							///< ＵＶステージ２
	Float v2;							///< ＵＶステージ２
	Float u3;							///< ＵＶステージ３
	Float v3;							///< ＵＶステージ３
	Float u4;							///< ＵＶステージ４
	Float v4;							///< ＵＶステージ４
}
PRIMITIVEPOINT3D;

/**
	@brief	２Ｄポリゴン

	通常のシンプルな２Ｄ描画を行う時に使用される頂点データ構造体。
*/
typedef struct CVertex2D
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	Float w;							///< Ｗ位置
	D3DCOLOR c;							///< 頂点色
	Float u;							///< ＵＶ
	Float v;							///< ＵＶ

	/**
		CVertex2D頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
}
VERTEX2D;

/**
	@brief	プリミティブ頂点

	テクスチャＵＶを４ステージ分含んだプリミティブ用頂点
*/
struct PRIMVERTEX0
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	Float w;							///< Ｗ位置
	D3DCOLOR c;							///< 頂点色

	/**
		PRIMVERTEX0頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
	};
};


/**
	@brief	プリミティブ頂点

	テクスチャＵＶを１ステージ分含んだプリミティブ用頂点
*/
struct PRIMVERTEX1
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	Float w;							///< Ｗ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１

	/**
		PRIMVERTEX1頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
};

/**
	@brief	プリミティブ頂点

	テクスチャＵＶを２ステージ分含んだプリミティブ用頂点
*/
struct PRIMVERTEX2
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	Float w;							///< Ｗ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１
	Float u2;							///< ＵＶステージ２
	Float v2;							///< ＵＶステージ２

	/**
		PRIMVERTEX2頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2)
	};
};

/**
	@brief	プリミティブ頂点

	テクスチャＵＶを３ステージ分含んだプリミティブ用頂点
*/
struct PRIMVERTEX3
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	Float w;							///< Ｗ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１
	Float u2;							///< ＵＶステージ２
	Float v2;							///< ＵＶステージ２
	Float u3;							///< ＵＶステージ３
	Float v3;							///< ＵＶステージ３

	/**
		PRIMVERTEX3頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX3)
	};
};

/**
	@brief	プリミティブ頂点

	テクスチャＵＶを４ステージ分含んだプリミティブ用頂点
*/
struct PRIMVERTEX4
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	Float w;							///< Ｗ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１
	Float u2;							///< ＵＶステージ２
	Float v2;							///< ＵＶステージ２
	Float u3;							///< ＵＶステージ３
	Float v3;							///< ＵＶステージ３
	Float u4;							///< ＵＶステージ４
	Float v4;							///< ＵＶステージ４

	/**
		PRIMVERTEX4頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX4)
	};
};

/**
	@brief	３Ｄプリミティブ頂点

	テクスチャＵＶを含まない３Ｄプリミティブ用頂点
*/
struct PRIMVERTEX3D0
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	D3DCOLOR c;							///< 頂点色

	/**
		PRIMVERTEX3D0頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE)
	};
};

/**
	@brief	３Ｄプリミティブ頂点

	テクスチャＵＶを１ステージ分含んだ３Ｄプリミティブ用頂点
*/
struct PRIMVERTEX3D1
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１

	/**
		PRIMVERTEX3D1頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
};

/**
	@brief	３Ｄプリミティブ頂点

	テクスチャＵＶを２ステージ分含んだ３Ｄプリミティブ用頂点
*/
struct PRIMVERTEX3D2
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１
	Float u2;							///< ＵＶステージ２
	Float v2;							///< ＵＶステージ２

	/**
		PRIMVERTEX3D2頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2)
	};
};

/**
	@brief	３Ｄプリミティブ頂点

	テクスチャＵＶを３ステージ分含んだ３Ｄプリミティブ用頂点
*/
struct PRIMVERTEX3D3
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１
	Float u2;							///< ＵＶステージ２
	Float v2;							///< ＵＶステージ２
	Float u3;							///< ＵＶステージ３
	Float v3;							///< ＵＶステージ３

	/**
		PRIMVERTEX3D3頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX3)
	};
};

/**
	@brief	３Ｄプリミティブ頂点

	テクスチャＵＶを４ステージ分含んだ３Ｄプリミティブ用頂点
*/
struct PRIMVERTEX3D4
{
	Float x;							///< Ｘ位置
	Float y;							///< Ｙ位置
	Float z;							///< Ｚ位置
	D3DCOLOR c;							///< 頂点色
	Float u1;							///< ＵＶステージ１
	Float v1;							///< ＵＶステージ１
	Float u2;							///< ＵＶステージ２
	Float v2;							///< ＵＶステージ２
	Float u3;							///< ＵＶステージ３
	Float v3;							///< ＵＶステージ３
	Float u4;							///< ＵＶステージ４
	Float v4;							///< ＵＶステージ４

	/**
		PRIMVERTEX3D4頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX4)
	};
};

/**
	@brief	シェーダー自動生成用

	シェーダーを選択するときに使用するデータ構造体。
*/
struct SHADERCREATE
{
	Uint32 BoneWeightCount;		///< ボーンウェイト数
	Uint32 ShaderVersion;		///< シェーダーバージョン
	Bool IsSoftwareVP;					///< ソフトウェア処理か否か
};

/**
	@brief	２次元上の点

	LunaCollisionクラスで使われる点データ構造体。
*/
struct POINT2D
{
	Float Px;							///< Ｘ位置
	Float Py;							///< Ｙ位置
};

/**
	@brief	２次元上の円

	LunaCollisionクラスで使われる円データ構造体。
*/
struct CIRCLE2D
{
	POINT2D Center;						///< 円の中心
	Float Radius;						///< 円の半径
};

/**
	@brief	２次元上の四角

	LunaCollisionクラスで使われる四角形データ構造体。
*/
struct RECT2D
{
	Float Sx;							///< 左上Ｘ座標
	Float Sy;							///< 左上Ｙ座標
	Float Ex;							///< 右下Ｘ座標
	Float Ey;							///< 右下Ｙ座標
};

/**
	@brief	２次元上の多角形

	LunaCollisionクラスで使われる多角形データ構造体。
*/
struct POLYGON2D
{
	Sint32 Count;							///< ポイント配列のポイント数
	POINT2D *pPts;						///< ポリゴンを表すためのポイント配列のポインタ
};

/**
	@brief	２次元上の線

	LunaCollisionクラスで使われる線データ構造体。
*/
struct LINE2D
{
	POINT2D Pt0;						///< 線分始点位置
	POINT2D Pt1;						///< 線分終点位置
};

/**
	@brief	３次元上の点
*/
struct POINT3D
{
	Float Px;							///< Ｘ位置
	Float Py;							///< Ｙ位置
	Float Pz;							///< Ｚ位置

	POINT3D(){}														///< コントラクタ
	POINT3D( Float x, Float y, Float z ){ Px = x; Py = y; Pz = z; }	///< コントラクタ
	POINT3D( POINT3D &pt ) { Px = pt.Px; Py = pt.Py; Pz = pt.Pz; }	///< コントラクタ
};

/**
	@brief	３次元上の円（球

	LunaCollisionクラスで使用される球データ構造体。
*/
struct SPHERE3D
{
	POINT3D Center;						///< 球の中心
	Float Radius;						///< 球の半径

	SPHERE3D(){}															///< コンストラクタ
	SPHERE3D( POINT3D &pt, Float radius ){ Center = pt; Radius = radius; }	///< コンストラクタ
};

/**
	@brief	３次元上の線

	LunaCollisionクラスで使われる線データ構造体。
*/
struct LINE3D
{
	POINT3D Pt0;						///< 線分始点位置
	POINT3D Pt1;						///< 線分終点位置

	LINE3D(){}																///< コンストラクタ
	LINE3D( POINT3D &pt0, POINT3D &pt1 ) { Pt0 = pt0; Pt1 = pt1; }			///< コンストラクタ
};

/**
	@brief	３次元上の面

	LunaCollisionクラスで使われる面データ構造体。
*/
struct PLANE3D
{
	Float a;							///< 一般平面方程式におけるクリップ面の a 係数 
	Float b;							///< 一般平面方程式におけるクリップ面の b 係数 
	Float c;							///< 一般平面方程式におけるクリップ面の c 係数 
	Float d;							///< 一般平面方程式におけるクリップ面の d 係数 
};

/**
	@brief	３次元上の箱

	LunaCollisionクラスで使われる箱データ構造体。
*/
struct BOX3D
{
	POINT3D Points[8];					///< 箱の各角を表す頂点データ
	PLANE3D Planes[6];					///< 箱の各面を表す面データ
};

/**
	@brief	シェーダー用ライトデータ

    シェーダー用のライティングデータを
	格納するための構造体。
*/
struct SHADERLIGHTDATA
{
	BOOL IsActive[LIGHT_MAX];			///< ライトを使用するか否か
	BOOL IsDirection[LIGHT_MAX];		///< ディレクショナルライトか否か
	Float Attenuation[LIGHT_MAX];		///< ライト減衰率
	D3DXVECTOR4 Position[LIGHT_MAX];	///< ライト位置
	D3DXVECTOR4 Direction[LIGHT_MAX];	///< ライト方向
	D3DCOLORVALUE Color[LIGHT_MAX];		///< ライト色
	D3DCOLORVALUE Specular;				///< 反射光
	D3DCOLORVALUE Ambient;				///< 環境光
};

/**
	@brief	モデル用頂点

	ボーン無し頂点ベース頂点構造体。<BR>
	固定機能で処理可能なボーン無し頂点形式の構造体。
*/
struct BASEVERTEX
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ

	/**
		BASEVERTEX頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
};

/**
	@brief	ボーンモデル用頂点

	ボーン有り頂点ベース頂点構造体。<BR>
	固定機能で処理可能なボーン有り頂点形式の構造体。
*/
struct BASEBONEVERTEX
{
	D3DXVECTOR3 Pos;					///< 位置
	Float Weight[3];					///< ウェイト
	Uint8 Index[4];				///< ボーンインデックス
	D3DXVECTOR3 Norm;					///< 法線
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ

	/**
		BASEBONEVERTEX頂点用ＦＶＦ定義
	*/
	enum {
		/// ＦＶＦフォーマット定義
		FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	};
};

/**
	@brief	全データ保有頂点

	全頂点データ保有用頂点データ構造体。
	読み込まれたモデルーデータは必ずこの形式の
	頂点データを保有しています。
*/
struct VERTEXALL
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	D3DXVECTOR3 PosMorph;				///< ターゲット頂点
	D3DXVECTOR3 NormMorph;				///< ターゲット法線
	Float Weight[3];					///< ウェイト
	Uint8 Index[4];				///< ボーンインデックス
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ
};

/**
	@brief	通常頂点

	通常の透視変換用の頂点構造体。
*/
struct VERTEXNORMAL
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ
};

/**
	@brief	モーフィング用頂点

	モーフィング処理が可能な頂点の構造体。
*/
struct VERTEXMORPH
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	D3DXVECTOR3 PosMorph;				///< ターゲット位置
	D3DXVECTOR3 NormMorph;				///< ターゲット法線
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ
};

/**
	@brief	ボーン２ウェイト頂点

	最大２本のボーンの影響を受ける頂点の構造体。
*/
struct VERTEXBONE2
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	Float Weight[1];					///< ウェイト
	Uint8 Index[4];				///< ボーンインデックス
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ
};

/**
	@brief	ボーン３ウェイト頂点

	最大３本のボーンの影響を受ける頂点の構造体。
*/
struct VERTEXBONE3
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	Float Weight[2];					///< ウェイト
	Uint8 Index[4];				///< ボーンインデックス
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ 
};

/**
	@brief	ボーン４ウェイト頂点

	最大４本のボーンの影響を受ける頂点の構造体。
*/
struct VERTEXBONE4
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	Float Weight[3];					///< ウェイト
	Uint8 Index[4];				///< ボーンインデックス
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ
};

/**
	@brief	ボーン２ウェイトモーフィング頂点

	最大２本のボーンの影響を受けるモーフィング有り頂点の構造体。
*/
struct VERTEXBONE2MORPH
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	D3DXVECTOR3 PosMorph;				///< ターゲット頂点
	D3DXVECTOR3 NormMorph;				///< ターゲット法線
	Float Weight[1];					///< ウェイト
	Uint8 Index[4];				///< ボーンインデックス
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ
};

/**
	@brief	ボーン３ウェイトモーフィング頂点

	最大３本のボーンの影響を受けるモーフィング有り頂点の構造体。
*/
struct VERTEXBONE3MORPH
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	D3DXVECTOR3 PosMorph;				///< ターゲット頂点
	D3DXVECTOR3 NormMorph;				///< ターゲット法線
	Float Weight[2];					///< ウェイト
	Uint8 Index[4];				///< ボーンインデックス
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ
};

/**
	@brief	ボーン４ウェイトモーフィング頂点

	最大４本のボーンの影響を受けるモーフィング有り頂点の構造体。
*/
struct VERTEXBONE4MORPH
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	D3DXVECTOR3 PosMorph;				///< ターゲット頂点
	D3DXVECTOR3 NormMorph;				///< ターゲット法線
	Float Weight[3];					///< ウェイト
	Uint8 Index[4];				///< ボーンインデックス
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ
};

/**
	@brief	バンプマップ用頂点

	バンプマップありの透視変換用の頂点構造体。
*/
struct VERTEXBUMPMAP
{
	D3DXVECTOR3 Pos;					///< 位置
	D3DXVECTOR3 Norm;					///< 法線
	D3DXVECTOR3 Tangent;				///< 接線
	D3DXVECTOR3 BiNorm;					///< 従法線
	D3DCOLOR Color;						///< 頂点色
	D3DXVECTOR2 Tex;					///< テクスチャＵＶ
};

/**
	@brief	ホスト情報

	ソケット使用時にホスト情報を格納するために使う構造体。
*/
struct HOSTINFO
{
	char Name[256];						///< ホスト名
	char Alias[16][256];				///< ホスト別名テーブル
	char Address[16][64];				///< IPアドレステーブル
	Sint32 Type;						///< データタイプ
	Sint32 Length;						///< データサイズ
	Sint32 AliasCount;					///< エイリアス数
	Sint32 AddressCount;				///< IPアドレス数
};

/**
	@brief	ソケット用送信データ定義

	ソケット使用時にデータを送信する際に使用されるデータ構造体。
*/
struct SOCKETSENDDATA
{
	Uint32 Send;					///< 送信済みデータサイズ
	Uint32 Size;					///< 送信合計サイズ
	Uint8 *pData;					///< 送信データ
};

/**
	@brief	ソケット接続情報

	ソケットでの接続時の接続情報を<BR>
	格納しておくための構造体です
*/
struct CONNECTCLIENTDATA
{
	SOCKET Socket;							///< ソケットデータ
	SOCKADDR_IN SockAddr;					///< ソケットアドレス
	HOSTINFO HostInfo;						///< ホスト情報
	char IPAddress[64];						///< ＩＰアドレス
	char Buffer[1024];						///< バッファ
	Sint32 Length;							///< バッファ長さ

	Bool IsWriteEnable;						///< 書き込みＯＫフラグ
	Bool IsReadEnable;						///< 読み込みＯＫフラグ

	SOCKETSENDDATA SendData;				///< 送信データ

	CONNECTCLIENTDATA *pNext;				///< 次の接続情報へのポインタ
};

/**
	@brief	非同期IO用オーバーラップ構造体

	非同期IOを用いた処理をする時に<BR>
	使う情報を格納するための構造体です。
*/
struct OVERLAPEDDATA
{
	Bool			IsRequest;				///< 送受信リクエスト中か否か
	Sint32			RequestCode;			///< リクエスト結果コード
	WSAOVERLAPPED	Overlap;				///< 送受信リクエスト用データ
	WSABUF			Buffer;					///< 送信バッファ
};

/**
	@brief	ファイル管理用データ定義

	LunaFileクラスで用いられるファイル管理関係の構造体。
*/
struct FILEDATA
{
	HANDLE hFile;						///< ファイルハンドル
	BOOL IsPack;						///< パックファイルか否か
	Uint32 Start;						///< ファイル開始位置
	Uint32 Size;						///< ファイル終了位置
	FILETIME CreationTime;				///< 作成日時
	FILETIME LastAccessTime;			///< 最終アクセス日時
	FILETIME LastWriteTime;				///< 最終更新日時
	char FileName[MAX_PATH];					///< ファイル名
};

//=============================================================================
// DEFINE
//=============================================================================
#define SOCKET_LOG_LINE_MAX				(256)


//=============================================================================
// WORK ENUM
//=============================================================================

/**
	@brief	漢字コード定義

	LunaFontSpriteクラスで使用される<BR>
	S-JIS漢字コード表のインデックス算出用定義です
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

	CODE_TABLE_SIZE			= (CODE_ASCII_END - CODE_ASCII_START) + (CODE_SJIS_A_END - CODE_SJIS_A_START) + (CODE_SJIS_B_END - CODE_SJIS_B_START) + (CODE_SJIS_C_END - CODE_SJIS_C_START),	///< 最終的なテーブルサイズ

	SHEET_MAX				= 32,		///< LunaFontSpriteクラスで使用するシート最大数
};

/**
	@brief	シートサイズ定義

	CSheetクラスで使用されるシートの各種定義です
*/
enum {
	SHEET_X_MAX		= 16,			///< Ｘ方向のシート最大数
	SHEET_Y_MAX		= 16,			///< Ｙ方向のシート最大数

	SHEET_SIZE_X	= 256,			///< シートのＸ方向最大サイズ
	SHEET_SIZE_Y	= 256,			///< シートのＹ方向最大サイズ
};

/**
	@brief	エフェクトパラメーターハンドル定義

	LunaModelExクラスで使用されるエフェクトハンドルの各種定義です
*/
enum {
	FX_HANDLE_mTransform,			///< 透視変換用行列
	FX_HANDLE_mWorld,				///< ワールド変換行列
	FX_HANDLE_mWorldView,			///< カメラ空間への変換行列

	FX_HANDLE_mBoneMatrixArray,		///< ボーン用行列
	FX_HANDLE_BoneWeightCount,		///< ボーンウェイト数

	FX_HANDLE_LightIsUse,			///< ライト：使用有無フラグ
	FX_HANDLE_LightIsDirectional,	///< ライト：平行光源フラグ（true:平行光源/false:点光源）
	FX_HANDLE_LightAttenuation,		///< ライト：スポットライト減衰率
	FX_HANDLE_LightColor,			///< ライト：色
	FX_HANDLE_LightParameter,		///< ライト：方向or位置（方向か位置かはLightIsDirectionalに依存）

	FX_HANDLE_MaterialDiffuse,		///< マテリアル：ディフーズ
	FX_HANDLE_MaterialAmbient,		///< マテリアル：アンビエント

	FX_HANDLE_vCameraPos,			///< カメラ位置
	FX_HANDLE_SlideTextureU,		///< テクスチャＵスライド値
	FX_HANDLE_SlideTextureV,		///< テクスチャＶスライド値
	FX_HANDLE_VertexExtrusion,		///< 頂点押し出し値
	FX_HANDLE_MorphWeight,			///< モーフィングウェイト

	FX_HANDLE_FogParameter,			///< フォグ：計算用
	FX_HANDLE_FogTransform,			///< フォグ：Ｚ値算出用

	FX_HANDLE_TextureStage0,		///< テクスチャ：ステージ０
	FX_HANDLE_TextureStage1,		///< テクスチャ：ステージ１
	FX_HANDLE_TextureStage2,		///< テクスチャ：ステージ２
	FX_HANDLE_TextureStage3,		///< テクスチャ：ステージ３

	FX_HANDLE_MAX,
};

/**
	@brief	頂点タイプ定義

	LunaModelExで使用される頂点フォーマット定義。
*/
enum eVertexType
{
	VX_NORMAL,						///< 通常の透視変換用
	VX_MORPH,						///< モーフィング有り透視変換用
	VX_BONE2,						///< ２ボーン影響ボーン変換
	VX_BONE3,						///< ３ボーン影響ボーン変換
	VX_BONE4,						///< ４ボーン影響ボーン変換
	VX_BONE2MORPH,					///< ２ボーン影響ボーン変換＋モーフィング
	VX_BONE3MORPH,					///< ３ボーン影響ボーン変換＋モーフィング
	VX_BONE4MORPH,					///< ４ボーン影響ボーン変換＋モーフィング

	VX_UNKNOW,
};


//=============================================================================
// WORK STRUCT
//=============================================================================

/**
	@brief	LFDファイルヘッダ

	LFDファイル用のファイルヘッダ構造体。
*/
struct LFDHEADER
{
	char Guid[4];						///< ファイル識別情報（常に 'L' 'F' 'D' '\0'
	Uint8 FontSize;						///< フォントサイズ
	Uint8 SheetMax;						///< シート最大数
	Uint16 SheetWidth;					///< シート横幅
	Uint16 SheetHeight;					///< シート縦幅
	Uint16 FontMax;						///< フォント最大数
	Uint16 IndexTbl[CODE_TABLE_SIZE];	///< インデックステーブル
};

/**
	@brief	基本オブジェクト

	各オブジェクトの基本となる構造体です
*/
struct OBJECTBASE
{
	Bool IsUse;							///< 使用フラグ
	Uint32 RefCount;					///< 参照カウンタ
};

/**
	@brief	基本オブジェクトファイル

	各ファイルオブジェクトの基本となる構造体です
*/
struct OBJECTFILE : public OBJECTBASE
{
	char FileName[MAX_PATH];				///< ファイル名
};

/**
	@brief	アダプター情報

	DirectXGraphicsで使用されるアダプターの<BR>
	情報を格納しておくための構造体です
*/
struct ADAPTERDATA
{
	Sint32 ModeCount;						///< 画面モード数
	D3DDISPLAYMODE Mode[128];				///< 画面モード

	Sint32 DepthCount;						///< 深度フォーマット数
	D3DFORMAT DepthFormats[16];				///< 深度フォーマット

	Sint32 TextureCount;					///< テクスチャフォーマット数
	D3DFORMAT TextureFormats[128];			///< テクスチャフォーマット

	Sint32 TargetCount;						///< レンダリングターゲットフォーマット数
	D3DFORMAT TargetFormats[32];			///< レンダリングターゲットフォーマット
};

/**
	@brief	サウンドデータ

	LunaSoundクラスで使用される、サウンドデータを<BR>
	管理するための構造体です
*/
struct SOUNDDATA : public OBJECTFILE
{
	IDirectSoundBuffer *pBuffer;
	Uint32 PausePos;
	Bool IsLoop;
	Bool IsPause;

	FILEDATA *pFile;						///< ファイルハンドル
	class CAyame *pAyame;					///< ドライバー

	// 制御用
	struct {
		Float fStart;
		Float fEnd;
		Sint32 Time;
		Sint32 TimeAll;
		Bool IsCtrl;
	} Volume, Pan;
};

/**
	@brief	メディアオブジェクト

	LunaMediaクラスで使用される、メディア関係の情報を<BR>
	管理するための構造体です
*/
struct MEDIADATA : public OBJECTFILE
{
	IGraphBuilder	*pGB;			///< DirectShowインターフェース
	IMediaSeeking	*pMS;			///< DirectShowインターフェース
	IMediaEventEx	*pME;			///< DirectShowインターフェース
	IVideoWindow	*pVW;			///< DirectShowインターフェース
	IMediaControl	*pMC;			///< DirectShowインターフェース
	IBasicAudio		*pBA;			///< DirectShowインターフェース
	Sint64			StartPos;		///< 開始位置
	Sint64			EndPos;			///< 終了位置
	Bool			IsPlay;			///< 再生フラグ
	Bool			IsLoop;			///< ループフラグ
	Bool			IsPause;		///< 一時停止フラグ
	Bool			IsTemp;			///< 一時ファイルからの読み込みか否か
};

/**
	@brief	ミュージックデータ

	LunaMusicクラスで使用される、シーケンスデータを<BR>
	管理するための構造体です
*/
struct MUSICDATA : public OBJECTFILE
{
	IDirectMusicPerformance8 *pPerformance;	///< パフォーマンスオブジェクト
	IDirectMusicSegment8 *pSegment;			///< セグメントオブジェクト
	IDirectMusicSegmentState *pState;		///< セグメントステータスオブジェクト

	void *pMusicData;						///< パックファイルからのデータ

	Bool IsPlay;							///< 再生中か否か
	Bool IsPause;							///< 一時停止中か否か
};

/**
	@brief	キーフレームデータ

	LunaAnimationクラスで使用される、アニメーションの<BR>
	キーフレームの情報を格納するための構造体です
*/
struct KEYFRAMEDATA
{
	Float fTime;							///< キー時間
	Float fParam;							///< キー値
	Bool IsIn;								///< スプライン時のIN係数を定数にするかどうか
	Bool IsOut;								///< スプライン時のOUT係数を定数にするかどうか
	Float fIn;								///< IN係数の定数
	Float fOut;								///< OUT係数の定数

	KEYFRAMEDATA *pPrev;					///< 前方キーフレームデータポインタ
	KEYFRAMEDATA *pNext;					///< 後方キーフレームデータポインタ
};

/**
	@brief	サウンドデータ

	LunaAnimationクラスで使用される、アニメーションの<BR>
	データを管理するための構造体です
*/
struct ANIMATIONDATA : public OBJECTBASE
{
	Float *pNewtonWork0;					///< ニュートン補間用ワーク
	Float *pNewtonWork1;					///< ニュートン補間用ワーク
	KEYFRAMEDATA *pKeys;					///< キーフレームデータポインタ
	Uint32 KeyMax;					///< キーフレーム数
	Float fTimeFirst;						///< 開始時間
	Float fTimeLast;						///< 終了時間
};

/**
	@brief	シェーダー転送用データ

	LunaModelExクラスで使用される、レンダリング時の<BR>
	シェーダーへの転送データを管理するための構造体です
*/
struct SHADERDATA
{
	CMatrix mWorld;							///< ワールド行列
	CMatrix mCamera;						///< カメラ行列
	CMatrix mTransform;						///< トランスオーム行列
	CMatrix mWorldView;						///< ワールドビュー行列
	CMatrix mInvRotateWorld;				///< 回転逆行列
	CMatrix mInvWorld;						///< ワールド逆行列

	Float fVertexExtrusion;					///< 頂点押し出し量
	Float fMorphWeight;						///< モーフィングウェイト
	Float fSlideTextureU;					///< Ｕマップスライド量
	Float fSlideTextureV;					///< Ｖマップスライド量
};

/**
	@brief	カメラデータ

	LunaCameraクラスで使用される、カメラデータを<BR>
	管理するための構造体です
*/
struct LUNACAMERADATA : public OBJECTBASE
{
	CMatrix mProjection;					///< プロジェクション行列
	CMatrix mView;							///< ビュー行列
	CMatrix mCamera;						///< カメラ行列
	CVector3D vPosition;						///< 位置

	CStyle Style;							///< 姿勢制御情報

	Float fFov;								///< カメラＦＯＶ
	Float fAspect;							///< カメラアスペクト
	Float fNearZ;							///< 最近平面
	Float fFarZ;							///< 最遠平面
};

/**
	@brief	マイクロスレッドデータ

	LunaMicroThreadクラスで使用される、<BR>
	スレッドデータを管理するための構造体です
*/
struct MICROTHREADDATA
{
	PMICROTHREADPROC pProcMain;							///< スレッドメイン関数
	PMICROTHREADPROC pProcTerminate;						///< スレッド終了関数

	Sint32 StackSize;									///< スタックサイズ

	Uint32 NextThreadNo;						///< 次のスレッドの番号
	Uint32 PrevThreadNo;						///< 前のスレッドの番号
	unsigned int ThreadId;							///< スレッドのＩＤ
	HANDLE hThread;									///< スレッドのハンドル
	HANDLE hSemaphore;								///< スレッドの管理用セマフォ

	Sint64 StartTime;								///< 計測開始時間
	Sint64 EndTime;								///< 計測終了時間
	Float CPUTime;									///< ＣＰＵ時間

	Bool IsActive;									///< アクティブか否か
};

/**
	@brief	ファイバーデータ

	LunaFiberクラスで使用される、<BR>
	ファイバーデータを管理するための構造体です
*/
struct FIBERDATA
{
	PFIBERPROC pProcMain;					///< スレッド用コールバック関数のポインタ
	Uint32 StackSize;				///< スタックサイズ
	Bool IsActive;							///< アクティブか否か
	Bool IsBoot;							///< 起動中か否か
	Bool IsSuspend;							///< サスペンド中か否か

	Uint64 StartTime;						///< 開始時間
	Uint64 EndTime;						///< 終了時間
	Float CPUTime;							///< ＣＰＵ使用時間（％）

	void *pFiber;							///< ファイバーのポインタ
	void *pNextFiber;						///< 次のファイバーのポインタ
};

/**
	@brief	エフェクトデータ

	LunaShaderFxクラスで使用される、エフェクト情報データを<BR>
	管理するための構造体です
*/
struct SHADERFXDATA : public OBJECTFILE
{
	ID3DXEffect *pEffect;
	Uint16 Major;
	Uint16 Minor;
};

/**
	@brief	モデルデータ

	LunaModelクラスで使用される、モデル情報データを<BR>
	管理するための構造体です
*/
struct MODELDATA : public OBJECTFILE
{
	ID3DXAnimationController *pAnimController;	///< アニメーションコントローラー
	D3DXFRAME *pFrameRoot;						///< フレームデータへのポインタ

	Sint32 MeshCount;								///< メッシュ数
	D3DXMESHCONTAINER **ppMeshTbl;				///< メッシュアクセステーブル

	Float fObjectRadius;						///< バウンディングスフィアの半径
	CVector3D vObjectCenter;						///< バウンディングスフィアの中心
	CVector3D vBBMin;							///< バウンディングボックス最小値
	CVector3D vBBMax;							///< バウンディングボックス最大値

	Float fSx;									///< Ｘ方向拡大縮小
	Float fSy;									///< Ｙ方向拡大縮小
	Float fSz;									///< Ｚ方向拡大縮小

	CStyle Style;								///< 姿勢制御情報
	CMatrix mWorld;								///< ワールド行列
};

/**
	@brief	マテリアルデータ

	LunaModelExクラスで使用される、マテリアルデータを<BR>
	管理するための構造体です
*/
struct LMATERIAL
{
	D3DMATERIAL9 Mat;						///< マテリアルデータ
	LTEXTURE lTex[4];						///< テクスチャハンドル
	Uint32 VertexStart;						///< 頂点開始位置
	Uint32 VertexCount;						///< 頂点数
	Uint32 IndexStart;						///< インデックス開始位置
	Uint32 FaceCount;						///< インデックス数
};


/**
	@brief	フィールドマテリアルデータ

	クオードツリー構築用マテリアルデータ
*/
struct LFIELDMATERIAL
{
	Sint32 IndexStart;
	Sint32 IndexCount;
};

/**
	@brief	フィールドメッシュデータ

	クオードツリー構築用メッシュデータ
*/
struct LFIELDMESH
{
	CVector3D BBMin;							///< バウンディングボックス最小点
	CVector3D BBMax;							///< バウンディングボックス最大点

	IDirect3DVertexDeclaration9 *pVD;		///< 頂点定義
	IDirect3DVertexBuffer9 *pVB;			///< 頂点バッファ
	IDirect3DIndexBuffer9 *pIB;				///< インデックスバッファ

	void *pVertexData;						///< 頂点データ
	void *pIndexData;						///< インデックスデータ
	Uint32 VertexCount;						///< 頂点数
	Uint32 IndexCount;						///< インデックス数

	CVector3D *pNormals;						///< 各面の法線

	LFIELDMATERIAL *pMaterial;				///< マテリアルデータ
};

/**
	@brief	フィールドフレームデータ

	クオードツリー構築用フレームデータ
*/
struct LFIELDFRAME
{
	LFIELDFRAME *pChild[4];					///< 子供フレームへのポインタ
	Sint32 MeshNo;							///< 関連付けられているメッシュ番号

	CVector3D BBMin;							///< バウンディングボックス最小点
	CVector3D BBMax;							///< バウンディングボックス最大点

	BOX3D Box;								///< バウンディングボックス
};

/**
	@brief	フィールドデータ

	LunaFieldクラスで使用される、フィールドデータを<BR>
	管理するための構造体です
*/
struct LUNAFIELDDATA : public OBJECTFILE
{
	Sint32 AreaCount;							///< エリア数
	LFIELDMESH *pMeshData;					///< メッシュデータ
	Bool *pIsDrawList;						///< 描画データリスト

	Bool IsBumpMap;							///< バンプマップの有無

	LFIELDFRAME *pFrameRoot;				///< フレームの有無

	LMATERIAL *pMaterial;					///< マテリアルデータポインタ
	Uint32 MaterialCount;			///< マテリアル数

	Uint16 Major;					///< シェーダーメジャーバージョン
	Uint16 Minor;					///< シェーダーマイナーバージョン

	D3DXHANDLE FxHandle[FX_HANDLE_MAX];		///< エフェクトハンドル
	LSHADERFX lShaderFx;					///< エフェクトハンドル
	Uint32 EffectSendData;			///< エフェクト送信データ
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
	@brief	アプリケーション管理クラス

	Windows関連の基本部分を管理するクラスです。
	ウィンドウの生成から、メッセージ処理、
	タイマー処理、メッセージボックス表示などの
	ウィンドウアプリの基本部分を管理しています
*/
class Luna
{
#ifndef __TOOL_MODE__
	friend int main( int argc, char *argv[] );													///< コンソールアプリメイン関数
	friend int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrev, LPSTR Cmd, INT Show );			///< ウィンドウアプリメイン関数
#endif // __TOOL_MODE__

protected:
	// アプリケーション情報
	static HINSTANCE m_hInstance;				///< インスタンスハンドル
	static HANDLE m_hMutex;						///< ミューテックスハンドル
	static MSG m_Message;						///< メッセージ
	static char m_ApplicationName[MAX_PATH];	///< アプリケーション名
	static Uint64 m_NowTime;					///< 現在フレーム時間
	static Uint64 m_OldTime;					///< 前フレーム時間
	static Uint64 m_BeforeTime;					///< フレーム差分時間
	static Bool m_IsInit;						///< 初期化フラグ
	static Bool m_IsClipMouse;					///< マウスクリップフラグ
	// ウィンドウ情報
	static char m_CurrentDirectry[MAX_PATH];	///< カレントディレクトリ
	static HWND m_hWindow;						///< ウィンドウハンドル
	static Sint32 m_ScreenWidth;				///< 画面横幅
	static Sint32 m_ScreenHeight;				///< 画面縦幅
	static Bool m_IsWindowMode;					///< ウィンドウモードか否か
	static Bool m_IsActive;						///< アクティブか否か
	static Bool m_IsActiveWindow;				///< ウィンドウがアクティブか否か
	static Sint32 m_VirtualScreenWidth;			///< 仮想画面横幅
	static Sint32 m_VirtualScreenHeight;		///< 仮想画面縦幅
	static Float m_Virtual2RealX;				///< 仮想画面からスクリーン画面への変換
	static Float m_Virtual2RealY;				///< 仮想画面からスクリーン画面への変換
	static Float m_BackUpVirtual2RealX;			///< 仮想画面からスクリーン画面への変換パラメータバックアップ
	static Float m_BackUpVirtual2RealY;			///< 仮想画面からスクリーン画面への変換パラメータバックアップ
	// メニュー関係
	static HMENU m_hMenu;						///< メニューハンドル
	static char m_MenuName[MAX_PATH];			///< メニュー名
	// 初期化関係
	static void (*m_pCallbackInit)( void );		///< 初期化完了後コールバック関数
	static Uint32 m_UseLunaFlag;				///< 使用オプション
	static Bool m_IsDrawMouse;					///< マウス描画するか否か
	static Bool m_IsDrawTitleInfo;				///< タイトルに情報を描画するか否か
	static Bool m_IsAllowMultiBoot;				///< 多重起動を許可するか否か
	// フレーム情報
	static Uint32 m_SyncCount;					///< 総フレーム数
	static Uint32 m_FrameRate;					///< フレームレート
	static Uint32 m_FPS;						///< 秒間フレーム数
	static Uint32 m_OldFPS;						///< 秒間フレーム数バックアップ
	static Uint32 m_PPS;						///< 秒間ポリゴン数
	static Uint32 m_OldPPS;						///< 秒間ポリゴン数バックアップ
	static Uint32 m_PPS3D;						///< 秒間３Ｄポリゴン数
	static Uint32 m_OldPPS3D;					///< 秒間３Ｄポリゴン数バックアップ
	static Uint32 m_PPF;						///< フレームポリゴン数
	static Uint32 m_OldPPF;						///< フレームポリゴン数バックアップ
	static Uint32 m_PPF3D;						///< フレーム３Ｄポリゴン数
	static Uint32 m_OldPPF3D;					///< フレーム３Ｄポリゴン数バックアップ
	static Float m_fFrameTime;					///< フレーム時間
	// 他
	static FILE *m_fpLogFile;					///< ログファイル用ファイルポインタ
	static char m_DebugFileName[MAX_PATH];		///< デバッグファイル名
	static Bool m_IsLogoutConsole;				///< ログをコンソールへ出力するか否か
	static Bool m_IsExit;						///< 終了するか否か
	static CRITICAL_SECTION m_CriticalSection;	///< クリティカルセクション
	static Bool m_IsExitBlock;					///< 終了ブロック
	static Bool m_IsExitCode;					///< 終了チェック

protected:

#ifndef __TOOL_MODE__
	static LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );		///< ウィンドウメッセージコールバック関数
	static int WINAPI Boot( HINSTANCE hInst, Sint32 argc, char *argv[] );						///< Lunaの起動
	static Bool RegisterWindowClass( void );													///< ウィンドウクラスの登録
	static Bool InitWindow( void );																///< ウィンドウの初期化
	static void ResizeWindow( void );															///< ウィンドウのリサイズ
#endif // __TOOL_MODE__
	static Bool InitSystem( void );																///< システムの初期化

public:

#ifdef __TOOL_MODE__
	static LRESULT CALLBACK MsgToolMode( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );	///< ウィンドウメッセージコールバック関数
	static Bool InitToolMode( HWND hWnd, Uint32 Flags );										///< MFC処理初期化
	static Bool StartToolMode( Uint32 ScreenWidth = 0, Uint32 ScreenHeight = 0 );				///< MFC処理開始
	static void UninitToolMode( void );															///< MFC処理終了
	static void WaitForMsgLoop( void );															///< メッセージループ処理
#else // __TOOL_MODE__
	static Bool Init( void );																	///< システムの初期化
	static void Exit( void );																	///< アプリケーションの終了
	static void Main( Sint32 ArgNum, char *ArgStr[] );											///< メイン関数
	static Bool MessageProc( Sint32 Msg, Sint32 wParam, Sint32 lParam );						///< メッセージ受信
	static Bool WaitForMsgLoop( Bool IsFullActive = false );									///< メッセージループ処理
	static void SyncFrame( void );																///< フレーム調整用
#endif // __TOOL_MODE__

	// 必須
	static Bool Start( void );																	///< システムの開始
	static void End( void );																	///< システムの終了
	// 補助関数
	static void MsgBox( Uint32 Flag, const char *pTitle, const char *pStr,... );				///< メッセージボックス表示
	static Bool SelectBox( const char *pTitle, const char *pStr,... );							///< 選択式メッセージボックス表示
	// 初期設定関連
	static void SetInitCallback( void (*pCallback)( void ) );									///< 初期化後コールバック関数設定
	static void SetUseOption( Uint32 Flags );													///< 使用クラスを設定
	static void SetApplicationName( const char *pName );										///< アプリケーション名を設定
	static void SetScreenInfo( Sint32 Width, Sint32 Height, Bool IsWindow );					///< 画面情報を設定
	static void SetMenu( const char *pMenuName );												///< メニューを設定
	static void SetFrameRate( Sint32 FrameRate );												///< フレームレート設定
	static void SetDrawMouse( void );															///< マウス描画ＯＮ
	static void SetDrawTitleInfo( void );														///< タイトルバーに情報描画ＯＮ
	static void SetLogFileName( const char *pFileName, const char *pExt = "html" );				///< ログファイル名設定
	static void AllowMultiBoot( void );															///< 多重起動ＯＮ
	static void SetVirtualScreenSize( Sint32 RealWidth, Sint32 RealHeight , Sint32 VirtualWidth, Sint32 VirtualHeight );	///< 仮想上の画面サイズ設定
	static void SetMouseClip( Bool IsClip );													///< マウスクリップ設定
	// 取得系
	static HINSTANCE GetInstanceHandle( void );													///< インスタンスハンドル取得
	static HWND GetWindowHandle( void );														///< ウィンドウハンドル取得
	static Sint32 GetFPS( void );																///< 秒間フレーム数取得
	static Sint32 GetPPS( void );																///< 秒間描画ポリゴン数種特
	static Sint32 GetPPF( void );																///< フレーム間描画ポリゴン数種特
	static Sint32 GetPPS3D( void );																///< 秒間描画ポリゴン数種特
	static Sint32 GetPPF3D( void );																///< フレーム間描画ポリゴン数種特
	static void GetAbsPath( const char *pAbsPath );												///< 絶対パス取得
	static void GetApplicationName( char *pAppName );											///< アプリケーション名取得
	static void GetScreenData( Sint32 *pWidth, Sint32 *pHeight, Bool *pIsWindow );				///< 画面情報取得
	static void GetVirtualScreenSize( Sint32 *pWidth, Sint32 *pHeight );						///< 仮想上の画面サイズ取得
	static Float Virtual2RealX( Float Pos );													///< スクリーン上での実際のＸ座標を取得します
	static Float Virtual2RealY( Float Pos );													///< スクリーン上での実際のＹ座標を取得します
	// その他各種
#ifndef __TOOL_MODE__
	static void ChangeScreenSize( Sint32 Width, Sint32 Height, Bool IsChange );					///< 画面サイズ変更
	static void ChangeScreenMode( void );														///< 画面モード変更
#endif // __TOOL_MODE__
	static void DefaultCurrentDirectory( void );												///< カレントディレクトリ設定
	static void ResetCurrentDirectory( void );													///< カレントディレクトリ初期化
	static void DrawPolygon( Sint32 Cnt );														///< 描画ポリゴン数通達
	static void DrawPolygon3D( Sint32 Cnt );													///< 描画３Ｄポリゴン数通達
	static void SetWindowCenter( HWND hWnd, HWND hWndParent );									///< 画面の中央にウィンドウを移動する
	static void SetVirtualScreenEnable( Bool Flag );											///< 仮想画面有無設定
	// タイマー系
	static Uint64 GetSystemTime( void );														///< パフォーマンスカウンターを取得
	static Uint64 GetSystemTimeSecondCount( void );													///< パフォーマンスカウンターを秒間のカウント数を取得
	static Float GetFrameTime( void );															///< フレーム時間取得
	static Uint32 GetSyncCounter( void );														///< ゲームの総フレーム取得
	static Uint32 GetFrameRate( void );															///< フレームレート取得
	// ログ関係
	static void LogoutConsole( void );															///< ログをコンソールに自動出力
	static void LogoutStart();																	///< ログ出力開始
	static void LogoutEnd();																	///< ログ出力終了
	static void LogoutMainCategory( const char *pStr );											///< メインカテゴリの出力
	static void LogoutKeyword( const char *pStr,... );											///< キーワードの出力
	static void LogoutError( const char *pStr,... );											///< エラーの出力
	static void LogoutOK( const char *pStr,... );												///< 成功処理出力
	static void LogoutStrong( const char *pStr,... );											///< 太字出力
	static void Logout( const char *pStr,... );													///< ログ出力
	static void LogoutNextLine( void );															///< ログ改行
	static Bool IsFullScreenMode( void );

	static void EnterCriticalSection( void );													///< クリティカルセクションに入る
	static void LeaveCriticalSection( void );													///< クリティカルセクションから出る
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// ENUM
//=============================================================================
/**
	@brief	アニメーションタイプ定義

	LunaAnimationクラスで使用されるアニメーションの方法を表す定義。
*/
enum eAnimationType
{
	ANIM_TYPE_STEP,						///< ステップ補間
	ANIM_TYPE_LINEAR,					///< 線形補間
	ANIM_TYPE_NEWTON,					///< ニュートン補間
	ANIM_TYPE_TCB,						///< ＴＣＢスプライン補間
};


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	アニメーション管理クラス

	アニメーションを管理するためのクラスです。
	線形補間からＴＣＢスプラインまで、
	色々な補間をサポートしています。
	いくつかのキーフレームを指定するだけで
	時間ごとの補間を自動的に行うようになっています。
*/
class LunaAnimation
{
protected:
	static ANIMATIONDATA *m_pAnimation;													///< アニメーションデータポインタ
	static Uint32 m_AnimMax;															///< アニメーションデータ最大数

protected:
	static LANIMATION GetFreeHandle( void );											///< 未使用ハンドルの取得
	static Bool Delete( LANIMATION lAnim );												///< 削除
	static void *GetKeyData( void *pData, Float fTime, Sint32 KeyMax );					///< キーデータ取得
	static void Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 );	///< エルミート関数
	static Float InComing( void *pData0, void *pData1 );								///< 補間先端計算
	static Float OutGoing( void *pData0, void *pData1 );								///< 補間終端計算

public:
	static Bool Initialize( void );														///< 初期化
	static void Finalize( void );														///< 解放

	static void SetMax( Uint32 Max );													///< 最大数設定
	static LANIMATION Create( Sint32 KeyMax );											///< アニメーションオブジェクト生成
	static void Release( LANIMATION lAnim );											///< オブジェクト解放
	static void SetKey( LANIMATION lAnim, Sint32 KeyNo, Float fTime, Float fParam, Bool IsIn = false, Bool IsOut = false, Float fIn = 0.0f, Float fOut = 0.0f );		///< アニメーションキー背って尾
	static Float GetParameter( LANIMATION lAnim, Float fTime, eAnimationType Type, Float fDefault );	///< パラメーター取得
	static void Optimize( LANIMATION lAnim );											///< アニメーションデータ最適化

	static Float FlatSpeed( Float fStart, Float fEnd, Float fAll, Float fNow );			///< 等速運動を行います
	static Float AddSpeed( Float fStart, Float fEnd, Float fAll, Float fNow );			///< 加速運動を行います
	static Float SubSpeed( Float fStart, Float fEnd, Float fAll, Float fNow );			///< 減速運動を行います
	static Float Bezier( Float p1, Float p2, Float p3, Float t );						///< Bezier補間を行います
	static Float Neville( Float p1, Float p2, Float p3, Float t );						///< Neville補間を行います
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
	HDC m_hDC;									///< デバイスコンテキストハンドル
	HFONT m_hFont;								///< フォントハンドル
	HFONT m_hFontOld;							///< 前のフォントハンドル
	TEXTMETRIC m_TextMetric;					///< フォントメトリック
	Sint32 m_FontSize;							///< フォントサイズ
	CTexture *m_pTarget;						///< ターゲットハンドル
	char *m_pBuffer;							///< バッファポインタ
	Bool m_IsBegin;								///< フォント描画可能状態かどうか
	Bool m_IsAlpha;								///< アルファチャンネル有無かどうか
	Bool m_IsUpdate;							///< 描画後にテクスチャを更新するかどうか

protected:
	CFont( CBaseMgr *pMgr );
	virtual ~CFont();

	virtual void Reset( void ) {}
	virtual void Restore( void ) {}

protected:
	virtual Bool Create( const char *pFontFace, Sint32 FontSize, Bool IsItalic = false, Bool IsBold = false );	///< フォントオブジェクト生成

	virtual Sint32 GetFontBuffer( HDC hDC, Uint16 Code, GLYPHMETRICS *pGM, char **ppData, Bool Alpha );	///< フォントバッファ取得
	virtual Bool LockTarget( void **ppBits, Sint32 *pPitch, D3DFORMAT *pFormat, Sint32 *pWidth, Sint32 *pHeight );	///< 描画ターゲットロック
	virtual void UnlockTarget( void );															///< 描画ターゲットロック解除
	virtual void DrawPixel1555( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< サーフェイスに文字描画
	virtual void DrawPixel565( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< サーフェイスに文字描画
	virtual void DrawPixel4444( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< サーフェイスに文字描画
	virtual void DrawPixel8888( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< サーフェイスに文字描画
	virtual void DrawPixel4444AA( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< サーフェイスに文字描画
	virtual void DrawPixel8888AA( Sint32 Char, CFontDrawRect *pDst, CFontDrawRect *pSrc );					///< サーフェイスに文字描画
	virtual Bool Clip( CFontDrawRect *pDst, CFontDrawRect *pSrc, Sint32 Width, Sint32 Height );			///< クリッピング

public:
	virtual void SetDestination( CTexture *pTarget = NULL );								///< 描画先設置
	virtual void DrawChar( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );									///< 文字描画
	virtual void DrawCharAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );								///< アンチエイリアス付き文字描画
	virtual Sint32 DrawText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< テキスト描画
	virtual Sint32 DrawTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< アンチエイリアス付きテキスト描画
	virtual Sint32 DrawPText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< プロポーショナルテキスト描画
	virtual Sint32 DrawPTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );					///< アンチエイリアス付きプロポーショナルテキスト描画
	virtual void GetFontData( Uint16 Code, ABC *pABC );												///< フォントデータ取得

	virtual void Begin( Bool IsUpdate = true );														///< フォント処理開始
	virtual void End( void );																					///< フォント処理終了

	virtual Sint32 GetTextWidth( const char *pStr );												///< 文字列の最大横幅取得
	virtual Sint32 GetFontSize( void );																	///< フォントサイズ取得
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

	virtual void Begin( CFont *pFont, Bool IsUpdate = true );													///< フォント処理開始
	virtual void End( void );																					///< フォント処理終了

	virtual void DrawChar( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );									///< 文字描画
	virtual void DrawCharAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );								///< アンチエイリアス付き文字描画
	virtual Sint32 DrawText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< テキスト描画
	virtual Sint32 DrawTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );					///< アンチエイリアス付きテキスト描画
	virtual Sint32 DrawPText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< プロポーショナルテキスト描画
	virtual Sint32 DrawPTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );					///< アンチエイリアス付きプロポーショナルテキスト描画
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
	Uint8 SheetNo;		///< シート番号
	Uint8 abcA;			///< ABC幅
	Uint8 abcB;			///< ABC幅
	Uint8 abcC;			///< ABC幅
	Uint16 x1;			///< UVデータ
	Uint16 y1;			///< UVデータ
	Uint16 x2;			///< UVデータ
	Uint16 y2;			///< UVデータ
};

//=============================================================================
/**
*/
//=============================================================================
class CBaseFontSheet : public CDeviceObject
{
protected:
	CFont *m_pFont;
	CFontSheetData *m_pSheetTbl;					///< フォントシートデータポインタ
	CTexture *m_pTextures[SHEET_MAX];				///< テクスチャハンドル
	Uint16 m_IndexTbl[CODE_TABLE_SIZE];				///< インデックステーブル

	Sint32 m_SheetWidth;							///< シート横幅
	Sint32 m_SheetHeight;							///< シート縦幅
	Sint32 m_SheetCount;							///< シート数
	Sint32 m_FontSize;								///< フォントサイズ
	Sint32 m_FontMax;								///< フォント数

	Bool m_IsAlpha;									///< αチャンネルを使うか否か
	Bool m_IsAntialias;								///< アンチエイリアスを使うか否か

protected:
	CBaseFontSheet( CBaseMgr *pMgr );
	virtual ~CBaseFontSheet();

	virtual Uint16 Code2Index( Uint16 Code );																///< 文字コードからインデックスへの変換

public:
	virtual Bool CreateSheetTable( const char *pBuffer, CFont *pFont, Bool IsAntialias );					///< フォントオブジェクト生成
	virtual Bool CreateSheetTableFromFile( const char *pFileName, const char *pExt );						///< フォントオブジェクトをLFDから生成
	virtual Bool CreateSheetTableFromMemory( void *pData, const char *pExt );								///< フォントオブジェクトをLFDから生成

	virtual Bool ReCreateSheetTable( const char *pBuffer );													///< フォントオブジェクト生成

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
	LAGFMT_A4R4G4B4,					///< 16Bitフォーマット
	LAGFMT_A8R8G8B8,					///< 32Bitフォーマット
	LAGFMT_A16R16G16B16,				///< 64Bitフォーマット
	LAGFMT_Float,						///< 浮動小数点型フォーマット

	LAGFMT_COMPRESS_A4R4G4B4,			///< 圧縮16Bitフォーマット
	LAGFMT_COMPRESS_A8R8G8B8,			///< 圧縮32Bitフォーマット
	LAGFMT_COMPRESS_A16R16G16B16,		///< 圧縮64Bitフォーマット
	LAGFMT_COMPRESS_Float,				///< 圧縮浮動小数点型フォーマット
};

//=============================================================================
/**
*/
//=============================================================================
class CLagLoader
{
protected:
	PIXELDATA32 *m_pBits;		///< 画像のピクセルデータが32BitARGB型で格納される
	Sint32 m_Width;				///< 画像の横幅が格納される
	Sint32 m_Height;			///< 画像の縦幅が格納される
	Sint32 m_Pitch;				///< 画像のピッチが格納される

protected:
	virtual Sint32 GetDitherColor5( Sint32 Color,  Sint32 Px, Sint32 Py );																///< 4Bit色ディザ取得
	virtual Sint32 GetDitherColor4( Sint32 Color,  Sint32 Px, Sint32 Py );																///< 5Bit色ディザ取得
	virtual void ConvertFormat( Sint32 Width, Sint32 Height, eLagFormat SrcFormat, void *pSrc, eLagFormat DstFormat, void *pDest );		///< 画像フォーマットコンバート

	virtual Sint32 LoadLAG( const char *pFileName, const char *pName, Sint32 *pWidth, Sint32 *pHeight, void **ppData, eLagFormat *Format );	///< LAGファイル読み込み
	virtual Sint32 GetLAGDataSize( Sint32 Width, Sint32 Height, eLagFormat Format );														///< LAGデータサイズ取得
	virtual Bool IsCompress( eLagFormat Format );																							///< 圧縮フォーマットか否か

	virtual Bool Decode( const Uint8 *pSrc, Uint8 **ppDst, Uint32 DstSize );																///< 画像データデコード

public:
	CLagLoader();																											///< コンストラクタ
	virtual ~CLagLoader();																											///< デストラクタ

	virtual const char *Load( const char *pFileName, const char *pDataName );														///< 読み込み
	virtual void Release( void );																									///< 解放

	virtual void GetPixelData( void **ppBits, Sint32 *ppitch );																		///< ピクセルデータ取得
	virtual void GetGraphicSize( Sint32 *pWidth, Sint32 *pHeight );																	///< 画像サイズ取得

	virtual Uint32 GetDataSize( void );																								///< 画像データサイズ
	virtual void *GetDataAddress( void );																							///< 画像データアドレス取得

	virtual Bool CopyToSurface( void *pDst, Sint32 Pitch, D3DFORMAT Format );																	///< サーフェイスにコピー
	virtual Bool CopyToSurface( Sint32 Dx, Sint32 Dy, Sint32 Px, Sint32 Py, Sint32 Sx, Sint32 Sy, void *pDst, Sint32 Pitch, D3DFORMAT Format );	///< 拡大機能付きサーフェイスコピー
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
	COLLISION_SPHERE,					///< 当たり判定を球で行う
	COLLISION_AABB,						///< 当たり判定をAABBで行う
	COLLISION_OBB,						///< 当たり判定をOBBで行う
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
typedef void *(*AYAME_MEMORY_ALLOC_PROC)( unsigned long Size, const char *pFileName, unsigned long Line );										///< メモリ確保用コールバック関数
typedef void (*AYAME_MEMORY_FREE_PROC)( void *pData );																							///< メモリ解放用コールバック関数

typedef Bool (*AYAME_INITIALIZE_PROC)( HWND hWnd, void **ppDirectSound, AYAME_MEMORY_ALLOC_PROC pAllocProc, AYAME_MEMORY_FREE_PROC pFreeProc );	///< ドライバー初期化
typedef void (*AYAME_UNINITIALIZE_PROC)( void );																								///< ドライバー解放
typedef Bool (*AYAME_GETERROR_PROC)( char *pErrStr );																							///< ドライバーからのエラーを取得
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_PROC)( const char *pFileName, Bool IsGlobal );													///< ドライバーからオブジェクト取得
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_EX_PROC)( const char *pFileName, unsigned long Start, unsigned long Size, Bool IsGlobal );		///< ドライバーからオブジェクト取得
typedef class CAyame *(*AYAME_CREATE_FROM_MEMORY_PROC)( void *pData, unsigned long Size, Bool IsGlobal );										///< ドライバーからオブジェクト取得


//====================================================================
/**
	@brief	OggVorbis再生用クラス

	DLL用に純粋仮想関数だけの中身のないクラスです
*/
//====================================================================
typedef class CAyame
{
public:
	virtual Bool __stdcall IsPlay( void )																		= 0;	///< 再生チェック
	virtual Bool __stdcall Play( unsigned long nLoopCount= 0, unsigned long nLoopInSample = 0 )					= 0;	///< 再生
	virtual Bool __stdcall Loop( unsigned long nLoopCount = LOOP_INFINITY, unsigned long nLoopInSample = 0 )	= 0;	///< ループ再生
	virtual Bool __stdcall Stop( void )																			= 0;	///< 停止
	virtual Bool __stdcall Pause( void )																		= 0;	///< 一時停止
	virtual Bool __stdcall SetVolume( Float fParam )															= 0;	///< ボリューム設定
	virtual Bool __stdcall SetPan( Float fParam )																= 0;	///< パン設定
	virtual Bool __stdcall Release( void )																		= 0;	///< 解放
	virtual Bool __stdcall AddRef( void )																		= 0;	///< 参照カウントインクリメント
	virtual void __stdcall WaitEvent( void )																	= 0;	///< イベント終了待ち
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
	static Sint32 m_SceneCount;										///< シーン処理カウンタ
	static HINSTANCE m_hDllD3D9;									///< DLLハンドル
	static IDirect3D9 *m_pDirect3D;									///< Direct3Dオブジェクト
	static IDirect3DDevice9 *m_pDevice;								///< デバイスオブジェクト
	static IDirect3DSurface9 *m_pRenderTarget;						///< レンダリングターゲット
	static IDirect3DQuery9 *m_pQuery[2];							///< デバイス問い合わせ用
	static D3DVIEWPORT9 m_Viewport;									///< ビューポート

	static char m_AdapterName[128];									///< アダプター名
	static char m_AdapterDriver[128];								///< アダプタードライバー名
	static char m_AdapterVersion[128];								///< アダプターバージョン名

	static DEVICEINFORMATION m_DeviceInfo;							///< デバイス情報

	static D3DDISPLAYMODE m_WindowMode;								///< ウィンドウモードのディスプレイモード
	static D3DDISPLAYMODE m_FullScreenMode[2];						///< フルクリーンモードのディスプレイモード

	static ADAPTERDATA m_AdapterData;								///< アダプターデータ

	static D3DPRESENT_PARAMETERS m_PresentParams[2];				///< プレゼンテーションパラメーター

	static LCAMERA m_lCamera;										///< アクティブカメラハンドル
	static LTEXTURE m_lTexTarget;									///< アクティブターゲットテクスチャハンドル
	static LSURFACE m_lSurfTarget;									///< アクティブターゲットサーフェイスハンドル
	static LSURFACE m_lSurfDepthStencil;							///< アクティブ深度バッファハンドル

	static LTEXTURE m_lTexActive[TEXTURE_STAGE_MAX];				///< アクティブテクスチャハンドル

	static Uint32 m_RenderState[RENDER_STATE_TBL_MAX];							///< レンダリングステート
	static Uint32 m_SamplerState[TEXTURE_STAGE_MAX][SAMPLER_STATE_TBL_MAX];		///< サンプラーステ－ト
	static Uint32 m_TextureState[TEXTURE_STAGE_MAX][TEXTURE_STATE_TBL_MAX];		///< テクスチャステート

	static eSurfaceFormat m_SurfaceFormatTbl[2][16];				///< サーフェイスフォーマット検索テーブル
	static Uint32 m_SurfaceFormatCount[2];							///< サーフェイスフォーマット数

	static Uint32 m_MaxVertexShaderVersion;							///< 使用する頂点シェーダー最大バージョン

	static HFONT m_hFont;											///< フォントハンドル
	static HFONT m_hOldFont;										///< 前のフォントハンドル
	static HDC m_hDC;												///< デバイスコンテキストハンドル

	static Float m_FogNear;											///< フォグ開始店
	static Float m_FogFar;											///< フォグ終了点
	static D3DCOLOR m_FogColor;										///< フォグ色

	static Bool m_IsWaitBlank;										///< 垂直同期待ち
	static Bool m_IsFullColor;										///< フルカラーモード
	static Bool m_IsEmulationMode;									///< エミュレーション起動フラグ
	static Bool m_IsLocked;											///< バックバッファロックフラグ
	static Bool m_IsCheckingFillRate;								///< フィルレートチェック中フラグ
	static Bool m_IsNVPerfHUD;										///< NVPerfHUDでの解析を使うか否か

	static void (*m_pCallbackReset)( void );						///< リセット時コールバック関数
	static void (*m_pCallbackRestore)( void );						///< リストア時コールバック関数

	static MATERIALSTATE m_DefaultState;							///< デフォルトのマテリアルステート

protected:
	static Bool InitAdapter( void );																	///< アダプター初期化
	static Bool CreateDirect3DObject( void );															///< Direct3DObject生成
	static Bool CheckAdapterInformation( void );														///< アダプター情報取得
	static Bool CheckDeviceInformation( void );															///< デバイス情報取得
	static void GetDeviceCaps( D3DCAPS9 *pCaps, DEVICEINFORMATION *pDevInfo );							///< デバイス性能取得
	static Sint32 GetDeviceTypeNo( void );																///< デバイスタイプ番号取得
	static D3DPRESENT_PARAMETERS MakePresentParameters( HWND hWnd, Bool IsWindow, Bool IsFullColor );	///< プレゼンテーションパラメーター作成
	static void InitializeDeviceSetteing( void );														///< デバイス設定初期化
	static void ResetDeviceSetteing( void );															///< デバイス設定初期化
	static Bool CreateDeviceByNVPerfHUD( HWND hWindow, D3DPRESENT_PARAMETERS *pPresentParam );			///< デバイス設定初期化

public:
	static Bool Initialize( void );															///< クラス初期化
	static void Finalize( void );															///< クラス解放

	static void ResetDevice( Bool IsChange );												///< デバイスリセット

	static Uint32 GetRestVRAM( void );														///< 使用可能な推定テクスチャメモリ容量を取得
	static char *GetPixelFormat( D3DFORMAT Format, char *pStr = NULL );						///< ピクセルフォーマットを文字列で取得
	static D3DFORMAT GetFormat( eSurfaceFormat Format, D3DFORMAT OrgFmt );					///< 指定フォーマットからDirect3Dフォーマットを取得
	static char *GetError( HRESULT hr );													///< エラー取得

	static Bool Start( HWND hWindow, Bool IsWindow );										///< ３Ｄ関係のデバイスを起動
	static void GetDeviceInformation( DEVICEINFORMATION *pInfo );							///< デバイス情報取得
	static Bool CopyToRenderTarget( RECT *pDstRect, LSURFACE lSurf, RECT *pSrcRect );

	static Bool CheckPixelShaderSupport( Uint16 Major, Uint16 Minor );						///< ピクセルシェーダーのサポートチェック
	static void EnableEmulationMode( void );												///< エミュレーションモードを使用
	static void EnableFullColorMode( void );												///< フルカラーモードを使用
	static void EnableWaitVBlank( void );													///< 垂直同期を待つ
	static void EnableNVPerfHUD( void );													///< NVPerfHUDでの解析を使う

	static HMONITOR GetAdapterMonitor( void );												///< モニターハンドル取得
	static IDirect3DDevice9 *GetDevice( void );												///< デバイス取得

	static void SetMaxVertexShaderVersion( Uint16 Major, Uint16 Minor );					///< 使用する頂点シェーダーの最高バージョンを設定
	static void SetVertexProccessing( Uint16 Major, Uint16 Minor );							///< 使用する頂点シェーダーのバージョンを設定
	static Bool GetVertexProccessing( Uint16 Major, Uint16 Minor );							///< 指定したバージョンの頂点シェーダーが使用可能かチェックする

	static Bool SetDepthStencilSurface( LSURFACE lSurf );									///< 深度ステンシルバッファを設定
	static Bool SetRenderTargetSurface( LSURFACE lSurf );									///< レンダリングターゲットサーフェイスを設定
	static Bool SetRenderTargetTexture( LTEXTURE lTex );									///< レンダリングターゲットテクスチャを設定
	static Bool ResetRenderTarget( void );													///< レンダリングターゲットを初期値に
	static Bool ResetDepthStencil( void );													///< 深度ステンシルバッファを初期値に

	static void SetLight( Sint32 No, Bool IsActive );																	///< ライトの有無を設定

	static void SetFogParameter( Float fNear, Float fFar, D3DCOLOR Color );												///< フォグ用データ設定
	static void GetFogParameter( Float *pfNear, Float *pfFar, D3DCOLOR *pColor );										///< フォグ用データ取得

	static Bool Clear( Uint32 ClearFlags = D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, D3DCOLOR Color = 0x00000000, Float Depth = 1.0f, Uint32 Stencil = 0, RECT *pDst = NULL );	///< バッファクリア
	static void ColorFill( RECT *pDst, D3DCOLOR Color );																///< 画面塗りつぶし
	static Bool BeginScene( void );																						///< シーン開始
	static void EndScene( void );																						///< シーン終了
	static void Refresh( HWND hWnd = NULL );																			///< 画面更新

	static void FillRateCheckStart( void );																				///< フィルレートチェックの開始
	static Uint32 FillRateCheckEnd( void );																				///< フィルレートチェックの終了
	static Bool BlockForEndRendering( void );																			///< レンダリングの終了を待つ

	static Bool Clip( RECT *pDst, RECT *pSrc );																			///< クリッピング領域設定

	static void SetCamera( LCAMERA lCam );																				///< カメラ設定
	static void SetViewport( RECT *pRect );																				///< ビューポート設定
	static void GetViewport( RECT *pRect );																				///< ビューポート取得

	static void SetTexture( Uint32 Stage, LTEXTURE lTex );																///< テクスチャ設定

	static void SetRenderState( D3DRENDERSTATETYPE State, Uint32 Param );												///< レンダリングステート設定
	static void SetTextureState( Uint32 Stage, D3DTEXTURESTAGESTATETYPE State, Uint32 Param );							///< テクスチャステート設定
	static void SetSamplerState( Uint32 Stage, D3DSAMPLERSTATETYPE State, Uint32 Param );								///< サンプリングステート設定
	static void SetBlendingType( eBlendType BlendType );																///< ブレンディングタイプ設定
	static void SetFilterEnable( Bool Flag );																			///< バイリニアフィルタ有無設定
	static void SetColorkeyEnable( Bool Flag );																			///< カラーキー有無設定
	static void SetZBufferEnable( Bool Flag );																			///< 深度バッファ有無設定
	static void SetZWriteEnable( Bool Flag );																			///< Z書き込み有無設定
	static void SetWireFrameEnable( Bool Flag );																		///< ワイヤフレームレンダリング有無設定

	static Bool FontBegin( const char *pFontFace, Sint32 FontSize );													///< フォント描画開始
	static void FontDraw( Sint32 Px, Sint32 Py, COLORREF FontColor, COLORREF BackColor, const char *pStr,... );			///< フォント描画
	static void FontEnd( void );																						///< フォント描画終了

	static Bool LockBackBuffer( void **ppBits, Sint32 *pPitch, D3DFORMAT *pFormat, Sint32 *pWidth, Sint32 *pHeight );	///< バックバッファロック
	static void UnlockBackBuffer( void );																				///< バックバッファロック解除

	static void SetScissoring( Bool IsUse, RECT *pRect );																///< シザリング領域を設定
	static void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );									///< パース補正レベルを設定
	static void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );										///< ズームレベルを設定
	static void WorldToScreen( CVector3D *pWorldPos, CVector3D *pScreenPos );											///< ワールド座標からスクリーン座標を取得
	static void ScreenToWorld( CVector3D *pWorldPos, CVector3D *pScreenPos );											///< スクリーン座標からワールド座標を取得
	static void ScreenToView( CVector3D *pViewPos, CVector3D *pScreenPos );												///< スクリーン座標からビュー座標を取得

	static Sint32 GetScreenModeCount( Bool IsFullColor );																///< 画面モード数取得
	static void GetScreenMode( Bool IsFullColor, Sint32 No, Sint32 *pWidth, Sint32 *pHeight );							///< 画面モード取得
	static Sint32 GetRenderTargetTextureSizeCount( void );																///< レンダリングターゲットテクスチャサイズ数取得
	static void GetRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight );								///< レンダリングターゲットテクスチャサイズ取得

	static void GetAdapterName( char *pName );																			///< アダプター名取得
	static void GetAdapterDriver( char *pName );																		///< アダプタードライバー名取得
	static void GetAdapterVersion( char *pName );																		///< アダプターバージョン取得

	static void SetDialogMode( Bool IsMode );																			///< ダイアログモードの有無

	static void SetCallbackDeviceReset( void (*pCallback)( void ) );													///< リセット時コールバック関数
	static void SetCallbackDeviceRestore( void (*pCallback)( void ) );													///< リストア時コールバック関数

	static void SetSurfaceFormatTblFor2D( eSurfaceFormat FmtTbl[], Uint32 Count );										///< 2D用サーフェイスフォーマット検索テーブル設定
	static void SetSurfaceFormatTblFor3D( eSurfaceFormat FmtTbl[], Uint32 Count );										///< 3D用サーフェイスフォーマット検索テーブル設定

	static void GetDefaultMateriaState( MATERIALSTATE *pState );														///< デフォルトマテリアルステート取得
	static void SetMateriaRenderState( MATERIALSTATE *pState );															///< マテリアルステートをデバイスに設定
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	カメラ制御クラス

	３Ｄ空間内のカメラを自在に操るためのクラスです。
	基本的な姿勢制御はCStyleクラスを解しており、
	モデルクラスと同様の方法で姿勢制御することが
	出来ますが、直接位置と視点を指定する方法なども
	使えます。
*/
class LunaCamera
{
	friend class Luna3D;

protected:
	static CMatrix m_mProjection;					///< プロジェクション行列
	static CMatrix m_mView;							///< ビュー行列
	static CMatrix m_mCamera;						///< カメラ行列
	static CMatrix m_mCameraInv;					///< カメラ逆行列
	static CVector3D m_vPosition;					///< カメラ位置

	static D3DXVECTOR3 m_FrustumPoint[8];			///< ビューフラスタム用頂点データ
	static D3DXPLANE m_FrustumPlane[6];				///< ビューフラスタム用面データ

	static BOX3D m_Box;								///< ビューフラスタムのバウンディングボックス

	static LUNACAMERADATA *m_pCamera;				///< カメラデータポインタ
	static Uint32 m_CameraMax;						///< カメラ最大数

protected:
	static void Init( LCAMERA lCamera );													///< カメラデータの初期化
	static Bool Delete( LCAMERA lCamera );													///< カメラデータの削除
	static void SetDevice( LCAMERA lCam );													///< デバイスに設定

public:
	static Bool Initialize( void );															///< カメラクラスの初期化
	static void Finalize( void );															///< カメラクラスの解放

	static void SetMatrixDirect( CMatrix *pProjection, CMatrix *pView );					///< カメラマトリックスを直接設定
	static void GetMatrixDirect( CMatrix *pProjection, CMatrix *pView, CMatrix *pCamera, CMatrix *pCameraInv = NULL );	///< カメラマトリックスを直接取得

	static LCAMERA Create( void );															///< 作成
	static void AddRef( LCAMERA lCam );														///< 参照カウンタインクリメント
	static void Release( LCAMERA lCam );													///< 解放

	static void GetProjectionMatrix( LCAMERA lCam, CMatrix *pMat );							///< プロジェクションマトリックス取得
	static void GetViewMatrix( LCAMERA lCam, CMatrix *pMat );								///< ビューマトリックス取得
	static void GetCameraMatrix( LCAMERA lCam, CMatrix *pMat );								///< カメラマトリックス取得
	static void GetPosition( LCAMERA lCam, CVector3D *pPos );								///< カメラ位置取得

	static void CreateProjection( LCAMERA lCam, Float fFovY, Float fNearZ, Float fFarZ, Float fAspect );	///< 透視変換用行列生成
	static void CreateOrtho( LCAMERA lCam, Float Width, Float Height, Float fNearZ, Float fFarZ );			///< 正射影行列生成

	static void TransformUpdate( LCAMERA lCam );											///< カメラ変換更新
	static void TransformInit( LCAMERA lCam );												///< カメラ変換初期化

	static void Heading( LCAMERA lCam, Sint32 Rot );										///< カメラヘッディング
	static void Pitching( LCAMERA lCam, Sint32 Rot );										///< カメラピッチング
	static void Rolling( LCAMERA lCam, Sint32 Rot );										///< カメラローリング
	static void RotationX( LCAMERA lCam, Sint32 Rot );										///< カメラＸ軸回転
	static void RotationY( LCAMERA lCam, Sint32 Rot );										///< カメラＹ軸回転
	static void RotationZ( LCAMERA lCam, Sint32 Rot );										///< カメラＺ軸回転
	static void Translation( LCAMERA lCam, Float fPx, Float fPy, Float fPz );				///< カメラ移動
	static void LookAt( LCAMERA lCam, CVector3D *pEye, CVector3D *pAt, CVector3D *pUp );		///< カメラを任意の点から任意の点を注視するようにする

	static Bool ViewfrustumCulling( BOX3D *pBox );											///< ビューフラスタムカリング実行

	static Sint32 GetAngleX( LCAMERA lCam );												///< Ｘ角度取得
	static Sint32 GetAngleY( LCAMERA lCam );												///< Ｙ角度取得
	static Sint32 GetAngleZ( LCAMERA lCam );												///< Ｚ角度取得

	static void SetFront( LCAMERA lCam, CVector3D *pVec );									///< カメラの姿勢データのを前方向ベクトル設定
	static void SetRight( LCAMERA lCam, CVector3D *pVec );									///< カメラの姿勢データのを右方向ベクトル設定
	static void SetUp( LCAMERA lCam, CVector3D *pVec );										///< カメラの姿勢データのを上方向ベクトル設定
	static void GetFront( LCAMERA lCam, CVector3D *pVec );									///< カメラの姿勢データのを前方向ベクトル取得
	static void GetRight( LCAMERA lCam, CVector3D *pVec );									///< カメラの姿勢データのを右方向ベクトル取得
	static void GetUp( LCAMERA lCam, CVector3D *pVec	);										///< カメラの姿勢データのを上方向ベクトル取得
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// STRUCT
//=============================================================================
/**
	@brief	CDトラックデータ

	LunaCDDAクラスで使用される、CDトラックデータを<BR>
	管理するための構造体です
*/
struct TRACKDATA
{
	Uint32 TrackStart;				///< トラック開始位置
	Uint32 TrackLength;				///< トラック終了位置
};


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	CDDA再生クラス

	ＭＣＩを用いてCDDAを再生するためのクラスです。
	基本的な指定トラック再生から、ループ再生、一時停止
	などをサポートしています。
*/
class LunaCDDA
{
protected:
	static TRACKDATA *m_pTrackData;								///< トラックデータ	
	static Uint32 m_TrackMax;									///< トラック最大数

	static Uint32 m_StartPos;									///< 再生開始位置
	static Uint32 m_EndPos;										///< 再生終了位置
	static Uint32 m_CurrenrPos;									///< 現在位置（一時停止用）
	static Sint32 m_StartTrack;									///< 開始トラック番号
	static Sint32 m_EndTrack;									///< 最終トラック番号

	static Uint32 m_DeviceID;									///< デバイスID
	static char m_DeviceName[32];								///< デバイス名（A:とかB:とかC:とか）

	static Bool m_IsOpen;										///< デバイスオープン中か否か
	static Bool m_IsPlay;										///< 再生中か否か
	static Bool m_IsPause;										///< 一時停止中か否か
	static Bool m_IsLoop;										///< ループ中か否か

public:
	static Bool Initialize( void );											///< クラス初期化
	static void Finalize( void );											///< クラス解放
	static Bool Replay( WPARAM wParam, LPARAM lParam );						///< リプレイ処理用

	static Bool Eject( Bool IsEject );										///< CD排出

	static Bool Open( const char *pDeviceName );							///< デバイスオープン
	static void Close( void );												///< デバイスクローズ

	static Bool Stop( void );												///< 停止
	static Bool Pause( void );												///< 一時停止
	static Bool Replay( void );												///< リプレイ
	static Bool Play( Bool IsLoop = false );								///< 全体再生
	static Bool Play( Sint32 Track, Bool IsLoop = false );					///< 一曲再生
	static Bool Play( Sint32 Track1, Sint32 Track2, Bool IsLoop = false );	///< 曲指定再生
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	文字関連クラス

	基本的な文字列操作関連のクラスです。
	文字コードの取得、半角から全角への変換、
	文字列中から数字、文字列の取得など、
	各種サポート関数が用意されています。
*/
class LunaChara
{
public:
	static void Code2Str( Uint16 Code, char *pStr );														///< 文字コードから文字を取得する
	static Uint16 GetCharCode( const unsigned char *pStr );													///< 指定文字から文字コードを取得する
	static Sint32 GetCharCodeEx( const unsigned char *pStr, Uint16 *pCode );								///< 文字列から文字コードを取得
	static Bool IsKanji( unsigned char Chara );																///< 全角文字か調べる
	static Bool IsKana( unsigned char Chara );																///< 半角カナか調べる
	static Sint32 GetString( char Chara, const unsigned char *pSrc, unsigned char *pDst );					///< 文字列から"で囲まれた文字列を取得
	static Sint32 GetString( char Chara1, char Chara2, const unsigned char *pSrc, unsigned char *pDst );	///< 文字列から指定文字に囲まれた文字列を取得
	static Sint32 GetNumber( const unsigned char *pSrc, Sint32 *pNum );										///< 文字列から数字を取得
	static Sint32 Hankaku2Zenkaku( const unsigned char *pSrc, unsigned char *pDst );						///< 指定半角文字を全角文字に変換
	static void Hankaku2ZenkakuStr( const unsigned char *pSrc, unsigned char *pDst );						///< 文字列中の半角を全角に変換
	static void Euc2Jis( unsigned char *pDst, const unsigned char *pSrc );									///< Euc  -> Jis  変換
	static void Jis2Euc( unsigned char *pDst, const unsigned char *pSrc );									///< Jis  -> Euc  変換
	static void Jis2SJis( unsigned char *pDst, const unsigned char *pSrc );									///< Jis  -> SJis 変換
	static void SJis2Jis( unsigned char *pDst, const unsigned char *pSrc );									///< Sjis -> Jis  変換
	static void Euc2SJis( unsigned char *pDst, const unsigned char *pSrc );									///< Euc  -> SJis 変換
	static void SJis2Euc( unsigned char *pDst, const unsigned char *pSrc );									///< SJis -> Euc  変換
	static void CopyUpper( unsigned char *pDst, const unsigned char *pSrc );								///< 小文字を大文字に変換しつつコピー
	static void CutAfterStr( char *pDst, const char *pSrc, char c );										///< 指定文字以下切捨てコピー
};





//======================================================================
// INCLUDE
//======================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	当たり判定クラス

	基本的な当たり判定処理を行うクラスです。
	２Ｄ関連の当たり判定は全て動作しますが、
	３Ｄ関連の当たり判定は未実装のものもあります。
*/
class LunaCollision
{
public:
	// ２Ｄ
	static Bool Point_Point( POINT2D *pPt1, POINT2D *pPt2 );												///< 点と線
	static Bool Point_Line( POINT2D *pPt, LINE2D *pLine );													///< 点と線
	static Bool Point_Rect( POINT2D *pPt, RECT2D *pRect );													///< 点と四角
	static Bool Point_Circle( POINT2D *pPt, CIRCLE2D *pCir );												///< 点と円
	static Bool Point_Polygon( POINT2D *pPt, POLYGON2D *pPoly );											///< 点と多角形
	static Bool Rect_Rect( RECT2D *pRect1, RECT2D *pRect2 );												///< 四角と四角
	static Bool Rect_Circle( RECT2D *pRect, CIRCLE2D *pCir );												///< 四角と円
	static Bool Rect_Line( RECT2D *pRect, LINE2D *pLine );													///< 四角と線
	static Bool Rect_Polygon( RECT2D *pRect, POLYGON2D *pPoly );											///< 四角と多角形
	static Bool Circle_Circle( CIRCLE2D *pCir1, CIRCLE2D *pCir2 );											///< 円と円
	static Bool Circle_Line( CIRCLE2D *pCir, LINE2D *pLine );												///< 円と線
	static Bool Circle_Polygon( CIRCLE2D *pCir, POLYGON2D *pPoly );											///< 円と多角形
	static Bool Line_Line( LINE2D *pLine1, LINE2D *pLine2 );												///< 線と線
	static Bool Line_Polygon( LINE2D *pLine, POLYGON2D *pPoly );											///< 線と多角形
	static Bool Polygon_Polygon( POLYGON2D *pPoly1, POLYGON2D *pPoly2 );									///< 多角形と多角形
	// ３Ｄ
	static Bool Point_Point_3D( POINT3D *pPt1, POINT3D *pPt2 );												///< 点と点
	static Bool Point_Sphere_3D( POINT3D *pPt, SPHERE3D *pSph );											///< 点と球
	static Bool Point_Line_3D( POINT3D *pPt, LINE3D *pLine );												///< 点と線
	static Bool Point_Plane_3D( POINT3D *pPt, PLANE3D *pPlane );											///< 点と面
	static Bool Point_Box_3D( POINT3D *pPt, BOX3D *pBox );													///< 点と箱
	static Bool Sphere_Sphere_3D( SPHERE3D *pSph1, SPHERE3D *pSph2 );										///< 球と球
	static Bool Sphere_Line_3D( SPHERE3D *pSph, LINE3D *pLine );											///< 球と線
	static Bool Sphere_Plane( SPHERE3D *pSph, PLANE3D *pPlane );											///< 球と面
	static Bool Sphere_Box_3D( SPHERE3D *pSph, BOX3D *pBox );												///< 球と箱
	static Bool Line_Plane_3D( LINE3D *pLine, PLANE3D *pPlane, POINT3D *pPoints, POINT3D *pPos );			///< 線と面
	static Bool Line_Box_3D( LINE3D *pLine, BOX3D *pBox );													///< 線と箱
	static Bool Line_Triangle_3D( LINE3D* pLine, POINT3D Points[], Float *pT, Float *pU, Float *pV );		///< 線と三角形
	static Bool Box_Box_3D( BOX3D *pBox1, BOX3D *pBox2 );													///< 箱と箱
	static Bool FrustumCulling( BOX3D *pFrustum, BOX3D *pBox );												///< ビューフラスタムと箱
	static Bool Plane_Plane_3D( PLANE3D *pPlane1, PLANE3D *pPlane2, POINT3D Points1[], POINT3D Points2[] );	///< 平面同士の判定

	// コリジョンデータ作成関数
	static void CreateBox( BOX3D *pOut, POINT3D *pMinPt, POINT3D *pMaxPt, CMatrix *pMatrix );				///< 箱生成
	static void CreateBoxProjection( BOX3D *pOut, POINT3D *pMinPt, POINT3D *pMaxPt, CMatrix *pMatrix );		///< 箱生成
	static void CreatePlaneFromPoint( PLANE3D *pOut, POINT3D *pPt0, POINT3D *pPt1, POINT3D *pPt2 );			///< 平面生成
	static void CreatePlane( PLANE3D *pOut, POINT3D *pPt, POINT3D *pNormal );								///< 平面生成

	static Bool PlaneIntersectLine( POINT3D *Intersection, PLANE3D *pPlane, POINT3D *pEdge0, POINT3D *pEdge1 );	///< 平面と直線の交点
	static Bool EdgeIntersectsQuad( POINT3D* pEdges, POINT3D* pFacePoints, PLANE3D* pPlane, POINT3D *pHitPos );	///< ４点で構成される平面と線分の交差判定
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	コンソール管理クラス

	コンソールを管理するためのクラスです。
	デバッグ処理などをより簡易的に行えるように
	なっています。
*/
class LunaConsole
{
protected:
	static Bool m_IsInit;											///< 初期化フラグ
	static HANDLE m_hConsole;										///< コンソールハンドル

public:
	static Bool Initialize( void );									///< クラスの初期化
	static void Finalize( void );									///< クラスの終了

	static Bool Create( void );										///< コンソール生成
	static void Release( void );									///< コンソール解体

	static void Clear( void );										///< 画面クリア
	static void Locate( Sint32 x, Sint32 y );						///< 位置指定
	static void Print( const char *pStr,... );						///< 出力
	static void Print( Sint32 x, Sint32 y, const char *pStr,... );	///< 位置指定付き出力
	static void SetColor( Uint16 Attributes );						///< 色設定
	static void CursorOff( void );									///< カーソルオフ
	static void CursorOn( void );									///< カーソルオン
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	デバッグ補佐クラス

	デバッグをサポートするクラスです。
	専用のデバッグウィンドウを開いての
	ログ表示や、ＶＣ＋＋のデバッグウィンドウへの
	文字列描画などを行うことが出来ます。
*/
class LunaDebug
{
protected:
	static HWND m_hListWnd;							///< デバッグ用ウィンドウのウィンドウハンドル

public:
	static Bool Initialize( void );					///< クラス初期化
	static void Finalize( void );					///< クラス解放

	static void OutputString( char *pStr,... );		///< 文字列をＶＣのデバッグウインドウに表示

	static Bool OpenWindow( void );					///< デバッグウインドウオープン
	static void CloseWindow( void );				///< デバッグウインドウクローズ
	static void DrawString( const char *pStr,... );	///< デバッグウインドウに文字列描画
	static void Clear( void );						///< 文字バッファクリア
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	プリミティブエフェクトクラス

	LunaPrimitiveのラッパークラスです。
	単純なポリゴンしか描画できないLunaPrimitive
	クラスに対して様々な形状のポリゴンを
	描画をサポートするラッパーになっています。
*/
class LunaEffect
{
public:
	static void FillRotate( LPRIMITIVE lPrim, CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 Angle );																		///< 回転可能ポリゴン描画
	static void FillRotateXYZ( LPRIMITIVE lPrim, CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );									///< ３軸回転可能ポリゴン描画

	static void FillTriangle( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color );																						///< 正三角形描画
	static void FillTriangleRotate( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color, Uint32 Angle );																	///< 回転可能正三角形描画
	static void FillTriangleRotateXYZ( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );									///< ３軸回転可能正三角形描画

	static void FillSquare( LPRIMITIVE lPrim, CLunaRect *pDstRect, Float fPosZ, D3DCOLOR Color );																									///< 四角形描画
	static void FillSquareRotate( LPRIMITIVE lPrim, CLunaRect *pDstRect, Float fPosZ, D3DCOLOR Color, Uint32 Angle );																				///< 回転可能四角形描画
	static void FillSquareRotateXYZ( LPRIMITIVE lPrim, CLunaRect *pDstRect, Float fPosZ, D3DCOLOR Color, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );												///< ３軸回転可能四角形描画

	static void FillPolygon( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color, Sint32 Num );																			///< 正多角形描画
	static void FillPolygonRotate( LPRIMITIVE lPrim, Float Px, Float Py, Float Radiust, Float fPosZ, D3DCOLOR Color, Sint32 Num, Uint32 Angle );													///< 回転可能正多角形描画
	static void FillPolygonRotateXYZ( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, D3DCOLOR Color, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );						///< ３軸回転可能正多角形描画

	static void FillRing( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num );										///< Ｚ軸リング描画
	static void FillRingRotate( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 Angle );					///< 回転可能Ｚ軸リング描画
	static void FillRingRotateXYZ( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );	///< ３軸回転可能Ｚ軸リング描画

	static void FillRingEx( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num );																///< Ｙ軸リング描画
	static void FillRingExRotate( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 Angle );											///< 回転可能Ｙ軸リング描画
	static void FillRingExRotateXYZ( LPRIMITIVE lPrim, Float Px, Float Py, Float Pz, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ );			///<　３軸回転可能Ｙ軸リング描画

	static void CircleFade( LPRIMITIVE lPrim, LTEXTURE lTex, CLunaRect *pSrc, Sint32 Divide, Sint32 Side, Sint32 Alpha, Bool IsSmooth );																///< 円状フェード描画
	static void CircleRoundFade( LPRIMITIVE lPrim, LTEXTURE lTex, CLunaRect *pSrc, Sint32 Divide, Sint32 Side, Sint32 Alpha, Bool IsSmooth );														///< 円状回転フェード描画
};




//==========================================================================
// INCLUDE
//==========================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	ＦＥＰ関連クラス

	FEPを操作するクラスです。
	OSで使用しているFEPを用いた
	基本的な入力処理をサポートしています
*/
class LunaFEP
{
	enum { FEP_BUFFER_SIZE = 2048 };

protected:
	static HWND				m_hWnd;							///< ウィンドウハンドル
	static HIMC				m_hImc;							///< FEPハンドル
	static CANDIDATELIST	*m_pCandidateList;				///< 辞書リストポインタ
	static char				m_String[FEP_BUFFER_SIZE];		///< 入力文字列格納バッファ
	static Sint32			m_Position;						///< カーソル番号
	static char				m_IsLastChara;					///< 最終文字
	static char				m_StrTbl[5][1024];				///< 文字列バッファ

public:
	static Bool Initialize( void );							///< クラス初期化
	static void Finalize( void );							///< クラス解放

	static Bool IsOpen( void );										///< ＦＥＰオープン中か否か
	static void BackChara( void );									///< 最終文字削除
	static void AddChara( Uint32 Chara );							///< 文字追加
	static Sint32 GetConvertPos( void );							///< 変換位置取得
	static Sint32 GetCursorCount( void );							///< カーソル位置取得
	static Sint32 GetCountCandidate( void );						///< 辞書文字列数取得
	static Sint32 GetCandidateStart( void );						///< 辞書開始位置取得
	static Sint32 GetCandidateCount( void );						///< 辞書データ数取得
	static Sint32 GetCandidateIndex( void );						///< 辞書インデックス取得
	static void GetCandidateString( char *pStr, Sint32 Index );		///< 該当辞書文字取得
	static Bool GetStatus( char *pStr );							///< 状態取得
	static void GetConvertString( char *pStr );						///< 変換中文字列取得
	static void GetInputString( char *pStr );						///< 入力済み文字列取得
	static void ClearInputString( void );							///< 入力済み文字列バッファ初期化
	static Bool LunaFEP::Notify( Uint32 Action, Uint32 Index, Uint32 Value );	///< 入力コンテキストの状態変更に関する情報を IME に知らせます

	static void RefreshStatus( void );								///< 状態更新
	static Bool GetStringTbl( char *pStatus, char *pInput1, char *pConvert1, char *pConvert2, char *pInput2 );	///< 文字列テーブル取得

	static HIMC GetHandle( void );									///< ＩＭＣハンドル取得
};



//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
#ifndef __TOOL_MODE__

/**
	@brief	ファイバークラス

	スレッドよりも軽く容易に並列処理を実現できます。
*/
class LunaFiber
{
private:
	static void UpdateFiberList( void );					///< ファイバーリスト更新

public:
	static Bool Initialize( void );							///< クラス初期化
	static void Finalize( void );							///< クラス解放

	static Bool Start( void );								///< ファイバー処理スタート

	static Bool Switch( Uint32 FiberId );					///< ファイバー切り替え

	static Bool Create( Uint32 FiberId, PFIBERPROC pProcMain, Uint32 StackSize );	///< ファイバー生成
	static Bool Exit( Uint32 FiberId );						///< ファイバー終了

	static void Suspend( Uint32 FiberId );					///< ファイバー一時停止
	static void Resume( Uint32 FiberId );					///< ファイバー再開

	static Float GetCPUTime( Uint32 FiberId );				///< ＣＰＵ使用時間取得
};

#endif



//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	ハイトフィールドクラス

	屋外型マップを管理するためのハイトフィールドクラスです。
	といっても実際には高さマップからの生成ではなく、
	Ｘファイルからのクオードツリー型フィールド管理クラスです。
*/
class LunaField
{
protected:
	static LUNAFIELDDATA *m_pField;																						///< フィールドデータポインタ
	static Uint32 m_FieldMax;																							///< フィールド最大数

protected:
	static void Init( LFIELD lField );																					///< フィールドデータ初期化
	static Bool Delete( LFIELD lField );																				///< フィールドデーア削除
	static void DeleteFrame( void *pData );																				///< フレーム削除
	static void DeleteMesh( void *pData );																				///< メッシュ削除
	static LFIELD GetFreeHandle( void );																				///< 未使用オブジェクトハンドル取得

	static void MeshInit( void *pData );																				///< メッシュ初期化
	static void FrameInit( void *pData );																				///< フレーム初期化

	static void RenderingFrame( LFIELD lField, void *pData );															///< フレームレンダリング
	static Sint32 SearchMeshNoFromPoint( void *pFrame, LFIELD lField, CVector3D *pPos );									///< 任意の点がどのメッシュ内にいるかを検索
	static void CreateQuadTree( void *pFrame, LFIELD lField, Sint32 Px, Sint32 Pz, Sint32 Count );						///< クオードツリーの作成
	static void CullQuadTree( void *pFrame, LFIELD lField );															///< クオードツリーのカリング
	static Bool UpdateVertexIndexBuffer( LFIELD lField );																///< 頂点・インデックスバッファ更新
	static Bool ConvertMeshToField( LFIELD lField, ID3DXMesh *pMesh, Sint32 TreeDepth, Sint32 ZoomSize );				///< メッシュデータをフィールドデータにコンバート
	static void SendToShaderConstant( void *pData0, void *pData1 );														///< シェーダーにデータを転送

	static LFIELD LoadFromMemory( void *pData, Uint32 Size, Sint32 TreeDepth, Sint32 ZoomSize, eSurfaceFormat Format, Bool IsBumpMap, D3DCOLOR KeyColor );	///< メモリからデータを読み込み

public:
	static Bool Initialize( void );																						///< フィールドシステム初期化
	static void Finalize( void );																						///< フィールドシステム解放
	static void Reset( void );																							///< フィールドデータリセット
	static void Restore( void );																						///< フィールドデータリストア
	static void SetMax( Uint32 Max );																					///< 最大フィールド使用量設定
	static void Release( LFIELD lField );																				///< フィールドデータ解放

	static void SetEffectHandle( LFIELD lField, LSHADERFX lShaderFx );													///< エフェクトファイルをフィールドに設定
	static void SetEffectSendData( LFIELD lField, Uint32 SendData );													///< エフェクトファイルへの送信データ
	static void ChangeShaderVersion( LFIELD lField, Uint16 Major, Uint16 Minor );										///< 使用するシェーダーのバージョンを変更
	static void SetTexture( LFIELD lField, Uint32 Stage, LTEXTURE lTex, Sint32 MateriaNo = -1 );						///< フィールドへテクスチャ設定

	static LFIELD CreateFromMemory( void *pData, Uint32 Size, Sint32 TreeDepth, Sint32 ZoomSize = -1, eSurfaceFormat Format = FORMAT_TEXTURE_3D, Bool IsBumpMap = false, D3DCOLOR KeyColor = COLORKEY_DISABLE );	///< メモリからデータを読み込み
	static LFIELD CreateFromFile( const char *pFileName, Sint32 TreeDepth, Sint32 ZoomSize = -1, eSurfaceFormat Format = FORMAT_TEXTURE_3D, Bool IsBumpMap = false, D3DCOLOR KeyColor = COLORKEY_DISABLE );			///< ファイルからフィールドデータを生成

	static void ViewfrustumCulling( LFIELD lField );																	///< ビューフラスタムカリング
	static Sint32 Rendering( LFIELD lField );																			///< フィールドレンダリング
	static Float RenderingTimer( LFIELD lField );																		///< フィールドレンダリング
	static Sint32 GetCellCount( LFIELD lField );																		///< セル数取得
	static Bool IsDrawCell( LFIELD lField, Sint32 Px, Sint32 Pz );														///< セル描画有無取得

	static Bool CheckCrossLine( LFIELD lField, CVector3D *pPos0, CVector3D *pPos1, CVector3D *pOut );						///< ２点を結ぶ線分とポリゴンの交差判定
	static Sint32 SearchMeshNoFromPoint( LFIELD lField, CVector3D *pPos );												///< 任意の点がどのメッシュ内にいるかを検索
	static Bool GetHeightFromPoint( LFIELD lField, CVector3D *pPos, CVector3D *pOut, CVector3D *pNorm = NULL, Float *pDistance = NULL );///< 任意の点から任意方向でのフィールド内の高さを求める
	static Bool GetNearPointFromPoint( LFIELD lField, CVector3D *pPos, CVector3D *pDir, CVector3D *pOut, CVector3D *pNorm = NULL, Float *pDistance = NULL );///< 任意の点から任意方向でのフィールド内の最近点を求める
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
	@brief	ファイルシーク定義

	LunaFileクラスで使用されるファイルシークの方法を表す定義。
*/
enum eSeekFlag
{
	SEEK_FILE_CURRENT,					///< カレント位置
	SEEK_FILE_START,					///< 先頭位置
	SEEK_FILE_END,						///< 終端位置
};

//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	ファイル管理クラス

	ファイルを管理するためのクラスです。
	標準対応ツールである、LLZSS、LPACKからの
	読み出しのサポートもしています。
*/
class LunaFile
{
protected:
	static char m_CurrentDirectory[MAX_PATH];
	static FILE_SEARCH_LIST m_FileSearchList[FILE_SEARCH_MAX];

protected:
	static Bool GetFileAddress( HANDLE hFile, const char *pFile, Uint32 *pAddress, Uint32 *pSize, Uint32 *pCrc );	///< ファイルアドレスの取得
	static Bool DecodeData( void **ppData, Uint32 *pSize );															///< データのデコード

public:
	static Bool Initialize( void );																					///< ファイルクラス初期化
	static void Finalize( void );																					///< ファイルクラス解放

	static Bool IsFileExistInPack( const char *pFile );																///< パック内ファイル存在チェック

	static Bool Load( const char *pFile, void **ppData, Uint32 *pSize );											///< ファイルを読み込む
	static Bool LoadFromFile( const char *pFile, void **ppData, Uint32 *pSize );									///< ファイルを読み込む
	static Bool LoadFromPack( const char *pFile, const char *pPack, void **ppData, Uint32 *pSize );					///< パックファイルから該当ファイルを読み込む
	static Bool LoadFromResource( const char *pFile, const char *pResource, void **ppData, Uint32 *pSize );			///< リソースからファイルを読み込み

	static FILEDATA *FileOpen( const char *pFile, Bool ReadOnly = false );											///< 指定ファイルのファイルハンドルを取得
	static FILEDATA *FileOpenFromFile( const char *pFile, Bool ReadOnly = false );									///< 指定ファイルのファイルハンドルを取得
	static FILEDATA *FileOpenFromPack( const char *pFile, const char *pPack, Bool ReadOnly = false );				///< パックファイル内のしてファイルのファイルハンドルを取得
	static void FileClose( FILEDATA *pFile );																		///< ファイルクローズ
	static Uint32 FileGetSize( FILEDATA *pFile );																	///< ファイルサイズ取得
	static Uint32 FileGetPosition( FILEDATA *pFile );																///< ファイル位置取得

	static Uint32 FileWrite( FILEDATA *pFile, Uint32 Size, void *pData );											///< ファイル書き込み
	static Uint32 FileRead( FILEDATA *pFile, Uint32 Size, void *pData );											///< ファイル読み込み
	static Bool FileSeek( FILEDATA *pFile, Uint32 Offset, eSeekFlag Flag );											///< ファイルシーク

	static Uint32 GetCRC( Uint8 Data[], Sint32 Size );																///< データのCRC32を取得

	static void SetCurrentDirectory( char *pCurrentDir );															///< 読込先カレントディレクトリを設定
	static void SetRootPath( Uint32 Priority, const char *pRootPath, const char *pPackFile );						///< 読込先のルート

	static Bool GetFilePath( char *pFilePath, const char *pSrcFile );												///< データごとのパス取得
	static Bool CopyFileToTempDir( const char *pSrcFile, char *pFilePath );											///< テンポラリディレクトリにパックの中身をコピー
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	フォント関連クラス

	単純なフォント描画をサポートするクラスです。
	バックバッファ、テクスチャ、オフスクリーン
	サーフェイスへのフォント描画処理をサポートします。
*/
class LunaFont
{
protected:
	static LibLuna::CFontMgr *m_pFontMgr;

public:
	static Bool Initialize( void );																				///< クラス初期化
	static void Finalize( void );																				///< クラス解放

	static LFONT Create( const char *pFontFace, Sint32 FontSize, Bool IsItalic = false, Bool IsBold = false );	///< フォントオブジェクト生成
	static void Release( LFONT lFont );																			///< フォントオブジェクト解放

	static Sint32 GetFontSize( LFONT lFont );																	///< フォントサイズ取得
	static Sint32 GetTextWidth( LFONT lFont, const char *pStr );												///< 文字列の最大横幅取得
	static void GetFontData( LFONT lFont, Uint16 Code, ABC *pABC );												///< フォントデータ取得
	static Bool GetWidth( LFONT lFont, const char *pStr, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight );	///< 文字幅取得
	static void SetDestination( LFONT lFont, LTEXTURE lTarget = INVALID_TEXTURE );								///< 描画先設置

	static void Begin( LFONT lFont, Bool IsUpdate = true );														///< フォント処理開始
	static void End( void );																					///< フォント処理終了
	static void DrawChar( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );									///< 文字描画
	static void DrawCharAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, Uint16 Code );								///< アンチエイリアス付き文字描画
	static Sint32 DrawText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< テキスト描画
	static Sint32 DrawTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< アンチエイリアス付きテキスト描画
	static Sint32 DrawPText( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );						///< プロポーショナルテキスト描画
	static Sint32 DrawPTextAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr,... );					///< アンチエイリアス付きプロポーショナルテキスト描画
	static Sint32 DrawTextDirect( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< テキスト描画
	static Sint32 DrawTextDirectAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< アンチエイリアス付きテキスト描画
	static Sint32 DrawPTextDirect( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );						///< プロポーショナルテキスト描画
	static Sint32 DrawPTextDirectAA( Sint32 Px, Sint32 Py, D3DCOLOR Color, const char *pStr );					///< アンチエイリアス付きプロポーショナルテキスト描画
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	フォントスプライト管理クラス

	スプライト形式のフォント描画クラスです。
	事前にテクスチャにフォントを敷き詰め、
	UVテーブルを作成しておき、テーブルアクセスから、
	任意の文字をテクスチャから切り出して描画
	するような構造になっています。
	性質上、単純な文字描画よりも高速に処理でき、
	エフェクトなども容易につけられますが、
	全ての文字をテクスチャに展開しておくため、
	使用メモリは増えてしまいます。
*/
class LunaFontSprite
{
protected:
	static LibLuna::CFontSprite2DMgr *m_pFontSprMgr;

public:
	static Bool Initialize( void );															///< クラス初期化
	static void Finalize( void );															///< クラス解放

	static LFONTSPRITE Create( const char *pBuffer, Bool IsAlpha, Uint32 Num, LFONT lFont, Bool IsSortZ = false, Bool IsAntialias = true );	///<フォントオブジェクト生成
	static LFONTSPRITE CreateFromFile( const char *pFileName, const char *pExt, Bool IsAlpha, Uint32 Num, Bool IsSortZ = false );		///< フォントオブジェクトをLFDから生成

	static void DisableHankakuSizeHalf( LFONTSPRITE lFontSpr );															///< 半角文字のサイズを1/2にするのを止める

	static Bool ReCreateStringBuffer( LFONTSPRITE lFontSpr, const char *pBuffer, Uint32 Num );			///<フォントオブジェクト再生成

	static void Release( LFONTSPRITE lFontSpr );											///< フォントオブジェクト解放
	static void BufferResize( LFONTSPRITE lFontSpr, Uint32 Count );							///< バッファサイズ再設定

	static Bool GetWidth( LFONTSPRITE lFontSpr, const char *pStr, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight );	///< 文字幅取得
	static void GetHeight( LFONTSPRITE lFontSpr, Sint32 *pHeight );							///< フォント高さ取得
	static void ResetBuffer( LFONTSPRITE lFontSpr, Sint32 Space = 0 );							///< フォントバッファ初期化
	static void UpdateBuffer( LFONTSPRITE lFontSpr );										///< フォントバッファ更新
	static void Rendering( LFONTSPRITE lFontSpr );											///< フォントバッファレンダリング

	static void DrawString( LFONTSPRITE lFontSpr, const char *pStr, Sint32 Px, Sint32 Py, Float Pz, D3DCOLOR Color );		///< テキスト描画
	static void DrawStringP( LFONTSPRITE lFontSpr, const char *pStr, Sint32 Px, Sint32 Py, Float Pz, D3DCOLOR Color );		///< プロポーショナルフォントテキスト描画
	static Sint32 DrawChara( LFONTSPRITE lFontSpr, const char *pStr, CLunaRect *pDst, Float Pz, D3DCOLOR Color );			///< 文字描画
	static Sint32 DrawCharaRotate( LFONTSPRITE lFontSpr, const char *pStr, CLunaRect *pDst, Float Pz, D3DCOLOR Color, Sint32 Angle );	///< 回転文字描画
	static Sint32 DrawCharaRotateXYZ( LFONTSPRITE lFontSpr, const char *pStr, CLunaRect *pDst, Float Pz, D3DCOLOR Color, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );	///< ３軸回転文字描画

	static POINT GetStringLastPos( LFONTSPRITE lFontSpr, const char *pStr, Sint32 Px, Sint32 Py );	///< 描画時最終位置取得
	static POINT GetStringLastPosP( LFONTSPRITE lFontSpr, const char *pStr, Sint32 Px, Sint32 Py );	///< プロポーショナルフォント描画時最終位置取得
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	フォントスプライト管理クラス

	スプライト形式のフォント描画クラスです。
	事前にテクスチャにフォントを敷き詰め、
	UVテーブルを作成しておき、テーブルアクセスから、
	任意の文字をテクスチャから切り出して描画
	するような構造になっています。
	性質上、単純な文字描画よりも高速に処理でき、
	エフェクトなども容易につけられますが、
	全ての文字をテクスチャに展開しておくため、
	使用メモリは増えてしまいます。
*/
class LunaFontSprite3D
{
protected:
	static LibLuna::CFontSprite3DMgr *m_pFontSprMgr;

public:
	static Bool Initialize( void );												///< クラス初期化
	static void Finalize( void );												///< クラス解放

	static LFONTSPRITE3D Create( const char *pBuffer, Bool IsAlpha, Uint32 Num, LFONT lFont, Bool IsAntialias = true );	///<フォントオブジェクト生成
	static LFONTSPRITE3D CreateFromFile( const char *pFileName, const char *pLagName, Bool IsAlpha, Uint32 Num );		///< フォントオブジェクトをLFDから生成

	static Bool ReCreateStringBuffer( LFONTSPRITE3D lFontSpr, const char *pBuffer, Uint32 Num );			///<フォントオブジェクト再生成

	static void BufferResize( LFONTSPRITE3D lFontSpr, Uint32 Count );							///< バッファサイズ再設定
	static void Release( LFONTSPRITE3D lFontSpr );											///< フォントオブジェクト解放

	static void ResetBuffer( LFONTSPRITE3D lFontSpr );										///< フォントバッファ初期化
	static void UpdateBuffer( LFONTSPRITE3D lFontSpr );										///< フォントバッファ更新
	static void Rendering( LFONTSPRITE3D lFontSpr );										///< フォントバッファレンダリング

	static void DrawString( LFONTSPRITE3D lFontSpr, const char *pStr, CStyle *pStyle, Float fScale, D3DCOLOR Color );	///< 文字列描画
	static void DrawStringP( LFONTSPRITE3D lFontSpr, const char *pStr, CStyle *pStyle, Float fScale, D3DCOLOR Color );	///< プロポーショナルフォントテキスト描画
};





//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// ENUM
//=============================================================================
/**
	@brief	POV角度定数
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
	@brief	キーステータス定義

	LunaPadクラスで使用されるキーの各種状態定義。
*/
enum eKeyState
{
	KEY_STATE_FREE,						///< キーはフリー状態
	KEY_STATE_PULL,						///< キーは離された瞬間
	KEY_STATE_PUSH,						///< キーは押された瞬間
	KEY_STATE_HOLD,						///< キーは押され続けている
};

/**
	@brief マウスボタン状態定義

	各種ボタンの状態定義。
*/
enum eMouseState
{
	MOUSE_FREE,							///< マウスボタンは押されていない
	MOUSE_PULL,							///< マウスボタンは離された
	MOUSE_PUSH,							///< マウスボタンは押された
	MOUSE_HOLD,							///< マウスボタンは押されつづけている
};

/**
	@brief	パッドステート定義

	LunaPadクラスで使用されるパッドの各種状態定義。
*/
enum ePadState
{
	PAD_STATE_PUSH,						///< 押した瞬間取得用
	PAD_STATE_PULL,						///< 離した瞬間取得用
	PAD_STATE_HOLD,						///< 押し続け取得用
	PAD_STATE_REPEAT,					///< リピート取得用

	PAD_STATE_MAX,
};

/**
	@brief	パッド用各種ボタン定義

	LunaPadクラスで使用される各種ボタンの定義。
*/
enum ePadSort
{
	PAD_DIR_UP,							///< 上方向指定
	PAD_DIR_DOWN,						///< 下方向指定
	PAD_DIR_LEFT,						///< 左方向指定
	PAD_DIR_RIGHT,						///< 右方向指定

	PAD_BUTTON_01,						///< ボタン１指定
	PAD_BUTTON_02,						///< ボタン２指定
	PAD_BUTTON_03,						///< ボタン３指定
	PAD_BUTTON_04,						///< ボタン４指定
	PAD_BUTTON_05,						///< ボタン５指定
	PAD_BUTTON_06,						///< ボタン６指定
	PAD_BUTTON_07,						///< ボタン７指定
	PAD_BUTTON_08,						///< ボタン８指定
	PAD_BUTTON_09,						///< ボタン９指定
	PAD_BUTTON_10,						///< ボタン１０指定
	PAD_BUTTON_11,						///< ボタン１１指定
	PAD_BUTTON_12,						///< ボタン１２指定
	PAD_BUTTON_13,						///< ボタン１３指定
	PAD_BUTTON_14,						///< ボタン１４指定
	PAD_BUTTON_15,						///< ボタン１５指定
	PAD_BUTTON_16,						///< ボタン１６指定

	PAD_SORT_MAX,

	PAD_SORT_NONE,						///< 無効

	PAD_BUTTON_MAX	= (PAD_BUTTON_16 - PAD_BUTTON_01),
};


//=============================================================================
// STRUCT
//=============================================================================
/**
	@brief	軸データ

	LunaInputクラスで使用される、入力デバイスの軸を<BR>
	管理するための構造体です
*/
struct AXISDATA
{
	Sint32 Ax;								///< Ｘ軸
	Sint32 Ay;								///< Ｙ軸
	Sint32 Az;								///< Ｚ軸
};

/**
	@brief	パッド情報データ

	LunaPadクラスで使用される、パッド情報データを<BR>
	管理するための構造体です
*/
struct PADSTATUS
{
	Sint32 KeyState[PAD_STATE_MAX];			///< キー状態データ
};

/**
	@brief	パッドデータヘッダ

	LunaPadクラスで使用される、パッド保存用データのヘッダ<BR>
	構造体です
*/
struct PADSAVEHEADER
{
	char Guid[4];								///< ファイル識別用
	Sint32 LayerMax;							///< レイヤー数
	Sint32 FrameMax;							///< フレーム数
};

/**
	@brief	マウスデータ

	マウスデータを格納するための構造体。
*/
struct MOUSEDATA
{
	Sint32 X;							///< Ｘ位置
	Sint32 Y;							///< Ｙ位置
	Sint32 W;							///< Ｚ位置

	Sint32 Mx;							///< Ｘ移動量
	Sint32 My;							///< Ｙ移動量

	Bool ClickL;						///< 左クリック
	Bool ClickR;						///< 右クリック
	Bool ClickW;						///< ホイールクリック

	Bool DoubleClickL;					///< 右ダブルクリック
	Bool DoubleClickR;					///< 左ダブルクリック
	Bool DoubleClickW;					///< ホイールダブルクリック

	eMouseState StateL;					///< 左ボタン状態
	eMouseState StateR;					///< 右ボタン状態
	eMouseState StateW;					///< ホイールボタン状態
};

/**
	@brief	キーボードデータ

	キーボードデータを受信するための構造体
*/
struct KEYBOARDDATA
{
	char Key[256];						///< 軸
};

/**
	@brief	ジョイスティックデータ

	ジョイスティック用データを格納しておくための構造体。
*/
struct JOYSTICKDATA
{
	Sint32 Px, Py, Pz;					///< 軸
	Sint32 Rx, Ry, Rz;					///< 回転軸
	Sint32 Vx, Vy, Vz;					///< 軸の速度
	Sint32 VRx, VRy, VRz;				///< 軸の角速度
	Sint32 Ax, Ay, Az;					///< 軸の加速度
	Sint32 ARx, ARy, ARz;				///< 軸の角加速度
	Sint32 Fx, Fy, Fz;					///< 軸のフォース
	Sint32 FRx, FRy, FRz;				///< 軸のトルク
	Sint32 Slider[2];					///< スライダー
	Sint32 Pov[4];						///< POV
	char Button[PAD_BUTTON_MAX];		///< ボタン
};

/**
	@brief	ジョイスティックデータデータ

	LunaInputクラスで使用される、ジョイスティックデータを<BR>
	管理するための構造体です
*/
struct JOYSTICKWORK
{
	JOYSTICKDATA Data;						///< ジョイスティックデータ
	AXISDATA Center;						///< 軸中心定義
	AXISDATA Max;							///< 軸最大値
	AXISDATA RotCenter;						///< 回転軸中心定義
	AXISDATA RotMax;						///< 回転軸最大値
	IDirectInputDevice8 *pDevice;			///< デバイス

	Bool IsPolling;							///< ポーリングがいるか否か
	Bool IsForceFeedback;					///< フォースフィードバックに対応しているか否か

	Sint32 LockKey;							///< ロックするキー
	Sint32 KeyState[PAD_STATE_MAX];			///< キー情報
	Sint32 KeyStateWork[2];					///< キー情報取得用ワーク
	Sint32 KeyRepeatCounter[PAD_SORT_MAX];	///< キーリピートカウンター
	Sint32 PadMap[PAD_SORT_MAX];				///< パッドマッピング情報
	Sint32 KeyAlias[PAD_SORT_MAX];			///< キーボードマッピング用

	Bool IsUsePOVDirection;					///< POV を方向キーに使用するかどうか
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
	static IDirectInput8			*m_pDirectInput;				///< DirectInputオブジェクト
	static IDirectInputDevice8		*m_pDevKeyboard;				///< キーボードデバイス
	static Uint32					m_JoystickMax;					///< ジョイスティック最大数
	static Uint32					m_JoystickCount;				///< ジョイスティック数
	static KEYBOARDDATA				m_KeyboardData;					///< キーボードデータ
	static MOUSEDATA				m_MouseData;					///< マウスデータ
	static JOYSTICKWORK				*m_pJoystickData;				///< ジョイスティックデータポインタ
	static DIDEVICEOBJECTDATA		m_KeyBuffer[KEY_BUFFER_MAX];	///< キーバッファ
	static Uint32					m_KeyBufferCount;				///< キーバッファカウント
	static Uint32					m_KeyBufferMax;					///< キーバッファ最大数
	static Bool						m_DoubleClickL;					///< 左ダブルクリックフラグ
	static Bool						m_DoubleClickR;					///< 右ダブルクリックフラグ
	static Bool						m_DoubleClickW;					///< ホイールダブルクリックフラグ

protected:
	static BOOL CALLBACK EnumAxisCallback( const DIDEVICEOBJECTINSTANCE* pdidoi, void *pContext );		///< 軸列挙用コールバック関数
	static BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, void* pContext );	///< パッド列挙用コールバック関数
	static Bool InitKeyboard( void );								///< キーボード初期化
	static Bool InitJoystick( void );								///< ジョイスティック初期化

	static Sint32 AdjustAxis( Sint32 axisSource, Sint32 axisCenter, Sint32 axisMax, Sint32 axisRange, Float deadZone );	///< 軸のアジャスト

	static void RefreshMouse( void );								///< マウス情報更新
	static void RefreshKeyboard( void );							///< キーボード情報更新
	static void RefreshKeyboardBuffer( void );						///< キーボードバッファ更新
	static void RefreshJoystick( void );							///< ジョイスティック更新

	static void Refresh( void );									///< デバイス情報更新

public:
	static Bool Initialize( void );									///< クラス初期化
	static void Finalize( void );									///< クラス解放

	static void SetCursorPos( POINT Pt );							///< マウス位置を設定

	static void SetMouseWheel( Sint16 w );							///< ホイール移動値設定
	static void SetDoubleClickL( void );							///< 左ダブルクリック設定
	static void SetDoubleClickR( void );							///< 右ダブルクリック設定
	static void SetDoubleClickM( void );							///< ホイールダブルクリック設定

	static void KeyBufferFlush( void );								///< キーバッファフラッシュ
	static Bool KeyBufferLoop( Uint32 *pKey );						///< キーバッファ取得ループ
	static Bool GetKeyData( Uint32 Key );							///< キーデータ取得
	static void GetMouseData( MOUSEDATA *pMouse );					///< マウスデータ取得
	static Bool GetJoystickData( Sint32 No, JOYSTICKDATA *pJoy );	///< ジョイスティックデータ取得
};


/**
	@brief	パッド簡易操作クラス

	LunaInputをより容易に扱えるようにした
	ラッパークラスです。
	各種方向ボタンをLunaInputのキーやボタンに
	マッピングすることで、キーコンフィグなども
	しやすく、各ボタンの詳細なデータを取得出来
	るようになっています。
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
	static Bool						m_IsUseAlias;					///< パッド別名定義フラグ
	static Sint32					m_UseMapPadMax;					///< 使用予定最大パッド数
	static Sint32					m_KeyRepeatTime;				///< キーリピート時間
	static Sint32					m_KeyRepeatInterval;			///< キーリピート間隔

protected:
	static void Refresh( void );																				///< パッド状態の更新

public:
	static void Initialize( Sint32 PadMax, Bool IsUseAlias, Sint32 KeyRepeatTime, Sint32 KeyRepeatInterval );	///< パッドシステムの初期化
	static void SetButton( Sint32 PadNo, ePadSort PadSort, Sint32 Button );										///< ボタン定義設定
	static void SetAlias( Sint32 PadNo, ePadSort PadSort, Sint32 KeyNo );										///< ボタンキーボード割り振り設定

	static void UsePOVDirection( Sint32 PadMax, Bool IsUse );													///< POV 方向キー使用可否設定
	static Bool IsUsePOVDirection( Sint32 PadMax );																///< POV 方向キーを使用するか否か

	static Bool IsPushAnyKey( Sint32 PadNo );																	///< ボタンロック
	static Bool GetState( Sint32 PadNo, ePadState PadState, ePadSort PadSort );									///< ボタン状態取得
	static void SetState( Sint32 PadNo, ePadState PadState, ePadSort PadSort );									///< ボタン状態設定
	static void SetLock( Sint32 PadNo, ePadSort PadSort );														///< ボタンロック
	static void SetUnlock( Sint32 PadNo, ePadSort PadSort );													///< ボタンロック

	static ePadSort CursorWrapUpDown( Sint32 PadNo, Sint32 *pCursor, Sint32 Max );								///< ラップ式上下カーソル処理
	static ePadSort CursorWrapLeftRight( Sint32 PadNo, Sint32 *pCursor, Sint32 Max );							///< ラップ式左右カーソル処理
	static ePadSort CursorClampUpDown( Sint32 PadNo, Sint32 *pCursor, Sint32 Max );								///< クランプ式上下カーソル処理
	static ePadSort CursorClampLeftRight( Sint32 PadNo, Sint32 *pCursor, Sint32 Max );							///< クランプ式左右カーソル処理
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// ENUM
//=============================================================================
/**
	@brief	ライトタイプ定義

	ライトの種類定義。
*/
enum eLightType
{
	LIGHT_DIRECTION,					///< 平行光源ライト
	LIGHT_POINT,						///< 点光源ライト
};


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	ライトクラス

	３Ｄ空間上に設置するライトを操作するためのクラスです。
	Lunaでは仕様上最大４つのディレクショナルライトと
	ポイントライトをサポートしています。
	またこれらのライトは頂点シェーダー2.0からサポートされた
	分岐命令により切り替えのコストは発生しません。
*/
class LunaLight
{
	friend class Luna3D;

protected:
	static D3DLIGHT9 m_Lights[LIGHT_MAX];			///< ライトデータ
	static Bool m_IsActiveLights[LIGHT_MAX];		///< ライト使用フラグ
	static D3DCOLORVALUE m_Ambient;					///< アンビエント

protected:
	static void SetDevice( Sint32 No, Bool IsActive );				///< デバイスに設定

public:
	static Bool Initialize( void );									///< クラス初期化
	static void Finalize( void );									///< クラス解放

	static void SetAmbient( Float r, Float g, Float b );			///< 環境光設定

	static void SetLightType( Sint32 No, eLightType Type );			///< ライトタイプ設定
	static void SetPosition( Sint32 No, CVector3D *pPos );			///< ライト位置設定
	static void SetDirection( Sint32 No, CVector3D *pDir );			///< ライト方向設定
	static void SetDiffuse( Sint32 No, Float r, Float g, Float b );	///< ライトディフューズ設定
	static void SetSpecular( Sint32 No, Float r, Float g, Float b );	///< ライトスペキュラ設定
	static void SetAttenuation( Sint32 No, Float Attenuation );		///< ライト減衰率設定

	static void GetLightDataForShader( SHADERLIGHTDATA *pData );	///< シェーダー用ライトデータ取得
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	ライン描画クラス

	２Ｄ上に単純なラインを描画するためのクラスです。
	機能的にはただ線分を引くだけの単純なもので
	このクラスに対するラッパーはまだありません。
*/
class LunaLine
{
	friend class Luna3D;

protected:
	static LibLuna::CLine2DMgr *m_pLineMgr;

protected:
	static void SetScissoring( Bool IsUse, RECT *pRect );								///< シザリング領域設定
	static void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );	///< パース補完データ設定
	static void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );		///< 拡大縮小設定

public:
	static Bool Initialize( void )	;													///< クラス初期化
	static void Finalize( void );														///< クラス解放
	static void Reset( void );															///< リセット
	static void Restore( void );														///< 復旧

	static LLINE Create( Uint32 VertexMax );											///< ラインオブジェクト生成

	static void Release( LLINE lLine );													///< ラインオブジェクト解放

	static void Rendering( LLINE lLine );												///< バッファレンダリング
	static void ResetBuffer( LLINE lLine );												///< バッファリセット
	static void UpdateBuffer( LLINE lLine );											///< バッファ更新

	static Bool PushRenderBuffer( LLINE lLine, CPrimitivePoint2D *pPoint, Uint32 Count );	///< バッファに描画データ追加
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	３Ｄライン描画クラス

	３Ｄ空間内にラインを描画するためのクラスです。
	このクラスは単純に線分を描画するだけであり、
	ラッパーもまだ用意されてません。
*/
class LunaLine3D
{
	friend class Luna3D;

protected:
	static LibLuna::CLine3DMgr *m_pLineMgr;

public:
	static Bool Initialize( void );																///< クラス初期化
	static void Finalize( void );																///< クラス解放
	static void Reset( void );																	///< リセット
	static void Restore( void );																///< 復旧

	static LLINE3D Create( Uint32 VertexMax );													///< ラインオブジェクト生成

	static void Release( LLINE3D lLine3D );														///< ラインオブジェクト解放

	static void TransformInit( LLINE3D lLine3D );												///< 変換初期化
	static void TransformUpdate( LLINE3D lLine3D );												///< 変換更新

	static void Heading( LLINE3D lLine3D, Sint32 Rot );											///< ヘッディング
	static void Pitching( LLINE3D lLine3D, Sint32 Rot );										///< ピッチング
	static void Rolling( LLINE3D lLine3D, Sint32 Rot );											///< ローリング
	static void RotationX( LLINE3D lLine3D, Sint32 Rot );										///< Ｘ軸回転
	static void RotationY( LLINE3D lLine3D, Sint32 Rot );										///< Ｙ軸回転
	static void RotationZ( LLINE3D lLine3D, Sint32 Rot );										///< Ｚ軸回転
	static void Translation( LLINE3D lLine3D, Float fPx, Float fPy, Float fPz );				///< 移動
	static void LookAt( LLINE3D lLine3D, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );		///< 注視

	static void Rendering( LLINE3D lLine3D );													///< バッファレンダリング
	static void ResetBuffer( LLINE3D lLine3D );													///< バッファリセット
	static void UpdateBuffer( LLINE3D lLine3D );												///< バッファ更新
	static Bool PushRenderBuffer( LLINE3D lLine3D, CPrimitivePoint3D *pPoint, Uint32 Count );	///< バッファに描画データ追加
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	LZSS管理クラス

	LZSSに関する処理を行うためのクラスです。
*/
class LunaLzss
{
protected:
	static Sint32 m_Dad[LZSS_RING_LENGTH+1];										///< 圧縮解凍用ワークデータポインタ
	static Sint32 m_LSon[LZSS_RING_LENGTH+1];										///< 圧縮解凍用ワークデータポインタ
	static Sint32 m_RSon[LZSS_RING_LENGTH+257];										///< 圧縮解凍用ワークデータポインタ
	static Sint32 m_MatchPos;														///< 最長一致位置
	static Sint32 m_MatchLen;														///< 最長一致長
	static Uint8 m_Text[LZSS_RING_LENGTH + LZSS_LONGEST_MATCH - 1];					///< テキストデータポインタ

protected:
	static void InitTree( void );													///< 木の初期化
	static void InsertNode( Sint32 r );												///< ノードを木に挿入
	static void DeleteNode( Sint32 p );												///< ノードを木から削除

public:
	static Sint32 GetOriginalSize( void *pSrc );									///< デコード後のオリジナルサイズ取得
	static Bool Decode( void *pSrc, void *pDst );									///< LZSSからのデコード
	static Bool Encode( void *pSrc, void *pDst, Uint32 SrcSize, Uint32 *pDstSize );	///< LZSSへのエンコード
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	算術クラス

	一般的に使用するであろう、算術処理を
	まとめたクラスです。
	サイン、コサイン、アークタンジェントのテーブルから
	使いやすくされた乱数取得関すなどが用意されています。
*/
class LunaMath
{
protected:
	static Float m_fSinTable[SIN_TABLE_SIZE];							///< サインテーブル
	static Uint32 m_fArcTanTable[ARCTAN_TABLE_SIZE+1];					///< アークタンジェントテーブル

public:
	static Float Sin( Sint32 Angle );									///< サイン取得
	static Float Cos( Sint32 Angle );									///< コサイン取得
	static void SinCos( Sint32 Angle, Float *pfSin, Float *pfCos );		///< サイン・コサイン取得
	static Sint32 Atan( Sint32 Dx, Sint32 Dy );							///< アークタンジェント取得
	static Sint32 Atan( Float Dx, Float Dy );							///< アークタンジェント取得

	static void RotationPoint( CLunaPoint *pPoint, Sint32 Angle );		///< 任意のポイントを回転させる
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	メディア再生クラス

	DirectShowを用いてメディアを再生するためのクラスです。
*/
class LunaMedia
{
protected:
	static MEDIADATA *m_pMedia;											///< メディア用オブジェクト
	static Uint32 m_MediaMax;											///< オブジェクト最大数

protected:
	static LMEDIA GetFreeHandle( void );								///< 未使用ハンドル取得
	static void Init( LMEDIA lMedia );									///< オブジェクト初期化
	static Bool Delete( LMEDIA lMedia );								///< オブジェクト削除

public:
	static Bool Initialize( void );										///< クラス初期化
	static void Finalize( void );										///< クラス解放

	static void HandleGraphEvent( void );								///< イベントハンドラ

	static void AddRef( LMEDIA lMedia );								///< 参照カウンタインクリメント
	static LMEDIA SearchHandle( const char *pFileName );				///< 同一ファイル検索

	static LMEDIA CreateFromAudio( const char *pFileName );				///< メディアオブジェクトの生成

	static void Release( LMEDIA lMedia );								///< オブジェクト解放

	static void Play( LMEDIA lMedia, Bool bLoop = false );				///< 再生
	static void Stop( LMEDIA lMedia );									///< 停止
	static void Pause( LMEDIA lMedia );									///< 一時停止
	static void SetVolume( LMEDIA lMedia, Float fParam );				///< ボリューム変更
	static void SetPan( LMEDIA lMedia, Float fParam );					///< パン移動
	static void SetSpeed( LMEDIA lMedia, Float fParam );				///< ボリューム変更
	static Bool IsPlay( LMEDIA lMedia );								///< 再生チェック
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	メモリ管理クラス

	メモリ管理を行うためのクラスです。
	初期化時にＯＳから使用する全メモリを
	一括で確保し、その領域から切り取って
	使用する構造になっています。
	メモリの境界オーバーチェックや
	解放忘れなどをチェックし、ファイル名とその
	行番号を出力することができます。
	メモリのコンパクションは行われませんので、
	アプリケーションによっては思わぬメモリ
	確保エラーを引き起こす可能性もあります。
*/
class LunaMemory
{
protected:
	static CRITICAL_SECTION m_CriticalSection;			///< クリティカルセクション
	static void *m_pDataAddr;							///< データアドレス
	static void *m_pDataAddrAligned;					///< アライメント後データアドレス
	static Uint32 m_MaxSize;							///< 最大サイズ
	static Uint32 m_UseMemory;							///< 使用中のサイズ
	static Uint32 m_MaxUseMemory;						///< 最大使用メモリ
	static Uint32 m_LastAllocMemorySize;				///< 最後に確保しようとしたメモリサイズ
	static Uint64 m_BaseGuid;							///< 終端チェック用識別子
	static Bool m_IsDebugMode;							///< デバッグモードか否か
	static Bool m_IsFastAlloc;							///< 高速モードか否か
	static Uint32 m_ListFree;							///< 未使用エリアリスト

protected:
	static void FreeListInsert( void *pAlloc );															///< 未使用エリアリストへ挿入
	static void FreeListErase( void *pAlloc );															///< 未使用エリアリストから削除
	static void Optimize( void *pData );																///< 指定メモリの前後を最適化
	static void *SearchFreeArea( Uint32 Size );															///< 未使用メモリ空間を検索
	static void *ComputeAddress( void *pAlloc, Uint32 Size, Uint32 RealSize );							///< 未使用メモリ空間から使用可能なメモリ空間のアドレスを取得

public:
	static Bool Initialize( void );																		///< メモリクラスの初期化
	static void Finalize( void );																		///< メモリクラスの解放

	static Bool SetWorkArea( Uint32 Size, Bool IsDebugMode );											///< 使用メモリ空間を設定
	static void SetTerminateGuid( Uint64 Guid );														///< 使用中のメモリ空間の終端識別子を設定

	static void *Alloc( Uint32 Size, const char *pFile, Sint32 Line );									///< メモリ確保
	static void *AllocLog( Uint32 Size, const char *pFile, Sint32 Line );								///< ログ出力用メモリ確保
	static void *ClearAlloc( Uint32 Size, const char *pFile, Sint32 Line );								///< ０クリア済みメモリ確保
	static void *ClearAllocLog( Uint32 Size, const char *pFile, Sint32 Line );							///< ログ出力用０クリア済みメモリ確保
	static void *ReAlloc( void *pOld, Uint32 Size, const char *pFile, Sint32 Line );					///< メモリ再確保
	static void *ReAllocLog( void *pOld, Uint32 Size, const char *pFile, Sint32 Line );					///< ログ出力用メモリ再確保

	static void Free( void *pAddr );																	///< メモリ解放
	static void FreeLog( void *pAddr );																	///< ログ出力用メモリ解放

	static void SetAllocMode( Bool IsFastMode );														///< メモリ確保モード
	static Uint32 GetRest( void );																		///< 残りメモリ容量取得
	static Bool CheckOverAccess( void );																///< メモリアクセスエラーをチェック
	static void Optimize( void );																		///< メモリ領域の最適化

	static Uint32 GetAllocLastSize( void );																///< 最後に確保しようとしたメモリサイズ

	static void RenderMap( LPRIMITIVE lPrim, Sint32 Px, Sint32 Py, Sint32 Width, Sint32 Height, D3DCOLOR Col1, D3DCOLOR Col2 );	///< メモリ使用状況をレンダリング

	static void PrintAlloc( void );																		///< 確保領域を出力
};


#ifndef __TOOL_MODE__

//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	マイクロスレッドクラス

	通常のスレッドをマイクロスレッド風に
	したものです。
	扱いは普通のスレッドよりも簡単ですが、
	使い方が邪道なので問題があるかもしれません。
*/
class LunaMicroThread
{
protected:
	static MICROTHREADDATA	*m_pThreadData;			///< スレッド用データ
	static PMICROTHREADPROC	m_pLoadProc;			///< ローダー関数
	static unsigned int		m_ThreadId;				///< スレッドID
	static HANDLE			m_Handle;				///< スレッドハンドル
	static Bool				m_IsSuccess;			///< 処理結果
	static Sint64			m_ThreadAllTimeOld;		///< 全スレッド処理時間
	static Float			m_ThreadAllTime;		///< 全スレッド処理時間
	static void				*m_pThreadProcTbl[32];	///< スレッド用関数

protected:
	static void UpdateThreadList( void );								///< マイクロスレッドリスト更新
	static void Terminate( Uint32 ThreadId );							///< マイクロマイクロスレッド終了

	static unsigned int __stdcall ThreadProc00( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc01( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc02( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc03( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc04( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc05( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc06( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc07( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc08( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc09( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc10( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc11( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc12( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc13( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc14( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc15( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc16( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc17( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc18( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc19( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc20( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc21( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc22( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc23( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc24( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc25( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc26( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc27( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc28( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc29( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc30( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProc31( void *pParam );			///< スレッド管理用関数
	static unsigned int __stdcall ThreadProcLoader( void *pParam );		///< スレッド用関数

public:
	static Bool Initialize( void );																					///< マイクロスレッドクラス初期化
	static void Finalize( void );																					///< マイクロスレッドクラス終了

	static void Start( void );																						///< マイクロマイクロスレッド始動
	static void End( void );																						///< マイクロマイクロスレッド終了
	static Bool StartLoadThread( PMICROTHREADPROC pLoadProc, void *pParam, Uint32 StackSize, Uint32 Priority = THREAD_PRIORITY_LOWEST );	///< データ読み込み用マイクロマイクロスレッド
	static Bool IsEndLoadThread( void );																			///< データ読み込みマイクロマイクロスレッド終了チェック
	static Bool IsSuccessLoadThread( void );																		///< データ読み込みマイクロマイクロスレッド成功チェック
	static void Exit( Uint32 ThreadId );																			///< マイクロマイクロスレッド終了
	static Bool Create( Uint32 ThreadId, PMICROTHREADPROC pProcMain, PMICROTHREADPROC pProcTerminate, void *pParam, Uint32 StackSize );	///< マイクロマイクロスレッド生成
	static void Switch( Uint32 ThreadId );																			///< マイクロマイクロスレッド切り替え

	static Float GetRateCPU( Uint32 ThreadId = THREAD_SYSTEM );														///< マイクロマイクロスレッド処理時間取得
};

#endif



//======================================================================
// INCLUDE
//======================================================================


//=============================================================================
// STRUCT
//=============================================================================
/**
	@brief	拡張フレームクラス

	LunaModelクラス用のサポートクラスです。
	Ｘファイル読み込み時のフレームを定義しています。
	ユーザーがこのクラスを直接参照することはありません。
*/
struct LUNAFRAME : public D3DXFRAME
{
    D3DXMATRIX CombinedTransformationMatrix;
};


/**
	@brief	拡張メッシュコンテナクラス

	LunaModelクラス用のサポートクラスです。
	Ｘファイル読み込み時のメッシュを定義しています。
	ユーザーがこのクラスを直接参照することはありません。
*/
struct LUNAMESH : public D3DXMESHCONTAINER
{
	// スキンメッシュ情報
	ID3DXMesh			*pMeshOriginal;

	D3DXATTRIBUTERANGE	*pAttributeTable;
	Uint32				NumAttributeGroups;

	D3DXMATRIX			**ppBoneMatrixPtr;
	D3DXMATRIX			*pBoneMatrix;
	D3DXMATRIX			*pBoneOffsetMatrix;
	Uint32				BoneMatrixMax;

	// アプリケーション情報
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
	@brief	モデルアロケーションクラス

	LunaModelでＸファイルを読み込む時に使われる、
	ローダークラスです。
	内部的にこのクラスの各メソッドが呼ばれる形で、
	ファイルの読み込みを行うようになっています。
	ユーザーがこのクラスを直接参照することはありません。
*/
class CModelAlloc : public ID3DXAllocateHierarchy
{
	Uint32 m_FrameCount;																		///< フレーム数
	Uint32 m_MeshCount;																			///< メッシュ数
	eSurfaceFormat m_Format;
	D3DCOLOR m_KeyColor;
	Bool m_IsMipmap;

public:
	CModelAlloc() {};																			///< コンストラクタ
	CModelAlloc( eSurfaceFormat Format, D3DCOLOR KeyColor );						///< コンストラクタ
	virtual ~CModelAlloc() {}																	///< デストラクタ

	Uint32 GetMeshCount( void );																///< メッシュ数取得
	Uint32 GetFrameCount( void );																///< フレーム数取得

	Bool CopyName( char **ppDstName, const char *pSrcName );									///< 名前コピー

    virtual HRESULT __stdcall DestroyFrame( D3DXFRAME *pFrameToFree );							///< フレームデータ解体
    virtual HRESULT __stdcall DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerBase );	///< メッシュデータ解体
    virtual HRESULT __stdcall CreateFrame( LPCTSTR pName, D3DXFRAME **ppNewFrame );				///< フレームデータ生成
    virtual HRESULT __stdcall CreateMeshContainer(												///< メッシュデータ生成
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
	@brief	モデルクラス

	DirectX用のモデルファイルであるＸファイルを
	処理するためのクラスです。
	各種キーフレームアニメーションからスキンメッシュの
	処理までをサポートしますが、基本的に処理は
	全てソフトウェアで行われ、凝った演出などには向きませんが、
	DirectXの固定シェーダー機能で処理されるため、高速で
	確実な動作が期待できます。
*/
class LunaModel
{
protected:
	static CMatrix m_mBase;
	static MODELDATA *m_pModel;								///< モデルデータポインタ
	static Uint32 m_ModelMax;								///< モデルデータ最大数

protected:
	static void Init( LMODEL lModel );						///< モデルオブジェクト初期化
	static Bool Delete( LMODEL lModel );					///< モデルオブジェクト削除
	static LMODEL GetFreeHandle( void );					///< 未使用ハンドル取得
	static void RenderingMesh( D3DXMESHCONTAINER *pMeshContainerBase, D3DXFRAME *pFrameBase );				///< メッシュレンダリング
	static void RenderingFrame( D3DXFRAME *pFrame );														///< フレームレンダリング
	static void FrameUpdate( D3DXFRAME *pFrameBase, D3DXMATRIX *pParentMatrix, D3DXMATRIX *pRootMatrix );	///< フレーム更新
	static Bool SetupBoneMatrixPointers( LMODEL lModel, D3DXFRAME *pFrame );								///< ボーン行列ポインター設定
	static Bool SetupBoneMatrixPointersOnMesh( LMODEL lModel, D3DXMESHCONTAINER *pMeshContainerBase );		///< メッシュのボーン行列ポインター設定

	static LMODEL LoadFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor );			///< メモリからＸファイルを読み込み
	static Bool MeshDataConvert( LUNAMESH *pMeshContainer, Float fScale );									///< メッシュデータコンバート

	static Sint32 CreateMeshList( D3DXFRAME *pFrame, D3DXMESHCONTAINER **ppList, Sint32 Count );			/// メッシュリスト生成

public:
	static Bool Initialize( void );																			///< クラス初期化
	static void Finalize( void );																			///< クラス解放
	static void Reset( void );																				///< デバイスデータリセット
	static void Restore( void );																			///< デバイスデータリストア
	static void SetMax( Uint32 Max );																		///< オブジェクト最大数設定
	static void Release( LMODEL lModel );																	///< オブジェクト解放

	static LMODEL CreateFromFile( const char *pFileName, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );		///< ファイルから生成
	static LMODEL CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );	///< メモリから生成

	static LMODEL CreateCube( Float fSizeX, Float fSizeY, Float fSizeZ, D3DCOLORVALUE Color );				///< キューブ作成
	static LMODEL CreateSphere( Float fRadius, Sint32 Slices, Sint32 Stacks, D3DCOLORVALUE Color );			///< スフィア生成
	static LMODEL CreatePolygon( Float fLength, Sint32 Sides, D3DCOLORVALUE Color );						///< ポリゴン作成
	static LMODEL CreateText( const char *pFontFace, const char *pText, Float fDeviation, Float fExtrusion, Float fScale, D3DCOLORVALUE Color );	///< テキスト生成

	static void TransformInit( LMODEL lModel );																///< 変換初期化
	static void TransformUpdate( LMODEL lModel, Float fTime = 0.0f );										///< 変換更新

	static void Scale( LMODEL lModel, Float fSx, Float fSy, Float fSz );									///< スケーリング
	static void Heading( LMODEL lModel, Sint32 Rot );														///< ヘッディング
	static void Pitching( LMODEL lModel, Sint32 Rot );														///< ピッチング
	static void Rolling( LMODEL lModel, Sint32 Rot );														///< ローリング
	static void RotationX( LMODEL lModel, Sint32 Rot );														///< Ｘ軸回転
	static void RotationY( LMODEL lModel, Sint32 Rot );														///< Ｙ軸回転
	static void RotationZ( LMODEL lModel, Sint32 Rot );														///< Ｚ軸回転
	static void RotationQuaternion( LMODEL lModel, CQuaternion *pQuat );									///< クォータニオンで回転
	static void Translation( LMODEL lModel, Float fPx, Float fPy, Float fPz );								///< 移動
	static void LookAt( LMODEL lModel, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );						///< 任意点から任意点への注視
	static Bool SetStyleToModel( LMODEL lModel, CStyle *pStyle );											///< 姿勢データをモデルに設定
	static Bool GetStyleFromModel( LMODEL lModel, CStyle *pStyle );											///< 姿勢データをモデルから取得

	static void Rendering( LMODEL lModel );																	///< レンダリング

	static void SetTexture( LMODEL lModel, Uint32 Stage, LTEXTURE lTex, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );	///< モデルへテクスチャ設定
	static void SetMaterialAlpha( LMODEL lModel, Uint8 Alpha, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );				///< モデルのマテリアルアルファを設定

	static Bool SphereBoundProbe( LMODEL lModel, CVector3D *pRayPosition, CVector3D *pRayDirection );			///< 光線との当り判定
	static Bool CheckSphereBound( LMODEL lModel1, LMODEL lModel2 );											///< 球単位の当り判定
	static void GetModelSphere( LMODEL lModel, CVector3D *pvCenter, Float *pRadius );						///< バウンディングスフィアを取得

	static Uint32 GetTrackCount( LMODEL lModel );															///< トラック数を取得
	static Bool SetTrackEnable( LMODEL lModel, Sint32 Track, Bool IsEnable );								///< トラックの使用の有無を設定
	static Bool SetTrackSpeed( LMODEL lModel, Sint32 Track, Float fSpeed );									///< トラックの速度設定
	static Bool SetTrackWeight( LMODEL lModel, Sint32 Track, Float fWeight );								///< トラックの重み設定
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	汎用モデルクラス

	DirectX用のモデルファイルであるＸファイルを
	扱うためのクラスです。
	LunaModelクラスでサポートしている機能は
	一通りそろえた上で、モーフィングやテクスチャ処理
	などを頂点シェーダー2.0で行うため、柔軟な処理が
	可能になっています。
	LunaModelクラスに比べると内部処理が複雑になっています
	ので、読み込み時間などは少々かかりますが、
	ユーザーがより自由な描画処理を選択することが
	可能です。
*/
class LunaModelEx
{
protected:
	static LibLuna::CModelMgr *m_pModelMgr;

public:
	static Bool Initialize( void );																							///< モデルシステム初期化
	static void Finalize( void );																							///< モデルシステム解放
	static void Reset( void );																								///< モデルデータリセット
	static void Restore( void );																							///< モデルデータリストア
	static void Release( LMODELEX lModelEx );																				///< モデルデータ解放

	static LMODELEX CreateFromMemory( void *pData, Uint32 Size, Uint16 ShaderVersionMajor = 2, Uint16 ShaderVersionMinor = 0, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );	///< メモリからデータを読み込み
	static LMODELEX CreateFromFile( const char *pFileName, Uint16 ShaderVersionMajor = 2, Uint16 ShaderVersionMinor = 0, eSurfaceFormat Format = FORMAT_TEXTURE_3D, D3DCOLOR KeyColor = COLORKEY_DISABLE );			///< ファイルからモデルデータを生成

	static void LoadEffectFromFile( LMODELEX lModelEx, const char *pShaderName, Uint32 SendFlag, Sint32 MeshNo );			///< エフェクトを設定
	static void SetEffectHandle( LMODELEX lModelEx, LSHADERFX lShaderFx, Uint32 SendFlag, Sint32 MeshNo );					///< エフェクトを設定
	static void AutoCreateShader( LMODELEX lModelEx, LibLuna::eAutoCreateShaderType Type, Sint32 MeshNo = -1 );						///< 自動シェーダー生成

	static void TransformInit( LMODELEX lModelEx );																			///< 変換初期化
	static void TransformUpdate( LMODELEX lModelEx, Float fAnimeTime = 0.0f, Bool IsAnime = false, eAnimationType Type = ANIM_TYPE_LINEAR );						///< 変換更新
	static void TransformFromMatrix( LMODELEX lModelEx, CMatrix *pMatrix, Float fAnimeTime = 0.0f, Bool IsAnime = false, eAnimationType Type = ANIM_TYPE_LINEAR );	///< 変換更新
	static void TransformUpdateBlend( LMODELEX lModelEx, Float fAnimeTimeA, Float fAnimeTimeB, eAnimationType Type = ANIM_TYPE_LINEAR );
	static void TransformFromMatrixBlend( LMODELEX lModelEx, CMatrix *pMatrix, Float fAnimeTimeA, Float fAnimeTimeB, eAnimationType Type = ANIM_TYPE_LINEAR );

	static void SetAnimationTrackEnable( LMODELEX lModelEx, Sint32 Track );													///< アニメーショントラック設定
	static void SetAnimationTrackBlend( LMODELEX lModelEx, Sint32 TrackA, Sint32 TrackB, Float fWeight, Sint32 FrameNo );	///< アニメーショントラックのブレンド設定
	static Sint32 GetAnimationTrackMax( LMODELEX lModelEx );																///< アニメーショントラック数を取得
	static Sint32 GetAnimationTrackNo( LMODELEX lModelEx, const char *pName );												///< アニメーショントラック番号を名前から取得
	static Sint32 GetAnimationFrameMax( LMODELEX lModelEx, Sint32 Track );													///< アニメーショントラックの最大フレーム数取得

	static void Scaling( LMODELEX lModelEx, Float fSx, Float fSy, Float fSz );												///< スケーリング
	static void Heading( LMODELEX lModelEx, Sint32 Rot );																	///< ヘッディング
	static void Pitching( LMODELEX lModelEx, Sint32 Rot );																	///< ピッチング
	static void Rolling( LMODELEX lModelEx, Sint32 Rot );																	///< ローリング
	static void RotationX( LMODELEX lModelEx, Sint32 Rot );																	///< Ｘ軸回転
	static void RotationY( LMODELEX lModelEx, Sint32 Rot );																	///< Ｙ軸回転
	static void RotationZ( LMODELEX lModelEx, Sint32 Rot );																	///< Ｚ軸回転
	static void RotationQuaternion( LMODELEX lModelEx, CQuaternion *pQuat );												///< クォータニオンで回転
	static void Translation( LMODELEX lModelEx, Float fPx, Float fPy, Float fPz );											///< 移動
	static void LookAt( LMODELEX lModelEx, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );								///< 任意座標を注視

	static void GetBoundingBox( LMODELEX lModelEx, Uint32 MeshNo, BOX3D *pBox );											///< バウンディングボックスデータ取得

	static void RenderingBox( LMODELEX lModelEx, D3DCOLOR Color );															///< モデルレンダリング
	static Sint32 Rendering( LMODELEX lModelEx = INVALID_MODELEX );															///< モデルレンダリング
	static Float RenderingTimer( LMODELEX lModelEx = INVALID_MODELEX );														///< モデルレンダリング

	static Sint32 GetMeshNoFromName( LMODELEX lModelEx, const char *pMeshName );											///< 該当する名前のメッシュの番号を取得
	static Sint32 GetFrameNoFromName( LMODELEX lModelEx, const char *pFrameName );											///< 該当する名前のフレームの番号を取得
	static void GetTransformMatrixFromMesh( LMODELEX lModelEx, CMatrix *pMatrix, Sint32 MeshNo );							///< メッシュから変換行列を取得
	static void GetTransformMatrixFromFrame( LMODELEX lModelEx, CMatrix *pMatrix, Sint32 FrameNo );							///< フレームへ変換行列を設定
	static void SetTransformMatrixToMesh( LMODELEX lModelEx, CMatrix *pMatrix, Sint32 MeshNo );								///< フレームから変換行列を取得
	static void SetStyleToModel( LMODELEX lModelEx, CStyle *pStyle );														///< 姿勢データをモデルに設定
	static void GetStyleFromModel( LMODELEX lModelEx, CStyle *pStyle );														///< 姿勢データをモデルから取得

	static Bool GetScreenPosition( LMODELEX lModelEx, CVector3D *pPos, Sint32 MeshNo );										///< スクリーン座標を取得

	static void SetVertexExtrusion( LMODELEX lModelEx, Float fOffset, Sint32 MeshNo = -1 );									///< 頂点押し出し量設定
	static void SetMorphWeight( LMODELEX lModelEx, Float fOffset, Sint32 MeshNo = -1 );										///< モーフィング処理用ウェイト値設定
	static void SetSlideTextureU( LMODELEX lModelEx, Float fOffset, Sint32 MeshNo = -1 );									///< テクスチャＵＶのＵのスライド値設定
	static void SetSlideTextureV( LMODELEX lModelEx, Float fOffset, Sint32 MeshNo = -1 );									///< テクスチャＵＶのＶのスライド値設定
	static void SetTexture( LMODELEX lModelEx, Uint32 Stage, LTEXTURE lTex, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );	///< モデルへテクスチャ設定
	static void SetMaterialAlpha( LMODELEX lModelEx, Uint8 Alpha, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );				///< モデルのマテリアルアルファを設定
	static Bool SetMorphTarget( LMODELEX lDst, Sint32 DstNo, LMODELEX lSrc, Sint32 SrcNo );									///< モーフィング用ターゲットメッシュ設定
	static Sint32 GetMeshCount( LMODELEX lModelEx );																		///< メッシュ数取得
	static Sint32 GetFrameCount( LMODELEX lModelEx );																		///< フレーム数取得
	static Bool IsBoneMesh( LMODELEX lModelEx, Sint32 MeshNo );																///< メッシュがボーン入りメッシュかを取得します
	static void SetRenderFlag( LMODELEX lModelEx, Uint8 Flag, Uint8 Mask = 0xff, Sint32 MeshNo = -1 );						///< レンダリングフラグの設定
	static Uint8 GetRenderFlag( LMODELEX lModelEx, Sint32 MeshNo );															///< レンダリングフラグの取得

	// ステート処理
	static void SetMateriaStateEnable( LMODELEX lModelEx, Bool IsEnable, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );											///< ステート処理フラグ
	static void SetTextureState( LMODELEX lModelEx, Uint32 Stage, D3DTEXTURESTAGESTATETYPE State, Uint32 Param, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );	///< テクスチャステート設定
	static void SetSamplerState( LMODELEX lModelEx, Uint32 Stage, D3DSAMPLERSTATETYPE State, Uint32 Param, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );		///< サンプリングステート設定
	static void SetBlendingType( LMODELEX lModelEx, eBlendType BlendType, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );											///< ブレンディングタイプ設定
	static void SetFilterEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< バイリニアフィルタ有無設定
	static void SetColorkeyEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< カラーキー有無設定
	static void SetZBufferEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< 深度バッファ有無設定
	static void SetZWriteEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< Z書き込み有無設定
	static void SetWireFrameEnable( LMODELEX lModelEx, Bool Flag, Sint32 MeshNo = -1, Sint32 MaterialNo = -1 );													///< ワイヤフレームレンダリング有無設定

	// 当たり判定
	static Bool CheckCollision( LibLuna::eCollisionType CollisionType, LMODELEX lModel1, Sint32 MeshNo1, LMODELEX lModel2, Sint32 MeshNo2, Float fScale = 1.0f );	///< 当たり判定チェック
	static Bool CollisionRay( LMODELEX lModelEx, Sint32 MeshNo, CVector3D *pvStart, CVector3D *pvEnd, Bool IsBackFace = false, Bool IsNormal = false );		///< 直線との交差チェック
	static Bool CollisionScreen( LMODELEX lModelEx, Sint32 MeshNo, CVector3D *pScreenPos, Bool IsBackFace = false, Bool IsNormal = false );					///< 画面との交差チェック
	static Bool CollisionScreenFast( LMODELEX lModelEx, Sint32 MeshNo, CVector3D *pScreenPos );																///< 画面との交差チェック
	static Bool GetCollisionInfo( LMODELEX lModelEx, Sint32 MeshNo, Sint32 PointNo, CVector3D *pPositionLocal, CVector3D *pPositionWorld, CVector3D *pNormalLocal, CVector3D *pNormalWorld );	///< 当たり判定結果ポリゴンの衝突情報取得
	static Uint32 GetCollisionInfoCount( LMODELEX lModelEx, Sint32 MeshNo );												///< 衝突ポイント数取得
	static void GetBoundingBox( LMODELEX lModelEx, Sint32 MeshNo, CVector3D *pMin, CVector3D *pMax );							///< バウンディングボックス取得
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	ミュージッククラス

	DirectMusicを容易に扱えるようにしたラッパーです。
	Midiの再生をサポートし、
	パンの移動やボリュームの変更なども行うことが出来ます。
*/
class LunaMusic
{
protected:
	static IDirectSound *m_pDirectSound;					///< DirectSoundオブジェクト
	static IDirectMusic *m_pDirectMusic;					///< DirectMusicオブジェクト
	static IDirectMusicLoader8 *m_pMusicLoader;				///< ミュージックローダーオブジトクト
	static MUSICDATA *m_pMusic;								///< ミュージックデータポインタ
	static Uint32 m_MusicMax;								///< ミュージックデータ最大数

protected:
	static Bool Delete( LMUSIC lMusic );									///< ミュージックデータ削除
	static void Init( LMUSIC lMusic );										///< ミュージックデータ初期化
	static LMUSIC GetFreeHandle( void );									///< 未使用ミュージックデータ取得

	static LMUSIC LoadFromMemoryMidi( void *pData, Uint32 Size, Uint32 DefaultPathType );	///< メモリ内のＭＩＤＩデータからオブジェクトを生成

public:
	static Bool Initialize( void );											///< ミュージッククラス初期化
	static void Finalize( void );											///< ミュージッククラス解放

	static void SetMax( Uint32 Max );										///< 使用最大ミュージッククラス設定

	static LMUSIC SearchHandle( const char *pFileName );					///< 同一名称のミュージックハンドルを取得

	static LMUSIC CreateFromMidi( const char *pFileName, Uint32 DefaultPathType = DMUS_APATH_SHARED_STEREOPLUSREVERB );	///< ＭＩＤＩからミュージックデータを作成しハンドルを取得

	static LMUSIC CreateFromMemoryMidi( void *pData, Uint32 Size, Uint32 DefaultPathType = DMUS_APATH_SHARED_STEREOPLUSREVERB );	///< メモリ内のＭＩＤＩデータからオブジェクトを生成

	static void AddRef( LMUSIC lMusic );									///< 参照カウント加算
	static void Release( LMUSIC lMusic );									///< ミュージック解放

	static void Play( LMUSIC lMusic, Uint32 LoopCount = 0 );				///< 再生
	static void Loop( LMUSIC lMusic );										///< ループ再生
	static void Pause( LMUSIC lMusic );										///< 一時停止
	static void Stop( LMUSIC lMusic );										///< 停止
	static void SetVolume( LMUSIC lMusic, Float fParam );					///< ボリューム設定
	static void SetPan( LMUSIC lMusic, Float fParam );						///< パン移動
	static Bool IsPlay( LMUSIC lMusic, MUSIC_TIME* pOffset = NULL, Uint32* pRepeats = NULL );		///< 再生状態チェック
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	ネットワーククラス

	WindowsSocketを扱うためのラッパークラスです。
	WinSock2.0の機能を使っており、非同期処理にも
	対応しています。
	DirectPlayを使ったネットワーク処理とは違い
	ネットワークなのでLinuxなどのほかのプラット
	フォームとの通信も容易に行えます。
*/
class LunaNetwork
{
public:
	/**
		@brief クライアント処理
	*/
	class Client
	{
	protected:
		static SOCKET			m_Socket;													///< 自分のネットワーク
		static Bool				m_IsConnect;												///< 接続中か否か
		static OVERLAPEDDATA	m_OverlapSend;												///< 送信用オーバーラップ
		static OVERLAPEDDATA	m_OverlapRecv;												///< 受信用オーバーラップ

	private:
		static void __stdcall CompleteCallbackRecv( Uint32 Error, Uint32 Recv, WSAOVERLAPPED *pOver, Uint32 Flags );	///< 処理完了時コールバック関数
		static void __stdcall CompleteCallbackSend( Uint32 Error, Uint32 Send, WSAOVERLAPPED *pOver, Uint32 Flags );	///< 処理完了時コールバック関数

	public:
		static Bool Initialize( void );														///< クラス初期化
		static void Finalize( void );														///< クラス解放

		static Bool ConnectServer( const char *pServerString, Uint16 PortNo );				///< サーバーへの接続
		static void Shutdown( void );														///< シャットダウン

		static Sint32 RequestSend( const void *pData, Uint32 Size );						///< データ送信
		static Sint32 RequestRecv( void *pData, Uint32 Size );								///< データ受信

		static Bool IsRequestEndSend( void );												///< リクエスト処理待ち
		static Bool IsRequestEndRecv( void );												///< リクエスト処理待ち

		static Sint32 GetRequestResultSend( void );											///< リクエスト結果コード取得
		static Sint32 GetRequestResultRecv( void );											///< リクエスト結果コード取得
	};

	/**
		@brief サーバー処理
	*/
	class Server
	{
	protected:
		static Bool					m_IsConnect;								///< 接続中か否か
		static HWND					m_hWindow;									///< 処理するウィンドウのウィンドウハンドル
		static Uint32				m_Message;									///< 処理するメッセージ
		static HOSTINFO				m_HostInfo;									///< ホスト情報
		static HOSTENT				m_HostEntry;								///< ホストエントリー
		static SOCKET				m_Socket;									///< 自分のソケット
		static Sint32				m_ClientCount;								///< クライアント数
		static CONNECTCLIENTDATA	*m_pConnectionList;							///< 接続ユーザーリスト
		static CONNECTCLIENTDATA	m_ConnectClient;							///< 最終接続クライアント
		static CONNECTCLIENTDATA	m_CloseClient;								///< 最終切断クライアント
		static PCALLBACKSOCKETPROC	m_pCallBackAccept;							///< 受信受付時用コールバック関数のポインタ
		static PCALLBACKSOCKETPROC	m_pCallBackClose;							///< 接続切断時用コールバック関数のポインタ
		static PCALLBACKSOCKETPROC	m_pCallBackRead;							///< データ受信時用コールバック関数のポインタ
		static PCALLBACKSOCKETPROC	m_pCallBackWrite;							///< データ送信時用コールバック関数のポインタ

	protected:
		static void List_Insert( CONNECTCLIENTDATA *pConnet );								///< リストにデータを挿入する
		static void List_Erase( CONNECTCLIENTDATA *pConnet );								///< リストからデータを削除する
		static void *List_Search( Sint32 No );												///< 番号からリスト内を検索
		static void *List_Search( SOCKET Socket );											///< ソケットからリスト内を検索

	public:
		static Bool Initialize( void );														///< クラス初期化
		static void Finalize( void );														///< クラス解放

		static Bool CreateServer( Uint16 PortNo );											///< サーバー生成
		static void Shutdown( void );														///< シャットダウン

		static void SetAsynCallBackAccept( PCALLBACKSOCKETPROC pCallBack );					///< 接続受付時コールバック関数の設定
		static void SetAsynCallBackConnect( PCALLBACKSOCKETPROC pCallBack );				///< 接続時コールバック関数の設定
		static void SetAsynCallBackClose( PCALLBACKSOCKETPROC pCallBack );					///< 切断時コールバック関数の設定
		static void SetAsynCallBackRead( PCALLBACKSOCKETPROC pCallBack );					///< 読み込み時コールバック関数の設定
		static void SetAsynCallBackWrite( PCALLBACKSOCKETPROC pCallBack );					///< 書き込み時コールバック関数の設定
		static void ReceiveMessage( HWND hWnd, WPARAM wParam, LPARAM lParam );				///< 受信メッセージ処理

		static Bool ASyncAccept( void );													///< 非同期接続受付
		static Sint32 ASyncSend( const void *pData, Uint32 Size, Sint32 Id );				///< 非同期データ送信
		static Sint32 ASyncRecv( void *pData, Uint32 Size, Sint32 Id );						///< 非同期データ受信

		static void GetConnectClientInfo( HOSTINFO *pHostInfo, char *pAddr );				///< 接続中のクライアント情報を取得する
		static void GetCloseClientInfo( HOSTINFO *pHostInfo, char *pAddr );					///< 切断されたクライアント情報を取得する
		static Sint32 GetClientCount( void );												///< 接続中のクライアント数を取得する
		static void GetClientInfo( Sint32 No, char *pName, char *pAddress );				///< 接続中のクライアント情報を取得する

		static Bool SetSendData( SOCKETSENDDATA *pSend, Sint32 Id );						///< 送信するデータを設定する
	};

	friend class LunaNetwork::Client;
	friend class LunaNetwork::Server;

protected:
	static char			m_LastError[1024];													///< エラー格納用文字列
	static WSADATA		m_WsaData;															///< ソケットデータ
	static HOSTINFO		m_HostInfo;															///< ホスト情報
	static HOSTENT		m_HostEntry;														///< ホストエントリー

	static void GetMakeError( Sint32 ErrorCode, char *pErrStr );							///< エラー文字列の生成

public:
	static Bool Initialize( void );															///< クラス初期化
	static void Finalize( void );															///< クラス解放

	static Bool GetLastError( char *pError );												///< 最後に発生したエラーを取得
	static Bool GetHostInfo( const char *pServerString, HOSTINFO *pHost );					///< ホスト情報の取得
	static void GetLocalHostName( char *pName );											///< ローカルホスト名を取得
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	ポイント描画クラス

	２Ｄ上にポイントを描画するだけにクラスです。
	単純に点を描画するだけのもので、このクラスの
	ラッパーは存在しません。
*/
class LunaPoint
{
	friend class Luna3D;

protected:
	static LibLuna::CPoint2DMgr *m_pPointMgr;

public:
	static Bool Initialize( void );																	///< クラス初期化
	static void Finalize( void );																	///< クラス解放
	static void Reset( void );																		///< デバイスデータリセット
	static void Restore( void );																	///< デバイスデータリストア

	static LPOINT Create( Uint32 VertexMax );														///< 生成

	static void Release( LPOINT lPt );																///< 解放

	static void Rendering( LPOINT lPt );															///< レンダリング
	static void ResetBuffer( LPOINT lPt );															///< レンダリングバッファリセット
	static void UpdateBuffer( LPOINT lPt );															///< レンダリングバッファ更新

	static Bool PushRenderBuffer( LPOINT lPt, CPrimitivePoint2D *pPoint, Uint32 Count );				///< レンダリングバッファにデータ追加

	static Sint32 GetRequestedVertexCount( LPOINT lPrim );															///< 実際にリクエストした頂点数取得

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
	@brief	３Ｄポイント描画クラス

	３Ｄ空間内にポイントを描画するためのクラスです。
	指定座標に点を描画するだけのクラスであり、
	このクラスのラッパーは存在しません。
*/
class LunaPoint3D
{
protected:
	static LibLuna::CPoint3DMgr *m_pPointMgr;

public:
	static Bool Initialize( void );																///< クラス初期化
	static void Finalize( void );																///< クラス解放
	static void Reset( void );																	///< デバイスデータリセット
	static void Restore( void );																///< デバイスデータリストア

	static LPOINT3D Create( Uint32 VertexMax );													///< 生成

	static void Release( LPOINT3D lPnt3D );														///< 解放

	static void TransformInit( LPOINT3D lPnt3D );												///< 変換初期化
	static void TransformUpdate( LPOINT3D lPnt3D );												///< 変換更新

	static void Heading( LPOINT3D lPnt3D, Sint32 Rot );											///< ヘッディング
	static void Pitching( LPOINT3D lPnt3D, Sint32 Rot );										///< ピッチング
	static void Rolling( LPOINT3D lPnt3D, Sint32 Rot );											///< ローリング
	static void RotationX( LPOINT3D lPnt3D, Sint32 Rot );										///< Ｘ軸回転
	static void RotationY( LPOINT3D lPnt3D, Sint32 Rot );										///< Ｙ軸回転
	static void RotationZ( LPOINT3D lPnt3D, Sint32 Rot );										///< Ｚ軸回転
	static void Translation( LPOINT3D lPnt3D, Float fPx, Float fPy, Float fPz );				///< 移動
	static void LookAt( LPOINT3D lPnt3D, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );	///< 注視

	static void Rendering( LPOINT3D lPnt3D );													///< レンダリング
	static void ResetBuffer( LPOINT3D lPnt3D );													///< レンダリングバッファリセット
	static void UpdateBuffer( LPOINT3D lPnt3D );												///< レンダリングバッファ更新

	static Bool PushRenderBuffer( LPOINT3D lPnt3D, CPrimitivePoint3D *pPoint, Uint32 Count );	///< レンダリングバッファにデータ追加
};




//=============================================================================
// INCLUDE
//=============================================================================



//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	プリミティブクラス

	２Ｄ平面状に単一のポリゴンを描画するためのクラスです。
	このクラス自身は単純なポリゴンを描画するだけのものですが、
	LunaEffectクラスやLunaSpriteクラスがより扱いやすいような
	ラッパーになっており、直接このクラスを使用するのは
	凝ったエフェクトを使用したいときなどだけになると思います。
*/
class LunaPrimitive
{
	friend class Luna3D;

protected:
	static LibLuna::CPrimitive2DMgr *m_pPrimMgr;

public:
	static Bool Initialize( void );																						///< クラス初期化
	static void Finalize( void );																						///< クラス終了
	static void Reset( void );																							///< デバイスリセット
	static void Restore( void );																						///< デバイスリストア

	static LPRIMITIVE Create( Uint32 VertexMax, eVertexPrimitiveType VertexType, Bool IsSortZ );						///< 生成

	static void BufferResize( LPRIMITIVE lPrim, Uint32 Count );															///< 再設定
	static void Release( LPRIMITIVE lPrim );																			///< 解放

	static void Rendering( LPRIMITIVE lPrim );																			///< レンダリング
	static void ResetBuffer( LPRIMITIVE lPrim );																		///< レンダリングバッファ初期化
	static void UpdateBuffer( LPRIMITIVE lPrim );																		///< レンダリングバッファ更新

	static Bool PushRenderBuffer( LPRIMITIVE lPrim, CPrimitivePoint2D *pPoint, Uint32 Count );								///< レンダリングバッファに追加

	static Sint32 GetRequestedVertexCount( LPRIMITIVE lPrim );															///< 実際にリクエストした頂点数取得

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
	@brief	３Ｄプリミティブ描画クラス

	３Ｄ空間内のプリミティブを描画するためのクラスです。
	このクラス自体は単純なポリゴン描画しかできません。
	またこのクラスのラッパーは存在しません。
*/
class LunaPrimitive3D
{
	friend class Luna3D;

protected:
	static LibLuna::CPrimitive3DMgr *m_pPrimMgr;

public:
	static Bool Initialize( void );																///< プリミティブクラス初期化
	static void Finalize( void );																///< プリミティブクラス解放
	static void Reset( void );																	///< 全プリミティブリセット
	static void Restore( void );																///< 全プリミティブリストア

	static LPRIMITIVE3D Create( Uint32 VertexMax, eVertexPrimitiveType VertexType );			///< プリミティブ生成

	static void Release( LPRIMITIVE3D lPrim3D );												///< プリミティブ解放

	static void TransformInit( LPRIMITIVE3D lPrim3D );											///< 変換初期化
	static void TransformUpdate( LPRIMITIVE3D lPrim3D );										///< 変換更新

	static void Heading( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< ヘッディング
	static void Pitching( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< ピッチング
	static void Rolling( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< ローリング
	static void RotationX( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< Ｘ軸回転
	static void RotationY( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< Ｙ軸回転
	static void RotationZ( LPRIMITIVE3D lPrim3D, Sint32 Rot );									///< Ｚ軸回転
	static void Translation( LPRIMITIVE3D lPrim3D, Float fPx, Float fPy, Float fPz );			///< 移動
	static void LookAt( LPRIMITIVE3D lPrim3D, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );	///< 指定座標注視
	static void Scaling( LPRIMITIVE3D lPrim3D, Float fSx, Float fSy, Float fSz );				///< ローリング

	static void Rendering( LPRIMITIVE3D lPrim3D );												///< レンダリング
	static void ResetBuffer( LPRIMITIVE3D lPrim3D );											///< バッファリセット
	static void UpdateBuffer( LPRIMITIVE3D lPrim3D );											///< バッファ更新

	static Bool PushRenderBuffer( LPRIMITIVE3D lPrim3D, CPrimitivePoint3D *pPoint, Uint32 Count );	///< バッファにプリミティブ追加

	static Sint32 GetRequestedVertexCount( LPRIMITIVE3D lPrim3D );									///< リクエストされた頂点数を取得
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	乱数処理クラス

	メルセンヌ・ツイスタを使用した擬似乱数発生生成クラスです。
*/
class LunaRand
{
protected:
	static Uint32 GenerateInt32( void );				///< 32Bit乱数生成

public:
	static void Seed( Uint32 Param );					///< 乱数の種を設定
	static Uint32 GetInt32( void );						///< 32Bit乱数を取得
	static Uint64 GetInt64( void );						///< 64Bit乱数を取得
	static Float GetFloat32( void );					///< 32Bit浮動小数点乱数を取得

	static Sint32 GetInt( Sint32 Min, Sint32 Max );		///< Min～Max範囲の整数乱数を取得
	static Float GetFloat( Float Min, Float Max );		///< Min～Max範囲の浮動小数点乱数を取得
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	レジストリー操作クラス

	レジストリを操作するためのラッパークラスです。
	キーの作成から、バイナリ、文字列、数値の
	読み書きが出来るような構成になっています。
*/
class LunaRegistry
{
public:
	static Bool Create( const char *pKeyName );														///< レジストリ生成
	static void Close( void );																		///< レジストリ閉じる
	static Bool Delete( const char *pKeyName );														///< レジストリ削除

	static Bool SetNumber( const char *pValue, Uint32 Data );										///< 数値を書き込み
	static Bool SetString( const char *pValue, const char *pStr );									///< 文字列を書き込み
	static Bool SetBinary( const char *pValue, const unsigned char *pData, Uint32 Size );			///< バイナリを書き込み

	static Bool GetNumber( const char *pValue, Uint32 *pData );										///< 数値を取得
	static Bool GetString( const char *pValue, char *pStr, Uint32 Size );							///< 文字列を取得
	static Bool GetBinary( const char *pValue, Uint8 *pData, Uint32 Size );							///< バイナリを取得
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CASS
//=============================================================================
/**
	@brief	シェーダー管理クラス

	シェーダーの管理を行うためのクラスです。
*/
class LunaShaderFx
{
protected:
	static LibLuna::CBaseList	m_ShaderList;																		///< シェーダーファイル管理リスト
	static LSHADERFX			m_lCurrentShader;																	///< カレントシェーダー

public:
	static Bool Initialize( void );																					///< シェーダークラスの初期化
	static void Finalize( void );																					///< シェーダークラスの解放
	static void Reset( void );																						///< デバイスリセット処理
	static void Restore( void );																					///< デバイスリストア処理

	static void Release( LSHADERFX lShaderFx );																		///< シェーダー解放
	static void AddRef( LSHADERFX lShaderFx );																		///< 参照カウンタインクリメント

	static Bool Begin( LSHADERFX lShaderFx, Uint32 *pPassMax );														///< シェーダー開始
	static void End( LSHADERFX lShaderFx );																			///< シェーダー終了
	static void BeginPass( LSHADERFX lShaderFx, Uint32 Pass );														///< シェーダーパス開始宣言
	static void EndPass( LSHADERFX lShaderFx );																		///< シェーダーパス修了宣言


	static LSHADERFX Create( Uint32 Type, Uint32 BoneWeightCount, Uint32 BoneMatrixCount, Uint32 *pSendFlag );		///< 基本シェーダーから作成
	static LSHADERFX CreateFromMemory( void *pData, Uint32 Size );													///< シェーダーをメモリから作成
	static LSHADERFX CreateFromFile( const char *pFile );															///< シェーダーをファイルから作成

	static void UpdateParameter( LSHADERFX lShaderFx );																///< 設定したパラメーターの更新
	static void SetCurrentShader( LSHADERFX lShaderFx );															///< 強制的に使用するシェーダー

	static void SetBool( LSHADERFX lShaderFx, const char *pHandle, BOOL Param );									///< ブール値を設定する
	static void SetBoolArray( LSHADERFX lShaderFx, const char *pHandle, BOOL *pParam, Sint32 Num );					///< ブール値の配列を設定する
	static void SetFloat( LSHADERFX lShaderFx, const char *pHandle, Float Param );									///< 浮動小数点値を設定する
	static void SetFloatArray( LSHADERFX lShaderFx, const char *pHandle, Float *pParam, Sint32 Num );				///< 浮動小数点値の配列を設定する
	static void SetInt( LSHADERFX lShaderFx, const char *pHandle, Sint32 Param );									///< 整数を設定する
	static void SetIntArray( LSHADERFX lShaderFx, const char *pHandle, Sint32 *pParam, Sint32 Num );				///< 整数の配列を設定す 
	static void SetMatrix( LSHADERFX lShaderFx, const char *pHandle, D3DXMATRIX *pMatrix );							///< 非転置行列を設定する
	static void SetMatrixArray( LSHADERFX lShaderFx, const char *pHandle, D3DXMATRIX *pMatrix, Sint32 Num );		///< 非転置行列の配列を設定する
	static void SetMatrixTranspose( LSHADERFX lShaderFx, const char *pHandle, D3DXMATRIX *pMatrix );				///< 転置行列を設定する
	static void SetMatrixTransposeArray( LSHADERFX lShaderFx, const char *pHandle, D3DXMATRIX *pMatrix, Sint32 Num );///< 転置行列の配列を設定する
	static void SetString( LSHADERFX lShaderFx, const char *pHandle, const char *pStr );							///< 文字列を設定する
	static void SetTexture( LSHADERFX lShaderFx, const char *pHandle, LTEXTURE lTex );								///< テクスチャを設定する
	static void SetVector( LSHADERFX lShaderFx, const char *pHandle, D3DXVECTOR4 *pVec );							///< ベクトルを設定する
	static void SetVectorArray( LSHADERFX lShaderFx, const char *pHandle, D3DXVECTOR4 *pVec, Sint32 Num );			///< ベクトルの配列を設定する

	static D3DXHANDLE GetParameterByName( LSHADERFX lShaderFx, const char *pName );									///< 名前からパラメーターハンドルを取得する
	static D3DXHANDLE GetParameterBySemantic( LSHADERFX lShaderFx, const char *pSemantic );							///< セマンティックからパラメーターハンドルを取得する
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	シート描画クラス

	自由なサイズのテクスチャを扱えるようにしたクラスです。
	内部的に256x256のテクスチャに自動分割して描画して
	いますので、処理速度的には問題がありますが、アドベンチャー
	ゲームなどで自由なサイズのテクスチャを描画したい場合などには
	有効だと思います。
*/
class LunaSheet
{
protected:
	static LibLuna::CSheetMgr *m_pSheetMgr;

public:
	static Bool Initialize( void );
	static void Finalize( void );

	static LSHEET CreateFromFile( const char *pFileName, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );							///< ファイルから生成
	static LSHEET CreateFromLAG( const char *pFileName, const char *pDataName, eSurfaceFormat Format );											///< ＬＡＧファイルから生成
	static LSHEET CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );					///< メモリファイルから生成

	static void AddRef( LSHEET lSheet );																		///< 参照カウント加算
	static void Release( LSHEET lSheet );																		///< 解放

	static Sint32 GetWidth( LSHEET lSheet );																	///< オリジナルの横幅取得
	static Sint32 GetHeight( LSHEET lSheet );																	///< オリジナルの縦幅取得

	static void Draw( LSHEET lSheet, Float Px, Float Py, D3DCOLOR Color );																				///< 描画
	static void DrawScale( LSHEET lSheet, Float fPx, Float fPy, Float fScale, D3DCOLOR Color, Float fCx = 0.0f, Float fCy = 0.0f );						///< 拡大縮小描画
	static void DrawRotate( LSHEET lSheet, Float fPx, Float fPy, Sint32 Angle, D3DCOLOR Color, Float fCx = 0.0f, Float fCy = 0.0f );					///< 回転描画
	static void DrawRotateScale( LSHEET lSheet, Float fPx, Float fPy, Sint32 Angle, Float fScale, D3DCOLOR Color, Float fCx = 0.0f, Float fCy = 0.0f );	///< 回転拡大縮小描画
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	簡易描画クラス

	単純なポリゴンの描画を簡易的に行えるクラスです。
	他の各種クラスのようにバッファを介さないために
	扱いが非常に単純になっています。
*/
class LunaSimple
{
protected:
	static IDirect3DVertexBuffer9 *m_pVB;																															///< 頂点バッファ

protected:
	static void DrawLine( Uint32 VertexCount );																														///< ライン描画
	static void DrawPorygon( Uint32 VertexCount, LTEXTURE TexList[], Sint32 TexNum );																				///< ポリゴン描画
	static void *LockVertexBuffer( Uint32 VertexCount, Uint32 VertexSize );																							///< 頂点バッファロック
	static void UnlockVertexBuffer( void );																															///< 頂点バッファアンロック
	static void UpdateTextureUV( CPrimitivePoint2D TriPt[], Sint32 VxNum, LTEXTURE TexList[], Sint32 TexNum );														///< テクスチャUV更新

public:	
	static Bool Initialize( void );																																	///< クラス初期化
	static void Finalize( void );																																	///< クラス解放

	static void Reset( void );																																		///< デバイスリセット時処理
	static void Restore( void );																																	///< デバイスリストア時処理

	static void DrawLinePointList( CPrimitivePoint2D PointTbl[], Sint32 PointNum );																						///< ポイントリストを使ってライン描画
	static void LineTriangle( CVector2D *pPos, Float fScale, Sint32 Angle, D3DCOLOR Color );																		///< 三角形ライン描画
	static void LineSquare( CLunaRect *pDst, Sint32 Angle, D3DCOLOR Color );																						///< 四角形ライン描画
	static void LineCircle( CVector2D *pPos, Float fSx, Float fSy, D3DCOLOR Color );																				///< 円形ライン描画

	static void DrawPolygonPointList( CPrimitivePoint2D PointTbl[], Sint32 PointNum, LTEXTURE TexList[], Sint32 TexNum );													///< ポイントリスト描画
	static void DrawTriangle( CVector2D *pPos, Float fScale, Sint32 Angle, CVector2D UvTbl[], D3DCOLOR Color, LTEXTURE TexList[], Sint32 TexNum );					///< 三角形描画
	static void DrawSquare( CLunaRect *pDst, Sint32 Angle, CLunaRect SrcTbl[], D3DCOLOR Color, LTEXTURE TexList[], Sint32 TexNum, Sint32 Cx = 0, Sint32 Cy = 0 );	///< 四角形描画
	static void DrawCircle( CVector2D *pPos, Float fSx, Float fSy, Sint32 Angle, CLunaRect SrcTbl[], D3DCOLOR Color, LTEXTURE TexList[], Sint32 TexNum );			///< 円形描画

	static void LineBox( CVector3D *pMin, CVector3D *pMax, CMatrix *pMatrix, D3DCOLOR Color );																		///< ラインで３Ｄボックス描画
};



//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	サウンド管理クラス

	サウンドドライバーAyameのラッパーです。
	Ayameを経由してサウンドを鳴らすので
	OggVorbis、未圧縮Wave、圧縮Waveの再生が可能です。
*/
class LunaSound
{
protected:
	static char								m_AyamePath[MAX_PATH];					///< Ayameのパス
	static Bool								m_IsInitAyame;							///< Ayameの初期化有無
	static IDirectSound						*m_pDirectSound;						///< DirectSoundオブジェクト
	static IDirectSound8					*m_pDirectSound8;						///< DirectSoundオブジェクト
	static IDirectSoundBuffer				*m_pPrimaryBuffer;						///< プライマリサウンドバッファ
	static SOUNDDATA						*m_pSound;								///< サウンドデータポインタ
	static Uint32							m_SoundMax;								///< サウンド最大数
	static HINSTANCE						m_hAyame;								///< Ayame DLLハンドル
	static AYAME_INITIALIZE_PROC			m_pAyameInitialize;						///< ドライバー初期化
	static AYAME_UNINITIALIZE_PROC			m_pAyameUninitialize;					///< ドライバー解放
	static AYAME_CREATE_FROM_FILE_EX_PROC	m_pAyameCreateFromFileEx;				///< ドライバーからオブジェクト取得
	static AYAME_CREATE_FROM_MEMORY_PROC	m_pAyameCreateFromMemory;				///< ドライバーからオブジェクト取得
	static AYAME_GETERROR_PROC				m_pAyameGetError;						///< エラー文字列

protected:
	static Bool Delete( LSOUND lSnd );												///< オブジェクト削除
	static void Init( LSOUND lSnd );												///< オブジェクト初期化
	static LSOUND GetFreeHandle( void );											///< 未使用ハンドル取得

	static Bool CreateSoundBuffer( IDirectSoundBuffer **ppBuffer, void *pMem, Uint32 Size );	///< サウンドバッファ生成
	static void CheckDeviceInfo( void );											///< デバイス情報チェック

	static Bool InitializeAyame( const char *pDllPath );							///< Ayameシステム初期化

public:
	static Bool Initialize( void );													///< クラス初期化
	static void Finalize( void );													///< クラス解放

	static void Manager( void );													///< マネージャー

	static void SetAyamePath( const char *pPath );									///< Ayame.dllのディレクトリ（デフォルトは.\)
	static void GetSoundObject( IDirectSound8 **ppSound );							///< サウンドオブジェクト取得

	static void SetMax( Uint32 Max );												///< オブジェクト最大数設定

	static LSOUND CreateFromFile( const char *pFileName, Bool IsNoStop, Bool IsAyame = true );				///< ファイルからオブジェクト生成
	static LSOUND CreateFromMemory( void *pData, Uint32 Size, Bool IsNoStop, Bool IsAyame = true  );		///< メモリからオブジェクト生成

	static LSOUND SearchHandle( const char *pFileName );							///< オブジェクトハンドル検索
	static void AddRef( LSOUND lSnd );												///< 参照カウント加算

	static void Release( LSOUND lSnd );												///< オブジェクト解放

	static Bool IsPlay( LSOUND lSnd );												///< 再生チェック
	static void Play( LSOUND lSnd, Uint32 LoopCount = 0, Uint32 LoopInSample = 0 );	///< 再生
	static void Loop( LSOUND lSnd );												///< ループ再生
	static void Pause( LSOUND lSnd );												///< 一時停止
	static void Stop( LSOUND lSnd );												///< 停止
	static void SetVolume( LSOUND lSnd, Float fParam );								///< ボリューム設定
	static void SetPan( LSOUND lSnd, Float fParam );								///< パン移動
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	２Ｄクラス
*/
class LunaSprite
{
protected:
	static LibLuna::CSprite2DMgr *m_pSprMgr;																																																							///< スプライトデータポインタ

public:
	static Bool Initialize( void );																																																										///< クラス初期化
	static void Finalize( void );																																																										///< クラス解放

	static void Reset( void );																																																											///< デバイスリセット時処理
	static void Restore( void );																																																										///< デバイスリストア時処理

	static LSPRITE Create( Uint32 VertexMax, eVertexPrimitiveType VertexType, Bool IsSortZ );																																											///< スプライト生成
	static void AttatchTexture( LSPRITE lSpr, Uint32 Stage, LTEXTURE lTex );																																															///< テクスチャを接続

	static void BufferResize( LSPRITE lSpr, Uint32 Count );																																																				///< バッファサイズ再設定
	static void Release( LSPRITE lSpr );																																																								///< スプライト解放

	static LPRIMITIVE GetPrimitive( LSPRITE lSpr );																																																						///< プリミティブハンドル取得

	static void SetScissoring( Bool IsUse, RECT *pRect );																																																				///< シザリング設定
	static void SetZoom( Bool IsUse, Float CenterX, Float CenterY, Float Zoom );																																														///< 拡大縮小設定
	static void SetPerspective( Bool IsUse, Float LookX, Float LookY, Float Scale );																																													///< パース補正設定

	static void Rendering( LSPRITE lSpr );																																																								///< レンダリング
	static void ResetBuffer( LSPRITE lSpr );																																																							///< バッファリセット
	static void UpdateBuffer( LSPRITE lSpr );																																																							///< バッファ更新

	static void DrawSquare( LSPRITE lSpr, CLunaRect *pDstRect, Float Pz, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 UvCount = 1 );																																	///< 四角形描画
	static void DrawSquareRotate( LSPRITE lSpr, CLunaRect *pDstRect, Float Pz, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 Angle, Uint32 UvCount = 1, Float fCx = 0.0f, Float fCy = 0.0f );																												///< 四角形回転描画
	static void DrawSquareRotateXYZ( LSPRITE lSpr, CLunaRect *pDstRect, Float Pz, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ, Uint32 UvCount = 1 );																				///< 四角形３軸回転描画
	static void DrawSquareMatrix( LSPRITE lSpr, CMatrix *pMatrix, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 UvCount = 1 );

	static void DrawRing( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );															///< リング状描画
	static void DrawRingRotate( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 Angle, Float Wrap, Uint32 UvCount = 1 );										///< リング状回転描画
	static void DrawRingRotateXYZ( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ, Float Wrap, Uint32 UvCount = 1 );	///< リング状３軸回転描画

	static void DrawRingEx( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );																					///< Ｚ軸リング状描画
	static void DrawRingExRotate( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 Angle, Float Wrap, Uint32 UvCount = 1 );																///< Ｚ軸リング状回転描画
	static void DrawRingExRotateXYZ( LSPRITE lSpr, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Uint32 AngleX, Uint32 AngleY, Uint32 AngleZ, Float Wrap, Uint32 UvCount = 1 );							///< Ｚ軸リング状３軸回転描画

	static void DrawRotate( LSPRITE lSpr, CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 Angle, Sint32 UvCount = 1 );																												///< 回転描画
	static void DrawRotateXYZ( LSPRITE lSpr, CPrimitivePoint2D *pPt0, CPrimitivePoint2D *pPt1, CPrimitivePoint2D *pPt2, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ, Sint32 UvCount = 1 );																				///< ３軸回転描画

	static void DrawList( LSPRITE lSpr, Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );																											///< リスト状描画
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	３Ｄクラス
*/
class LunaSprite3D
{
protected:
	static LibLuna::CSprite3DMgr *m_pSprMgr;																																														///< スプライトデータポインタ

public:
	static Bool Initialize( void );																																																	///< クラス初期化
	static void Finalize( void );																																																	///< クラス解放

	static void Reset( void );																																																		///< デバイスリセット時処理
	static void Restore( void );																																																	///< デバイスリストア時処理

	static LSPRITE3D Create( Uint32 VertexMax, eVertexPrimitiveType VertexType );																																					///< スプライト生成
	static void AttatchTexture( LSPRITE3D lSpr, Uint32 Stage, LTEXTURE lTex );																																						///< テクスチャを接続

	static void Release( LSPRITE3D lSpr );																																															///< スプライト解放

	static void TransformInit( LSPRITE3D lSpr3D );																																													///< 変換初期化
	static void TransformUpdate( LSPRITE3D lSpr3D );																																												///< 変換更新

	static void Heading( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< ヘッディング
	static void Pitching( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< ピッチング
	static void Rolling( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< ローリング
	static void RotationX( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< Ｘ軸回転
	static void RotationY( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< Ｙ軸回転
	static void RotationZ( LSPRITE3D lSpr3D, Sint32 Rot );																																											///< Ｚ軸回転
	static void Translation( LSPRITE3D lSpr3D, Float fPx, Float fPy, Float fPz );																																					///< 移動
	static void LookAt( LSPRITE3D lSpr3D, CVector3D *pPos, CVector3D *pEye, CVector3D *pUp );																																		///< 指定座標注視
	static void Scaling( LSPRITE3D lSpr3D, Float fSx, Float fSy, Float fSz );																																						///< ローリング

	static LPRIMITIVE3D GetPrimitive( LSPRITE3D lSpr );																																												///< プリミティブハンドル取得

	static void Rendering( LSPRITE3D lSpr );																																														///< レンダリング
	static void ResetBuffer( LSPRITE3D lSpr );																																														///< バッファリセット
	static void UpdateBuffer( LSPRITE3D lSpr );																																														///< バッファ更新

	static void DrawSquare( LSPRITE3D lSpr, CStyle *pStyle, Float Px, Float Py, Float Pz, Float fSx, Float fSy, CLunaRect *pSrcRects, D3DCOLOR Color, Uint32 UvCount );																///< 四角形描画
	static void DrawRing( LSPRITE3D lSpr, CStyle *pStyle, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float InRadius, Float OutRadius, D3DCOLOR InColor, D3DCOLOR OutColor, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );	///< リング状描画
	static void DrawRingEx( LSPRITE3D lSpr, CStyle *pStyle, Float Px, Float Py, Float Pz, CLunaRect *pSrcRects, Float Radius, Float Width, D3DCOLOR Color, Sint32 Num, Float Wrap, Uint32 UvCount = 1 );							///< Ｚ軸リング状描画

	static void DrawListXY( LSPRITE3D lSpr3D, Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );																	///< リスト描画
	static void DrawListYZ( LSPRITE3D lSpr3D, Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );																	///< リスト描画
	static void DrawListZX( LSPRITE3D lSpr3D, Float Px[], Float Py[], Float Pz[], Float Width[], Sint32 Angle[], D3DCOLOR Color[], Sint32 Count, CLunaRect *pSrc );																	///< リスト描画
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	サーフェイス管理クラス
*/
class LunaSurface
{
protected:
	static LibLuna::CSurfaceMgr *m_pSurfMgr;															///< サーフェイス管理用

public:
	static Bool Initialize( void );																		///< クラス初期化
	static void Finalize( void );																		///< クラス解放
	static void Reset( void );																			///< デバイスリセット時処理
	static void Restore( void );																		///< デバイスリストア時処理

	static LSURFACE Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );						///< 空のサーフェイスを生成
	static LSURFACE CreateFromFile( const char *pFileName, eSurfaceFormat Format );					///< 画像ファイルからサーフェイスを生成
	static LSURFACE CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );			///< レンダリングターゲットを生成
	static LSURFACE CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format );			///< 深度ステンシルサーフェイスを生成

	static void AddRef( LSURFACE lSurf );																///< 参照カウント加算
	static void Release( LSURFACE lSurf );																///< サーフェイスの解放

	static Bool Copy( LSURFACE lDstSurf, RECT *pDstRect, LSURFACE lSrcSurf, RECT *pSrcRect );			///< サーフェイスをコピー

	static HDC GetDC( LSURFACE lSurf );																	///< デバイスコンテキストを取得
	static void ReleaseDC(  LSURFACE lSurf, HDC hDC );													///< デバイスコンテキストを解放
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	システムクラス

	主にWindowsAPIを使用して、Windowsの基本的な
	処理を行う為のクラスです。
	主にファイル操作関連とコモンダイアログ関連の
	処理になります。
*/
class LunaSystem
{
public:
	static Bool CheckVolumeLabel( const char *pLabel, char *pPath );											///< CD-ROMドライブ無いのメディアのボリュームラベルをチェック
	static Bool SetWallPaper( const char *pFile, Sint32 Type, Bool IsReboot );									///< 壁紙を設定
	static Bool RunApplication( const char *pDir, const char *pAppName );										///< アプリケーションを起動
	static void OpenBrowser( const char *pURL );																///< ブラウザをオープン
	static void GetWindowsDir( char *pDir );																	///< Windowsディレクトリを取得
	static Bool CopyFile( const char *pSrc, char *pDst );														///< ファイルコピー
	static void DeleteFile( const char *pSrc );																	///< ファイル削除
	static Uint32 GetFileSize( const char *pSrc );																///< ファイルサイズ取得
	static Bool SaveData( const char *pFile, void *pData, Uint32 Size );										///< データセーブ
	static Bool LoadData( const char *pFile, void *pData, Uint32 Size );										///< データロード
	static Bool FolderSelect( char *pDir );																		///< フォルダ選択ダイアログ
	static Bool FileOpenDialog( char *pPath, const char *pTitle, const char *pFilter, const char *pExt );		///< ファイル選択ダイアログ
	static Bool FileSaveDialog( char *pPath, const char *pTitle, const char *pFilter, const char *pExt );		///< ファイル保存ダイアログ
	static Bool CreateLinkFile( const char *pShortcutFile, const char *pDescription, const char *pTargetFile );	///< ショートカット作成
	static Bool GetDesktopFolder( char *pPath );																///< デスクトップディレクトリ取得
	static void SetShowIME( Bool Flag );																		///< IME表示切替
	static Bool FileExist( const char *pFile );																	///< ファイル存在確認
	static Bool CreateDirectory( const char *pPath );															///< ディレクトリ生成
	static void GetMemorySize( Uint32 *pTotalMem, Uint32 *pFreeMem );											///< メモリ容量取得
	static Bool OpenColorDialog( Sint32 *pR, Sint32 *pG, Sint32 *pB );											///< 色選択ダイアログ
	static void GetLocalTime( Sint32 *pYear, Sint32 *pMonth, Sint32 *pWeekDay, Sint32 *pDay, Sint32 *pHour, Sint32 *pMinute, Sint32 *pSecond, Sint32 *pMilliSecond );	///< ローカル時間取得
	static Sint32 DayOfMonth( Sint32 Year, Sint32 Month );														///< 月の日数取得
	static Sint32 DayOfWeek( Sint32 Year, Sint32 Month );														///< 月の開始曜日を取得
	static void KeyCheck( eKeyState *pKey, Uint32 KeyNo );														///< キーボードのキーチェック
	static void ChangeEndian( void *pData, Uint32 Bytes );														///< エンディアン変換
	static void GetLongFullPathName( const char *pSrcPath, char *pDstPath );									///< ショートファイル名をロングファイル名に変換

	static void HostToNet( void *pData, Sint32 Size );															///< ホストバイトオーダーをネットワークバイトオーダーに変換
	static void NetToHost( void *pData, Sint32 Size );															///< ネットワークバイトオーダーをホストバイトオーダーに変換

	static void GetSocketError( Sint32 ErrorCode, char *pErrStr );												///< ソケットのエラーを取得します
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	テクスチャ管理クラス
*/
class LunaTexture
{
	friend class Luna3D;

protected:
	static LibLuna::CTextureMgr	*m_pTexMgr;																												///< テクスチャ管理用

public:
	static Bool Initialize( void );																														///< クラス初期化
	static void Finalize( void );																														///< クラス解放
	static void Reset( void );																															///< デバイスリセット時処理
	static void Restore( void );																														///< デバイスリストア時処理

	static void SetOffsetUV( Float offset );																											///< テクスチャオフセットＵＶ設定
	static Float GetOffsetUV( void );																													///< テクスチャオフセットＵＶ取得

	static Sint32 GetWidth( LTEXTURE lTex );																											///< テクスチャの横サイズ取得
	static Sint32 GetHeight( LTEXTURE lTex );																											///< テクスチャの縦サイズ取得
	static Sint32 GetOriginalWidth( LTEXTURE lTex );																									///< 元画像の横サイズ取得
	static Sint32 GetOriginalHeight( LTEXTURE lTex );																									///< 元画像の縦サイズ取得

	static LTEXTURE Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );																		///< 空のテクスチャ生成
	static LTEXTURE CreateEx( Uint32 Width, Uint32 Height, Uint32 Levels, Uint32 Usage, D3DFORMAT Format, D3DPOOL Pool );								///< 空のテクスチャ生成
	static LTEXTURE CreateFromFile( const char *pFileName, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );								///< ファイルからテクスチャ生成
	static LTEXTURE CreateFromLAG( const char *pFileName, const char *pDataName, eSurfaceFormat Format );												///< ＬＡＧファイルからテクスチャ生成
	static LTEXTURE CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );															///< レンダリングターゲットテクスチャ生成
	static LTEXTURE CreateFromMemory( void *pData, Uint32 Size, eSurfaceFormat Format, D3DCOLOR KeyColor = COLORKEY_DISABLE );							///< メモリからテクスチャを生成
	static LTEXTURE CreateFromRenderTarget( LTEXTURE lTex );																							///< レンダリングターゲットの内容をコピーしたテクスチャを作成

	static LTEXTURE SearchHandle( const char *pFileName );																								///< 指定ファイル名のテクスチャハンドル取得
	static void AddRef( LTEXTURE lTex );																												///< 参照カウント加算

	static void ColorFill( LTEXTURE lTex, D3DCOLOR Color );																								///< 指定色での塗りつぶし
	static Bool Lock( LTEXTURE lTex, void **ppBits, Uint32 *pPitch, D3DFORMAT *pFormat, Uint32 *pWidth, Uint32 *pHeight, RECT *pLockRect = NULL );		///< テクスチャロック
	static void Unlock( LTEXTURE lTex, Bool IsUpdate = true );																							///< テクスチャロック解除
	static void UpdateTexture( LTEXTURE lTex );																											///< テクスチャ更新

	static void Release( LTEXTURE lTex );																												///< テクスチャ解放

	static void Draw( LTEXTURE lTex, CLunaRect *pDstRect, CLunaRect *pSrcRect, D3DCOLOR Color );														///< テクスチャ描画
	static void DrawRotate( LTEXTURE lTex, CLunaRect *pDstRect, CLunaRect *pSrcRect, D3DCOLOR Color, Uint32 Angle, Sint32 Cx = 0, Sint32 Cy = 0 );		///< テクスチャ回転描画

	static void DrawMulti( LTEXTURE *plTexList, CLunaRect *pDstRect, CLunaRect *pSrcRectList, D3DCOLOR Color, Sint32 Num );								///< マルチテクスチャ描画

	static Float GetLastU( LTEXTURE lTex, Float fPos );																									///< テクスチャの最終的なＵ値を取得
	static Float GetLastV( LTEXTURE lTex, Float fPos );																									///< テクスチャの最終的なＶ値を取得

	static D3DFORMAT GetFormat( LTEXTURE lTex );																										///< テクスチャフォーマットを取得
	static void GetInstance( LTEXTURE lTex, IDirect3DTexture9 **ppTexture );																			///< テクスチャハンドルからIDirect3DTexture9を取得
	static void GetBaseInstance( LTEXTURE lTex, IDirect3DTexture9 **ppTexture );																		///< テクスチャハンドルからIDirect3DTexture9を取得

	static Bool StretchBlt( LTEXTURE lTexDst, RECT *pDstRect, LTEXTURE lTexSrc, RECT *pSrcRect, Bool IsUvToTexel = false );								///< テクスチャからテクスチャへコピー
	static Bool SaveToFile( LTEXTURE lTex, const char *pFile, D3DXIMAGE_FILEFORMAT Format );															///< テクスチャをファイルに保存

	static HDC GetDC( LTEXTURE lTex );																													///< デバイスコンテキスト取得
	static void ReleaseDC( LTEXTURE lTex, HDC hDC );																									///< デバイスコンテキスト解放
};




//=============================================================================
// INCLUDE
//=============================================================================


//=============================================================================
// CLASS
//=============================================================================
/**
	@brief	ビデオレンダラー管理クラス
*/
class LunaVMR9
{
protected:
	static LibLuna::CVMR9Mgr	*m_pVMRMgr;							///< VMR9ムービー管理用

public:
	static Bool Initialize( void );									///< クラス初期化
	static void Finalize( void );									///< クラス解放
	static void Reset( void );										///< デバイスリセット時処理
	static void Restore( void );									///< デバイスリストア時処理

	static void AddRef( LVMR9 lVMR9 );								///< 参照カウンタ＋１
	static void Release( LVMR9 lVMR9 );								///< 参照カウンタ－１

	static LVMR9 CreateFromFile( const char *pFile );				///< ファイルから読み込み
	static Bool Play( LVMR9 lVMR9 );								///< 再生
	static void Stop( LVMR9 lVMR9 );								///< 停止
	static Bool IsPlay( LVMR9 lVMR9 );								///< 再生中かチェック

	static void Render( LVMR9 lVMR9 );								///< バックバッファにレンダリング
	static LTEXTURE GetTexture( LVMR9 lVMR9 );						///< レンダリング先テクスチャハンドル取得
};


#endif	// ___LUNA_DX9___
