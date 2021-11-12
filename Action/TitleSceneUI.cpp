//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitleSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StartButtonSprite.h"
#include "SkyBoxObject.h"

/*
@fn コンストラクタ
@brief  objectの生成を行う
*/
TitleSceneUI::TitleSceneUI()
	: GameObject(false,UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 300.0f, 0.0f));
	SetScale(Vector3(0.2f, 0.2f, 0.2f));
	// spriteComponentをnewする
	sprite = new SpriteComponent(this, false);
	// タイトルのtextureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/Title_test.png");
	// textureをComponentにセット
	sprite->SetTexture(tex);
	// alpha値を初期化
	sprite->SetAlpha(1.0f);
	new StartButtonSprite();
	// スカイボックスを生成
	skyBox = new SkyBoxObject(false, Tag::UI);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TitleSceneUI::~TitleSceneUI()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TitleSceneUI::UpdateGameObject(float _deltaTime)
{
}