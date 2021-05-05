#include "FierWorksEffect.h"
#include "ParticleComponent.h"
#include "CrystalEffectManager.h"

FierWorksEffect::FierWorksEffect(const Vector3& _pos, const Vector3& _velocity, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, _velocity, 210, "Assets/Effect/Particle_Soft.png")
{
	scale = 2.0f;
	alpha = 0.1f;
	inFlag = true;
	speed = 200.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);

	if (_crystalColor == CrystalColor::WHITE)
	{
		particleComponent->SetColor(Vector3(0.9f, 0.9f, 0.9f));
	}
	else if (_crystalColor == CrystalColor::RED)
	{
		particleComponent->SetColor(Vector3(1.0f, 0.5f, 0.5f));
	}
	else if (_crystalColor == CrystalColor::BLUE)
	{
		particleComponent->SetColor(Vector3(0.5f, 0.5f, 1.0f));
	}
	else if (_crystalColor == CrystalColor::GREEN)
	{
		particleComponent->SetColor(Vector3(0.5f, 1.0f, 0.5f));
	}
}

FierWorksEffect::~FierWorksEffect()
{
}

void FierWorksEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (lifeCount > 190)
	{
		if (inFlag == true)
		{
			alpha += 0.05f;
			if (alpha >= 0.9f)
			{
				inFlag = false;
			}
		}

		scale += 2.0f;

		particleComponent->SetScale(scale);
		particleComponent->SetAlpha(alpha);

		position += velocity * speed * _deltaTime;
		SetPosition(position);
	}
	else if (lifeCount <= 190)
	{
		scale += 5.0f;
		alpha -= 0.001f;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		if (speed >= 40.0f)
		{
			speed -= 1.0f;
			if (speed <= 40.0f)
			{
				speed = 40.0f;
			}
		}
		particleComponent->SetAlpha(alpha);
		particleComponent->SetScale(scale);

		position += velocity * speed * _deltaTime;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
