//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ResultScene.h"
#include "TitleScene.h"
#include "InputSystem.h"
#include "ResultSceneUI.h"

ResultScene::ResultScene()
{
	// �V�[���X�e�[�^�X������
	state = SceneState::RESULT_SCENE;
	// �V�[��UI�ǉ�
	new ResultSceneUI();
}

ResultScene::~ResultScene()
{

}

SceneState ResultScene::Update(const InputState& _inputState)
{
	// �g���K�[�̏���ϐ��ɓ����
	float leftTrigger = _inputState.Controller.GetLeftTrigger();
	float rightTrigger = _inputState.Controller.GetRightTrigger();

	// ���͂����ăV�[���J��
	if (_inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_GUIDE) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_START) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_LEFTSTICK) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_RIGHTSTICK) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Pressed ||
		leftTrigger == 1.0f || rightTrigger == 1.0f)
	{
		state = SceneState::TITLE_SCENE;
	}

	// �X�V��̃V�[���X�e�[�^�X��Ԃ�
	return state;
}

