#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectBase.h"

/*
@file NormalEnemyObject.h
@brief �����Ȃ��G�I�u�W�F�N�g�N���X
*/
class NormalEnemyObject :
    public EnemyObjectBase
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	@param	�ǐՂ���I�u�W�F�N�g�̃|�C���^
	*/
	NormalEnemyObject(const Vector3& _pos, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~NormalEnemyObject()override;

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	/*
	@fn �߂荞�ݔ���
	@param	������AABB
	@param	�����AABB
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB)override;

	// ��]�p�x
	const float Angle;

public:

};