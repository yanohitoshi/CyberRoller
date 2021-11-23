//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateIdle.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return ExplosionObjectState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
ExplosionObjectState ExplosionObjectStateIdle::Update(ExplosionObjectBase* _owner, float _deltaTime)
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
		// �X�e�[�^�X��Active�ɕύX
		_owner->SetState(State::Active);
		// �����ړ�����
		VerticalMove(_owner, _deltaTime);
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ExplosionObjectStateIdle::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X���A�C�h�����O��Ԃɂ���
	state = ExplosionObjectState::IDLE;
	// �ϐ�������
	rate = 0.0f;
	angle = 0.0f;
	nowScaleZ = _owner->GetScaleVec().z;
}
