//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJumpStart.h"
#include "SkeletalMeshComponent.h"
#include "SoundEffectComponent.h"

/*
@fn �R���X�g���N�^
@param _owner �e�N���X�̃|�C���^
*/
PlayerObjectStateJumpStart::PlayerObjectStateJumpStart(PlayerObject* _owner)
	: JumpCorrection(80.0f)
	, SwitchJumpCorrection(160.0f)
	, JumpTime(8)
	, SwitchJumpTime(15)
	, JumpAccelPower(100.0f)
	, SwitchJumpAccelPower(120.0f)
	, Deceleration(0.5f)
{
	soundEffect = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Player/Jump.wav");
	switchJumpSoundEffect = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Player/switchJump.wav");
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateJumpStart::~PlayerObjectStateJumpStart()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
PlayerState PlayerObjectStateJumpStart::Update(PlayerObject* _owner, float _deltaTime)
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
		// �X�e�[�^�X���W�����v���[�v�ɂ���
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// �ڒn�t���O��true����state�I���t���O��true�ɂȂ��Ă�����
	if (_owner->GetOnGround() == true && endFlag == true)
	{
		// owner�ϐ����X�V
		_owner->SetMoveSpeed(moveSpeed);
		_owner->SetVelocity(velocity);
		// �X�e�[�^�X�𒅒n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
	}

	// ���S��ԃ`�F�b�N
	CheckDeadFlag(_owner);
	// ���Ԑ؂�`�F�b�N
	CheckTimeOverFlag();

	// �X�V���ꂽstate��Ԃ�
	return state;
}

/*
@fn �C���v�b�g
@brief	state�ɉ����ē��͏������s��
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
void PlayerObjectStateJumpStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// ���͏��`�F�b�N����
		CheckInputProcess(_owner, _keyState);
	}
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateJumpStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPSTART),0.6f);
	// state���W�����v�J�n��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_JUMPSTART;

	_owner->SetJumpFlag(true);
	// �W�����v�t���[���J�E���g�����炤
	jumpFrameCount = _owner->GetJumpFrameCount();
	// owner�̑��x�x�N�g�������炤
	velocity = _owner->GetVelocity();
	// owner�̑��x�����炤
	moveSpeed = _owner->GetMoveSpeed() * Deceleration;

	// state�I���t���O��������
	endFlag = false;

	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();
	// �X�C�b�`�W�����v�̏ꍇ�X�C�b�`�W�����v�������łȂ��ꍇ���؂艹��炷
	if (_owner->GetSwitchJumpFlag())
	{
		switchJumpSoundEffect->Play();
	}
	else
	{
		// �T�E���h�G�t�F�N�g��炷
		soundEffect->Play();
	}
}

/*
@fn ���̓`�F�b�N�֐������֐�
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
void PlayerObjectStateJumpStart::CheckInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	//���ۂɓ�����������������Ă���̂ŕ␳
	Vector3 axis = CheckControllerAxis(_keyState);

	// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// ���͂�����ꍇ�̏���
		InputJumpMovableProcess(_owner, axis);
	}
	else
	{
		// ���͂��Ȃ��ꍇ�̏���
		UninputMovableProcess(_owner);
	}

	// �W�����v�{�^�����p�\�t���O��true���W�����v�t���O��true�܂��̓X�C�b�`�W�����v�t���O��true���W�����v�{�^�����p�\�t���O��true�̎�
	if (_owner->GetIsAvailableJumpKey() == true && _owner->GetJumpFlag() == true ||
		_owner->GetSwitchJumpFlag() == true && _owner->GetIsAvailableJumpKey() == true)
	{
		// �W�����v���̓{�^���������ꑱ���Ă��鎞�܂��̓W�����v�{�^�����p�\�t���O��true�̎�
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Held ||
			_owner->GetIsAvailableJumpKey() == true)
		{
			// �W�����v�J�n����
			JumpStartProcess(_owner);
		}
	}

	// �W�����v�����蓖�Ă��Ă���R���g���[���[�̃{�^���������ꂽ��
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released)
	{
		// �W�����v�I������
		JumpEndProcess(_owner);
	}

}

/*
@fn ���͂��Ȃ��ꍇ�̏����֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateJumpStart::UninputMovableProcess(PlayerObject* _owner)
{
	// �ړ����̓t���O��false�ɃZ�b�g
	_owner->SetInputFlag(false);
}

/*
@fn �W�����v�J�n�����֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateJumpStart::JumpStartProcess(PlayerObject* _owner)
{
	// �W�����v���Ă��鎞�Ԃ��t���[���ŃJ�E���g
	++jumpFrameCount;

	// �W�����v�͂̉��ϐ������O�t���[���ł̃W�����v�͂����炤
	float jumpPower = _owner->GetJumpPower();

	// Z���ɃW�����v�͂���
	velocity.z = jumpPower;

	// �X�C�b�`�W�����v�ł͂Ȃ��Ă��W�����v���p�\�Ȏ��ԓ���������
	if (JumpTime > jumpFrameCount && !_owner->GetSwitchJumpFlag())
	{
		// �W�����v�͂ɒ萔�l�𑫂��ăW�����v�͂�owner�̃W�����v�͕ϐ��ɃZ�b�g
		_owner->SetJumpPower(jumpPower + JumpAccelPower);
	}
	else if (_owner->GetSwitchJumpFlag() && SwitchJumpTime > jumpFrameCount) // �X�C�b�`�W�����v�ł��W�����v���p�\�Ȏ��ԓ���������
	{
		// �W�����v�͂ɒ萔�l�𑫂��ăW�����v�͂�owner�̃W�����v�͕ϐ��ɃZ�b�g
		_owner->SetJumpPower(jumpPower + SwitchJumpAccelPower);
	}
	else // �W�����v���p���Ԃ��o�߂��Ă�����
	{
		// �W�����v�{�^�����p�\��ԃt���O��false�ɃZ�b�g
		_owner->SetIsAvailableJumpKey(false);
		// �X�e�[�^�X�I���t���O��true�ɃZ�b�g
		endFlag = true;
		// �W�����v�t���O��false�ɃZ�b�g
		_owner->SetJumpFlag(false);
	}
}

/*
@fn �W�����v�I�����������֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateJumpStart::JumpEndProcess(PlayerObject* _owner)
{
	// �W�����v�{�^�����p�\��ԃt���O��false�ɃZ�b�g
	_owner->SetIsAvailableJumpKey(false);
	// �X�e�[�^�X�I���t���O��true�ɃZ�b�g
	endFlag = true;

	// �W�����v�t���O��false�ɃZ�b�g
	_owner->SetJumpFlag(false);
	// �W�����v�p���[�������l�ɍăZ�b�g
	_owner->SetJumpPower(_owner->GetFirstJumpPower());
}