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
	@param	�v���C���[�̃|�C���^
	@param	�V�[���̍Ō�̓����ǃI�u�W�F�N�g�̃|�C���^
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
	@param	��������GameObject�̓����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	Mesh* mesh;
	// �v���C���[�̃|�C���^�������߂̃|�C���^�ϐ�
	PlayerObject* playerObject;
	// �V�[���Ō�̓����ǂ������߂̃|�C���^�ϐ�
	MoveWallBlock* lastMoveWallBlock;
	// �����蔻����s���N���X
	BoxCollider* boxCollider;

	// ��]����ۂ̊p�x
	const float Angle;
	// �ړ����x�̒萔
	const float MoveSpeed;
};

