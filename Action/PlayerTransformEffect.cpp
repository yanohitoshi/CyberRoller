#include "PlayerTransformEffect.h"

PlayerTransformEffect::PlayerTransformEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 10, "Assets/Effect/Particle7.png")
	, AddScale(1.0f)
	, SubAlpha(0.05f)
{
	// �����o�[�ϐ��̏�����
	scale = 32.0f;
	alpha = 1.0f;
	speed = 50.0f;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(1.0f, 0.1f, 0.0f));
}

PlayerTransformEffect::~PlayerTransformEffect()
{
}

void PlayerTransformEffect::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ̃J�E���g�_�E��
	ParticleEffectBase::LifeCountDown();

	// ���C�t�J�E���g��0�ȏ�
	if (lifeCount >= 0)
	{
		//// �萔�𑫂��Ċg��
		//scale += AddScale;
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

	// ���C�t�J�E���g��0�ȉ�
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}