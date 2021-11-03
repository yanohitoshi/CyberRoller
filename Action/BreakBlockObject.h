#pragma once
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class BoxCollider;
class Mesh;

class BreakBlockObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	BreakBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~BreakBlockObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	@param	�����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// Mesh���Ǘ�����N���X
	Mesh* mesh;
	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	// �����蔻����s���N���X
	BoxCollider* boxCollider;
	// �v���C���[�����蔲���Ȃ��悤��AABB�̃T�C�Y��␳���邽�߂̒萔
	const float CorrectionAabbValue;
};