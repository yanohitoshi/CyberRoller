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
	//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto stateMaps = selectIconSpriteMap.find(_stateTag);
	//����Ƃ�
	if (stateMaps != selectIconSpriteMap.end())
	{
		return;
	}
	else //�Ȃ��Ƃ�
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
	//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto stateMaps = unSelectIconMap.find(_stateTag);
	//����Ƃ�
	if (stateMaps != unSelectIconMap.end())
	{
		return;
	}
	else //�Ȃ��Ƃ�
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
	//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto stateMaps = selectSpriteMap.find(_stateTag);
	//����Ƃ�
	if (stateMaps != selectSpriteMap.end())
	{
		return;
	}
	else //�Ȃ��Ƃ�
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
