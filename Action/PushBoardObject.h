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
@file PushBoardObject.h
@brief PushBoardObject�̐����ƍX�V���s��
*/
class PushBoardObject :
	public GameObject
{
public:
	
	/*
	@fn �R���X�g���N�^
	@param	�e�ƂȂ�object�̃|�C���^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	@param  �ǂꂭ�炢�̋��������̂�
	@param�@�ǂ̕����ɓ����̂�
	@param�@���x
	@param�@�߂�ۂɑ��x�𗎂Ƃ�����
	@param�@�ǂ̕����ɓ����̂����ʂ��邽�߂̃^�O
	*/
	PushBoardObject(GameObject* _owner,const Vector3& _p, const Vector3& _size, const Tag& _objectTag ,const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed, MoveDirectionTag _moveTag);
	
	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~PushBoardObject();
	
	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

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
	const float moveSpeed;
	const float cutBackSpeed;
	//�ړ�����
	Vector3 direction;
	// �ǂ̕����ɓ������𔻒肷�邽�߂�Tag�ϐ�
	MoveDirectionTag moveTag;

};
