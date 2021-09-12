#include "PlayerObjectStateJumpAttackEnd.h"

PlayerObjectStateJumpAttackEnd::PlayerObjectStateJumpAttackEnd()
	: SuccessJumpTime(10)
	, SuccessJumpAccelPower(110.0f)
{
}

PlayerObjectStateJumpAttackEnd::~PlayerObjectStateJumpAttackEnd()
{
}

PlayerState PlayerObjectStateJumpAttackEnd::Update(PlayerObject* _owner, float _deltaTime)
{
	// �d�͂Ƀf���^�^�C�����������l����
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;

	// �������x���K��l�𒴂��Ă�����
	if (velocity.z <= MaxFallSpeed)
	{
		// �K��l�ɌŒ�
		velocity.z = MaxFallSpeed;
	}

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	// state�I���t���O��true�ɂȂ��Ă�����
	if (endFlag == true)
	{
		// owner�ϐ����X�V
		_owner->SetMoveSpeed(moveSpeed);
		_owner->SetVelocity(velocity);
		_owner->SetJumpFrameCount(jumpFrameCount);
		_owner->SetIsJumpAttck(false);
		_owner->SetIsJumpAttackSuccess(false);
		// �X�e�[�^�X���W�����v���[�v�ɂ���
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

    return state;
}

void PlayerObjectStateJumpAttackEnd::Input(PlayerObject* _owner, const InputState& _keyState)
{

	// �W�����v���Ă��鎞�Ԃ��t���[���ŃJ�E���g
	++jumpFrameCount;

	// �W�����v�͂̉��ϐ������O�t���[���ł̃W�����v�͂����炤
	float jumpPower = _owner->GetJumpPower();

	// Z���ɃW�����v�͂���
	velocity.z = jumpPower;

	// �X�C�b�`�W�����v�ł��W�����v���p�\�Ȏ��ԓ���������
	if (SuccessJumpTime > jumpFrameCount)
	{
		// �W�����v�͂ɒ萔�l�𑫂��ăW�����v�͂�owner�̃W�����v�͕ϐ��ɃZ�b�g
		_owner->SetJumpPower(jumpPower + SuccessJumpAccelPower);
	}
	else // �W�����v���p���Ԃ��o�߂��Ă�����
	{
		// �X�e�[�^�X�I���t���O��true�ɃZ�b�g
		endFlag = true;
	}
}

void PlayerObjectStateJumpAttackEnd::Enter(PlayerObject* _owner, float _deltaTime)
{
    // state���W�����v�U����Ԃɂ��ĕۑ�
    state = PlayerState::PLAYER_STATE_JUMP_ATTACK_END;
	endFlag = false;
	jumpFrameCount = 0;
	// �W�����v�͂��Z�b�g����
	_owner->SetJumpPower(_owner->GetFirstJumpPower());

}