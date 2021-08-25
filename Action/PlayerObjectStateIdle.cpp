//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateIdle.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateIdle::PlayerObjectStateIdle()
	: DanceStartTime(1800)
{
}

PlayerObjectStateIdle::~PlayerObjectStateIdle()
{
}

PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, float _deltaTime)
{
	
	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// 移動系入力確認
	ChackMovableInputProcess(_owner);

	// 死亡フラグがfalseでかつタイムオーバー状態でもなくダンス開始フラグがtrueだったら
	if (!_owner->GetDeadFlag() && CountDownFont::GetTimeOverFlag() == false && isDanceFlag == true)
	{
		// ステータスをダンス状態に変更
		state = PlayerState::PLAYER_STATE_IDLE_DANCE;
	}

	// 死亡フラグが立っていたら
	if (_owner->GetDeadFlag())
	{
		// ステータスをジャンプ開始状態に変更
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// タイムオーバーフラグがtrueだったら
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// ステータスをコンティニュー選択スタート状態に変更
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// 更新されたstateを返す
	return state;

}

void PlayerObjectStateIdle::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// state変更の可能性のある入力のチェック
		ChackInput(_owner, _keyState);
	}
}

void PlayerObjectStateIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE));
	// stateを待機状態にして保存
	state = PlayerState::PLAYER_STATE_IDLE;

	// 初速度をもらう
	_owner->SetMoveSpeed(_owner->GetFirstMovePower());
	// 速度ベクトルを初期化
	_owner->SetVelocity(Vector3::Zero);

	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();

	// ダンスフラグをfalseに初期化
	isDanceFlag = false;

	// ダンス状態に入るまでのカウントを初期化
	danceCount = 0;

	// 切り返しを行える時間をゼロ初期化
	_owner->SetTurnDelayCount(0);

}

void PlayerObjectStateIdle::ChackMovableInputProcess(PlayerObject* _owner)
{

	// ジャンプフラグがfalseでかつ接地していなかったら
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// 落下状態なのでステータスをジャンプループに変更
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}
	else if (_owner->GetInputFlag()) // 入力フラグがtrueだったら
	{
		// ステータスを走り出し状態に変更
		state = PlayerState::PLAYER_STATE_RUN_START;
	}
	else if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag()) // ジャンプ系フラグがtrueだったら
	{
		// ステータスをジャンプ開始状態に変更
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// 入力がなかったら
	if (!_owner->GetInputFlag())
	{
		DanceCountProcess();
	}
	else
	{
		// 入力があったらダンスカウントを初期化
		danceCount = 0;
	}
}

void PlayerObjectStateIdle::DanceCountProcess()
{
	// ダンス以降までのカウントを数える
	++danceCount;

	// カウントが規定値を超えたら
	if (danceCount >= DanceStartTime)
	{
		// ダンス開始フラグをtrueに
		isDanceFlag = true;
	}
}
