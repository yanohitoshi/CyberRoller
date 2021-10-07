//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateDownLoop.h"
#include "SkeletalMeshComponent.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateDownLoop::PlayerObjectStateDownLoop()
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateDownLoop::~PlayerObjectStateDownLoop()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
PlayerState PlayerObjectStateDownLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	// �d�͂Ƀf���^�^�C�����������l����
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;

	// �������x���K��l�𒴂��Ă�����
	if (velocity.z <= MaxFallSpeed)
	{
		// �K��l�ɌŒ�
		velocity.z = MaxFallSpeed;
	}

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// ���̓t���O��true�ɂȂ�����
	if (isInput)
	{
		// ���͏�Ԃ����ăR���e�B�j���[��Ԃ��m�F
		ChackContinueProcess();
	}

	// �X�V���ꂽstate��Ԃ�
	return state;
}

/*
@fn �C���v�b�g
@brief	state�ɉ����ē��͏������s��
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
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

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateDownLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_LOOP));
	// state���_�E�����[�v��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	// �I�[�i�[�̎����x���擾
	velocity = _owner->GetVelocity();
	// �R���e�B�j���[�t���O��������
	isContinue = false;
	// ���͂����������ǂ����t���O��������
	isInput = false;
}

/*
@fn �R���e�B�j���[�m�F�����֐�
*/
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
