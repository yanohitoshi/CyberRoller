#pragma once
#include "BaseScene.h"


/*
@file PlayScene.h
@brief プレイシーンの初期化と生成、次のシーンへのシーン遷移を行う
*/

class FirstStageScene : public BaseScene
{
public:

	FirstStageScene();
	
	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~FirstStageScene()override;

	/*
	@fn　シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& state)override;

private:
	// カウント変数
	int count;
	// シーンが始まったかフラグ
	bool startScene;
};

