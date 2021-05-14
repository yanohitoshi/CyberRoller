#include "PlayerObjectStateRunStart.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateRunStart::PlayerObjectStateRunStart()
{
}

PlayerObjectStateRunStart::~PlayerObjectStateRunStart()
{
}

PlayerState PlayerObjectStateRunStart::Update(PlayerObject* _owner, float _deltaTime)
{
	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// ステータスを走り状態にする
		state = PlayerState::PLAYER_STATE_RUN;
	}

	// ジャンプフラグがfalseで接地状態でも無ければ
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// ステータスをジャンプループにする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}
	// 移動入力が無ければ
	if (!_owner->GetInputFlag())
	{
		// ステータスを走り終わりにする
		state = PlayerState::PLAYER_STATE_RUN_STOP;
	}
	// ジャンプフラグもしくはスイッチジャンプフラグがtrueだったら
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// ステータスをジャンプ開始状態にする
		state = PlayerState::PLAYER_STATE_JUMPSTART;
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

	// ownerの変数を更新
	_owner->SetVelocity(velocity);
	_owner->SetMoveSpeed(moveSpeed);

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateRunStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// 移動入力処理
		GroundMove(_owner, _keyState);
	}
}

void PlayerObjectStateRunStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_START));
	// stateを走り出し状態にして保存
	state = PlayerState::PLAYER_STATE_RUN_START;
	// ownerの移動速度をもらう
	moveSpeed = _owner->GetMoveSpeed();

	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();
}
