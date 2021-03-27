#include "PlayerObjectStateRun.h"
#include "SkeletalMeshComponent.h"
#include "GameObject.h"

PlayerObjectStateRun::PlayerObjectStateRun()
{
}

PlayerObjectStateRun::~PlayerObjectStateRun()
{
}

PlayerState PlayerObjectStateRun::Update(PlayerObject* _owner,float _deltaTime)
{

	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	return state;
}

void PlayerObjectStateRun::Input(PlayerObject* _owner,const InputState& _keyState)
{
	//Axis�̒l���Ƃ�32700~-32700
	float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
	float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

	//�A�i���O�X�e�B�b�N�̃L�[���͂��擾
	Vector2 Axis = Vector2(0.0f, 0.0f);
	Axis = _keyState.Controller.GetLAxisLeftVec();

	//���ۂɓ�����������������Ă���̂ŕ␳
	Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

	//���͂����邩
	if (Math::Abs(axis.x) > 0.0f || Math::Abs(axis.y) > 0.0f)
	{
		// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
		// charaForwardVec = forwardVec * axis.x + rightVec * axis.y;
		Vector3 tmpVec = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
		tmpVec.Normalize();
		_owner->SetCharaForwardVec(tmpVec);
		// inputFlag = true;

		velocity.x = _owner->GetCharaForwardVec().x * _owner->GetMoveSpeed() * 2.0f;
		velocity.y = _owner->GetCharaForwardVec().y * _owner->GetMoveSpeed() * 2.0f;


		if (_owner->GetTmpCharaForwardVec() != _owner->GetCharaForwardVec())
		{
			Vector3 tmpRotateVec = _owner->GetCharaForwardVec();
			tmpRotateVec.Normalize();
			//��]
			_owner->SetRotateVec(Vector3::Lerp(_owner->GetRotateVec(), tmpRotateVec, 0.2f));
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

void PlayerObjectStateRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN));
	state = PlayerState::PLAYER_STATE_RUN;
}