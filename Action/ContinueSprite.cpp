//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ContinueSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"
#include "TimeUpSprite.h"

// 静的メンバー初期化
bool ContinueSprite::drawFlag = true;
bool ContinueSprite::continueFlag = true;

/*
@brief	コンストラクタ
*/
ContinueSprite::ContinueSprite()
	:GameObject(false, Tag::UI)
	, DrawCount(60)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// textureをロード
	Texture* tex = RENDERING_OBJECT_MANAGER->CreateTexture("Assets/sprite/information/continue.png");
	// SpriteComponentを初期化
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	frameCount = 0;
	visibleFlag = true;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ContinueSprite::~ContinueSprite()
{
	// 静的メンバー初期化
	drawFlag = true;
	continueFlag = true;
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ContinueSprite::UpdateGameObject(float _deltaTime)
{
	// タイムアップ状態中タイムアップ画像の描画が終わったら描画する
	if (TimeUpSprite::GetDrawFlag() == false && visibleFlag == true)
	{
		sprite->SetVisible(true);
		++frameCount;
	}
}

/*
@brief	入力
@param	入力情報
*/
void ContinueSprite::GameObjectInput(const InputState& _keyState)
{
	// タイムアップ画像の描画が終わってコンテニュー画像描画開始から一定時間たっていたら
	if (TimeUpSprite::GetDrawFlag() == false && frameCount >= DrawCount)
	{
		CheckKeyProcess(_keyState);
	}
}

/*
@brief	入力情報を元に描画を切り替える
@param	入力情報
*/
void ContinueSprite::CheckKeyProcess(const InputState& _keyState)
{
	// Aボタンが押されたら
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
	{
		// 描画を切ってコンテニューフラグをtrueに
		sprite->SetVisible(false);
		visibleFlag = false;
		drawFlag = false;
		continueFlag = true;
	}
	else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed) // Bボタンが押されたら
	{
		// 描画を切ってコンテニューフラグをfalseに
		sprite->SetVisible(false);
		visibleFlag = false;
		drawFlag = false;
		continueFlag = false;
	}
}