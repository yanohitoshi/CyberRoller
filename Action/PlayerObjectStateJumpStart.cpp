#include "PlayerObjectStateJumpStart.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateJumpStart::PlayerObjectStateJumpStart()
	: MaxFallSpeed(-2000.0f)
	, JumpCorrection(80.0f)
	, SwitchJumpCorrection(160.0f)
{
}

PlayerObjectStateJumpStart::~PlayerObjectStateJumpStart()
{
}

PlayerState PlayerObjectStateJumpStart::Update(PlayerObject* _owner, float _deltaTime)
{
	// 重力にデルタタイムをかけた値を代入
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;
	
	// 落下速度が規定値を超えていたら
	if (velocity.z <= MaxFallSpeed)
	{
		// 規定値に固定
		velocity.z = MaxFallSpeed;
	}

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);


	// state終了フラグがtrueになっていたら
	if (endFlag == true)
	{
		// owner変数を更新
		_owner->SetMoveSpeed(moveSpeed);
		_owner->SetVelocity(velocity);
		_owner->SetJumpFrameCount(jumpFrameCount);
		// ステータスをジャンプループにする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// 接地フラグがtrueかつstate終了フラグがtrueになっていたら
	if (_owner->GetOnGround() == true && endFlag == true)
	{
		// owner変数を更新
		_owner->SetMoveSpeed(moveSpeed);
		_owner->SetVelocity(velocity);
		// ステータスを着地状態にする
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
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

void PlayerObjectStateJumpStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		//実際に動かしたい軸がずれているので補正
		Vector3 axis = ChackControllerAxis(_keyState);

		//入力があるか
		if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
		{
			// 前のフレームのキャラクターの前方ベクトルを保存
			Vector3 tmpForward = _owner->GetCharaForwardVec();
			// 方向キーの入力値とカメラの向きから、移動方向を決定
			Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
			forward.Normalize();

			// 空中用の移動力の定数を足す
			moveSpeed += _owner->GetAirMovePower();

			// SwitchJumpの場合飛ぶ時間が長いので割合を変更
			if (_owner->GetSwitchJumpFlag())
			{
				// ループしているフレームカウントを定数で割って徐々に減速をかける
				moveSpeed *= 1.0f - jumpFrameCount / SwitchJumpCorrection;
			}
			else
			{
				// ループしているフレームカウントを定数で割って徐々に減速をかける
				moveSpeed *= 1.0f - jumpFrameCount / JumpCorrection;
			}

			if (moveSpeed >= MaxMoveSpeed)
			{
				moveSpeed = MaxMoveSpeed;
			}

			velocity.x = forward.x * moveSpeed;
			velocity.y = forward.y * moveSpeed;

			RotationProcess(_owner, forward, tmpForward);

			_owner->SetMoveSpeed(moveSpeed);


			_owner->SetInputFlag(true);
		}
		else
		{
			_owner->SetInputFlag(false);
		}

		if (_owner->GetIsAvailableJumpKey() == true && _owner->GetJumpFlag() == true || _owner->GetSwitchJumpFlag() == true && _owner->GetIsAvailableJumpKey() == true)
		{

			if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Held ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Held ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Held ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Held ||
				_owner->GetIsAvailableJumpKey() == true)
			{
				++jumpFrameCount;
				float jumpPower = _owner->GetJumpPower();
				velocity.z = jumpPower;

				if (8 > jumpFrameCount && _owner->GetSwitchJumpFlag() == false)
				{
					_owner->SetJumpPower(jumpPower + 100.0f);
				}
				else if (_owner->GetSwitchJumpFlag() == true && 24 > jumpFrameCount)
				{
					_owner->SetJumpPower(jumpPower + 100.0f);
				}
				else
				{
					_owner->SetIsAvailableJumpKey(false);
					_owner->SetJumpFlag(false);
					endFlag = true;
				}

			}
		}

		// ジャンプを割り当てられているコントローラーのボタンが離されたら
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Released ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Released ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released)
		{
			_owner->SetIsAvailableJumpKey(false);
			_owner->SetJumpFlag(false);
			_owner->SetJumpPower(_owner->GetFirstJumpPower());
			endFlag = true;
		}
	}
}

void PlayerObjectStateJumpStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPSTART),0.6f);
	// stateをジャンプ開始状態にして保存
	state = PlayerState::PLAYER_STATE_JUMPSTART;

	_owner->SetJumpFlag(true);
	// ジャンプフレームカウントをもらう
	jumpFrameCount = _owner->GetJumpFrameCount();
	// ownerの速度ベクトルをもらう
	velocity = _owner->GetVelocity();
	// ownerの速度をもらう
	moveSpeed = _owner->GetMoveSpeed();

	// state終了フラグを初期化
	endFlag = false;

	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();
}
