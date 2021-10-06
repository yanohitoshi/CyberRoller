//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FinalStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "GameClearSprite.h"
#include "PlayerObject.h"
#include "SkyBoxObject.h"


FinalStageUI::FinalStageUI(PlayerObject* _playerObject)
	: GameObject(false, Tag::UI)
	, SceneTime(500)
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
	// GameClear時のsprite
	new GameClearSprite(_playerObject);

	skyBox = new SkyBoxObject(false, Tag::UI);
}

FinalStageUI::~FinalStageUI()
{
}

void FinalStageUI::UpdateGameObject(float _deltaTime)
{
}
