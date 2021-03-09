#pragma once
#include "BaseScene.h"

class SecondStageScene :
    public BaseScene
{
public:

	SecondStageScene();
	
	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~SecondStageScene()override;

	/*
	@fn　シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

