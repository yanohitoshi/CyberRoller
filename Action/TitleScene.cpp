//-----------------------------------------------------------------------------
//	@brief	インクルード
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
	// ライト情報初期化
	light = Vector3(0.8f, 0.8f, 0.8f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// シーンステータス初期化
	state = SceneState::TITLE_SCENE;

	//ステージを生成するクラスのインスタンス
	TitleStageCreator* titleStageCreator = new TitleStageCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!titleStageCreator->OpenFile())
	{
		titleStageCreator->CreateStage();
	}

	skyBox = new SkyBoxObject(false,Tag::UI);
	//RENDERER->SetActiveSkyBox(skyBox);
	// シーンUIを追加
	new TitleSceneUI();

}

TitleScene::~TitleScene()
{
}

SceneState TitleScene::Update(const InputState& _inputState)
{
	// トリガーの情報を変数に入れる
	float leftTrigger = _inputState.Controller.GetLeftTrigger();
	float rightTrigger = _inputState.Controller.GetRightTrigger();

	// 入力を見てシーン遷移
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

	// 更新後のシーンステータスを返す
	return state;

}

