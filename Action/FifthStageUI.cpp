#include "FifthStageUI.h"
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
#include "CollectionUI.h"
#include "CollectionObject.h"

FifthStageUI::FifthStageUI(PlayerObject* _playerObject, CollectionObject* _first, CollectionObject* _second, CollectionObject* _third)
	: GameObject(false, Tag::UI)
	, SceneTime(300)
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
	// スカイボックスを生成
	skyBox = new SkyBoxObject(false, Tag::UI);

	playerObject = _playerObject;

	firstCollectionUI = new CollectionUI(_first);
	secondCollectionUI = new CollectionUI(_second);
	thirdCollectionUI = new CollectionUI(_third);

	clearCount = 0;
	isChangePosition = false;
}

FifthStageUI::FifthStageUI(PlayerObject* _playerObject)
	: GameObject(false, Tag::UI)
	, SceneTime(300)
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
	// スカイボックスを生成
	skyBox = new SkyBoxObject(false, Tag::UI);

	playerObject = _playerObject;
}

FifthStageUI::~FifthStageUI()
{
}

void FifthStageUI::UpdateGameObject(float _deltaTime)
{
	if (playerObject->GetClearFlag())
	{
		++clearCount;

		if (!isChangePosition)
		{
			firstCollectionUI->SetDrawPosition(Vector3(-150.0f, 0.0f, 0.0f));
			firstCollectionUI->ResetDraw();

			secondCollectionUI->SetDrawPosition(Vector3(0.0f, 0.0f, 0.0f));
			secondCollectionUI->ResetDraw();

			thirdCollectionUI->SetDrawPosition(Vector3(150.0f, 0.0f, 0.0f));
			thirdCollectionUI->ResetDraw();
			isChangePosition = true;
		}

		if (clearCount >= 120)
		{
			firstCollectionUI->DrawInGame();
		}

		if (clearCount >= 180)
		{
			secondCollectionUI->DrawInGame();
		}

		if (clearCount >= 240)
		{
			thirdCollectionUI->DrawInGame();
		}
	}
	else
	{
		firstCollectionUI->DrawInGame();
		secondCollectionUI->DrawInGame();
		thirdCollectionUI->DrawInGame();
	}
}
