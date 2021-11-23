#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectBase.h"

/*
@file MoveEnemyObject.h
@brief �ړ�����G�I�u�W�F�N�g�N���X
*/
class MoveEnemyObject :
    public EnemyObjectBase
{
public:
	
	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	@param	�ǐՑΏۂ̃I�uy�W�F�N�g�̃|�C���^
	@param	���E�Ɉړ�����G���ŗL�Ŏ��f�[�^�\����
	*/
	MoveEnemyObject(const Vector3& _pos, const Tag _objectTag, MoveEnemyData _moveEnemyData);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~MoveEnemyObject()override;

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn �߂荞�ݔ���
	@param	������AABB
	@param	�����AABB
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB)override;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;
};