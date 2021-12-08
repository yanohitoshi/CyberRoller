//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRunTurn.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateRunTurn::PlayerObjectStateRunTurn()
	: MinimumSpeed(200.0f)
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateRunTurn::~PlayerObjectStateRunTurn()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return PlayerState　更新終了時のステータスを返す
*/
PlayerState PlayerObjectStateRunTurn::Update(PlayerObject* _owner, float _deltaTime)
{
	// 速度が0.0f以上だったら
	if (moveSpeed >= 0.0f)
	{
		// 減速をかける
		moveSpeed -= decelerationForce;
	}

	// キャラクターの前方ベクトルに移動速度をかけてターンするので-1.0fをかける
	velocity.x = _owner->GetCharaForwardVec().x * moveSpeed * -1.0f;
	velocity.y = _owner->GetCharaForwardVec().y * moveSpeed * -1.0f;

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// ステータスを走り状態にする
		state = PlayerState::PLAYER_STATE_RUN;
		// 速度が規定値以下だったら
		if (moveSpeed <= MinimumSpeed)
		{
			// 速度を規定値にする
			moveSpeed = MinimumSpeed;
		}
	}

	// 移動入力が無ければ
	if (!_owner->GetInputFlag())
	{
		// ステータスを走り終わりにする
		state = PlayerState::PLAYER_STATE_RUN_STOP;
	}

	// ジャンプフラグがfalseで接地状態でも無ければ
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// ステータスをジャンプループにする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// ジャンプフラグもしくはスイッチジャンプフラグがtrueだったら
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// ステータスをジャンプ開始状態にする
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// 死亡状態チェック
	CheckDeadFlag(_owner);

	// 時間切れチェック
	CheckTimeOverFlag();

	// ownerの変数を更新
	_owner->SetVelocity(velocity);
	_owner->SetMoveSpeed(moveSpeed);

	// 更新されたstateを返す
	return state;
}

/*
@fn インプット
@brief	stateに応じて入力処理を行う
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateRunTurn::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// 入力情報チェック処理
		CheckInputProcess(_owner, _keyState);
	}
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateRunTurn::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_TURN),1.5f);
	// stateを切り替えし状態にして保存
	state = PlayerState::PLAYER_STATE_RUN_TURN;
	// ownerの速度をもらう
	moveSpeed = _owner->GetMoveSpeed();
	// 減速度をもらう
	decelerationForce = _owner->GetDecelerationForce();
	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();
	// ownerのターン間隔速度を初期化
	_owner->SetTurnDelayCount(0);
}

/*
@fn 入力チェック関数処理関数
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateRunTurn::CheckInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	// コントローラのアナログスティックの入力情報を計算する
	Vector3 axis = CheckControllerAxis(_keyState);

	// 取得した数値を見てデッドスペース外だったら入力処理を行う
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// 入力がある場合の処理
		InputMovableProcess(_owner,axis);
	}
	else
	{
		// 入力がない場合の処理
		UninputMovableProcess(_owner);
	}

	// ジャンプを割り当てられているコントローラーのボタンが押されたらもしくはジャンプスイッチが押されたら
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
		_owner->GetSwitchJumpFlag() == true)
	{
		// ジャンプ準備
		JumpTransitionProcess(_owner);
	}
}

/*
@fn 入力がある場合の処理関数
@param	_owner 親クラスのポインタ
@param	_axis 補正済みのアナログスティック情報
*/
void PlayerObjectStateRunTurn::InputMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// 方向キーの入力値とカメラの向きから、移動方向を決定
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;

	if (!Math::NearZero(forward.Length()))
	{
		// ベクトルの正規化
		forward.Normalize();
	}
	// 前方ベクトルの更新
	_owner->SetCharaForwardVec(forward);
	// 入力フラグをtrueに
	_owner->SetInputFlag(true);
}

/*
@fn 入力がない場合の処理関数
@param	_owner 親クラスのポインタ
*/
void PlayerObjectStateRunTurn::UninputMovableProcess(PlayerObject* _owner)
{
	// 入力フラグをfalseに
	_owner->SetInputFlag(false);
}

/*
@fn ジャンプ状態に遷移するための準備処理関数
@param	_owner 親クラスのポインタ
*/
void PlayerObjectStateRunTurn::JumpTransitionProcess(PlayerObject* _owner)
{
	// ジャンプフラグをtrueにセット
	_owner->SetJumpFlag(true);
}
