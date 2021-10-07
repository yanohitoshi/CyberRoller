//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ResultSceneUI.h"
#include "Renderer.h"
#include "SkyBoxObject.h"

/*
@fn コンストラクタ
@brief  objectの生成を行う
*/
ResultSceneUI::ResultSceneUI()
	: GameObject(false, UI)
{
	// スカイボックスを生成
	skyBox = new SkyBoxObject(false, Tag::UI);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ResultSceneUI::~ResultSceneUI()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ResultSceneUI::UpdateGameObject(float _deltaTime)
{
}