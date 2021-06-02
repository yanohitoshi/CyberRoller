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

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// ステータスを待機状態にする
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// ジャンプフラグもしくはスイッチジャンプフラグがtrueだったら
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// ステータスをジャンプ開始状態にする
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// 移動入力があれば
	if (_owner->GetInputFlag())
	{
		// ステータスを走り出し状態にする
		state = PlayerState::PLAYER_STATE_RUN_START;
	}

	// 死亡フラグが立っていたら
	if (_owner->GetDeadFlag())
	{
		// ステータスを死亡状態にする
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// タイムオーバーフラグがtrueだったら
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// ステータスをコンティニュー選択開始状態にする
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// ownerに速度をセット
	_owner->SetVelocity(velocity);

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateJumpEndToIdle::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// state変更の可能性のある入力のチェック
		ChackInput(_owner, _keyState);
	}
}

void PlayerObjectStateJumpEndToIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE));
	// stateを待機状態にして保存
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;

	// ジャンプ力をセットする
	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	// 着地状態になったのでジャンプ利用可能フラグをtrueにセット
	_owner->SetIsAvailableJumpKey(true);
	// ジャンプフラグをfalseにセット
	_owner->SetJumpFlag(false);
	_owner->SetSwitchJumpFlag(false);
	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();
}
