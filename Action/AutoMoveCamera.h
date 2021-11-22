#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectBase.h"

/*
@file AutoMoveCamera.h
@brief �����ړ�����J�����N���X
*/
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

	// �ʏ펞�̒Ǐ]����I�u�W�F�N�g�Ƃ̊Ԋu
	const Vector3 NormalOffset;
};

