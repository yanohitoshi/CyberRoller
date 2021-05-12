#include "PlayerObjectStateFlinch.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateFlinch::PlayerObjectStateFlinch()
{
}

PlayerObjectStateFlinch::~PlayerObjectStateFlinch()
{
}

PlayerState PlayerObjectStateFlinch::Update(PlayerObject* _owner, float _deltaTime)
{
	// �A�j���[�V�����̍Đ�������Ă��Ȃ�������
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �ǂɓ��������t���O��false��
		_owner->SetIsHitWall(false);
		// state���A�C�h�����O�ɕύX
		state = PlayerState::PLAYER_STATE_IDLE;
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

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateFlinch::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateFlinch::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_TO_FLINCH));
	// state�����ݏ�Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_RUN_TO_FLINCH;

	_owner->SetMoveSpeed(_owner->GetFirstMovePower());
	_owner->SetVelocity(Vector3::Zero);
}
