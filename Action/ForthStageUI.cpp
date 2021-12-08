//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ForthStageUI.h"
#include "RenderingObjectManager.h"
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


/*
@fn コンストラクタ
@brief  objectの生成を行う
@param	_playerObject プレイヤークラスのポインタ
@param	_first 1つ目の収集物オブジェクトのポインタ
@param	_second 2つ目の収集物オブジェクトのポインタ
@param	_third 3つ目の収集物オブジェクトのポインタ
*/
ForthStageUI::ForthStageUI(PlayerObject* _playerObject, CollectionObject* _first, CollectionObject* _second, CollectionObject* _third)
	: GameObject(false, Tag::UI)
	, SceneTime(300)
	, FirstDrawTime(120)
	, SecondDrawTime(180)
	, ThirdDrawTime(240)
	, FirstCollectionPosition(Vector3(-150.0f, -200.0f, 0.0f))
	, SecondCollectionPosition(Vector3(0.0f, -200.0f, 0.0f))
	, ThirdCollectionPosition(Vector3(150.0f, -200.0f, 0.0f))
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

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ForthStageUI::~ForthStageUI()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ForthStageUI::UpdateGameObject(float _deltaTime)
{
	// シーンをクリアしたら
	if (playerObject->GetClearFlag())
	{
		// カウントを数える
		++clearCount;

		// ポジションが結果を出す場所に移動していなかったら
		if (!isChangePosition)
		{
			// それぞれポジションをセットして描画状態をリセット
			firstCollectionUI->SetDrawPosition(FirstCollectionPosition);
			firstCollectionUI->ResetDraw();

			secondCollectionUI->SetDrawPosition(SecondCollectionPosition);
			secondCollectionUI->ResetDraw();

			thirdCollectionUI->SetDrawPosition(ThirdCollectionPosition);
			thirdCollectionUI->ResetDraw();
			isChangePosition = true;
		}

		// それぞれ時間が来たら描画する
		if (clearCount >= FirstDrawTime)
		{
			firstCollectionUI->DrawInGame();
		}

		if (clearCount >= SecondDrawTime)
		{
			secondCollectionUI->DrawInGame();
		}

		if (clearCount >= ThirdDrawTime)
		{
			thirdCollectionUI->DrawInGame();
		}
	}
	else
	{
		// 描画する
		firstCollectionUI->DrawInGame();
		secondCollectionUI->DrawInGame();
		thirdCollectionUI->DrawInGame();
	}
}
