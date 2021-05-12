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
	// アニメーションの再生がされていなかったら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// 壁に当たったフラグをfalseに
		_owner->SetIsHitWall(false);
		// stateをアイドリングに変更
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// 死亡フラグが立っていたら
	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// タイムオーバーフラグがtrueだったら
	if (CountDownFont::timeOverFlag == true)
	{
		// ステータスをコンティニュー選択開始状態にする
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateFlinch::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateFlinch::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_TO_FLINCH));
	// stateを怯み状態にして保存
	state = PlayerState::PLAYER_STATE_RUN_TO_FLINCH;

	_owner->SetMoveSpeed(_owner->GetFirstMovePower());
	_owner->SetVelocity(Vector3::Zero);
}
