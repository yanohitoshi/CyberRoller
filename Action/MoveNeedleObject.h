#pragma once
#include "NeedleObject.h"

/*
@file MoveNeedleObject.h
@brief MoveNeedleObject�̐����ƍX�V���s��
*/
class MoveNeedleObject :
    public NeedleObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�e�ƂȂ�object�̃|�C���^
	@param	�eobject�Ƃ̊Ԋu
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	@param	���x
	*/
	MoveNeedleObject(GameObject* _owner, const Vector3& _offset, const Vector3& _size, const Tag& _objectTag, const float& _speed);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~MoveNeedleObject();

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
	// �e�ƂȂ�N���X�̃|�C���^�ۑ��p�ϐ�
	GameObject* owner;

	//�����ʒu
	Vector3 initPos;
	//�ړ���ʒu
	Vector3 goalPos;
	//�ړ��J�n�t���O
	bool moveFlag;
	//���]�t���O
	bool inversionFlag;
	//�ړ��Ԋu�J�E���g
	int intervalCount;
	//�ړ����x
	const float moveSpeed;
	//�ړ�����
	Vector3 direction;

};

