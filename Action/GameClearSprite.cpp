//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameClearSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "PlayerObject.h"

/*
@brief	コンストラクタ
@param	_playerObject プレイヤーオブジェクトのポインタ
*/
GameClearSprite::GameClearSprite(PlayerObject* _playerObject)
	:GameObject(false, Tag::UI)
	, DrawCount(120)
{

	playerObject = _playerObject;

	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// textureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/information/gameclear.png");
	// SpriteComponent初期化
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	SetScale(1.5f);
	// メンバー変数初期化
	frameCount = 0;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
GameClearSprite::~GameClearSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void GameClearSprite::UpdateGameObject(float _deltaTime)
{
	// クリア状態になったら
	if (playerObject->GetClearFlag() == true)
	{
		// フレームカウントを数える
		++frameCount;
		// 120カウント超えたら描画する
		if (frameCount >= DrawCount)
		{
			sprite->SetVisible(true);
		}
	}
}