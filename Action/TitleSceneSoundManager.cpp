//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"
#include "SoundEffectComponent.h"

/*
@fn �R���X�g���N�^
@param �e�N���X�̃V�[���N���X�̃|�C���^
*/
TitleSceneSoundManager::TitleSceneSoundManager()
	: GameObject(false,Tag::AUDIO)
{
	// �ϐ�������
	isAvailableSelectInput = true;
	isPlayDecisionSound = false;

	// BGM�𐶐�
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Title/Title.wav");

	// �T�E���h�G�t�F�N�g�𐶐�
	startSceneSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/button.wav");

	// �Đ�����
	bgm->Play();
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TitleSceneSoundManager::~TitleSceneSoundManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TitleSceneSoundManager::UpdateGameObject(float _deltaTime)
{
}

/*
@fn ���͂������Ŏ󂯎��X�V�֐�
@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
@param	_keyState ���͏��
*/
void TitleSceneSoundManager::GameObjectInput(const InputState& _keyState)
{
	// �V�[������{�^�����g�p�\��
	if (isAvailableSelectInput)
	{

		// �g���K�[�̏���ϐ��ɓ����
		float leftTrigger = _keyState.Controller.GetLeftTrigger();
		float rightTrigger = _keyState.Controller.GetRightTrigger();

		// ���͏�Ԃ𔻒�
		isPushDecisionSceneButton = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_GUIDE) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_START) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_LEFTSTICK) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_RIGHTSTICK) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Pressed ||
			leftTrigger == 1.0f || rightTrigger == 1.0f;

		// ���͂���������
		if (isPushDecisionSceneButton)
		{
			// �T�E���h��炷
			startSceneSound->Play();
			// ���͕s��ԂɕύX
			isAvailableSelectInput = false;
			if (bgm->IsPlaying())
			{
				bgm->Stop();
			}
		}
	}

	// ���͂��ꂽ��Ԃ̎�
	if (isPushDecisionSceneButton)
	{
		// �Đ��������X�V
		isPlayDecisionSound = startSceneSound->IsPlaying();
	}
}