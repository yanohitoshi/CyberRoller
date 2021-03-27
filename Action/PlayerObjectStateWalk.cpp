#include "PlayerObjectStateWalk.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateWalk::PlayerObjectStateWalk()
{
}

PlayerObjectStateWalk::~PlayerObjectStateWalk()
{
}

PlayerState PlayerObjectStateWalk::Update(PlayerObject* _owner, float _deltaTime)
{

	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);


	if (_owner->GetInputFlag())
	{
		if (_owner->GetRunFlag())
		{
			state = PlayerState::PLAYER_STATE_RUN;
		}
		else if (!_owner->GetRunFlag())
		{
			state = PlayerState::PLAYER_STATE_WALK;
		}
	}

	if (_owner->GetIsJumping() || _owner->GetJumpFlag())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	return state;
}

void PlayerObjectStateWalk::Input(PlayerObject* _owner, const InputState& _keyState)
{
	//Axisの値をとる32700~-32700
	float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
	float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

	//アナログスティックのキー入力を取得
	Vector2 Axis = Vector2(0.0f, 0.0f);
	Axis = _keyState.Controller.GetLAxisLeftVec();

	//実際に動かしたい軸がずれているので補正
	Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);


	// 方向キーの入力値とカメラの向きから、移動方向を決定
	Vector3 tmpVec = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
	_owner->SetCharaForwardVec(tmpVec);
	// inputFlag = true;

	velocity.x = _owner->GetCharaForwardVec().x * _owner->GetMoveSpeed();
	velocity.y = _owner->GetCharaForwardVec().y * _owner->GetMoveSpeed();

	if (ALX >= 28000.0f || ALX <= -28000.0f || ALY >= 28000.0f || ALY <= -28000.0f)
	{
		_owner->SetRunFlag(true);
	}
	else if (ALX <= 28000.0f && ALX >= 100.0f || ALX >= -28000.0f && ALX <= -100.0f ||
			 ALY >= 28000.0f && ALY >= 100.0f || ALY <= -28000.0f && ALY <= -100.0f)
	{
		_owner->SetRunFlag(false);
	}
	else
	{
		_owner->SetInputFlag(false);
	}

	if (_owner->GetTmpCharaForwardVec() != _owner->GetCharaForwardVec())
	{
		Vector3 tmpRotateVec = _owner->GetCharaForwardVec();
		//tmpRotateVec.Normalize();
		//回転
		_owner->SetRotateVec(Vector3::Lerp(_owner->GetRotateVec(), tmpRotateVec, 0.2f));
		_owner->RotateToNewForward(_owner->GetRotateVec());
	}

	_owner->SetTmpCharaForwardVec(_owner->GetCharaForwardVec());

	if (true)
	{
		_owner->SetInputFlag(true);
	}


	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed)
	{
		//jumpFlag = true;
		_owner->SetJumpFlag(true);
		//isJumping = true;
		_owner->SetIsJumping(true);
	}

}

void PlayerObjectStateWalk::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_WALK));
	state = PlayerState::PLAYER_STATE_WALK;
}
