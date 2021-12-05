//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StageSelectSceneSoundManager.h"
#include "SoundEffectComponent.h"
#include "MusicComponent.h"

/*
@fn �R���X�g���N�^
@param �e�N���X�̃V�[���N���X�̃|�C���^
*/
StageSelectSceneSoundManager::StageSelectSceneSoundManager()
	: GameObject(false, Tag::AUDIO)
	, InputDeadSpace(0.3f)
{
	// �ϐ�������
	isAnalogStickSelect = false;
	selectCount = 0;
	isPlayDecisionSound = false;
	isPushDecisionSceneButton = false;
	isAvailableSelectInput = true;

	// BGM�𐶐�
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/StageSelect/StageSelect.wav");

	// �T�E���h�G�t�F�N�g�𐶐�
	changeSelectSceneSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/Cursor.wav");
	sceneDecisionSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/button.wav");
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
StageSelectSceneSoundManager::~StageSelectSceneSoundManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void StageSelectSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	// �Đ�����Ă��Ȃ�������
	if (!bgm->IsPlaying())
	{
		// �Đ�����
		bgm->Play();
	}
}

/*
@fn ���͂������Ŏ󂯎��X�V�֐�
@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
@param	_keyState ���͏��
*/
void StageSelectSceneSoundManager::GameObjectInput(const InputState& _keyState)
{
	// �V�[������{�^�����g�p�\��
	if (isAvailableSelectInput)
	{
		// ���͏�Ԃ𔻒�
		isPushDecisionSceneButton = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed;

		// ���͂���Ă�����
		if (isPushDecisionSceneButton)
		{
			// �T�E���h��炷
			sceneDecisionSound->Play();
			// ���͕s��ԂɕύX
			isAvailableSelectInput = false;
		}
	}

	// ����{�^����������Ă�����
	if (isPushDecisionSceneButton)
	{
		// �Đ�����Ă��邩���X�V
		isPlayDecisionSound = sceneDecisionSound->IsPlaying();
	}

	if (isAnalogStickSelect)
	{
		++selectCount;

		if (selectCount >= 30)
		{
			isAnalogStickSelect = false;
			selectCount = 0;
		}
	}

	// �A�i���O�X�e�B�b�N���X���Ă��邩�ǂ���
	bool inclineSelectSceneStick = false;

	if (!isAnalogStickSelect && isAvailableSelectInput)
	{
		// �R���g���[���̃A�i���O�X�e�B�b�N�̓��͏����v�Z����
		float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
		float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

		//�A�i���O�X�e�B�b�N�̃L�[���͂��擾
		Vector2 Axis = Vector2(0.0f, 0.0f);
		Axis = _keyState.Controller.GetLAxisLeftVec();

		//���ۂɓ�����������������Ă���̂ŕ␳
		Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

		// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
		if (Math::Abs(axis.y) > InputDeadSpace && !isAnalogStickSelect)
		{
			inclineSelectSceneStick = true;
			isAnalogStickSelect = true;
		}
	}

	// �V�[���I���{�^�����X���Ă��邩�ǂ���
	bool pushSelectSceneButton = false;
	if (isAvailableSelectInput)
	{
		pushSelectSceneButton = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Pressed ||
			_keyState.Keyboard.GetKeyState(SDL_SCANCODE_A) == Pressed ||
			_keyState.Keyboard.GetKeyState(SDL_SCANCODE_D) == Pressed;
	}

	// �V�[���I���{�^����������邩Stick���X���Ă�����
	if (pushSelectSceneButton || inclineSelectSceneStick)
	{
		if (changeSelectSceneSound->IsPlaying())
		{
			changeSelectSceneSound->Stop();
		}

		// �T�E���h��炷
		changeSelectSceneSound->Play();
	}
}