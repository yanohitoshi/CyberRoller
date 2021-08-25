//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRespown.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateRespown::PlayerObjectStateRespown()
{
}

PlayerObjectStateRespown::~PlayerObjectStateRespown()
{
}

PlayerState PlayerObjectStateRespown::Update(PlayerObject* _owner, float _deltaTime)
{

	// ownerのリスポーンフラグをfalseにセット
	_owner->SetRespawnFlag(false);
	// ownerを入力可能状態にセット
	_owner->SetIsAvailableInput(true);

	// ステータスをアイドリング状態に変更する
	state = PlayerState::PLAYER_STATE_IDLE;

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateRespown::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateRespown::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE));
	// stateをリスポーン状態にして保存
	state = PlayerState::PLAYER_STATE_RESPAWN;

}
