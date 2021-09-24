#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class BoxCollider;
class Mesh;
class PlayerObject;
class MoveWallBlock;

/*
@file ClearPointObject.h
@brief �N���A�|�C���g�̐����ƍX�V�������s��
*/
class ClearPointObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	*/
	ClearPointObject(const Vector3& _pos, const Tag& _objectTag, PlayerObject* _playerObject, MoveWallBlock* _lastMoveWallBlock);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~ClearPointObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;


private:
	
	/*
	@fn ��]�����֐�
	*/
	void RotationProcess();

	/*
	@fn �������֐�
	*/
	void MovableProcess();
	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	Mesh* mesh;

	PlayerObject* playerObject;
	MoveWallBlock* lastMoveWallBlock;
	// �����蔻����s���N���X
	BoxCollider* boxCollider;
	// ��]����ۂ̊p�x
	const float Angle;
	// �ړ����x�̒萔
	const float MoveSpeed;
};

