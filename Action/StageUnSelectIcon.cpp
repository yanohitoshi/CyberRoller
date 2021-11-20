#include "StageUnSelectIcon.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

StageUnSelectIcon::StageUnSelectIcon(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(300.0f, -300.0f, 0.0f));
	SetScale(Vector3(0.2f, 0.2f, 0.2f));

	myState = _state;
	_owner->AddUnSelectIconSpriteMap(this, myState);

	isVisible = true;

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

StageUnSelectIcon::~StageUnSelectIcon()
{
}

void StageUnSelectIcon::UpdateGameObject(float _deltaTime)
{
	// 映す映さないをセット
	sprite->SetVisible(isVisible);
}
