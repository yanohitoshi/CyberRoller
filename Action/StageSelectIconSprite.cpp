//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "StageSelectIconSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

/*
@fn コンストラクタ
@parma 親クラスのポインタ
@parma シーンのステータス
@parma 描画する画像のファイルネーム
*/
StageSelectIconSprite::StageSelectIconSprite(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
	, FirstStagePosition(Vector3(-800.0f, -300.0f, 0.0f))
	, SecondStagePosition(Vector3(-400.0f, -300.0f, 0.0f))
	, ThirdStagePosition(Vector3(0.0f, -300.0f, 0.0f))
	, FourthStagePosition(Vector3(400.0f, -300.0f, 0.0f))
	, FinalStagePosition(Vector3(800.0f, -300.0f, 0.0f))
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	SetScale(Vector3(0.25f, 0.25f, 0.25f));

	myState = _state;
	_owner->AddSelectIconSpriteMap(this, myState);


	switch (myState)
	{
	case FIRST_SATGE_SCENE:
		// ポジションをセット
		SetPosition(FirstStagePosition);
		break;
	case SECOND_SATGE_SCENE:
		// ポジションをセット
		SetPosition(SecondStagePosition);
		break;
	case THIRD_SATGE_SCENE:
		// ポジションをセット
		SetPosition(ThirdStagePosition);
		break;
	case FOURTH_SATGE_SCENE:
		// ポジションをセット
		SetPosition(FourthStagePosition);
		break;
	case FINAL_STAGE_SCENE:
		// ポジションをセット
		SetPosition(FinalStagePosition);
		break;
	}

	isVisible = true;

	// spriteComponenをnewする
	sprite = new SpriteComponent(this, false);
	// 背景テクスチャをロード
	Texture* tex = RENDERING_OBJECT_MANAGER->CreateTexture(_spriteFileName);
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
StageSelectIconSprite::~StageSelectIconSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void StageSelectIconSprite::UpdateGameObject(float _deltaTime)
{
	// 映す映さないをセット
	sprite->SetVisible(isVisible);
}
