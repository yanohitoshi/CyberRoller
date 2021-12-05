//-----------------------------------------------------------------------------
//	@brief	インクルード
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
	// ライト情報初期化
	light = Vector3(0.8f, 0.8f, 0.8f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// シーンステータス初期化
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
		// コントローラのアナログスティックの入力情報を計算する
		float ALX = _inputState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
		float ALY = _inputState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

		//アナログスティックのキー入力を取得
		Vector2 Axis = Vector2(0.0f, 0.0f);
		Axis = _inputState.Controller.GetLAxisLeftVec();

		//実際に動かしたい軸がずれているので補正
		Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

		// 取得した数値を見てデッドスペース外だったら入力処理を行う
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

	// 選択されたら選ばれたシーンを返す
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
