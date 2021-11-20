#include "StageSelectIconSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

StageSelectIconSprite::StageSelectIconSprite(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	SetScale(Vector3(0.25f, 0.25f, 0.25f));

	myState = _state;
	_owner->AddSelectIconSpriteMap(this, myState);


	switch (myState)
	{
	case FIRST_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(Vector3(-800.0f, -300.0f, 0.0f));
		break;
	case SECOND_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(Vector3(-400.0f, -300.0f, 0.0f));
		break;
	case THIRD_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(Vector3(0.0f, -300.0f, 0.0f));
		break;
	case FOURTH_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(Vector3(400.0f, -300.0f, 0.0f));
		break;
	case FINAL_STAGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(Vector3(800.0f, -300.0f, 0.0f));
		break;
	}

	isVisible = true;

	// spriteComponen��new����
	sprite = new SpriteComponent(this, false);
	// �w�i�e�N�X�`�������[�h
	Texture* tex = RENDERER->GetTexture(_spriteFileName);
	// �w�i�e�N�X�`�����Z�b�g
	sprite->SetTexture(tex);
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(isVisible);
	// alpha�l���Z�b�g
	sprite->SetAlpha(1.0f);
}

StageSelectIconSprite::~StageSelectIconSprite()
{
}

void StageSelectIconSprite::UpdateGameObject(float _deltaTime)
{
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(isVisible);
}
