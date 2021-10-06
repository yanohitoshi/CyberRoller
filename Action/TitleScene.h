#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"
#include "GameObject.h"

/*
@file TitleScene.h
@brief タイトルシーンの初期化と生成、次のシーンへのシーン遷移を行う
*/
class TitleScene : public BaseScene
{
public:

	/*
	@fn コンストラクタ
	@brief  Sceneの生成を行う
	*/
	TitleScene();

	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~TitleScene()override;

	/*
	@fn     シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

