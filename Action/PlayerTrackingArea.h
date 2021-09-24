#pragma once
#include "GameObject.h"

class SphereCollider;
class TrackingEnemyObject;

class PlayerTrackingArea :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	PlayerTrackingArea(const Tag& _objectTag,TrackingEnemyObject* _ownerEnemy);

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
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// �����蔻����s���N���X
	SphereCollider* sphereCollider;
	TrackingEnemyObject* ownerEnemy;
};

