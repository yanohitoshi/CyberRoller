//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ResultSceneUI.h"
#include "Renderer.h"
#include "ThankYouSprite.h"
#include "SkyBoxObject.h"

ResultSceneUI::ResultSceneUI()
	: GameObject(false, UI)
{
	//// �N���A����spriteUI
	//new ThankYouSprite();
	skyBox = new SkyBoxObject(false, Tag::UI);
}

ResultSceneUI::~ResultSceneUI()
{
}

void ResultSceneUI::UpdateGameObject(float _deltaTime)
{
}
