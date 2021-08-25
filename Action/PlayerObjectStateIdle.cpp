//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateIdle.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateIdle::PlayerObjectStateIdle()
	: DanceStartTime(1800)
{
}

PlayerObjectStateIdle::~PlayerObjectStateIdle()
{
}

PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, float _deltaTime)
{
	
	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �ړ��n���͊m�F
	ChackMovableInputProcess(_owner);

	// ���S�t���O��false�ł��^�C���I�[�o�[��Ԃł��Ȃ��_���X�J�n�t���O��true��������
	if (!_owner->GetDeadFlag() && CountDownFont::GetTimeOverFlag() == false && isDanceFlag == true)
	{
		// �X�e�[�^�X���_���X��ԂɕύX
		state = PlayerState::PLAYER_STATE_IDLE_DANCE;
	}

	// ���S�t���O�������Ă�����
	if (_owner->GetDeadFlag())
	{
		// �X�e�[�^�X���W�����v�J�n��ԂɕύX
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// �^�C���I�[�o�[�t���O��true��������
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// �X�e�[�^�X���R���e�B�j���[�I���X�^�[�g��ԂɕύX
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// �X�V���ꂽstate��Ԃ�
	return state;

}

void PlayerObjectStateIdle::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// state�ύX�̉\���̂�����͂̃`�F�b�N
		ChackInput(_owner, _keyState);
	}
}

void PlayerObjectStateIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_IDLE;

	// �����x�����炤
	_owner->SetMoveSpeed(_owner->GetFirstMovePower());
	// ���x�x�N�g����������
	_owner->SetVelocity(Vector3::Zero);

	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();

	// �_���X�t���O��false�ɏ�����
	isDanceFlag = false;

	// �_���X��Ԃɓ���܂ł̃J�E���g��������
	danceCount = 0;

	// �؂�Ԃ����s���鎞�Ԃ��[��������
	_owner->SetTurnDelayCount(0);

}

void PlayerObjectStateIdle::ChackMovableInputProcess(PlayerObject* _owner)
{

	// �W�����v�t���O��false�ł��ڒn���Ă��Ȃ�������
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// ������ԂȂ̂ŃX�e�[�^�X���W�����v���[�v�ɕύX
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}
	else if (_owner->GetInputFlag()) // ���̓t���O��true��������
	{
		// �X�e�[�^�X�𑖂�o����ԂɕύX
		state = PlayerState::PLAYER_STATE_RUN_START;
	}
	else if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag()) // �W�����v�n�t���O��true��������
	{
		// �X�e�[�^�X���W�����v�J�n��ԂɕύX
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// ���͂��Ȃ�������
	if (!_owner->GetInputFlag())
	{
		DanceCountProcess();
	}
	else
	{
		// ���͂���������_���X�J�E���g��������
		danceCount = 0;
	}
}

void PlayerObjectStateIdle::DanceCountProcess()
{
	// �_���X�ȍ~�܂ł̃J�E���g�𐔂���
	++danceCount;

	// �J�E���g���K��l�𒴂�����
	if (danceCount >= DanceStartTime)
	{
		// �_���X�J�n�t���O��true��
		isDanceFlag = true;
	}
}
