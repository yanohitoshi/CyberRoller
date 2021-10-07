//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BoneTransform.h"

/*
@fn 行列を出力
@return 回転と平行移動から、行列を返す
*/
Matrix4 BoneTransform::ToMatrix() const
{
	// 回転と平行移動から、行列を返す
	Matrix4 rot = Matrix4::CreateFromQuaternion(rotation);
	Matrix4 trans = Matrix4::CreateTranslation(translation);

	return rot * trans;
}

/*
@fn ボーン補間
*/
BoneTransform BoneTransform::Interpolate(const BoneTransform& a, const BoneTransform& b, float f)
{
	BoneTransform retVal;
	retVal.rotation = Quaternion::Slerp(a.rotation, b.rotation, f);        // aからb に数値fで球面線形補間(slerp)する
	retVal.translation = Vector3::Lerp(a.translation, b.translation, f);   // 平行移動成分はf で線形補間(lerp)する
	return retVal;
}