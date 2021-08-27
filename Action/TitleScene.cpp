//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleScene.h"
#include "InputSystem.h"
#include "TitleSceneUI.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TitleStageCreator.h"
#include "BoxObject.h"
#include "SkyBoxObject.h"

TitleScene::TitleScene()
{
	// ���C�g��񏉊���
	light = Vector3(0.8f, 0.8f, 0.8f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
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

	skyBox = new SkyBoxObject(false,Tag::UI);
	//RENDERER->SetActiveSkyBox(skyBox);
	// �V�[��UI��ǉ�
	new TitleSceneUI();

}

TitleScene::~TitleScene()
{
}

SceneState TitleScene::Update(const InputState& _inputState)
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
		state = SceneState::FIRST_SATGE_SCENE;
	}

	// �X�V��̃V�[���X�e�[�^�X��Ԃ�
	return state;

}

