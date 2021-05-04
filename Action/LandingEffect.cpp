#include "LandingEffect.h"

LandingEffect::LandingEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 30, "Assets/Effect/Particle7.png")
{
	scale = 32.0f;
	alpha = 1.0f;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
}

LandingEffect::~LandingEffect()
{
}

void LandingEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();
	if (lifeCount >= 0)
	{
		scale += 0.8f;
		alpha -= 0.05f;
		particleComponent->SetScale(scale);
		particleComponent->SetAlpha(alpha);
		position += velocity * 2.0f;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
