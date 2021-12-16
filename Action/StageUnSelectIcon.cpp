//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "StageUnSelectIcon.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"
#include "GraphicsResourceManager.h"

/*
@fn コンストラクタ
@parma 親クラスのポインタ
@parma シーンのステータス
@parma 描画する画像のファイルネーム
*/
StageUnSelectIcon::StageUnSelectIcon(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
	, FirstStagePosition(Vector3(-800.0f, -300.0f, 0.0f))
	, SecondStagePosition(Vector3(-400.0f, -300.0f, 0.0f))
	, ThirdStagePosition(Vector3(0.0f, -300.0f, 0.0f))
	, FourthStagePosition(Vector3(400.0f, -300.0f, 0.0f))
	, FinalStagePosition(Vector3(800.0f, -300.0f, 0.0f))
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

	// spriteComponenをnewする
	sprite = new SpriteComponent(this, false);
	// 背景テクスチャをロード
	Texture* tex = GRAPHICS_RESOURCE->CreateTexture(_spriteFileName);
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
StageUnSelectIcon::~StageUnSelectIcon()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void StageUnSelectIcon::UpdateGameObject(float _deltaTime)
{
	// 映す映さないをセット
	sprite->SetVisible(isVisible);
}