#pragma once
#include "BaseScene.h"

class FourthStageScene :
    public BaseScene
{
public:

	/*
	@fn コンストラクタ
	@brief  Sceneの生成を行う
	*/
	FourthStageScene();

	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~FourthStageScene()override;

	/*
	@fn　シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

