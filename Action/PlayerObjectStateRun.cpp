#include "PlayerObjectStateRun.h"
#include "GameObject.h"

PlayerObjectStateRun::PlayerObjectStateRun(PlayerObject* _owner)
	: PlayerObjectStateBase(_owner)
{
}

PlayerObjectStateRun::~PlayerObjectStateRun()
{
}

PlayerState PlayerObjectStateRun::Update(float _deltaTime)
{

	// positionに速度を足してキャラクターを動かす
	owner->SetPosition(owner->GetPosition() + velocity * _deltaTime);

	return state;
}

void PlayerObjectStateRun::Input(const InputState& _keyState)
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
		// 方向キーの入力値とカメラの向きから、移動方向を決定
		// charaForwardVec = forwardVec * axis.x + rightVec * axis.y;
		Vector3 tmpVec = owner->GetForwardVec() * axis.x + owner->GetRightVec() * axis.y;
		tmpVec.Normalize();
		owner->SetCharaForwardVec(tmpVec);
		// inputFlag = true;

		velocity.x = owner->GetCharaForwardVec().x * owner->GetMoveSpeed() * 2.0f;
		velocity.y = owner->GetCharaForwardVec().y * owner->GetMoveSpeed() * 2.0f;


		if (owner->GetTmpCharaForwardVec() != owner->GetCharaForwardVec())
		{
			Vector3 tmpRotateVec = owner->GetCharaForwardVec();
			tmpRotateVec.Normalize();
			//回転
			owner->SetRotateVec(Vector3::Lerp(owner->GetRotateVec(), tmpRotateVec, 0.2f));
			//RotateToNewForward(rotateVec);
		}
	}

	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed)
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	if (state != PlayerState::PLAYER_STATE_JUMPSTART && state != PlayerState::PLAYER_STATE_RUN)
	{
		state = PlayerState::PLAYER_STATE_IDLE;
	}

}

void PlayerObjectStateRun::Enter( float _deltaTime)
{
}
