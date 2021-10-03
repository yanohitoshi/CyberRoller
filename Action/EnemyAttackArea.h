#pragma once
#include "GameObject.h"

// �N���X�̑O���錾
class SphereCollider;
class EnemyObjectBase;

class EnemyAttackArea :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	EnemyAttackArea(const Tag& _objectTag, EnemyObjectBase* _ownerEnemy);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~EnemyAttackArea();

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

	// �����蔻����s���N���X
	SphereCollider* sphereCollider;
	// �e�ƂȂ�N���X�̃|�C���^
	EnemyObjectBase* ownerEnemy;
	// �U���G���A�̃T�C�Y
	const float AttackArea;
	int disableCount;
	// �U������G���A���L�����ǂ���
	bool isEnable;
	// �L���ɐ؂�ւ��鎞��
	const int EnableTime;
};

