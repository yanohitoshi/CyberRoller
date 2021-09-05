//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ResultSceneUI.h"
#include "Renderer.h"
#include "ThankYouSprite.h"
#include "SkyBoxObject.h"

ResultSceneUI::ResultSceneUI()
	: GameObject(false, UI)
{
	//// クリア時のspriteUI
	//new ThankYouSprite();
	skyBox = new SkyBoxObject(false, Tag::UI);
}

ResultSceneUI::~ResultSceneUI()
{
}

void ResultSceneUI::UpdateGameObject(float _deltaTime)
{
}
