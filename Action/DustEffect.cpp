#include "DustEffect.h"

DustEffect::DustEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 45, "Assets/Effect/Particle_Soft.png", true)
	, AddScale(12.0f)
	, SubAlpha(0.02f)
	, EffectColor(Vector3(0.93f, 0.93f, 0.93f))
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
	owner = _owner;
}

DustEffect::~DustEffect()
{
}

void DustEffect::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ̃J�E���g�_�E��
	ParticleEffectBase::LifeCountDown();

	// ���C�t�J�E���g��0�ȏ�ɂ�������
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
