//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameOverSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"

/*
@fn コンストラクタ
@brief  objectの生成を行う
*/
GameOverSceneUI::GameOverSceneUI()
	: GameObject(false, UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponentをnew
	sprite = new SpriteComponent(this, false);
	// ゲームオーバーのtextureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/GameOver.png");
	// textureをComponentにセット
	sprite->SetTexture(tex);
	// alpha値を初期化
	sprite->SetAlpha(1.0f);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
GameOverSceneUI::~GameOverSceneUI()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void GameOverSceneUI::UpdateGameObject(float _deltaTime)
{
}