#include "JumpAttackEffect.h"

JumpAttackEffect::JumpAttackEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 30, "Assets/Effect/Particle7.png")
	, AddScale(0.8f)
	, SubAlpha(0.05f)
{
	// �����o�[�ϐ��̏�����
	scale = 128.0f;
	alpha = 0.6f;
	speed = 2.0f;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	//particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 0.65f));
}

JumpAttackEffect::~JumpAttackEffect()
{
}

void JumpAttackEffect::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ̃J�E���g�_�E��
	ParticleEffectBase::LifeCountDown();

	// ���C�t�J�E���g��0�ȏ�
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
	}

	// ���C�t�J�E���g��0�ȉ�
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}
