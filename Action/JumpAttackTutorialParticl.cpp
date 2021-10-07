//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "JumpAttackTutorialParticl.h"

/*
@brief	コンストラクタ
@param	ポジション
*/
JumpAttackTutorialParticl::JumpAttackTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/jump_attack_tutorial.png", true)
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
JumpAttackTutorialParticl::~JumpAttackTutorialParticl()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void JumpAttackTutorialParticl::UpdateGameObject(float _deltaTime)
{
}