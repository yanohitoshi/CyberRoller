//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraChangePoint.h"
#include "BoxCollider.h"
#include "CameraObjectStateBase.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�����蔻��pAABB
@param	�ύX����Ԋu
@param	�I�u�W�F�N�g���ʗptag
*/
CameraChangePoint::CameraChangePoint(const Vector3& _p, const AABB& _box, Vector3& _changeOffset,const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	// �|�W�V�����̏�����
	position = _p;
	changeOffset = _changeOffset;
	// �|�W�V�������Z�b�g
	SetPosition(position);

	// �����蔻��p�{�b�N�X�R���C�_�[�t�^
	boxCollider = new BoxCollider(this, PhysicsTag::CAMERA_MODE_CHANGE_AREA, GetOnCollisionFunc());
	boxCollider->SetObjectBox(_box);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CameraChangePoint::~CameraChangePoint()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CameraChangePoint::UpdateGameObject(float _deltaTime)
{
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	��������GameObject�̓����蔻��^�O
*/
void CameraChangePoint::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �v���C���[�Ɠ���������
	if (_physicsTag == PhysicsTag::PLAYER_TAG)
	{
		mainCamera->SetNextState(CameraState::CHANGEMODE);
		mainCamera->SetOffsetPosition(changeOffset);
	}
}