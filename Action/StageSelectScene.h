#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"

// クラスの前方宣言
class StageSelectSceneSoundManager;

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

	// アナログスティックによる選択シーン変更が可能かどうか
	bool isAnalogStickSelect;
	// アナログスティックによる選択の再使用可能になるまでのカウントを数える
	int selectCount;

	// シーンが決定されたかどうか
	bool isSceneSelect;

	// 選択されているシーンステータス
	SceneState selectState;

	// stage選択画面のサウンドを管理しているクラス
	StageSelectSceneSoundManager* stageSelectSceneSoundManager;

	// デッドスペース定数
	const float InputDeadSpace;

public:

	SceneState GetSelectState() const { return selectState; }

};