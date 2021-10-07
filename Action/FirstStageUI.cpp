//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FirstStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "JumpAttackTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "SkyBoxObject.h"

FirstStageUI::FirstStageUI()
	: GameObject(false, Tag::UI)
	, JumpTutorialPosition(Vector3(3700.0f, -1000.0f, 700.0f))
	, MoveTutorialPosition(Vector3(3700.0f, -2200.0f, 700.0f))
	, JumpAttackTutorialPosition(Vector3(9200.0f, -2000.0f, 1200.0f))
{
	// ジャンプチュートリアル用Particl
	new JumpTutorialParticl(JumpTutorialPosition);
	// 移動チュートリアル用Particl
	new MoveTutorialParticl(MoveTutorialPosition);
	// ジャンプ攻撃チュートリアル用Particl
	new JumpAttackTutorialParticl(JumpAttackTutorialPosition);

	// プレイヤーを動かすことができるようにするためのフラグ
	CountDownFont::SetCountStartFlag(true);
	// スカイボックスを生成
	skyBox = new SkyBoxObject(false, Tag::UI);
}

FirstStageUI::~FirstStageUI()
{
	// プレイヤーを動かすことができるようにするためのフラグの初期化
	CountDownFont::SetCountStartFlag(false);
}

void FirstStageUI::UpdateGameObject(float _deltaTime)
{
}
