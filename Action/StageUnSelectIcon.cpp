#include "StageUnSelectIcon.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

StageUnSelectIcon::StageUnSelectIcon(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
	, FirstStagePosition(Vector3(-800.0f, -300.0f, 0.0f))
	, SecondStagePosition(Vector3(-400.0f, -300.0f, 0.0f))
	, ThirdStagePosition(Vector3(0.0f, -300.0f, 0.0f))
	, FourthStagePosition(Vector3(400.0f, -300.0f, 0.0f))
	, FinalStagePosition(Vector3(800.0f, -300.0f, 0.0f))
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(300.0f, -300.0f, 0.0f));
	SetScale(Vector3(0.2f, 0.2f, 0.2f));

	myState = _state;
	_owner->AddUnSelectIconSpriteMap(this, myState);

	isVisible = true;

	switch (myState)
	{
	case FIRST_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(FirstStagePosition);
		break;
	case SECOND_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(SecondStagePosition);
		break;
	case THIRD_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(ThirdStagePosition);
		break;
	case FOURTH_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(FourthStagePosition);
		break;
	case FINAL_STAGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(FinalStagePosition);
		break;
	}

	// spriteComponen��new����
	sprite = new SpriteComponent(this, false);
	// �w�i�e�N�X�`�������[�h
	Texture* tex = RENDERING_OBJECT_MANAGER->GetTexture(_spriteFileName);
	// �w�i�e�N�X�`�����Z�b�g
	sprite->SetTexture(tex);
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(isVisible);
	// alpha�l���Z�b�g
	sprite->SetAlpha(1.0f);
}

StageUnSelectIcon::~StageUnSelectIcon()
{
}

void StageUnSelectIcon::UpdateGameObject(float _deltaTime)
{
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(isVisible);
}
