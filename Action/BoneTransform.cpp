//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BoneTransform.h"

/*
@fn �s����o��
@return ��]�ƕ��s�ړ�����A�s���Ԃ�
*/
Matrix4 BoneTransform::ToMatrix() const
{
	// ��]�ƕ��s�ړ�����A�s���Ԃ�
	Matrix4 rot = Matrix4::CreateFromQuaternion(rotation);
	Matrix4 trans = Matrix4::CreateTranslation(translation);

	return rot * trans;
}

/*
@fn �{�[�����
*/
BoneTransform BoneTransform::Interpolate(const BoneTransform& a, const BoneTransform& b, float f)
{
	BoneTransform retVal;
	retVal.rotation = Quaternion::Slerp(a.rotation, b.rotation, f);        // a����b �ɐ��lf�ŋ��ʐ��`���(slerp)����
	retVal.translation = Vector3::Lerp(a.translation, b.translation, f);   // ���s�ړ�������f �Ő��`���(lerp)����
	return retVal;
}