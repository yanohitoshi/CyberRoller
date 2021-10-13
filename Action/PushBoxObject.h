#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class BoxCollider;
class Mesh;
class GeometryInstanceComponent;

/*
@struct PushBoxData
	�v�b�V���{�b�N�X�ň����ŗL�̃f�[�^�\����
*/
struct PushBoxData
{
	MoveDirectionTag tag;
	Vector3 direction;
	Vector3 distance;
	float cutBackSpeed;
	float speed;
};

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
	@param  �v�b�V���{�[�h���X�V����̂Ɏg�p����f�[�^�\����
	*/
	PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, PushBoxData _pushBoxData);
	
	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~PushBoxObject()override;

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

