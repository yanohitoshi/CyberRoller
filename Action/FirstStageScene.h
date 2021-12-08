#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"

/*
@file FirstStageScene.h
@brief 第1ステージの管理と更新を行う
*/
class FirstStageScene :
    public BaseScene
{
public:

	/*
	@fn コンストラクタ
	@brief  Sceneの生成を行う
	*/
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
	SceneState Update(const InputState& _inputState)override;

private:

};