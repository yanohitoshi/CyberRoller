//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MoveTutorialParticl.h"

/*
@brief	コンストラクタ
@param	ポジション
*/
MoveTutorialParticl::MoveTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/Tutorial/Move/move_tutorial.png", 1.0f)
	, InitScale(512.0f)
{
	// ParticleComponent初期化
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(true);
	particleComponent->SetScale(InitScale);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
MoveTutorialParticl::~MoveTutorialParticl()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void MoveTutorialParticl::UpdateGameObject(float _deltaTime)
{
}