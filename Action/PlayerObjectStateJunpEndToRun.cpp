//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJunpEndToRun.h"
#include "SkeletalMeshComponent.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateJunpEndToRun::PlayerObjectStateJunpEndToRun()
	: UnInputDecelerationForce(75.0f)
	, InputDecelerationForce(0.7f)
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateJunpEndToRun::~PlayerObjectStateJunpEndToRun()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
PlayerState PlayerObjectStateJunpEndToRun::Update(PlayerObject* _owner, float _deltaTime)
{
	// ���n���̌����l���|����
	velocity *= InputDecelerationForce;
	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �A�j���[�V�����̍Đ����I����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �ړ����͂���������
		if (_owner->GetInputFlag())
		{
			// �X�e�[�^�X�𑖂�o����Ԃɂ���
			state = PlayerState::PLAYER_STATE_RUN_START;
		}
		else
		{
			// �X�e�[�^�X��ҋ@��Ԃɂ���
			state = PlayerState::PLAYER_STATE_IDLE;
		}
	}

	// �W�����v�t���O�������̓X�C�b�`�W�����v�t���O��true��������
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// �X�e�[�^�X���W�����v�J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// �W�����v�t���O��false���ڒn��Ԃł��������
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// �X�e�[�^�X���W�����v���[�v��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// ���S��ԃ`�F�b�N
	CheckDeadFlag(_owner);
	// ���Ԑ؂�`�F�b�N
	CheckTimeOverFlag();

	// owner�̕ϐ����X�V
	_owner->SetMoveSpeed(moveSpeed);

	// �X�V���ꂽstate��Ԃ�
	return state;
}

/*
@fn �C���v�b�g
@brief	state�ɉ����ē��͏������s��
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
void PlayerObjectStateJunpEndToRun::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// ���͏��`�F�b�N����
		CheckInputProcess(_owner,_keyState);
	}
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateJunpEndToRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_RUN),1.4f);
	// state�𒅒n���[�����O��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_RUN;

	// owner�̈ړ����x�����炤
	moveSpeed = _owner->GetMoveSpeed();
	// owner�̈ړ��x�N�g�������炤
	velocity = _owner->GetVelocity();
	// ���n��ԂȂ̂�Z����0�ɌŒ�
	velocity.z = 0.0f;
	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();

	// owner�̃W�����v�͂����Z�b�g
	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	// �W�����v�{�^�����p���\��ԂɃZ�b�g
	_owner->SetIsAvailableJumpKey(true);
	// �W�����v�t���O��false�ɃZ�b�g
	_owner->SetJumpFlag(false);
	// �W�����v�U���n�t���O������
	_owner->SetSwitchJumpFlag(false);
	_owner->SetIsAvailableJumpAttck(true);

}

/*
@fn ���̓`�F�b�N�֐������֐�
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
void PlayerObjectStateJunpEndToRun::CheckInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	//���ۂɓ�����������������Ă���̂ŕ␳
	Vector3 axis = CheckControllerAxis(_keyState);

	// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// ���͂�����ꍇ�̏���
		InputMovableProcess(_owner, axis);
	}
	else // �f�b�h�X�y�[�X���������猸���������s��
	{
		// ���͂��Ȃ��ꍇ�̏���
		UninputMovableProcess(_owner);
	}

	// �W�����v�����蓖�Ă��Ă���R���g���[���[�̃{�^���������ꂽ��������̓W�����v�X�C�b�`�������ꂽ��
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
		_owner->GetSwitchJumpFlag() == true)
	{
		// �W�����v����
		JumpTransitionProcess(_owner);
	}
}

/*
@fn ���͂�����ꍇ�̏����֐�
@param	_owner �e�N���X�̃|�C���^
@param	_axis �␳�ς݂̃A�i���O�X�e�B�b�N���
*/
void PlayerObjectStateJunpEndToRun::InputMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// �O�̃t���[���̃L�����N�^�[�̑O���x�N�g����ۑ�
	Vector3 tmpForward = _owner->GetCharaForwardVec();

	// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;
	if (!Math::NearZero(forward.Length()))
	{
		// ���K��
		forward.Normalize();
	}

	// �ړ����x�ɉ����x�萔�𑫂�
	moveSpeed += _owner->GetMovePower();

	// �ړ����x���ő�l�𒴂��Ă�����
	if (moveSpeed >= MaxMoveSpeed)
	{
		// �ړ����x���ő�l�ɌŒ�
		moveSpeed = MaxMoveSpeed;
	}


	// �ړ��x�N�g���ɑ��x��������
	velocity.x = forward.x * moveSpeed;
	velocity.y = forward.y * moveSpeed;

	// ��]����
	RotationProcess(_owner, forward, tmpForward);

	// owner�̑��x�ϐ����X�V
	_owner->SetMoveSpeed(moveSpeed);

}

/*
@fn ���͂��Ȃ��ꍇ�̏����֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateJunpEndToRun::UninputMovableProcess(PlayerObject* _owner)
{
	// ���x��0.0f�ȏゾ������
	if (moveSpeed >= 0.0f)
	{
		// ���x���猸���萔������
		moveSpeed -= UnInputDecelerationForce;
	}

	// �ړ��x�N�g���̕ύX���Ȃ��̂�owner�̑O���x�N�g�������炢���̃x�N�g���ɑ��x��������
	velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
	velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

	// �ړ����̓t���O��false�ɃZ�b�g
	_owner->SetInputFlag(false);

}

/*
@fn �W�����v��ԂɑJ�ڂ��邽�߂̏��������֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateJunpEndToRun::JumpTransitionProcess(PlayerObject* _owner)
{
	// �W�����v�t���O��true�ɃZ�b�g
	_owner->SetJumpFlag(true);
}