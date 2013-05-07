//================================================
//include
//================================================
#include "model.h"

//================================================
//モデル初期化関数
//================================================
void CModelData::Initialize()
{
	fPosX = 100;
	fPosY = 0;
	fPosZ = 0;
	
}

//================================================
//モデルデータ読み込み
//================================================
void CModelData::LoadData(char *name, int ColorKey)
{
	lModel = LunaModelEx::CreateFromFile(name, FORMAT_TEXTURE_3D, ColorKey);
	
	LunaModelEx::AutoCreateShader(lModel, AUTO_SHADER_NORMAL_NOLIGHT);
	
}

//================================================
//モデルデータ変形
//================================================
void CModelData::Translation()
{
	/*変換初期化*/
	LunaModelEx::TransformInit(lModel);
	
	/*移動*/
	//LunaModel::Translation(lModel, 0, 0, 0);
	
	/*拡大*/
	LunaModelEx::Scaling(lModel, 2, 2, 2);
	
	/*回転*/
	//LunaModelEx::RotationY(lModel, GET_ANGLE(-5) );
	
	/*変換更新*/
	LunaModelEx::TransformUpdate(lModel);
	
}

//================================================
//モデルデータレンダリング
//================================================
void CModelData::Rendering()
{
	LunaModelEx::Rendering(lModel);
}

//================================================
//モデルデータメモリ開放
//================================================
void CModelData::Release()
{
	LunaModelEx::Release(lModel);
}

//================================================
//モデルデータデバッグ
//================================================
void CModelData::Debug()
{
	LunaDebug::DrawString("Px:%f", fPosX);
	LunaDebug::DrawString("Py:%f", fPosY);
	LunaDebug::DrawString("Pz:%f", fPosZ);
}