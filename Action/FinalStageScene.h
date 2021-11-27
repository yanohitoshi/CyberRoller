#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"

/*
@file FinalStageScene.h
@brief 最終ステージの管理と更新を行う
*/
class FinalStageScene :
    public BaseScene
{
public:

	/*
	@fn コンストラクタ
	@brief  Sceneの生成を行う
	*/
	FinalStageScene();
	
	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~FinalStageScene()override;

	/*
	@fn　シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

	// クリアした時のシーンが遷移するまでのカウント
	// 最終ステージのみ演出が長いので別で定義
	const int FinalClearToChangeScene;
};