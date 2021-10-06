//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SecondStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "PlayerObject.h"
#include "SkyBoxObject.h"

SecondStageUI::SecondStageUI(PlayerObject* _playerObject)
	: GameObject(false, Tag::UI)
	, SceneTime(200)
{
	// カウントダウン
	new CountDownFont(SceneTime);
	// start時のカウントダウン
	new StartCountDownSprite();
	// タイムアップ時のsprite
	new TimeUpSprite();
	// コンティニュー選択時のsprite
	new ContinueSprite();
	// GameOver時のsprite
	new GameOverSprite();

	skyBox = new SkyBoxObject(false, Tag::UI);

}

SecondStageUI::~SecondStageUI()
{
}

void SecondStageUI::UpdateGameObject(float _deltaTime)
{
}
