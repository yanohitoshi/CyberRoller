//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJunpEndToRun.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateJunpEndToRun::PlayerObjectStateJunpEndToRun()
	: DecelerationForce(75.0f)
{
}

PlayerObjectStateJunpEndToRun::~PlayerObjectStateJunpEndToRun()
{
}

PlayerState PlayerObjectStateJunpEndToRun::Update(PlayerObject* _owner, float _deltaTime)
{

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

	//// ���S�t���O�������Ă�����
	//if (_owner->GetDeadFlag())
	//{
	//	state = PlayerState::PLAYER_STATE_DEAD;
	//}

	//// �^�C���I�[�o�[�t���O��true��������
	//if (CountDownFont::GetTimeOverFlag() == true)
	//{
	//	// �X�e�[�^�X���R���e�B�j���[�I���J�n��Ԃɂ���
	//	state = PlayerState::PLAYER_STATE_DOWNSTART;
	//}

	// owner�̕ϐ����X�V
	_owner->SetMoveSpeed(moveSpeed);

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateJunpEndToRun::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// ���͏��`�F�b�N����
		ChackInputProcess(_owner,_keyState);
	}
}

void PlayerObjectStateJunpEndToRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_RUN));
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

void PlayerObjectStateJunpEndToRun::ChackInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	//���ۂɓ�����������������Ă���̂ŕ␳
	Vector3 axis = ChackControllerAxis(_keyState);

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

void PlayerObjectStateJunpEndToRun::InputMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// �O�̃t���[���̃L�����N�^�[�̑O���x�N�g����ۑ�
	Vector3 tmpForward = _owner->GetCharaForwardVec();

	// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;
	forward.Normalize();

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

void PlayerObjectStateJunpEndToRun::UninputMovableProcess(PlayerObject* _owner)
{
	// ���x��0.0f�ȏゾ������
	if (moveSpeed >= 0.0f)
	{
		// ���x���猸���萔������
		moveSpeed -= DecelerationForce;
	}

	// �ړ��x�N�g���̕ύX���Ȃ��̂�owner�̑O���x�N�g�������炢���̃x�N�g���ɑ��x��������
	velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
	velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

	// �ړ����̓t���O��false�ɃZ�b�g
	_owner->SetInputFlag(false);

}

void PlayerObjectStateJunpEndToRun::JumpTransitionProcess(PlayerObject* _owner)
{
	// �W�����v�t���O��true�ɃZ�b�g
	_owner->SetJumpFlag(true);
}
