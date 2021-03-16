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
@file NeedleObject.h
@brief NeedleObject�̐����ƍX�V���s��
*/
class NeedleObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�e�ƂȂ�object�̃|�C���^
	@param	�eobject�Ƃ̊Ԋu
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	NeedleObject(GameObject* _owner, const Vector3& _offset, const Vector3& _size, const Tag& _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~NeedleObject();
	
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

};

