#include "ExplosionRipplesEffect.h"

ExplosionRipplesEffect::ExplosionRipplesEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 30, "Assets/Effect/Shockwave.png", false)
	, AddScale(8.0f)
	, SubAlpha(0.02f)
	, EffectColor(Vector3(0.68f, 0.85f, 0.9f))
	, RandValue(361)
{
	// �����o�[�ϐ��̏�����
	scale = 0.0f;
	alpha = 0.0f;
	alpha = 1.0f;
	position = _pos;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);

	RotateEffect();
}

ExplosionRipplesEffect::~ExplosionRipplesEffect()
{
}

void ExplosionRipplesEffect::UpdateGameObject(float _deltaTime)
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

		//// �|�W�V�����ɑ��x��ǉ�
		//position += velocity * speed;
		//// �|�W�V�������X�V
		//SetPosition(position);
	}

	// ���C�t�J�E���g��0�ȉ��ɂȂ�����
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}


/*
@fn ��]�����֐�
@brief	�G�t�F�N�g�̉�]���s��
*/
void ExplosionRipplesEffect::RotateEffect()
{
	angle = (float)(rand() % RandValue + 90);
	Rotation(this, angle, Vector3::UnitX);
	angle = (float)(rand() % RandValue + 90);
	Rotation(this, angle, Vector3::UnitY);
	angle = (float)(rand() % RandValue + 90);
	Rotation(this, angle, Vector3::UnitZ);
}