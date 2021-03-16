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
@file NextSceneObject.h
@brief NextSceneObject�̐����ƍX�V���s��
*/
class NextSceneObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�I�u�W�F�N�g���ʗptag
	*/
	NextSceneObject(const Vector3& _pos, const Tag& _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~NextSceneObject();
	
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
	// �������ꂽ�Ƃ��̃|�W�V������ۑ�����悤
	Vector3 firstPos;
	// ��]����ۂ̊p�x�ϐ�
	float angle;

};

