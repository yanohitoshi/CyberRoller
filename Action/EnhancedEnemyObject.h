#pragma once
#include "EnemyObjectBase.h"

// �N���X�̑O���錾
class SphereCollider;
class Mesh;

/*
@file EnhancedEnemyObject.h
@brief �W�����v�U���Ŏ��ȂȂ��������ꂽ�G�I�u�W�F�N�g�N���X
*/
class EnhancedEnemyObject :
    public EnemyObjectBase
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	@param	�ړ����x
	@param	�ǐՂ���I�u�W�F�N�g�̃|�C���^
	@param	�ǐՃG���A�̒l
	*/
	EnhancedEnemyObject(const Vector3& _pos, const Tag _objectTag, float _moveSpeed, float _areaValue);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~EnhancedEnemyObject()override;

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn �߂荞�ݔ���
	@param	������AABB
	@param	�����AABB
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB)override;

private:

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	@param	�����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// Mesh�̓ǂݍ��݂��s���N���X
	Mesh* mesh;

	// ��]�p�x
	const float Angle;

public:
};

