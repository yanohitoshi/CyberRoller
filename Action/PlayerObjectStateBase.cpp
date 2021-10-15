//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"
#include "CountDownFont.h"

/*
@fn 地面移動処理関数
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateBase::GroundMove(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力情報チェック処理
	CheckInputProcess(_owner, _keyState);
}

/*
@fn 入力チェック処理関数
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateBase::CheckInput(PlayerObject* _owner, const InputState& _keyState)
{

	// コントローラのアナログスティックの入力情報を計算する
	Vector3 axis = CheckControllerAxis(_keyState);

	// 取得した数値を見てデッドスペース外だったら入力処理を行う
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// 移動入力フラグをtrueにセット
		_owner->SetInputFlag(true);
	}
	else
	{
		// 移動入力フラグをfalseにセット
		_owner->SetInputFlag(false);
	}

	// 接地中でジャンプ中でもなければ
	if (_owner->GetOnGround() == true && _owner->GetJumpFlag() == false)
	{
		// ジャンプを割り当てられているコントローラーのボタンが押されたらもしくはジャンプスイッチが押されたら
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
			_owner->GetSwitchJumpFlag() == true)
		{
			// ジャンプフラグをtrueにセット
			_owner->SetJumpFlag(true);
		}
	}
}

/*
@fn 死亡状態か確認する関数
@param	_owner 親クラスのポインタ
*/
void PlayerObjectStateBase::CheckDeadFlag(PlayerObject* _owner)
{
	// 死亡フラグが立っていたら
	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}
}

/*
@fn タイムオーバーか確認する関数
*/
void PlayerObjectStateBase::CheckTimeOverFlag()
{
	// タイムオーバーフラグがtrueだったら
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// ステータスをコンティニュー選択開始状態にする
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}
}

/*
@fn 回転処理関数
@param	_owner 親クラスのポインタ
@param	_forward 回転させる方向ベクトル
@param	_tmpForward 回転させる前の方向ベクトル
*/
void PlayerObjectStateBase::RotationProcess(PlayerObject* _owner, Vector3 _forward, Vector3 _tmpForward)
{
	//前のフレームと今のフレームの前方ベクトルで線形補間を取る
	Vector3 rotatioin = Vector3::Lerp(_forward, _tmpForward, 0.01f);

	// 回転軸を求める
	_owner->RotateToNewForward(rotatioin);
	// 前方ベクトル更新
	_owner->SetCharaForwardVec(rotatioin);
}

/*
@fn アナログスティック処理関数
@param	_keyState 入力情報
*/
Vector3 PlayerObjectStateBase::CheckControllerAxis(const InputState& _keyState)
{
	//Axisの値をとる32700~-32700
	float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
	float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

	//アナログスティックのキー入力を取得
	Vector2 Axis = Vector2(0.0f, 0.0f);
	Axis = _keyState.Controller.GetLAxisLeftVec();

	//実際に動かしたい軸がずれているので補正
	Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

	// 軸を返す
	return axis;
}

/*
@fn 入力チェック関数処理関数
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateBase::CheckInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	// コントローラのアナログスティックの入力情報を計算する
	Vector3 axis = CheckControllerAxis(_keyState);

	// 取得した数値を見てデッドスペース外だったら入力処理を行う
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// 入力がある場合の処理
		InputMovableProcess(_owner, axis);
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
		// ジャンプ状態遷移準備
		JumpTransitionProcess(_owner);
	}
}

/*
@fn 入力がある場合の処理関数
@param	_owner 親クラスのポインタ
@param	_axis 補正済みのアナログスティック情報
*/
void PlayerObjectStateBase::InputMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// 前のフレームのキャラクターの前方ベクトルを保存
	Vector3 tmpForward = _owner->GetCharaForwardVec();

	// 方向キーの入力値とカメラの向きから、移動方向を決定
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;

	if (!Math::NearZero(forward.Length()))
	{
		forward.Normalize();
	}

	// 移動速度に加速度を足す
	moveSpeed += _owner->GetMovePower();

	// 移動速度が最大値を超えていたら固定する
	if (moveSpeed >= MaxMoveSpeed)
	{
		// 移動速度の最大定数を代入
		moveSpeed = MaxMoveSpeed;
	}

	// アナログスティックの入力角度を絶対値化
	Vector2 absAxis = Vector2(fabs(_axis.x), fabs(_axis.y));

	// 移動ベクトルに速度をかける
	if (absAxis.x > absAxis.y)
	{
		moveSpeed *= absAxis.x;
	}
	else
	{
		moveSpeed *= absAxis.y;
	}

	velocity.x = forward.x * moveSpeed;
	velocity.y = forward.y * moveSpeed;


	// 回転処理
	RotationProcess(_owner, forward, tmpForward);

	// ownerの移動速度を更新
	_owner->SetMoveSpeed(moveSpeed);
}

/*
@fn ジャンプ系のステータスの時入力がある場合の処理関数
@param	_owner 親クラスのポインタ
@param	_axis 補正済みのアナログスティック情報
*/
void PlayerObjectStateBase::InputJumpMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// 前のフレームのキャラクターの前方ベクトルを保存
	Vector3 tmpForward = _owner->GetCharaForwardVec();

	// 方向キーの入力値とカメラの向きから、移動方向を決定
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;
	forward.Normalize();

	// 空中用の移動力の定数を足す
	moveSpeed += _owner->GetAirMovePower();

	// 移動速度が最大速度を超えていたら
	if (moveSpeed >= MaxAirMoveSpeed)
	{
		// 最高速度に固定する
		moveSpeed = MaxAirMoveSpeed;
	}

	// アナログスティックの入力角度を絶対値化
	Vector2 absAxis = Vector2(fabs(_axis.x), fabs(_axis.y));
	// アナログスティックの入力を考慮した移動速度の作成
	if (absAxis.x > absAxis.y)
	{
		moveSpeed *= absAxis.x;
	}
	else
	{
		moveSpeed *= absAxis.y;
	}

	// X軸とY軸に前方ベクトルに速度をかけて速度付きベクトルを作る
	velocity.x = forward.x * moveSpeed;
	velocity.y = forward.y * moveSpeed;

	// 回転処理
	RotationProcess(_owner, forward, tmpForward);

	// ownerの速度変数を更新
	_owner->SetMoveSpeed(moveSpeed);
}

/*
@fn 入力がない場合の処理関数
@param	_owner 親クラスのポインタ
*/
void PlayerObjectStateBase::UninputMovableProcess(PlayerObject* _owner)
{
	// 移動入力フラグをfalseにセット
	_owner->SetInputFlag(false);
}

/*
@fn ジャンプ状態に遷移するための準備処理関数
@param	_owner 親クラスのポインタ
*/
void PlayerObjectStateBase::JumpTransitionProcess(PlayerObject* _owner)
{
	// ジャンプフラグをtrueにセット
	_owner->SetJumpFlag(true);
}
