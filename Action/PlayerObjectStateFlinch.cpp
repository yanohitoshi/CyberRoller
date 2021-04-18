#include "PlayerObjectStateFlinch.h"
#include "SkeletalMeshComponent.h"

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
		// state��7�A�C�h�����O�ɕύX
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateFlinch::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateFlinch::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_TO_FLINCH));
	state = PlayerState::PLAYER_STATE_RUN_TO_FLINCH;

	_owner->SetMoveSpeed(_owner->GetFirstMovePower());
	_owner->SetVelocity(Vector3::Zero);
}
