#pragma once
#include "CameraObjectStateBase.h"

/*
@file GameObject.h
@brief �Q�[���I�u�W�F�N�g�̊��N���X
*/
class CameraObjectStateSceneStart :
    public CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateSceneStart()
		: GameClearRadius(1000.0f)
		, AutomaticMoveSpeed(0.02f)
		, TrackingTime(60) {};

	/*
	@fn �f�X�g���N�^
	*/
	~CameraObjectStateSceneStart() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	CameraState Update(CameraObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(CameraObjectBase* _owner, float _deltaTime)override;

private:

	float yaw;
	const float GameClearRadius;
	// ������]����ۂ̈ړ����x
	const float AutomaticMoveSpeed;
	int trackingCount;
	const int TrackingTime;
	float stopPisitionZ;
};