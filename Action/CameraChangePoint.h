#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"


// �N���X�̑O���錾
class BoxCollider;

class CameraChangePoint :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�����蔻��pAABB
	@param	�I�u�W�F�N�g���ʗptag
	*/
	CameraChangePoint(const Vector3& _p, const AABB& _box,Vector3& _changeOffset ,const Tag& _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~CameraChangePoint();

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
	@param	��������GameObject�̓����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;
	// �����蔻����s���N���X
	BoxCollider* boxCollider;

	Vector3 changeOffset;
};

