//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FallExplosionObjectStateIdle.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return ExplosionObjectState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
ExplosionObjectState FallExplosionObjectStateIdle::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ����scale�T�C�Y��������scale�T�C�Y�̕����傫��������
	if (nowScaleZ > OriginalScale)
	{
		// scale�T�C�Y�����炷
		nowScaleZ -= SubScale;
		_owner->SetScaleZ(nowScaleZ);
	}
	else
	{
		// �X�e�[�^�X��Active�ɂ���
		_owner->SetState(State::Active);
	}

	// �����J�n��ԂŖ���������
	if (!_owner->GetIsFallStart())
	{
		// ���̂܂܃X�e�[�g��Ԃ�
		return state;
	}

	// �ҋ@���Ԃ𐔂���
	++stayCount;

	// �ҋ@���Ԃ𒴂��Ă��ė����J�n��Ԃ�������
	if (stayCount >= StayTime && _owner->GetIsFallStart())
	{
		// �X�e�[�^�X�𗎉���ԂɑJ��
		state = ExplosionObjectState::FALL;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void FallExplosionObjectStateIdle::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X���A�C�h�����O��ԂɃZ�b�g
	state = ExplosionObjectState::IDLE;

	// �ϐ�������
	rate = 0.0f;
	angle = 0.0f;
	nowScaleZ = _owner->GetScaleVec().z;
	stayCount = 0;
}
