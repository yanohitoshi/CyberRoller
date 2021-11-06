#pragma once
#include "BaseScene.h"

class FifthStageScene :
    public BaseScene
{
public:

	/*
	@fn コンストラクタ
	@brief  Sceneの生成を行う
	*/
	FifthStageScene();

	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~FifthStageScene()override;

	/*
	@fn　シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

};

