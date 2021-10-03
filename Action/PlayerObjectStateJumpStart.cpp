//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJumpStart.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateJumpStart::PlayerObjectStateJumpStart()
	: JumpCorrection(80.0f)
	, SwitchJumpCorrection(160.0f)
	, JumpTime(8)
	, SwitchJumpTime(10)
	, JumpAccelPower(100.0f)
	, SwitchJumpAccelPower(110.0f)
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

	ChackDeadFlag(_owner);

	ChackTimeOverFlag();

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateJumpStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// 入力情報チェック処理
		ChackInputProcess(_owner, _keyState);
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

void PlayerObjectStateJumpStart::ChackInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	//実際に動かしたい軸がずれているので補正
	Vector3 axis = ChackControllerAxis(_keyState);

	// 取得した数値を見てデッドスペース外だったら入力処理を行う
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// 入力がある場合の処理
		InputJumpMovableProcess(_owner, axis);
	}
	else
	{
		// 入力がない場合の処理
		UninputMovableProcess(_owner);
	}

	// ジャンプボタン利用可能フラグがtrueかつジャンプフラグがtrueまたはスイッチジャンプフラグがtrueかつジャンプボタン利用可能フラグがtrueの時
	if (_owner->GetIsAvailableJumpKey() == true && _owner->GetJumpFlag() == true ||
		_owner->GetSwitchJumpFlag() == true && _owner->GetIsAvailableJumpKey() == true)
	{
		// ジャンプ入力ボタンが押され続けている時またはジャンプボタン利用可能フラグがtrueの時
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Held ||
			_owner->GetIsAvailableJumpKey() == true)
		{
			JumpStartProcess(_owner);
		}
	}

	// ジャンプを割り当てられているコントローラーのボタンが離されたら
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released)
	{
		// ジャンプ終了準備
		JumpEndProcess(_owner);
	}

}

void PlayerObjectStateJumpStart::UninputMovableProcess(PlayerObject* _owner)
{
	// 移動入力フラグをfalseにセット
	_owner->SetInputFlag(false);
}

void PlayerObjectStateJumpStart::JumpStartProcess(PlayerObject* _owner)
{
	// ジャンプしている時間をフレームでカウント
	++jumpFrameCount;

	// ジャンプ力の仮変数を作り前フレームでのジャンプ力をもらう
	float jumpPower = _owner->GetJumpPower();

	// Z軸にジャンプ力を代入
	velocity.z = jumpPower;

	// スイッチジャンプではなくてかつジャンプ利用可能な時間内だったら
	if (JumpTime > jumpFrameCount && _owner->GetSwitchJumpFlag() == false)
	{
		// ジャンプ力に定数値を足してジャンプ力をownerのジャンプ力変数にセット
		_owner->SetJumpPower(jumpPower + JumpAccelPower);
	}
	else if (_owner->GetSwitchJumpFlag() == true && SwitchJumpTime > jumpFrameCount) // スイッチジャンプでかつジャンプ利用可能な時間内だったら
	{
		// ジャンプ力に定数値を足してジャンプ力をownerのジャンプ力変数にセット
		_owner->SetJumpPower(jumpPower + SwitchJumpAccelPower);
	}
	else // ジャンプ利用時間を経過していたら
	{
		// ジャンプボタン利用可能状態フラグをfalseにセット
		_owner->SetIsAvailableJumpKey(false);
		// ステータス終了フラグをtrueにセット
		endFlag = true;
		// ジャンプフラグをfalseにセット
		_owner->SetJumpFlag(false);
	}
}

void PlayerObjectStateJumpStart::JumpEndProcess(PlayerObject* _owner)
{
	// ジャンプボタン利用可能状態フラグをfalseにセット
	_owner->SetIsAvailableJumpKey(false);
	// ステータス終了フラグをtrueにセット
	endFlag = true;

	// ジャンプフラグをfalseにセット
	_owner->SetJumpFlag(false);
	// ジャンプパワーを初期値に再セット
	_owner->SetJumpPower(_owner->GetFirstJumpPower());
}
