//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
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
#include "SkyBoxObject.h"

/*
@fn コンストラクタ
@brief  objectの生成を行う
@param	_playerObject プレイヤークラスのポインタ
*/
ThirdStageUI::ThirdStageUI(PlayerObject* _playerObject)
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
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ThirdStageUI::~ThirdStageUI()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ThirdStageUI::UpdateGameObject(float _deltaTime)
{
}