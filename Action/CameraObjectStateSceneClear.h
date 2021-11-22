#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectStateBase.h"

/*
@file CameraObjectStateSceneClear.h
@brief �J�����̃V�[���N���A��Ԃ��X�V����N���X
*/
class CameraObjectStateSceneClear :
    public CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateSceneClear()
	: GameClearRadius(1000.0f)
	, AutomaticMoveSpeed(0.02f)
	, TrackingTime(60)
	, InitYaw(180.0f)
	, OffsetZ(400.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	~CameraObjectStateSceneClear() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return CameraState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	CameraState Update(CameraObjectBase* _owner, float _deltaTime)override;


	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(CameraObjectBase* _owner, float _deltaTime)override;

private:

	// ���[�ϐ�
	float yaw;
	// �ǐՎ��Ԃ𐔂���J�E���g�ϐ�
	int trackingCount;
	// ��~����Z���|�W�V�������i�[����ϐ�
	float stopPisitionZ;
	// �X�e�[�^�X�J�n���̃��[�̒l�萔
	const float InitYaw;
	// �N���A���̉�]����ۂ̔��a
	const float GameClearRadius;
	// ������]����ۂ̈ړ����x
	const float AutomaticMoveSpeed;
	// �ǐՂ��鎞��
	const int TrackingTime;
	// Z���̊Ԋu
	const float OffsetZ;
};

