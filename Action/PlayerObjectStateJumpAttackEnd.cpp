#include "PlayerObjectStateJumpAttackEnd.h"

PlayerObjectStateJumpAttackEnd::PlayerObjectStateJumpAttackEnd()
	: SuccessJumpTime(6)
	, SuccessJumpAccelPower(80.0f)
	, JumpAttackSuccessFirstPower(1500.0f)
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
	if (endFlag == true || !_owner->GetIsJumpAttackSuccess())
	{
		// owner�ϐ����X�V
		_owner->SetMoveSpeed(moveSpeed);
		_owner->SetVelocity(velocity);
		_owner->SetIsJumpAttackSuccess(false);
		_owner->SetIsJumpAttck(false);

		// �X�e�[�^�X���W�����v���[�v�ɂ���
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	ChackDeadFlag(_owner);

	ChackTimeOverFlag();

    return state;
}

void PlayerObjectStateJumpAttackEnd::Input(PlayerObject* _owner, const InputState& _keyState)
{
	if (_owner->GetIsJumpAttackSuccess())
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

}

void PlayerObjectStateJumpAttackEnd::Enter(PlayerObject* _owner, float _deltaTime)
{
    // state���W�����v�U����Ԃɂ��ĕۑ�
    state = PlayerState::PLAYER_STATE_JUMP_ATTACK_END;
	endFlag = false;
	jumpFrameCount = 0;

	// �W�����v�U���������������ǂ�������
	if (_owner->GetIsJumpAttackSuccess())
	{
		// �W�����v�͂��Z�b�g����
		_owner->SetJumpPower(JumpAttackSuccessFirstPower);
		_owner->SetIsAvailableJumpAttck(true);
	}
	else
	{
		velocity = _owner->GetVelocity();
		velocity.z = 0.0f;
		_owner->SetVelocity(velocity);
	}
}
