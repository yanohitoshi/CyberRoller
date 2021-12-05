//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ResultScene.h"
#include "InputSystem.h"
#include "ResultSceneUI.h"
#include "GameObject.h"
#include "RenderingObjectManager.h"
#include "ResultSceneCreator.h"
#include "SkyBoxObject.h"
#include "ResultSceneSoundManager.h"

/*
@fn �R���X�g���N�^
@brief  Scene�̐������s��
*/
ResultScene::ResultScene()
{
	// ���C�g��񏉊���
	light = Vector3(0.8f, 0.8f, 0.8f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
	dir.direction = Vector3(0.5f, 0.5f, 0.8f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(1.0f, 1.0f, 1.0f);

	// �V�[���X�e�[�^�X������
	state = SceneState::RESULT_SCENE;

	//�X�e�[�W�𐶐�����N���X�̃C���X�^���X
	ResultSceneCreator* resultSceneCreator = new ResultSceneCreator(false, Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!resultSceneCreator->OpenFile())
	{
		resultSceneCreator->CreateStage();
	}

	// �V�[���X�e�[�^�X������
	state = SceneState::RESULT_SCENE;
	// �V�[��UI�ǉ�
	new ResultSceneUI();

	// �N���G�C�^�[�̏�Ԃ�dead�ɂ��ЂÂ���
	resultSceneCreator->SetState(State::Dead);

	resultSceneSoundManager = new ResultSceneSoundManager();

	isSceneEnd = false;
}

/*
@fn �f�X�g���N�^
@brief  scene�̍폜���s��
*/
ResultScene::~ResultScene()
{
}

/*
@fn�@�V�[���̃A�b�v�f�[�g�֐�
@brief	�V�[���̍X�V�������s��
@param	���͏��
@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
*/
SceneState ResultScene::Update(const InputState& _inputState)
{
	if (!isSceneEnd)
	{
		// �g���K�[�̏���ϐ��ɓ����
		float leftTrigger = _inputState.Controller.GetLeftTrigger();
		float rightTrigger = _inputState.Controller.GetRightTrigger();

		isSceneEnd = _inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed ||
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
	}


	// ���͂����ăV�[���J��
	if (isSceneEnd && !resultSceneSoundManager->GetIsPlayDecisionSound())
	{
		state = SceneState::TITLE_SCENE;
	}

	// �X�V��̃V�[���X�e�[�^�X��Ԃ�
	return state;
}