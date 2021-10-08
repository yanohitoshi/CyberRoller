#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class PlayerObject;
class SphereCollider;
class BoxCollider;

/*
@file JumpAttackPlayerObject.h
@brief �W�����v�U�����̃v���C���[�I�u�W�F�N�g
*/
class JumpAttackPlayerObject :
    public GameObject
{
public:
	
	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	JumpAttackPlayerObject(PlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~JumpAttackPlayerObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	@param	��������GameObject�̓����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

private:

	// 3D���f���̕`����s���N���X
    MeshComponent* meshComponent;
	// �e�ƂȂ�I�u�W�F�N�g�̃|�C���^
	PlayerObject* ownerObject;
	// AABB�̓����蔻����s���N���X
	BoxCollider* boxCollider;
	// ���̂̓����蔻����s���N���X
	SphereCollider* sphereCollider;

	// ��]����ۂ̊p�x
	float rotationAngle;
	// ��]�p�ɑ���������l�萔
	const float Rotation;
	// Z�������炷���߂̒萔
	const float ShiftPositionZ;
};

