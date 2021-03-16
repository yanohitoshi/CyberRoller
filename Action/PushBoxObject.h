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
@file PushBoxObject.h
@brief PushBoxObject�̐����ƍX�V���s��
*/
class PushBoxObject :
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
	@param�@�߂�ۂɑ��x�𗎂Ƃ�����
	@param�@�ǂ̕����ɓ����̂����ʂ��邽�߂̃^�O
	*/
	PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed , MoveDirectionTag _moveTag);
	
	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~PushBoxObject();

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

};

