//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleScene.h"
#include "InputSystem.h"
#include "TitleSceneUI.h"
#include "GameObject.h"
#include "RenderingObjectManager.h"
#include "TitleStageCreator.h"
#include "MusicComponent.h"

/*
@fn �R���X�g���N�^
@brief  Scene�̐������s��
*/
TitleScene::TitleScene()
{
	// ���C�g��񏉊���
	light = Vector3(0.8f, 0.8f, 0.8f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// �V�[���X�e�[�^�X������
	state = SceneState::TITLE_SCENE;

	//�X�e�[�W�𐶐�����N���X�̃C���X�^���X
	TitleStageCreator* titleStageCreator = new TitleStageCreator(false, Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!titleStageCreator->OpenFile())
	{
		titleStageCreator->CreateStage();
	}

	// �V�[��UI��ǉ�
	new TitleSceneUI();

	// �N���G�C�^�[�̏�Ԃ�dead�ɂ��ЂÂ���
	titleStageCreator->SetState(State::Dead);

}

/*
@fn �f�X�g���N�^
@brief  scene�̍폜���s��
*/
TitleScene::~TitleScene()
{
}

/*
@fn�@�V�[���̃A�b�v�f�[�g�֐�
@brief	�V�[���̍X�V�������s��
@param	���͏��
@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
*/
SceneState TitleScene::Update(const InputState& _inputState)
{
	// �g���K�[�̏���ϐ��ɓ����
	float leftTrigger = _inputState.Controller.GetLeftTrigger();
	float rightTrigger = _inputState.Controller.GetRightTrigger();

	bool isPressedButton = _inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed ||
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
		leftTrigger == 1.0f || rightTrigger == 1.0f;

	// ���͂����ăV�[���J��
	if (isPressedButton)
	{
		state = SceneState::TUTORIAL_SATGE_SCENE;
	}

	// �X�V��̃V�[���X�e�[�^�X��Ԃ�
	return state;
}