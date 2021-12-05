#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"

// クラスの前方宣言
class ResultSceneSoundManager;

/*
@file ResultScene.h
@brief リザルトシーンの管理と更新を行う
*/
class ResultScene :
    public BaseScene
{
public:
	/*
	@fn コンストラクタ
	@brief  Sceneの生成を行う
	*/
	ResultScene();
	
	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~ResultScene()override;

	/*
	@fn　シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

	ResultSceneSoundManager* resultSceneSoundManager;

	bool isSceneEnd;
};