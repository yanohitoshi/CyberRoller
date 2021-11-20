#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"

/*
@file ThirdStageScene.h
@brief 第三ステージの初期化と生成、次のシーンへのシーン遷移を行う
*/
class SecondStageScene :
    public BaseScene
{
public:

	/*
	@fn コンストラクタ
	@brief  Sceneの生成を行う
	*/
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
	SceneState Update(const InputState& _inputState)override;

private:

};

