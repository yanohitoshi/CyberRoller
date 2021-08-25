//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FirstStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"


FirstStageUI::FirstStageUI()
	: GameObject(false, Tag::UI)
	, JumpTutorialPosition(Vector3(3700.0f, -1000.0f, 700.0f))
	, MoveTutorialPosition(Vector3(3700.0f, -2200.0f, 700.0f))
{
	// ジャンプチュートリアル用Particl
	new JumpTutorialParticl(JumpTutorialPosition);
	// 移動チュートリアル用Particl
	new MoveTutorialParticl(MoveTutorialPosition);

	// プレイヤーを動かすことができるようにするためのフラグ
	CountDownFont::SetCountStartFlag(true);
}

FirstStageUI::~FirstStageUI()
{
	// プレイヤーを動かすことができるようにするためのフラグの初期化
	CountDownFont::SetCountStartFlag(false);
}

void FirstStageUI::UpdateGameObject(float _deltaTime)
{
}
