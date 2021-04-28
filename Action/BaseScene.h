#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Math.h"

// クラスの前方宣言
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
	: MAX_LIGHT(0.8f),
	  CLEAR_TO_CHANGE_SCENE(120),
	  CHOICE_CONTINUE_COUNT(90),
	  CONTINUE_TO_CHANGE_SCENE(360),
	  TIMEOVERS_LIGHT(Vector3(0.3f, 0.3f, 0.3f)),
	  CHANGE_LIGHT_SPEED(Vector3(0.01f, 0.01f, 0.01f))
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
	const float MAX_LIGHT;
	// クリアした時のシーンが遷移するまでのカウント
	const int CLEAR_TO_CHANGE_SCENE;
	// コンテニュー選択状態に入るまでのカウント
	const int CHOICE_CONTINUE_COUNT;
	// コンテニュー選択後、次のシーンに遷移するまでのカウント
	const int CONTINUE_TO_CHANGE_SCENE;
	// タイムオーバー時のライトの明るさ
	const Vector3 TIMEOVERS_LIGHT;
	// ライトアップ・ダウン時の変更速度
	const Vector3 CHANGE_LIGHT_SPEED;

private:


};

