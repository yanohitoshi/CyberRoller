//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ResultSceneUI.h"
#include "Renderer.h"
#include "SkyBoxObject.h"

ResultSceneUI::ResultSceneUI()
	: GameObject(false, UI)
{
	// スカイボックスを生成
	skyBox = new SkyBoxObject(false, Tag::UI);
}

ResultSceneUI::~ResultSceneUI()
{
}

void ResultSceneUI::UpdateGameObject(float _deltaTime)
{
}
