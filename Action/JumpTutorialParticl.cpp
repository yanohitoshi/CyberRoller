#include "JumpTutorialParticl.h"

JumpTutorialParticl::JumpTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/jump_tutorial.png")
	, InitScale(512.0f)
{
	// ParticleComponent‰Šú‰»
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
