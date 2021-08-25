//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "JumpTutorialParticl.h"

JumpTutorialParticl::JumpTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/jump_tutorial.png")
	, InitScale(512.0f)
{
	// ParticleComponent初期化
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(true);
	particleComponent->SetScale(InitScale);
}

JumpTutorialParticl::~JumpTutorialParticl()
{
}

void JumpTutorialParticl::UpdateGameObject(float _deltaTime)
{

}
