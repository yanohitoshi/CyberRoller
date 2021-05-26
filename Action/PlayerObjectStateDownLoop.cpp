#include "PlayerObjectStateDownLoop.h"
#include "SkeletalMeshComponent.h"
PlayerObjectStateDownLoop::PlayerObjectStateDownLoop()
{
}

PlayerObjectStateDownLoop::~PlayerObjectStateDownLoop()
{
}

PlayerState PlayerObjectStateDownLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	// ���̓t���O��true�ɂȂ�����
	if (isInput)
	{
		// ���͏�Ԃ����ăR���e�B�j���[��Ԃ��m�F
		ChackContinueProcess();
	}

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateDownLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// �����A�R���g���[���[��A�{�^���܂��̓L�[�{�[�h��C�{�^���������ꂽ��
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_C) == true)
	{
		// ���̓t���O��true�ɕύX
		isInput = true;
		// �R���e�B�j���[�t���O��true�ɕύX
		isContinue = true;
	}
	// �����A�R���g���[���[��B�{�^���܂��̓L�[�{�[�h��Z�{�^���������ꂽ��
	else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			 _keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_Z) == true)
	{
		// ���̓t���O�݂̂�true�ɕύX
		isInput = true;
	}
	
}

void PlayerObjectStateDownLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_LOOP));
	// state���_�E�����[�v��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	// �R���e�B�j���[�t���O��������
	isContinue = false;
	// ���͂����������ǂ����t���O��������
	isInput = false;
}

void PlayerObjectStateDownLoop::ChackContinueProcess()
{
	// �R���e�B�j���[�t���O��true��������
	if (isContinue)
	{
		// �R���e�B�j���[���I�����ꂽ��ԂɕύX
		state = PlayerState::PLAYER_STATE_DOWN_UP;
	}
	else // �R���e�B�j���[����Ă��Ȃ�������
	{
		// �Q�[���I�[�o�[��ԂɕύX
		state = PlayerState::PLAYER_STATE_DOWN_OVER;
	}
}
