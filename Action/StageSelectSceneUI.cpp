#include "StageSelectSceneUI.h"
#include "StageSelectScene.h"
#include "StageSelectIconSprite.h"
#include "StageUnSelectIcon.h"
#include "StageSelectSprite.h"
#include "SkyBoxObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
@param _owner �e�N���X�ƂȂ�scene�N���X�̃|�C���^
*/
StageSelectSceneUI::StageSelectSceneUI(StageSelectScene* _owner)
	: GameObject(false, UI)
	, owner(_owner)
{

	CreatStageSelectSprite();

	skyBox = new SkyBoxObject(false, Tag::UI);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
StageSelectSceneUI::~StageSelectSceneUI()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void StageSelectSceneUI::UpdateGameObject(float _deltaTime)
{
	// �I�΂�Ă���scene�̃X�e�[�^�X���擾
	SceneState select = owner->GetSelectState();

	// �I�΂�Ă���scene���Ƃɕ`����Z�b�g
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
@brief �I������Ă����Ԃ̃A�C�R���p�}�b�v�ɃX�v���C�g�N���X��ǉ�����֐�
@param	_state �ǉ�����X�v���C�g�N���X�̃|�C���^
@param	_stateTag ���ƂȂ�^�O
*/
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

/*
@brief �I������Ă����Ԃ̃A�C�R���p�}�b�v����X�v���C�g�N���X���폜����֐�
@param	_stateTag ���ƂȂ�^�O
*/
void StageSelectSceneUI::RemoveSelectIconSpriteMap(SceneState _stateTag)
{
	delete selectIconSpriteMap[_stateTag];
}

/*
@brief �I������Ă��Ȃ���Ԃ̃A�C�R���p�}�b�v�ɃX�v���C�g�N���X��ǉ�����֐�
@param	_state �ǉ�����X�v���C�g�N���X�̃|�C���^
@param	_stateTag ���ƂȂ�^�O
*/
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

/*
@brief �I������Ă��Ȃ���Ԃ̃A�C�R���p�}�b�v����X�v���C�g�N���X���폜����֐�
@param	_stateTag ���ƂȂ�^�O
*/
void StageSelectSceneUI::RemoveUnSelectIconSpriteMap(SceneState _stateTag)
{
	delete unSelectIconMap[_stateTag];
}

/*
@brief stage�I����ʂ̃X�v���C�g�N���X�p�}�b�v�ɃX�v���C�g�N���X��ǉ�����֐�
@param	_state �ǉ�����X�v���C�g�N���X�̃|�C���^
@param	_stateTag ���ƂȂ�^�O
*/
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

/*
@brief �I������Ă��Ȃ���Ԃ̃A�C�R���p�}�b�v����X�v���C�g�N���X���폜����֐�
@param	_stateTag ���ƂȂ�^�O
*/
void StageSelectSceneUI::RemoveStageSelectSpriteMap(SceneState _stateTag)
{
	delete selectSpriteMap[_stateTag];
}

/*
@brief �S�Ă�sprite�}�b�v���N���A����
*/
void StageSelectSceneUI::ClearAllSpriteMap()
{
	// �}�b�v�̌�Еt��
	selectIconSpriteMap.clear();
	unSelectIconMap.clear();
	selectSpriteMap.clear();
}

/*
@brief �S�Ă�sprite�}�b�v�𐶐�����
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
@brief ��1stage���I�΂�Ă��鎞�̕`���Ԃ��Z�b�g����
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
@brief ��2stage���I�΂�Ă��鎞�̕`���Ԃ��Z�b�g����
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
@brief ��3stage���I�΂�Ă��鎞�̕`���Ԃ��Z�b�g����
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
@brief ��4stage���I�΂�Ă��鎞�̕`���Ԃ��Z�b�g����
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
@brief ��5stage���I�΂�Ă��鎞�̕`���Ԃ��Z�b�g����
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
