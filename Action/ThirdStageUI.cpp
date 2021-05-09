#include "ThirdStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "PlayerObject.h"
// 静的メンバー初期化
bool ThirdStageUI::timeOverFlag = false;
bool ThirdStageUI::countStartFlag = false;

ThirdStageUI::ThirdStageUI(PlayerObject* _playerObject)
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

}

ThirdStageUI::~ThirdStageUI()
{
	// 静的メンバー初期化
	timeOverFlag = false;
	countStartFlag = false;
}

void ThirdStageUI::UpdateGameObject(float _deltaTime)
{
}
