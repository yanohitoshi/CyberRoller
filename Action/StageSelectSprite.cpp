#include "StageSelectSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

/*
@fn コンストラクタ
*/
StageSelectSprite::StageSelectSprite(StageSelectSceneUI* _owner, SceneState _state,Vector3& _pos,const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	SetScale(Vector3(1.0f, 1.0f, 1.0f));
	SetPosition(_pos);

	myState = _state;
	_owner->AddStageSelectSpriteMap(this, myState);

	// spriteComponenをnewする
	sprite = new SpriteComponent(this, false);
	// 背景テクスチャをロード
	Texture* tex = RENDERER->GetTexture(_spriteFileName);
	// 背景テクスチャをセット
	sprite->SetTexture(tex);
	// 映す映さないをセット
	sprite->SetVisible(true);
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
}