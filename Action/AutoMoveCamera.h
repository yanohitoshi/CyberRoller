#pragma once
#include "CameraObjectBase.h"

class AutoMoveCamera :
    public CameraObjectBase
{
public:

	/*
	@brief	�R���X�g���N�^
	@param	�|�W�V����
	@param	�v���C���[�̃|�C���^
	*/
	AutoMoveCamera(const Vector3 _pos, PlayerObject* _playerObject);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~AutoMoveCamera();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime = 1.0f)override;

	/*
	@fn ���͂������Ŏ󂯎��X�V�֐�
	@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	@param	_keyState ���͏��
	*/
	void GameObjectInput(const InputState& _keyState)override;

private:

};

