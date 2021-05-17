#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file MoveBlockObject.h
@brief MoveBlockObject�̐����ƍX�V���s��
*/
class MoveBlockObject :
    public GameObject
{

public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	@param  �ǂꂭ�炢�̋��������̂�
	@param�@�ǂ̕����ɓ����̂�
	@param�@���x
	@param�@�ǂ̕����ɓ����̂����ʂ��邽�߂̃^�O
	*/
	MoveBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction,const float& _speed,MoveDirectionTag _moveTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~MoveBlockObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	
	/*
	@fn �ړ���Ԃ��m�F����֐�
	*/
	void ChackMoveProcess();

	// 3D���f���̕`����s���N���X
	Mesh* mesh;
	MeshComponent* meshComponent;
	// �����蔻����s���N���X
	BoxCollider* boxCollider;

	//�����ʒu
	Vector3 initPos;
	//�ړ���ʒu
	Vector3 goalPos;
	//���]�t���O
	bool inversionFlag;
	//�ړ����x
	float moveSpeed;
	//�ړ�����
	Vector3 direction;
	// �ǂ̕����ɓ������𔻒肷�邽�߂�Tag�ϐ�
	MoveDirectionTag moveTag;

};

