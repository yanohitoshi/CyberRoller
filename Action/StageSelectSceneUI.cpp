#include "StageSelectSceneUI.h"
#include "StageSelectScene.h"
#include "StageSelectIconSprite.h"
#include "StageUnSelectIcon.h"
#include "StageSelectSprite.h"
#include "SkyBoxObject.h"

/*
@fn コンストラクタ
@brief  objectの生成を行う
@param _owner 親クラスとなるsceneクラスのポインタ
*/
StageSelectSceneUI::StageSelectSceneUI(StageSelectScene* _owner)
	: GameObject(false, UI)
	, owner(_owner)
{

	CreatStageSelectSprite();

	skyBox = new SkyBoxObject(false, Tag::UI);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
StageSelectSceneUI::~StageSelectSceneUI()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void StageSelectSceneUI::UpdateGameObject(float _deltaTime)
{
	// 選ばれているsceneのステータスを取得
	SceneState select = owner->GetSelectState();

	// 選ばれているsceneごとに描画をセット
	switch (select)
	{
	case FIRST_SATGE_SCENE:
		SetFirstStageSprite();
		break;

	case SECOND_SATGE_SCENE:
		SetSecondStageSprite();
		break;

	case THIRD_SATGE_SCENE:
		SetThirdStageSprite();
		break;

	case FOURTH_SATGE_SCENE:
		SetFourthStageSprite();
		break;

	case FINAL_STAGE_SCENE:
		SetFinalStageSprite();
		break;
	}

}

/*
@brief 選択されている状態のアイコン用マップにスプライトクラスを追加する関数
@param	_state 追加するスプライトクラスのポインタ
@param	_stateTag 鍵となるタグ
*/
void StageSelectSceneUI::AddSelectIconSpriteMap(StageSelectIconSprite* _sprite, SceneState _stateTag)
{
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto stateMaps = selectIconSpriteMap.find(_stateTag);
	//あるとき
	if (stateMaps != selectIconSpriteMap.end())
	{
		return;
	}
	else //ないとき
	{
		selectIconSpriteMap[_stateTag] = _sprite;
	}
}

/*
@brief 選択されている状態のアイコン用マップからスプライトクラスを削除する関数
@param	_stateTag 鍵となるタグ
*/
void StageSelectSceneUI::RemoveSelectIconSpriteMap(SceneState _stateTag)
{
	delete selectIconSpriteMap[_stateTag];
}

/*
@brief 選択されていない状態のアイコン用マップにスプライトクラスを追加する関数
@param	_state 追加するスプライトクラスのポインタ
@param	_stateTag 鍵となるタグ
*/
void StageSelectSceneUI::AddUnSelectIconSpriteMap(StageUnSelectIcon* _sprite, SceneState _stateTag)
{
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto stateMaps = unSelectIconMap.find(_stateTag);
	//あるとき
	if (stateMaps != unSelectIconMap.end())
	{
		return;
	}
	else //ないとき
	{
		unSelectIconMap[_stateTag] = _sprite;
	}
}

/*
@brief 選択されていない状態のアイコン用マップからスプライトクラスを削除する関数
@param	_stateTag 鍵となるタグ
*/
void StageSelectSceneUI::RemoveUnSelectIconSpriteMap(SceneState _stateTag)
{
	delete unSelectIconMap[_stateTag];
}

/*
@brief stage選択画面のスプライトクラス用マップにスプライトクラスを追加する関数
@param	_state 追加するスプライトクラスのポインタ
@param	_stateTag 鍵となるタグ
*/
void StageSelectSceneUI::AddStageSelectSpriteMap(StageSelectSprite* _sprite, SceneState _stateTag)
{
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto stateMaps = selectSpriteMap.find(_stateTag);
	//あるとき
	if (stateMaps != selectSpriteMap.end())
	{
		return;
	}
	else //ないとき
	{
		selectSpriteMap[_stateTag] = _sprite;
	}
}

/*
@brief 選択されていない状態のアイコン用マップからスプライトクラスを削除する関数
@param	_stateTag 鍵となるタグ
*/
void StageSelectSceneUI::RemoveStageSelectSpriteMap(SceneState _stateTag)
{
	delete selectSpriteMap[_stateTag];
}

/*
@brief 全てのspriteマップをクリアする
*/
void StageSelectSceneUI::ClearAllSpriteMap()
{
	// マップの後片付け
	selectIconSpriteMap.clear();
	unSelectIconMap.clear();
	selectSpriteMap.clear();
}

/*
@brief 全てのspriteマップを生成する
*/
void StageSelectSceneUI::CreatStageSelectSprite()
{
	new StageSelectIconSprite(this, SceneState::FIRST_SATGE_SCENE, "Assets/sprite/icon/firstStage_icon_select.png");
	new StageSelectIconSprite(this, SceneState::SECOND_SATGE_SCENE, "Assets/sprite/icon/secondStage_icon_select.png");
	new StageSelectIconSprite(this, SceneState::THIRD_SATGE_SCENE, "Assets/sprite/icon/thirdStage_icon_select.png");
	new StageSelectIconSprite(this, SceneState::FOURTH_SATGE_SCENE, "Assets/sprite/icon/forthStage_icon_select.png");
	new StageSelectIconSprite(this, SceneState::FINAL_STAGE_SCENE, "Assets/sprite/icon/finalStage_icon_select.png");

	new StageUnSelectIcon(this, SceneState::FIRST_SATGE_SCENE, "Assets/sprite/icon/firstStage_icon.png");
	new StageUnSelectIcon(this, SceneState::SECOND_SATGE_SCENE, "Assets/sprite/icon/secondStage_icon.png");
	new StageUnSelectIcon(this, SceneState::THIRD_SATGE_SCENE, "Assets/sprite/icon/thirdStage_icon.png");
	new StageUnSelectIcon(this, SceneState::FOURTH_SATGE_SCENE, "Assets/sprite/icon/forthStage_icon.png");
	new StageUnSelectIcon(this, SceneState::FINAL_STAGE_SCENE, "Assets/sprite/icon/finalStage_icon.png");

	new StageSelectSprite(this, SceneState::FIRST_SATGE_SCENE, "Assets/sprite/stageSelect/FirstStageSprite.png");
	new StageSelectSprite(this, SceneState::SECOND_SATGE_SCENE, "Assets/sprite/stageSelect/SecondStageSprite.png");
	new StageSelectSprite(this, SceneState::THIRD_SATGE_SCENE, "Assets/sprite/stageSelect/ThirdStageSprite.png");
	new StageSelectSprite(this, SceneState::FOURTH_SATGE_SCENE, "Assets/sprite/stageSelect/FourthStageSprite.png");
	new StageSelectSprite(this, SceneState::FINAL_STAGE_SCENE, "Assets/sprite/stageSelect/FinalStageSprite.png");
}

/*
@brief 第1stageが選ばれている時の描画状態をセットする
*/
void StageSelectSceneUI::SetFirstStageSprite()
{
	selectIconSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(true);
	selectIconSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(false);

	selectSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(true);
	selectSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(false);

}

/*
@brief 第2stageが選ばれている時の描画状態をセットする
*/
void StageSelectSceneUI::SetSecondStageSprite()
{
	selectIconSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(true);
	selectIconSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(false);

	selectSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(true);
	selectSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(false);
}

/*
@brief 第3stageが選ばれている時の描画状態をセットする
*/
void StageSelectSceneUI::SetThirdStageSprite()
{
	selectIconSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(true);
	selectIconSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(false);

	selectSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(true);
	selectSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(false);
}

/*
@brief 第4stageが選ばれている時の描画状態をセットする
*/
void StageSelectSceneUI::SetFourthStageSprite()
{
	selectIconSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(true);
	selectIconSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(false);

	selectSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(true);
	selectSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(false);
}

/*
@brief 第5stageが選ばれている時の描画状態をセットする
*/
void StageSelectSceneUI::SetFinalStageSprite()
{
	selectIconSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(true);
	selectIconSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(false);
	selectIconSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(false);

	selectSpriteMap[FINAL_STAGE_SCENE]->SetIsVisible(true);
	selectSpriteMap[FIRST_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[SECOND_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[THIRD_SATGE_SCENE]->SetIsVisible(false);
	selectSpriteMap[FOURTH_SATGE_SCENE]->SetIsVisible(false);
}
