//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@fn �O���x�N�g����p���ăL�����N�^�[����]������֐�
@param	_owner �e�N���X�̃|�C���^
@param	_forward ���̃t���[���̑O���x�N�g��
@param	_tmpForward �O�̃t���[���̑O���x�N�g��
*/
void ExplosionObjectStateBase::RotationProcess(ExplosionObjectBase* _owner, float _angle, Vector3 _axis)
{
	//_axis����_angle�x��]������
	float radian = Math::ToRadians(_angle);
	Quaternion rot = _owner->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	_owner->SetRotation(target);
}

/*
@fn �����ړ�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ExplosionObjectStateBase::VerticalMove(ExplosionObjectBase* _owner, float _deltaTime)
{
	++frameCount;

	if (frameCount % ChangeRateTime == 0)
	{
		++angle;
		rate = Math::Cos(angle);
	}

	velocity.z = rate * VerticalMoveSpeed;

	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
}