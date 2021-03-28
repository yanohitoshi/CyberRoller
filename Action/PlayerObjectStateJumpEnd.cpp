#include "PlayerObjectStateJumpEnd.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateJumpEnd::PlayerObjectStateJumpEnd()
{
}

PlayerObjectStateJumpEnd::~PlayerObjectStateJumpEnd()
{
}

PlayerState PlayerObjectStateJumpEnd::Update(PlayerObject* _owner, float _deltaTime)
{

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
		state = PlayerState::PLAYER_STATE_RUN;
	}

	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	return state;
}

void PlayerObjectStateJumpEnd::Input(PlayerObject* _owner, const InputState& _keyState)
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
	if (Math::Abs(axis.x) > 0.0f || Math::Abs(axis.y) > 0.0f)
	{
		_owner->SetInputFlag(true);
	}
	else
	{
		_owner->SetInputFlag(false);
	}

}

void PlayerObjectStateJumpEnd::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND));
	state = PlayerState::PLAYER_STATE_JUMPEND;

	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	endFlag = false;
}
