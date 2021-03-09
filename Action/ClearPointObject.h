#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file ClearPointObject.h
@brief �N���A�|�C���g�̐����ƍX�V�������s��
*/

class ClearPointObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	*/
	ClearPointObject(const Vector3& _pos, const Tag& _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~ClearPointObject();

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
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	Mesh* mesh;

	// �����蔻����s���N���X
	BoxCollider* boxCollider;
	// ��]������Ƃ��̊p�x
	float angle;
};

