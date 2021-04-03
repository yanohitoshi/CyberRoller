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

	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();

	if (!skeletalMeshComponent->IsPlaying())
	{
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	if (_owner->GetSwitchJumpFlag())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	if (_owner->GetInputFlag())
	{
		state = PlayerState::PLAYER_STATE_RUN_START;
	}

	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	if (CountDownFont::timeOverFlag == true)
	{
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	_owner->SetVelocity(velocity);

	return state;
}

void PlayerObjectStateJumpEndToIdle::Input(PlayerObject* _owner, const InputState& _keyState)
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
	if (Math::Abs(axis.x) > 0.3f || Math::Abs(axis.y) > 0.3f)
	{
		_owner->SetInputFlag(true);
	}
	else
	{
		_owner->SetInputFlag(false);
	}

}

void PlayerObjectStateJumpEndToIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE));
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;

	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	endFlag = false;
}
