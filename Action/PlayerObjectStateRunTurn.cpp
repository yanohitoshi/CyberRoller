#include "PlayerObjectStateRunTurn.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateRunTurn::PlayerObjectStateRunTurn()
	: MinimumSpeed(200.0f)
{
}

PlayerObjectStateRunTurn::~PlayerObjectStateRunTurn()
{
}

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

	if (_owner->GetIsJumping() || _owner->GetJumpFlag() || _owner->GetSwitchJumpFlag()) // ジャンプ系フラグがtrueだったら
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

void PlayerObjectStateRunTurn::Input(PlayerObject* _owner, const InputState& _keyState)
{

	if (_owner->GetIsAvailableInput())
	{
		//Axisの値をとる32700~-32700
		float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
		float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

		//アナログスティックのキー入力を取得
		Vector2 Axis = Vector2(0.0f, 0.0f);
		Axis = _keyState.Controller.GetLAxisLeftVec();

		//実際に動かしたい軸がずれているので補正
		Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

		//入力があるか
		if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
		{
			_owner->SetTmpCharaForwardVec(_owner->GetCharaForwardVec());

			// 方向キーの入力値とカメラの向きから、移動方向を決定
			Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
			forward.Normalize();
			_owner->SetCharaForwardVec(forward);

		}
		else
		{
			_owner->SetInputFlag(false);
		}

		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed)
		{
			_owner->SetJumpFlag(true);
			_owner->SetIsJumping(true);
		}
	}
}

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
