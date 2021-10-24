#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class Mesh;
class TitlePlayerObject;

/*
@file TitleJumpAttackPlayerObject.h
@brief �^�C�g���V�[�����ł̃W�����v�A�^�b�N�v���C���[
*/
class TitleJumpAttackPlayerObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�e�N���X�̃|�C���^
	@param	�I�u�W�F�N�g�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	TitleJumpAttackPlayerObject(TitlePlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~TitleJumpAttackPlayerObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn ��]�����֐�
	*/
	void RotationProcess(float _angle, Vector3 _axis);

private:

	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	TitlePlayerObject* ownerObject;
	Mesh* mesh;
	// Z�������炷���߂̒萔
	const float ShiftPositionZ;
public:

	/*
	@fn meshComponent��getter�֐�
	@return meshComponent�@meshComponent�N���X�̃|�C���^��Ԃ�
	*/
	MeshComponent* GetMeshComponent() { return meshComponent; }

};