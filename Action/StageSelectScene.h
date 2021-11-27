#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"

/*
@file StageSelectScene.h
@brief ステージ選択シーンの管理と更新を行う
*/
class StageSelectScene :
    public BaseScene
{
public:

	/*
	@fn コンストラクタ
	@brief  Sceneの生成を行う
	*/
	StageSelectScene();

	/*
	@fn デストラクタ
	@brief  sceneの削除を行う
	*/
	~StageSelectScene()override;

	/*
	@fn     シーンのアップデート関数
	@brief	シーンの更新処理を行う
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

	void SelectRight();
	void SelectLeft();
	void SelectAnalogStick(float _axis);

	bool isAnalogStickSelect;
	int selectCount;

	SceneState selectState;

	const float InputDeadSpace;

public:

	SceneState GetSelectState() const { return selectState; }

};