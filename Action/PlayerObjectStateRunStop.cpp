//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRunStop.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateRunStop::PlayerObjectStateRunStop()
	: TurnDelayValue(30)
	, TurnValue(10)
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateRunStop::~PlayerObjectStateRunStop()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
PlayerState PlayerObjectStateRunStop::Update(PlayerObject* _owner, float _deltaTime)
{
	// ターン有効カウントを数える
	++isTurnCount;

	// 移動速度が0.0f以上だったら
	if (moveSpeed >= 0.0f)
	{
		// 減速させる
		moveSpeed -= decelerationForce;
	}

	// ownerの方向ベクトルに移動速度を掛けて移動ベクトルを更新
	velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
	velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

	// 移動ベクトルにデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// アニメーションの再生が終わっているもしくは移動速度が0.0f以下になっていたら
	if (!skeletalMeshComponent->IsPlaying() || moveSpeed <= 0.0f)
	{
		// ステータスを待機状態にする
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// 移動入力があってターンする間隔のカウントが規定値以上でターンに入れるカウントも規定値以上だったら
	if (_owner->GetInputFlag() && _owner->GetTurnDelayCount() >= TurnDelayValue && isTurnCount <= TurnValue)
	{
		// ステータスをターン状態にする
		state = PlayerState::PLAYER_STATE_RUN_TURN;
	}

	// ジャンプフラグもしくはスイッチジャンプフラグがtrueだったら
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// ステータスをジャンプ開始状態にする
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// ジャンプフラグがfalseで接地状態でも無ければ
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// ステータスをジャンプループにする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// 死亡状態チェック
	CheckDeadFlag(_owner);

	// 時間切れチェック
	CheckTimeOverFlag();

	// ownerの変数を更新
	_owner->SetVelocity(velocity);

	// 更新されたstateを返す
	return state;
}

/*
@fn インプット
@brief	stateに応じて入力処理を行う
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateRunStop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// state変更の可能性のある入力のチェック
		CheckInput(_owner, _keyState);
	}
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateRunStop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_STOP));
	// stateを走り終わり状態にして保存
	state = PlayerState::PLAYER_STATE_RUN_STOP;
	// ownerの移動速度をもらう
	moveSpeed = _owner->GetMoveSpeed();
	// ターンに可能カウントを初期化
	isTurnCount = 0;
	// 減速力をもらう
	decelerationForce = _owner->GetDecelerationForce();
	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();
}
