//================================================
//include
//================================================
#include "field.h"

//================================================
//初期化関数
//================================================
void Init_Field(FieldData &field)
{
	field.Field = INVALID_FIELD;
	field.lShaderFx = INVALID_SHADERFX;
}


//================================================
//読み込み
//================================================
void Load_Field(FieldData &field, char *name, Sint32 ZoomSize, int ColorKey)
{
	field.Field = LunaField::CreateFromFile(name, 5, ZoomSize, FORMAT_TEXTURE_3D, false, ColorKey);
}

//================================================
//ビューフラスタムカリング
//================================================
void ViewFrustumCulling(FieldData &field)
{
	LunaField::ViewfrustumCulling(field.Field);
}

//================================================
//レンダリング
//================================================
void Rendering_Field(FieldData &field)
{
	LunaField::Rendering(field.Field);
}

//================================================
//シェーダー設定
//================================================
void SetShader(FieldData &field)
{
	/*フィールド用エフェクトファイル*/
	field.lShaderFx = LunaShaderFx::CreateFromFile("field00.fx");
		
	/*フィールドにシェーダー設定*/
	LunaField::SetEffectHandle(field.Field, field.lShaderFx);
	
	LunaShaderFx::Release(field.lShaderFx);
		
	LunaField::SetEffectSendData(field.Field, FX_SEND_TRANSFORM | FX_SEND_FOGDATA);
	
}

//================================================
//メモリ開放
//================================================
void Release_Field(FieldData &field)
{
	LunaField::Release(field.Field);
	LunaShaderFx::Release(field.lShaderFx);
}

