#pragma once
#include "CameraObjectBase.h"

/*
@enum class CameraState
	�J�����̏��
*/
enum class CameraState
{
	// �ʏ���
	NORMAL,
	// �G���A�ɂ���p�ύX���
	CHANGEMODE,
	// �_���X��
	DANCE,
	// �Q�[���I�[�o�[���
	GAMEOVER,
	// �N���A���
	SCENECLEAR,
	// �V�[���J�n���
	SCENESTART,
	// ��Ԗ���
	NONE
};

/*
@file CameraObjectStateBase.h
@brief �J�����̃X�e�[�^�X�̊��N���X
*/
class CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateBase()
	: DeltaCorrection(8.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	virtual ~CameraObjectStateBase() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return CameraState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	virtual CameraState Update(CameraObjectBase* _owner, float _deltaTime) = 0;

	/*
	@fn �C���v�b�g
	@brief	state�ɉ����ē��͏������s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	virtual void Input(CameraObjectBase* _owner, const InputState& _keyState) {};

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Enter(CameraObjectBase* _owner, float _deltaTime) {};

protected:

	// ���`�ۊǎ��Ƀf���^�^�C����������Ƃ��p�̕␳�萔
	const float DeltaCorrection;
	// �X�e�[�^�X�ϐ�
	CameraState state;
	// �v���C���[�Ƃ̊Ԋu
	Vector3 offsetPosition;
};

