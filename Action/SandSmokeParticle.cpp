#include "SandSmokeParticle.h"

SandSmokeParticle::SandSmokeParticle(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 25, "Assets/Effect/Particle_Soft.png")
{
	scale = 16.0f;
	alpha = 1.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
}

SandSmokeParticle::~SandSmokeParticle()
{
}

void SandSmokeParticle::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();
	
	if (lifeCount >= 0)
	{
		scale += 5.0f;
		alpha -= 0.05f;
		particleComponent->SetScale(scale);
		particleComponent->SetAlpha(alpha);
		position += velocity * _deltaTime;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
