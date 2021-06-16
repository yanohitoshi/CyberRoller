#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------

#include "Math.h"

/*
 @file BoneTransform.h
 @fn モデルのボーン変換
*/
class BoneTransform
{
public:

	//回転
	Quaternion rotation;
	// 移動
	Vector3 translation;

	/*
	@fn 行列を出力
	@return 回転と平行移動から、行列を返す
	*/
	Matrix4 ToMatrix() const;                  
	
	/*
	@fn ボーン補間
	*/
	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f); 

};
