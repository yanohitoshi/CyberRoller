#include "PlayerObjectStateJumpLoop.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateJumpLoop::PlayerObjectStateJumpLoop()
	: MaxFallSpeed(-2000.0f)
	, TurnValue(600.0f)
	, JumpCorrection(840.0f)
	, SwitchJumpCorrection(1320.0f)
{
}

PlayerObjectStateJumpLoop::~PlayerObjectStateJumpLoop()
{
}

PlayerState PlayerObjectStateJumpLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	// 滞空時間のカウントを数える
	++jumpLoopCount;

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

	// アニメーション変更フラグがtrueでかつZ軸の速度が0.0f以下になったら
	if (animChangeFlag == true && velocity.z <= 0.0f)
	{
		// ジャンプループのアニメーションを再生
		skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPLOOP));
		// 毎回再生をかけないようにフラグをfalseに
		animChangeFlag = false;
	}

	// 接地フラグがtrueでかつ移動入力がある状態でかつ速度が一定値以上だったら
	if (_owner->GetOnGround() == true && _owner->GetInputFlag() && moveSpeed >= TurnValue)
	{
		// ステータスをローリングアニメーションを持つ着地状態にする
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_RUN;
	}
	else if (_owner->GetOnGround() == true) // 接地フラグがtrueになったら
	{
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

	// ownerの変数を更新
	_owner->SetVelocity(velocity);
	_owner->SetMoveSpeed(moveSpeed);

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateJumpLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		//実際に動かしたい軸がずれているので補正
		Vector3 axis = ChackControllerAxis(_keyState);

		// 取得した数値を見てデッドスペース外だったら入力処理を行う
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
				moveSpeed *= 1.0f - jumpLoopCount / SwitchJumpCorrection;
			}
			else
			{
				// ループしているフレームカウントを定数で割って徐々に減速をかける
				moveSpeed *= 1.0f - jumpLoopCount / JumpCorrection;
			}

			// 移動速度が最大速度を超えていたら
			if (moveSpeed >= MaxMoveSpeed)
			{
				// 最低速度に固定する
				moveSpeed = MaxMoveSpeed;
			}

			// X軸とY軸に前方ベクトルに速度をかけて速度付きベクトルを作る
			velocity.x = forward.x * moveSpeed;
			velocity.y = forward.y * moveSpeed;

			// 回転処理
			RotationProcess(_owner,forward, tmpForward);

			// ownerの速度変数を更新
			_owner->SetMoveSpeed(moveSpeed);
		}
		else // 取得した数値を見てデッドスペース内だったら減速処理を行う
		{
			//　移動速度から空中用減速値を引く
			moveSpeed -= _owner->GetAirMovePower();

			// 移動速度が0.0f以下になったら
			if (moveSpeed <= 0.0f)
			{
				// マイナスにならないように0.0fに固定
				moveSpeed = 0.0f;
			}

			// ownerの方向ベクトルに移動速度を掛けて移動ベクトルを更新
			velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
			velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

			// 移動入力フラグをfalseにセット
			_owner->SetInputFlag(false);
		}
		
	}

}

void PlayerObjectStateJumpLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// stateをジャンプループ状態にして保存
	state = PlayerState::PLAYER_STATE_JUMPLOOP;
	// アニメーション変更フラグを初期化
	animChangeFlag = true;
	// 滞空時間を測るカウントの初期化
	jumpLoopCount = 0;
	// ownerの速度をもらう
	velocity = _owner->GetVelocity();

	// 見た目上スムーズに遷移させるために前のステータスがジャンプ開始だったらジャンプ力をもらう
	if (_owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPSTART)
	{
		// 前フレームのジャンプ力をもらう
		velocity.z = _owner->GetJumpPower();
	}

	// ownerの加速度変数の数値をもらう
	moveSpeed = _owner->GetMoveSpeed();

	// 加速度変数の数値が0.0f以下だったら
	if (moveSpeed <= 0.0f)
	{
		// 初速度を入れる
		moveSpeed = _owner->GetFirstMovePower();
	}

	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();

}
