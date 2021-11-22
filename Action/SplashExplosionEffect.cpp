//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SplashExplosionEffect.h"

SplashExplosionEffect::SplashExplosionEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 20, "Assets/Effect/Bomb/Splash.png", true)
	, AddScale(24.0f)
	, SubAlpha(0.01f)
	, EffectColor(Color::LightBlue)
	, InitAlpha(1.0f)
	, InitScale(12.0f)
	, SpeedRandValue(50)
	, SpeedCorrection(5)
{
	// �����o�[�ϐ��̏�����
	scale = InitScale;
	alpha = InitAlpha;
	position = _pos;
	velocity = _velocity;
	speed = (float)(rand() % SpeedRandValue / SpeedCorrection);
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
}

SplashExplosionEffect::~SplashExplosionEffect()
{
}

void SplashExplosionEffect::UpdateGameObject(float _deltaTime)
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
