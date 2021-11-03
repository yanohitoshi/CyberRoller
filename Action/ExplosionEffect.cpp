#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 30, "Assets/Effect/Particle04_bokashistrong_soft.png", true)
	, AddScale(8.0f)
	, SubAlpha(0.02f)
	, EffectColor(Vector3(0.68f, 0.85f, 0.9f))
{
	// �����o�[�ϐ��̏�����
	scale = 0.0f;
	alpha = 0.0f;
	alpha = 1.0f;
	position = _pos;
	velocity = _velocity;
	speed = rand() % 50 / 10.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
}

ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ̃J�E���g�_�E��
	ParticleEffectBase::LifeCountDown();

	// ���C�t�J�E���g��0�ȏ�ɂȂ�����
	if (lifeCount >= 0)
	{
		// �萔�𑫂��Ċg��
		scale += AddScale;
		// �萔�������ē���
		alpha -= SubAlpha;

		// scale�l���Z�b�g
		particleComponent->SetScale(scale);
		// alpha�l���Z�b�g
		particleComponent->SetAlpha(alpha);

		// �|�W�V�����ɑ��x��ǉ�
		position += velocity * speed;
		// �|�W�V�������X�V
		SetPosition(position);
	}

	// ���C�t�J�E���g��0�ȉ��ɂȂ�����
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}
