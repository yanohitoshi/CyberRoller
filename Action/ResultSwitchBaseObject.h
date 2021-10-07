#pragma once
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;

/*
@file ResultSwitchBaseObject.h
@brief ���U���g�V�[���p�X�C�b�`�̓y��class
*/
class ResultSwitchBaseObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	ResultSwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~ResultSwitchBaseObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;

	// ���U���g�p�X�C�b�`�������ꍇ�ɉ�]������p�x
	const float Angle;
};

