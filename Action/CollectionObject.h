#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class BoxCollider;
class Mesh;

enum class CollectionTag
{
	FIRST,
	SECOND,
	THIRD
};

class CollectionObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	*/
	CollectionObject(const Vector3& _pos, const Tag& _objectTag, CollectionTag _collectionTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~CollectionObject()override;

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
	void RotationProcess(float _angle,Vector3 _axis);

	/*
	@fn �������֐�
	*/
	void Movable(float _deltaTime);

	/*
	@fn �������֐�
	*/
	void Collected(float _deltaTime);

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	@param	��������GameObject�̓����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	Mesh* mesh;
	BoxCollider* boxCollider;
	CollectionTag collectionTag;

	float collectedRotationAngle;
	bool isCollected;
	int collectedCount;
	int frameCount;
	float value;
	float rate;

public:

	bool GetIsCollected() { return isCollected; }

	CollectionTag GetCollectionTag() { return collectionTag; }
};

