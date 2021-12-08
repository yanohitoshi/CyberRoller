#include "ThirdStageScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "ThirdStageCreator.h"
#include "ThirdStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"
#include "ThirdSceneSoundManager.h"

ThirdStageScene::ThirdStageScene()
{
	// ライト情報初期化
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
	dir.direction = Vector3(0.5f, 0.5f, 0.8f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// メンバー変数初期化
	clearCount = 0;
	changeCount = 0;
	startScene = true;
	isContinueFlag = false;
	isEndFlag = false;
	lightDownFlag = true;
	state = SceneState::THIRD_SATGE_SCENE;

	// クリエイター生成
	ThirdStageCreator* thirdStageCreator = new ThirdStageCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!thirdStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = thirdStageCreator->CreatePlayer();
		//ステージを生成する
		thirdStageCreator->CreateStage();
	}

	// クリエイターから収集物クラスのポインタをもらう
	CollectionObject* firstCollection = thirdStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = thirdStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = thirdStageCreator->FindCollectionObject(CollectionTag::THIRD);

	// シーンUIを追加
	new ThirdStageUI(playerObject, firstCollection, secondCollection, thirdCollection);

	// クリエイターの状態をdeadにし片づける
	thirdStageCreator->SetState(State::Dead);

	// サウンドマネージャークラスを生成
	new ThirdSceneSoundManager(this);
}

ThirdStageScene::~ThirdStageScene()
{
}

SceneState ThirdStageScene::Update(const InputState& _inputState)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		// シーン開始時のライトアップ処理
		StartSceneLightUp();
	}

	// クリアしたかのチェックとクリアカウントを数える処理関数
	SceneClearCount(playerObject);

	// クリアカウントが一定を超えたらシーンを切り替える
	if (clearCount >= ClearToChangeSceneTime)
	{
		state = SceneState::FOURTH_SATGE_SCENE;
	}

	// タイムオーバー状態かつライトを一定まで落とす状態だったら
	if (CountDownFont::GetTimeOverFlag() == true && lightDownFlag == true)
	{
		// コンティニュー選択処理
		ContinueSelect(_inputState);
	}

	// コンテニューかゲームオーバーが選択されたら
	if (isContinueFlag == true || isEndFlag == true)
	{
		// コンティニュー選択時のライト遷移処理
		LightTransitionAtContinue();
	}

	// コンティニュー選択後のシーン切り替えカウントが一定以上になったら
	if (changeCount >= ContinueToChangeScene)
	{
		// シーンステータス切り替え処理
		SceneStateChangeAtContinue(SceneState::THIRD_SATGE_SCENE);
	}

	// 一定時間操作がなかったらタイトルへ
	if (playerObject->GetRestartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// 更新後のシーンステータスを返す
	return state;
}
