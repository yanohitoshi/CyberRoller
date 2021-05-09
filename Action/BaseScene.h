#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Math.h"

// クラスの前方宣言
struct InputState;
enum SceneState;
class PlayerObject;

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
	, ClearToChangeScene(120)
	, ChoiceContinueCount(90)
	, ContinueToChangeScene(360)
	, TimeoversLight(Vector3(0.3f, 0.3f, 0.3f))
	, ChangeLightSpeed(Vector3(0.01f, 0.01f, 0.01f))
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
	virtual SceneState Update(const InputState& state) = 0;


protected:

	// ステージクリエイターからプレイヤーのポインタをもらうための変数
	PlayerObject* playerObject;

	// ライト用Vector3変数
	Vector3 light;
	// クリア後のカウント
	int clearCount;
	// 切り替え用カウント
	int changeCount;
	// シーンが始まったかどうかフラグ
	bool startScene;
	// コンテニューされたかフラグ
	bool isContinueFlag;
	// 終了フラグ
	bool endFlag;
	// ライトを落とすかどうかフラグ
	bool lightDownFlag;

	// ライトの強さの最大値
	const float MaxLight;
	// クリアした時のシーンが遷移するまでのカウント
	const int ClearToChangeScene;
	// コンテニュー選択状態に入るまでのカウント
	const int ChoiceContinueCount;
	// コンテニュー選択後、次のシーンに遷移するまでのカウント
	const int ContinueToChangeScene;
	// タイムオーバー時のライトの明るさ
	const Vector3 TimeoversLight;
	// ライトアップ・ダウン時の変更速度
	const Vector3 ChangeLightSpeed;

private:


};

