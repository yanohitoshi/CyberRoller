#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"

/*
@file FirstStageScene.h
@brief チュートリアルシーン管理と更新を行う
*/
class TutorialStageScene : public BaseScene
{
public:
	/*
	@fn コンストラクタ
	@brief  Sceneの生成を行う
	*/
	TutorialStageScene();
	
	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~TutorialStageScene()override;

	/*
	@fn　シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

};