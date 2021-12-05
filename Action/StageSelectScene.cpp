//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StageSelectScene.h"
#include "InputSystem.h"
#include "GameObject.h"
#include "RenderingObjectManager.h"
#include "SkyBoxObject.h"
#include "StageSelectSceneUI.h"
#include "StageSelectSceneSoundManager.h"

StageSelectScene::StageSelectScene()
	: InputDeadSpace(0.3f)
{
	// ���C�g��񏉊���
	light = Vector3(0.8f, 0.8f, 0.8f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// �V�[���X�e�[�^�X������
	state = SceneState::STAGE_SELECT_SCENE;
	selectState = SceneState::FIRST_SATGE_SCENE;

	new StageSelectSceneUI(this);
	stageSelectSceneSoundManager = new StageSelectSceneSoundManager();
	isAnalogStickSelect = false;
	selectCount = 0;
	isSceneSelect = false;

	new StageSelectSceneSoundManager();
}

StageSelectScene::~StageSelectScene()
{
}

SceneState StageSelectScene::Update(const InputState& _inputState)
{

	if (isAnalogStickSelect)
	{
		++selectCount;

		if (selectCount >= 30)
		{
			isAnalogStickSelect = false;
			selectCount = 0;
		}
	}

	if (!isAnalogStickSelect && !isSceneSelect)
	{
		// �R���g���[���̃A�i���O�X�e�B�b�N�̓��͏����v�Z����
		float ALX = _inputState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
		float ALY = _inputState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

		//�A�i���O�X�e�B�b�N�̃L�[���͂��擾
		Vector2 Axis = Vector2(0.0f, 0.0f);
		Axis = _inputState.Controller.GetLAxisLeftVec();

		//���ۂɓ�����������������Ă���̂ŕ␳
		Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

		// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
		if (Math::Abs(axis.y) > InputDeadSpace && !isAnalogStickSelect)
		{
			SelectAnalogStick(axis.y);
		}
	}

	if (!isSceneSelect)
	{
		if (_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Pressed)
		{
			SelectLeft();
		}
		else if (_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Pressed)
		{
			SelectRight();
		}

		if (_inputState.Keyboard.GetKeyState(SDL_SCANCODE_A) == Pressed)
		{
			SelectLeft();
		}
		else if (_inputState.Keyboard.GetKeyState(SDL_SCANCODE_D) == Pressed)
		{
			SelectRight();
		}
	}


	if (!isSceneSelect)
	{
		isSceneSelect = _inputState.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == Pressed ||
			_inputState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed;
	}

	// �I�����ꂽ��I�΂ꂽ�V�[����Ԃ�
	bool isPushDecisionSceneButton = isSceneSelect && !stageSelectSceneSoundManager->GetIsPlayDecisionSound();

	if (isPushDecisionSceneButton)
	{
		return selectState;
	}

	return state;
}

void StageSelectScene::SelectRight()
{
	switch (selectState)
	{
	case FIRST_SATGE_SCENE:
		selectState = SceneState::SECOND_SATGE_SCENE;
		break;

	case SECOND_SATGE_SCENE:
		selectState = SceneState::THIRD_SATGE_SCENE;
		break;

	case THIRD_SATGE_SCENE:
		selectState = SceneState::FOURTH_SATGE_SCENE;
		break;

	case FOURTH_SATGE_SCENE:
		selectState = SceneState::FINAL_STAGE_SCENE;
		break;

	case FINAL_STAGE_SCENE:
		selectState = SceneState::FIRST_SATGE_SCENE;
		break;
	}
}

void StageSelectScene::SelectLeft()
{
	switch (selectState)
	{
	case FIRST_SATGE_SCENE:
		selectState = SceneState::FINAL_STAGE_SCENE;
		break;

	case SECOND_SATGE_SCENE:
		selectState = SceneState::FIRST_SATGE_SCENE;
		break;

	case THIRD_SATGE_SCENE:
		selectState = SceneState::SECOND_SATGE_SCENE;
		break;

	case FOURTH_SATGE_SCENE:
		selectState = SceneState::THIRD_SATGE_SCENE;
		break;

	case FINAL_STAGE_SCENE:
		selectState = SceneState::FOURTH_SATGE_SCENE;
		break;
	}
}

void StageSelectScene::SelectAnalogStick(float _axis)
{
	if (_axis < 0.0f)
	{
		SelectRight();
		isAnalogStickSelect = true;
		return;
	}
	else if (_axis > 0.0f)
	{
		SelectLeft();
		isAnalogStickSelect = true;
		return;
	}
}
