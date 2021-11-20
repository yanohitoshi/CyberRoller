#include "StageSelectSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

/*
@fn コンストラクタ
*/
StageSelectSprite::StageSelectSprite(StageSelectSceneUI* _owner, SceneState _state,const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	SetScale(Vector3(1.0f, 1.0f, 1.0f));

	myState = _state;
	_owner->AddStageSelectSpriteMap(this, myState);
	isVisible = true;
	//switch (myState)
	//{
	//case FIRST_SATGE_SCENE:
	//	// ポジションをセット
	//	SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	//	break;
	//case SECOND_SATGE_SCENE:
	//	// ポジションをセット
	//	SetPosition(Vector3(1500.0f, 100.0f, 0.0f));
	//	break;
	//case THIRD_SATGE_SCENE:
	//	// ポジションをセット
	//	SetPosition(Vector3(2500.0f, 100.0f, 0.0f));
	//	break;
	//case FOURTH_SATGE_SCENE:
	//	// ポジションをセット
	//	SetPosition(Vector3(3500.0f, 100.0f, 0.0f));
	//	break;
	//case FINAL_STAGE_SCENE:
	//	// ポジションをセット
	//	SetPosition(Vector3(4500.0f, 100.0f, 0.0f));
	//	break;
	//}

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

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
StageSelectSprite::~StageSelectSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void StageSelectSprite::UpdateGameObject(float _deltaTime)
{
	// 映す映さないをセット
	sprite->SetVisible(isVisible);
}

void StageSelectSprite::MoveLeft()
{
}

void StageSelectSprite::MoveRight()
{
}
