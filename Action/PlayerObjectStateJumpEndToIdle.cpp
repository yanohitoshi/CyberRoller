#include "PlayerObjectStateJumpEndToIdle.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateJumpEndToIdle::PlayerObjectStateJumpEndToIdle()
{
}

PlayerObjectStateJumpEndToIdle::~PlayerObjectStateJumpEndToIdle()
{
}

PlayerState PlayerObjectStateJumpEndToIdle::Update(PlayerObject* _owner, float _deltaTime)
{

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �A�j���[�V�����̍Đ����I����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �X�e�[�^�X��ҋ@��Ԃɂ���
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// �W�����v�t���O�������̓X�C�b�`�W�����v�t���O��true��������
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// �X�e�[�^�X���W�����v�J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// �ړ����͂������
	if (_owner->GetInputFlag())
	{
		// �X�e�[�^�X�𑖂�o����Ԃɂ���
		state = PlayerState::PLAYER_STATE_RUN_START;
	}

	// ���S�t���O�������Ă�����
	if (_owner->GetDeadFlag())
	{
		// �X�e�[�^�X�����S��Ԃɂ���
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// �^�C���I�[�o�[�t���O��true��������
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// �X�e�[�^�X���R���e�B�j���[�I���J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// owner�ɑ��x���Z�b�g
	_owner->SetVelocity(velocity);

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateJumpEndToIdle::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// state�ύX�̉\���̂�����͂̃`�F�b�N
		ChackInput(_owner, _keyState);
	}
}

void PlayerObjectStateJumpEndToIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;

	// �W�����v�͂��Z�b�g����
	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	// ���n��ԂɂȂ����̂ŃW�����v���p�\�t���O��true�ɃZ�b�g
	_owner->SetIsAvailableJumpKey(true);
	// �W�����v�t���O��false�ɃZ�b�g
	_owner->SetJumpFlag(false);
	_owner->SetSwitchJumpFlag(false);
	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();
}
