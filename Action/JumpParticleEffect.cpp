#include "JumpParticleEffect.h"

JumpParticleEffect::JumpParticleEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 30, "Assets/Effect/Burst_2.png")
{
	scale = 160.0f;
	alpha = 1.0f;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
}

JumpParticleEffect::~JumpParticleEffect()
{
}

void JumpParticleEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();
	if (lifeCount >= 0)
	{
		scale -= 3.0f;
		alpha -= 0.1f;
		particleComponent->SetScale(scale);
		particleComponent->SetAlpha(alpha);
		position += velocity;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
