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
@file BoxObject.h
@brief �{�b�N�X�I�u�W�F�N�g�̐����ƍX�V�������s��
*/
class GroundObject : public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	GroundObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, bool _isLight = false);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~GroundObject();
	
	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// Mesh���Ǘ�����N���X
	Mesh* mesh;
	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;

	// �����蔻����s���N���X
	BoxCollider* boxCollider;
};

