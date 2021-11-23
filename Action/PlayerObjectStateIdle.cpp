//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateIdle.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateIdle::PlayerObjectStateIdle()
	: DanceStartTime(1800)
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateIdle::~PlayerObjectStateIdle()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, float _deltaTime)
{
	
	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �ړ��n���͊m�F
	CheckMovableInputProcess(_owner);

	// ���S�t���O��false�ł��^�C���I�[�o�[��Ԃł��Ȃ��_���X�J�n�t���O��true��������
	if (!_owner->GetDeadFlag() && CountDownFont::GetTimeOverFlag() == false && isDanceFlag == true)
	{
		// �X�e�[�^�X���_���X��ԂɕύX
		state = PlayerState::PLAYER_STATE_IDLE_DANCE;
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
void PlayerObjectStateIdle::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// state�ύX�̉\���̂�����͂̃`�F�b�N
		CheckInput(_owner, _keyState);
	}
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
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

	// �W�����v�͂��Z�b�g����
	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	// ���n��ԂɂȂ����̂ŃW�����v���p�\�t���O��true�ɃZ�b�g
	_owner->SetIsAvailableJumpKey(true);
	// �W�����v�t���O��false�ɃZ�b�g
	_owner->SetJumpFlag(false);
	_owner->SetSwitchJumpFlag(false);

	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();

	// �_���X�t���O��false�ɏ�����
	isDanceFlag = false;

	// �_���X��Ԃɓ���܂ł̃J�E���g��������
	danceCount = 0;

	// �؂�Ԃ����s���鎞�Ԃ��[��������
	_owner->SetTurnDelayCount(0);
}

/*
@fn ���̓`�F�b�N�����֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateIdle::CheckMovableInputProcess(PlayerObject* _owner)
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

/*
@fn �_���X�J�n�J�E���g�֐�
@brief	�_���X�J�n�܂ł̃J�E���g�𐔂����Ԃ�������t���O��؂�ւ���
*/
void PlayerObjectStateIdle::DanceCountProcess()
{
	// �_���X�J�n�܂ł̃J�E���g�𐔂���
	++danceCount;

	// �J�E���g���K��l�𒴂�����
	if (danceCount >= DanceStartTime)
	{
		// �_���X�J�n�t���O��true��
		isDanceFlag = true;
	}
}
