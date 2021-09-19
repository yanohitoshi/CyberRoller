#include "JumpAttackTutorialParticl.h"

JumpAttackTutorialParticl::JumpAttackTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/jump_attack_tutorial.png")
	, InitScale(512.0f)
{
	// ParticleComponent‰Šú‰»
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(true);
	particleComponent->SetScale(InitScale);
}

JumpAttackTutorialParticl::~JumpAttackTutorialParticl()
{
}

void JumpAttackTutorialParticl::UpdateGameObject(float _deltaTime)
{
}