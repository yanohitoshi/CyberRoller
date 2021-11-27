//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitleSceneUI.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "TitleSprite.h"
#include "StartButtonSprite.h"
#include "SkyBoxObject.h"

/*
@fn コンストラクタ
@brief  objectの生成を行う
*/
TitleSceneUI::TitleSceneUI()
	: GameObject(false,UI)
{
	new TitleSprite();
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