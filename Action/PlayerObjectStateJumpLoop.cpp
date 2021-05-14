#include "PlayerObjectStateJumpLoop.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateJumpLoop::PlayerObjectStateJumpLoop()
	: MaxFallSpeed(-2000.0f)
	, TurnValue(600.0f)
	, JumpCorrection(840.0f)
	, SwitchJumpCorrection(1320.0f)
{
}

PlayerObjectStateJumpLoop::~PlayerObjectStateJumpLoop()
{
}

PlayerState PlayerObjectStateJumpLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	// �؋󎞊Ԃ̃J�E���g�𐔂���
	++jumpLoopCount;

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

	// �A�j���[�V�����ύX�t���O��true�ł���Z���̑��x��0.0f�ȉ��ɂȂ�����
	if (animChangeFlag == true && velocity.z <= 0.0f)
	{
		// �W�����v���[�v�̃A�j���[�V�������Đ�
		skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPLOOP));
		// ����Đ��������Ȃ��悤�Ƀt���O��false��
		animChangeFlag = false;
	}

	// �ڒn�t���O��true�ł��ړ����͂������Ԃł����x�����l�ȏゾ������
	if (_owner->GetOnGround() == true && _owner->GetInputFlag() && moveSpeed >= TurnValue)
	{
		// �X�e�[�^�X�����[�����O�A�j���[�V�����������n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_RUN;
	}
	else if (_owner->GetOnGround() == true) // �ڒn�t���O��true�ɂȂ�����
	{
		// �X�e�[�^�X�𒅒n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
	}

	// ���S�t���O�������Ă�����
	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// �^�C���I�[�o�[�t���O��true��������
	if (CountDownFont::timeOverFlag == true)
	{
		// �X�e�[�^�X���R���e�B�j���[�I���J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// owner�̕ϐ����X�V
	_owner->SetVelocity(velocity);
	_owner->SetMoveSpeed(moveSpeed);

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateJumpLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		//���ۂɓ�����������������Ă���̂ŕ␳
		Vector3 axis = ChackControllerAxis(_keyState);

		// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
		if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
		{
			// �O�̃t���[���̃L�����N�^�[�̑O���x�N�g����ۑ�
			Vector3 tmpForward = _owner->GetCharaForwardVec();

			// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
			Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
			forward.Normalize();

			// �󒆗p�̈ړ��͂̒萔�𑫂�
			moveSpeed += _owner->GetAirMovePower();
			
			// SwitchJump�̏ꍇ��Ԏ��Ԃ������̂Ŋ�����ύX
			if (_owner->GetSwitchJumpFlag())
			{
				// ���[�v���Ă���t���[���J�E���g��萔�Ŋ����ď��X�Ɍ�����������
				moveSpeed *= 1.0f - jumpLoopCount / SwitchJumpCorrection;
			}
			else
			{
				// ���[�v���Ă���t���[���J�E���g��萔�Ŋ����ď��X�Ɍ�����������
				moveSpeed *= 1.0f - jumpLoopCount / JumpCorrection;
			}

			// �ړ����x���ő呬�x�𒴂��Ă�����
			if (moveSpeed >= MaxMoveSpeed)
			{
				// �Œᑬ�x�ɌŒ肷��
				moveSpeed = MaxMoveSpeed;
			}

			// X����Y���ɑO���x�N�g���ɑ��x�������đ��x�t���x�N�g�������
			velocity.x = forward.x * moveSpeed;
			velocity.y = forward.y * moveSpeed;

			// ��]����
			RotationProcess(_owner,forward, tmpForward);

			// owner�̑��x�ϐ����X�V
			_owner->SetMoveSpeed(moveSpeed);
		}
		else // �擾�������l�����ăf�b�h�X�y�[�X���������猸���������s��
		{
			//�@�ړ����x����󒆗p�����l������
			moveSpeed -= _owner->GetAirMovePower();

			// �ړ����x��0.0f�ȉ��ɂȂ�����
			if (moveSpeed <= 0.0f)
			{
				// �}�C�i�X�ɂȂ�Ȃ��悤��0.0f�ɌŒ�
				moveSpeed = 0.0f;
			}

			// owner�̕����x�N�g���Ɉړ����x���|���Ĉړ��x�N�g�����X�V
			velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
			velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

			// �ړ����̓t���O��false�ɃZ�b�g
			_owner->SetInputFlag(false);
		}
		
	}

}

void PlayerObjectStateJumpLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// state���W�����v���[�v��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_JUMPLOOP;
	// �A�j���[�V�����ύX�t���O��������
	animChangeFlag = true;
	// �؋󎞊Ԃ𑪂�J�E���g�̏�����
	jumpLoopCount = 0;
	// owner�̑��x�����炤
	velocity = _owner->GetVelocity();

	// �����ڏ�X���[�Y�ɑJ�ڂ����邽�߂ɑO�̃X�e�[�^�X���W�����v�J�n��������W�����v�͂����炤
	if (_owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPSTART)
	{
		// �O�t���[���̃W�����v�͂����炤
		velocity.z = _owner->GetJumpPower();
	}

	// owner�̉����x�ϐ��̐��l�����炤
	moveSpeed = _owner->GetMoveSpeed();

	// �����x�ϐ��̐��l��0.0f�ȉ���������
	if (moveSpeed <= 0.0f)
	{
		// �����x������
		moveSpeed = _owner->GetFirstMovePower();
	}

	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();

}
