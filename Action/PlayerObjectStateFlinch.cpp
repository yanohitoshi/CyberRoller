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
	// アニメーションの再生がされていなかったら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// 壁に当たったフラグをfalseに
		_owner->SetIsHitWall(false);
		// stateを7アイドリングに変更
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// 更新されたstateを返す
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
