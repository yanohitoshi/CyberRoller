#include "EnemyExplosionEffect.h"

EnemyExplosionEffect::EnemyExplosionEffect(GameObject* _owner, const Vector3& _pos,const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 30, "Assets/Effect/glow.png", true)
	, AddScale(12.0f)
	, SubAlpha(0.02f)
	, EffectColor(Vector3(0.65f, 0.65f, 1.0f))
	, EnableTime(60)
{
	// �����o�[�ϐ��̏�����
	scale = 16.0f;
	alpha = 0.0f;
	position = _pos;
	velocity = _velocity;
	speed = 3.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;
	enableCount = 0;
	isEnabled = false;
}

EnemyExplosionEffect::~EnemyExplosionEffect()
{
}

void EnemyExplosionEffect::UpdateGameObject(float _deltaTime)
{
	++enableCount;

	if (enableCount >= EnableTime)
	{
		if (!isEnabled)
		{
			isEnabled = true;
			alpha = 1.0f;
			particleComponent->SetAlpha(alpha);
		}

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
}

