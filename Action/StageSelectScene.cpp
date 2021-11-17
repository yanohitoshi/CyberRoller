#include "StageSelectScene.h"
#include "InputSystem.h"
#include "GameObject.h"
#include "Renderer.h"
#include "SkyBoxObject.h"

StageSelectScene::StageSelectScene()
{
	// ���C�g��񏉊���
	light = Vector3(0.8f, 0.8f, 0.8f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// �V�[���X�e�[�^�X������
	state = SceneState::STAGE_SELECT_SCENE;
	selectState = SceneState::FIRST_SATGE_SCENE;
}

StageSelectScene::~StageSelectScene()
{
}

SceneState StageSelectScene::Update(const InputState& _inputState)
{
	if (_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Pressed)
	{
		Select();
		//selectState = FIRST_SATGE_SCENE;
	}
	else if (_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Pressed)
	{
		Select();
		//selectState = SECOND_SATGE_SCENE;
	}

	switch (state)
	{
	case FIRST_SATGE_SCENE:
		break;

	case SECOND_SATGE_SCENE:
		break;
	case THIRD_SATGE_SCENE:
		break;
	case FOURTH_SATGE_SCENE:
		break;
	case FIFTH_SATGE_SCENE:
		break;
	case FINAL_STAGE_SCENE:
		break;
	}


	// �I�����ꂽ��I�΂ꂽ�V�[����Ԃ�
	if (_inputState.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == Pressed ||
		_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
	{
		return selectState;
	}

	return state;
}

void StageSelectScene::Select(const InputState& _inputState)
{
}
