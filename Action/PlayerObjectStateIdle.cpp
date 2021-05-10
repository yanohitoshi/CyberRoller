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
	else if (_owner->GetIsJumping() || _owner->GetJumpFlag() || _owner->GetSwitchJumpFlag()) // ジャンプ系フラグがtrueだったら
	{
		// ステータスをジャンプ開始状態に変更
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// 死亡フラグがtrueだったら
	if (_owner->GetDeadFlag())
	{
		// ステータスをジャンプ開始状態に変更
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// タイムオーバーフラグがtrueだったら
	if (CountDownFont::timeOverFlag == true)
	{
		// ステータスをコンティニュー選択スタート状態に変更
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// 入力がなかったら
	if (!_owner->GetInputFlag())
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
	else
	{
		// 入力があったらダンスカウントを初期化
		danceCount = 0;
	}

	// 死亡フラグがfalseでかつタイムオーバー状態でもなくダンス開始フラグがtrueだったら
	if (!_owner->GetDeadFlag() && CountDownFont::timeOverFlag == false && isDanceFlag == true)
	{
		// ステータスをダンス状態に変更
		state = PlayerState::PLAYER_STATE_IDLE_DANCE;
	}

	// 更新されたstateを返す
	return state;

}

void PlayerObjectStateIdle::Input(PlayerObject* _owner, const InputState& _keyState)
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
			_owner->SetInputFlag(true);
		}
		else
		{
			_owner->SetInputFlag(false);
		}

		if (_owner->GetOnGround() == true && _owner->GetJumpFlag() == false)
		{
			if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
				_owner->GetSwitchJumpFlag() == true)
			{
				_owner->SetJumpFlag(true);
				_owner->SetIsJumping(true);
			}
		}
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
