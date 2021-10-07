//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "RespawnPoint.h"
#include "BoxCollider.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�����蔻��pAABB
@param	�I�u�W�F�N�g���ʗptag
*/
RespawnPoint::RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false,_objectTag)
	, CorrectionPositionZ(600.0f)
{
	// �|�W�V�����̏�����
	position = _p;
	// ������␳
	position.z += CorrectionPositionZ;
	// �|�W�V�������Z�b�g
	SetPosition(position);

	// �����蔻��p�{�b�N�X�R���C�_�[�t�^
	boxCollider = new BoxCollider(this,PhysicsTag::RESPOWN_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(_box);

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
RespawnPoint::~RespawnPoint()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void RespawnPoint::UpdateGameObject(float _deltaTime)
{
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	��������GameObject�̓����蔻��^�O
*/
void RespawnPoint::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
}