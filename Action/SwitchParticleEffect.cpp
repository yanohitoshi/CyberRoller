#include "SwitchParticleEffect.h"

SwitchParticleEffect::SwitchParticleEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 20, "Assets/Effect/Star.png")
{
	scale = 96.0f;
	alpha = 1.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 0.0f));
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
	speed = 20.0f;
}

SwitchParticleEffect::~SwitchParticleEffect()
{
}

void SwitchParticleEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();		
	if (lifeCount >= 0)
	{
		scale += 1.0;
		alpha -= 0.02f;
		particleComponent->SetScale(scale);
		particleComponent->SetAlpha(alpha);
		velocity.Normalize();
		position += velocity * speed;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
