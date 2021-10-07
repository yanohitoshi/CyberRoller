//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ResultScene.h"
#include "InputSystem.h"
#include "ResultSceneUI.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResultSceneCreator.h"
#include "SkyBoxObject.h"

/*
@fn コンストラクタ
@brief  Sceneの生成を行う
*/
ResultScene::ResultScene()
{
	// ライト情報初期化
	light = Vector3(0.8f, 0.8f, 0.8f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.5f, 0.5f, 0.8f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(1.0f, 1.0f, 1.0f);

	// シーンステータス初期化
	state = SceneState::RESULT_SCENE;

	//ステージを生成するクラスのインスタンス
	ResultSceneCreator* resultSceneCreator = new ResultSceneCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!resultSceneCreator->OpenFile())
	{
		resultSceneCreator->CreateStage();
	}

	// シーンステータス初期化
	state = SceneState::RESULT_SCENE;
	// シーンUI追加
	new ResultSceneUI();
}

/*
@fn デストラクタ
@brief  sceneの削除を行う
*/
ResultScene::~ResultScene()
{
}

/*
@fn　シーンのアップデート関数
@brief	シーンの更新処理を行う
@param	入力情報
@return シーンの遷移を判定するためのenum型のSceneState
*/
SceneState ResultScene::Update(const InputState& _inputState)
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
		state = SceneState::TITLE_SCENE;
	}

	// 更新後のシーンステータスを返す
	return state;
}