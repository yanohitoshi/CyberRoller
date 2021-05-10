#include "PlayerObjectStateDownStart.h"
#include "SkeletalMeshComponent.h"
PlayerObjectStateDownStart::PlayerObjectStateDownStart()
{
}

PlayerObjectStateDownStart::~PlayerObjectStateDownStart()
{
}

PlayerState PlayerObjectStateDownStart::Update(PlayerObject* _owner, float _deltaTime)
{
	// タイムオーバーループスタート状態のアニメーションが再生されていなかったら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// コンティニュー選択状態に変更
		state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	}

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateDownStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDownStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWNSTART));
	// stateをコンティニューするか選択する状態にして保存
	state = PlayerState::PLAYER_STATE_DOWNSTART;
}
