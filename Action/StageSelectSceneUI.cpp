#include "StageSelectSceneUI.h"
#include "StageSelectIconSprite.h"
#include "StageUnSelectIcon.h"
#include "StageSelectSprite.h"

StageSelectSceneUI::StageSelectSceneUI()
	: GameObject(false, UI)
{
	//new StageSelectIconSprite("Assets/sprite/icon/finalStage_icon_select.png");
	//new StageUnSelectIcon("Assets/sprite/icon/finalStage_icon.png");
	//new StageSelectSprite("Assets/sprite/stageSelect/finalStageSprite.png");
}

StageSelectSceneUI::~StageSelectSceneUI()
{
}

void StageSelectSceneUI::UpdateGameObject(float _deltaTime)
{
}

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

void StageSelectSceneUI::RemoveSelectIconSpriteMap(SceneState _stateTag)
{
	delete selectIconSpriteMap[_stateTag];
}

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

void StageSelectSceneUI::RemoveUnSelectIconSpriteMap(SceneState _stateTag)
{
	delete unSelectIconMap[_stateTag];
}

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

void StageSelectSceneUI::RemoveStageSelectSpriteMap(SceneState _stateTag)
{
	delete selectSpriteMap[_stateTag];
}

void StageSelectSceneUI::ClearAllSpriteMap()
{
	selectIconSpriteMap.clear();
	unSelectIconMap.clear();
	selectSpriteMap.clear();
}
