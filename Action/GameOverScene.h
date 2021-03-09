#pragma once
#include "BaseScene.h"

class GameOverScene :
    public BaseScene
{
public:

	GameOverScene();
	
	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~GameOverScene()override;

	/*
	@fn　シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

