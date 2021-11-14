#pragma once
#include "GameObject.h"

// �N���X�̑O���錾
class SphereCollider;
class EnemyObjectBase;

/*
@file PlayerTrackingArea.h
@brief �v���C���[�����m����X�t�B�A����N���X
*/
class PlayerTrackingArea :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�I�u�W�F�N�g���ʗptag
	@param	�e�ƂȂ�G�N���X�̃|�C���^
	@param	�G���A�̑傫���ƂȂ�l
	*/
	PlayerTrackingArea(const Tag& _objectTag,EnemyObjectBase* _ownerEnemy,float _areaValue);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~PlayerTrackingArea();

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
	@param	�����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// �����蔻����s���N���X
	SphereCollider* sphereCollider;
	// �e�ƂȂ�N���X�̃|�C���^
	EnemyObjectBase* owner;
};

