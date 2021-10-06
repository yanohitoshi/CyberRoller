//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ResultSceneUI.h"
#include "Renderer.h"
#include "SkyBoxObject.h"

ResultSceneUI::ResultSceneUI()
	: GameObject(false, UI)
{
	skyBox = new SkyBoxObject(false, Tag::UI);
}

ResultSceneUI::~ResultSceneUI()
{
}

void ResultSceneUI::UpdateGameObject(float _deltaTime)
{
}
