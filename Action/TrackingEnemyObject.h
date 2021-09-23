#pragma once
#include "EnemyObjectBase.h"

class SphereCollider;

class TrackingEnemyObject :
    public EnemyObjectBase
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	*/
	TrackingEnemyObject(const Vector3& _pos, const Tag _objectTag, float _moveSpeed,GameObject* _trackingObject);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~TrackingEnemyObject()override;

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn �߂荞�ݔ���
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB)override;

private:

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(�W�����v�U�����s���G�l�~�[�Ƃ̔�������)
	@param	��������GameObject
	*/
	void OnCollisionTracking(const GameObject& _hitObject);

	// ���̂̓����蔻����s���N���X
	SphereCollider* trackingSphereCol;

public:

};

