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
//関数のプロトタイプ宣言
//================================================
void Init_Field(FieldData &field);//初期化
void Load_Field(FieldData &field, char *name, Sint32 ZoomSize, int ColorKey);//フィールド読み込み
void ViewFrustumCulling(FieldData &field);//ビューフラスタムカリング

void Rendering_Field(FieldData &field);//レンダリング処理
void SetShader(FieldData &field);//シェーダー設定
void Release_Field(FieldData &field);//メモリ開放


#endif