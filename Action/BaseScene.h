#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Math.h"

// クラスの前方宣言
class PlayerObject;
struct InputState;
enum SceneState;

/*
@file BaseScene.h
@brief Sceneの基底クラス
*/
class BaseScene
{
public:

	// コンストラクタ
	BaseScene()
	: MaxLight(0.8f)
	, ClearToChangeSceneTime(360)
	, ChoiceContinueCount(90)
	, ContinueToChangeScene(360)
	, TimeoversLight(Vector3(0.3f, 0.3f, 0.3f))
	, ChangeLightSpeed(Vector3(0.01f, 0.01f, 0.01f))
	, isSceneClear(false)
	{};

	/*
	@fn デストラクタ(仮想関数)
	@brief  sceneの削除を行う
	*/
	virtual ~BaseScene() {};

	/*
	@fn　シーンのアップデート関数(純粋仮想関数)
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	virtual SceneState Update(const InputState& _inputState) = 0;


protected:

	/*
	@fn シーン開始時のライトアップ関数
	*/
	void StartSceneLightUp();

	/*
	@fn クリアしたかのチェックとクリアカウントを数える処理関数
	@param _playerObject シーンに存在するプレイヤーのポインタ
	*/
	void SceneClearCount(PlayerObject* _playerObject);

	/*
	@fn コンティニュー選択処理関数
	@param _inputState 入力情報
	*/
	void ContinueSelect(const InputState& _inputState);

	/*
	@fn コンティニュー選択時のライト遷移関数
	*/
	void LightTransitionAtContinue();
	
	/*
	@fn コンティニュー選択後のシーンステータス変更処理関数
	@param _nowScene コンティニューが選択された場合そのシーンのステータスが必要なため今のステータスをもらう
	*/
	void SceneStateChangeAtContinue(SceneState _nowScene);

	// ステージクリエイターからプレイヤーのポインタをもらうための変数
	PlayerObject* playerObject;

	// シーンステータスを管理するための変数
	SceneState state;

	// ライト用Vector3変数
	Vector3 light;
	// クリア後のカウント
	int clearCount;
	// コンティニュー選択後の切り替え用カウント
	int changeCount;
	// シーンが始まったかどうかフラグ
	bool startScene;
	// コンテニューされたかフラグ
	bool isContinueFlag;
	// 終了フラグ
	bool isEndFlag;
	// ライトを落とすかどうかフラグ
	bool lightDownFlag;
	// シーンをクリアしたかどうか
	bool isSceneClear;
	// タイムオーバーになったか
	bool isTimeOver;

	// ライトの強さの最大値
	const float MaxLight;
	// クリアした時のシーンが遷移するまでのカウント
	const int ClearToChangeSceneTime;
	// コンテニュー選択状態に入るまでのカウント
	const int ChoiceContinueCount;
	// コンテニュー選択後、次のシーンに遷移するまでのカウント
	const int ContinueToChangeScene;
	// タイムオーバー時のライトの明るさ
	const Vector3 TimeoversLight;
	// ライトアップ・ダウン時の変更速度
	const Vector3 ChangeLightSpeed;

public:

	/*
	@fn シーンが始まったかどうかフラグのgetter
	@return シーンが始まったかどうか
	*/
	bool GetStartScene() { return startScene; }

	/*
	@fn シーンをクリアしたかどうかフラグのgetter
	@return シーンをクリアしたかどうか
	*/
	bool GetIsSceneClear() { return isSceneClear; }

	/*
	@fn タイムオーバーになったかフラグのgetter
	@return タイムオーバーになったか
	*/
	bool GetIsTimeOver() { return isTimeOver; }

	/*
	@fn コンテニューされたかフラグのgetter
	@return コンテニューされたか
	*/
	bool GetIsContinueFlag() { return isContinueFlag; }

	/*
	@fn 終了フラグのgetter
	@return 終了しているかどうか
	*/
	bool GetIsEndFlag() { return isEndFlag; }
};