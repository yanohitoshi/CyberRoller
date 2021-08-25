//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateDownOver.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateDownOver::PlayerObjectStateDownOver()
{
}

PlayerObjectStateDownOver::~PlayerObjectStateDownOver()
{
}

PlayerState PlayerObjectStateDownOver::Update(PlayerObject* _owner, float _deltaTime)
{
	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateDownOver::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDownOver::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_OVER));
	// stateをゲームオーバー状態にして保存
	state = PlayerState::PLAYER_STATE_DOWN_OVER;
}
