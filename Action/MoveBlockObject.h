#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class BoxCollider;
class Mesh;

struct MoveBlockData
{
	MoveDirectionTag tag;
	Vector3 direction;
	Vector3 distance;
	float speed;
};

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
	@param  �������ɕK�v�ȃf�[�^�\����
	*/
	MoveBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, MoveBlockData _data);

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
	@fn �������֐�
	*/
	void MovableProcess();

	/*
	@fn ���]�`�F�b�N�����֐�
	*/
	void ChackInversionProcess();

	/*
	@fn X�����]�`�F�b�N�����֐�
	*/
	void ChackAxisX();

	/*
	@fn Y�����]�`�F�b�N�����֐�
	*/
	void ChackAxisY();

	/*
	@fn Z�����]�`�F�b�N�����֐�
	*/
	void ChackAxisZ();

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

