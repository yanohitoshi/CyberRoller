#pragma once
#include "TitlePlayerStateBase.h"
class TitlePlayerStateJumpLoop :
    public TitlePlayerStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TitlePlayerStateJumpLoop()
	: OnGroundCoordinate(100.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	~TitlePlayerStateJumpLoop() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	TitlePlayerState Update(TitlePlayerObject* _owner, float _deltaTime)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(TitlePlayerObject* _owner, float _deltaTime)override;

private:

	// ��p����W�����v��
	float jumpPower;
	int jumpFrameCount;
	// �ڒn����������W�l�萔
	const float OnGroundCoordinate;
};

