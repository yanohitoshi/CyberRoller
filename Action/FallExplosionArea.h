#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class BoxCollider;
class FallExplosionObject;

/*
@file FallExplosionArea.h
@brief �����J�n����G���A�I�u�W�F�N�g�N���X
*/
class FallExplosionArea:
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	@param	�G���A�̍L��
	@param	�������̐�
	*/
	FallExplosionArea(const Vector3& _pos, const Tag _objectTag, Vector3& _area, int _quantity);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~FallExplosionArea()override;

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

	// AABB�̓����蔻����s���N���X
	BoxCollider* boxCollider;

	// ���e���~��G���A
	Vector3 area;

	// �G���A�ɍ~���
	int quantity;

	bool isFallStart;

	std::vector<FallExplosionObject*> fallExplosionObjects;

public:

	bool GetIsFallStart() { return isFallStart; }

	Vector3 GetArea() { return area; }
};

