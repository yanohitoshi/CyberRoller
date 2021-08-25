//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MoveTutorialParticl.h"

MoveTutorialParticl::MoveTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/move_tutorial.png", 1.0f)
	, InitScale(512.0f)
{
	// ParticleComponent初期化
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(true);
	particleComponent->SetScale(InitScale);
}

MoveTutorialParticl::~MoveTutorialParticl()
{
}

void MoveTutorialParticl::UpdateGameObject(float _deltaTime)
{

}
