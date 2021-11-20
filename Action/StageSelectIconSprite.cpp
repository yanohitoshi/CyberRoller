#include "StageSelectIconSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

StageSelectIconSprite::StageSelectIconSprite(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	SetScale(Vector3(0.25f, 0.25f, 0.25f));

	myState = _state;
	_owner->AddSelectIconSpriteMap(this, myState);


	switch (myState)
	{
	case FIRST_SATGE_SCENE:
		// ポジションをセット
		SetPosition(Vector3(-800.0f, -300.0f, 0.0f));
		break;
	case SECOND_SATGE_SCENE:
		// ポジションをセット
		SetPosition(Vector3(-400.0f, -300.0f, 0.0f));
		break;
	case THIRD_SATGE_SCENE:
		// ポジションをセット
		SetPosition(Vector3(0.0f, -300.0f, 0.0f));
		break;
	case FOURTH_SATGE_SCENE:
		// ポジションをセット
		SetPosition(Vector3(400.0f, -300.0f, 0.0f));
		break;
	case FINAL_STAGE_SCENE:
		// ポジションをセット
		SetPosition(Vector3(800.0f, -300.0f, 0.0f));
		break;
	}

	isVisible = true;

	// spriteComponenをnewする
	sprite = new SpriteComponent(this, false);
	// 背景テクスチャをロード
	Texture* tex = RENDERER->GetTexture(_spriteFileName);
	// 背景テクスチャをセット
	sprite->SetTexture(tex);
	// 映す映さないをセット
	sprite->SetVisible(isVisible);
	// alpha値をセット
	sprite->SetAlpha(1.0f);
}

StageSelectIconSprite::~StageSelectIconSprite()
{
}

void StageSelectIconSprite::UpdateGameObject(float _deltaTime)
{
	// 映す映さないをセット
	sprite->SetVisible(isVisible);
}
