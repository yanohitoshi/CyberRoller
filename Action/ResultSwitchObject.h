#pragma once
#include "GameObject.h"
#include <glew.h>

// �N���X�̑O���錾
class ChangeColorMeshComponent;

/*
@file ResultSwitchObject.h
@brief ���U���g�V�[���p�X�C�b�`class
*/
class ResultSwitchObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	ResultSwitchObject(GameObject* _owner, const Vector3& _size, const Tag& _objectTag, const float _angle );

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~ResultSwitchObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// �F�ύX�@�\�t��MeshComponent
	ChangeColorMeshComponent* meshComponent;

	// �S�X�C�b�`��ON�̎��̐F
	const Vector3 AllClearColer;
	// �X�C�b�`��ON�̎��̐F
	const Vector3 OnColor;
	// �X�C�b�`��OFF�̎��̐F
	const Vector3 OffColor;
};

