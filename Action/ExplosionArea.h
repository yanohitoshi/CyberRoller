#pragma once
#include "GameObject.h"

// �N���X�̑O���錾
class SphereCollider;
class ExplosionObject;

class ExplosionArea :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�e�N���X�̃|�C���^
	*/
	ExplosionArea(const Tag& _objectTag, ExplosionObject* _owner);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~ExplosionArea();

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
	ExplosionObject* owner;

	bool isActive;
	// �U���G���A�̃T�C�Y
	const float ExplosionAreaSize;
};

