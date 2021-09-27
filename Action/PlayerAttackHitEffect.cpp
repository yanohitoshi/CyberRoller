#include "PlayerAttackHitEffect.h"
#include "PlayerAttackHitEffectRipples.h"
PlayerAttackHitEffect::PlayerAttackHitEffect(GameObject* _owner,const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 20, "Assets/Effect/Particle04_clear_hard.png", false)
	, AddScale(16.0f)
	, SubAlpha(0.01f)
{

	new PlayerAttackHitEffectRipples(_owner, _pos, _velocity);

	// �����o�[�ϐ��̏�����
	owner = _owner;
	scale = 0.0f;
	alpha = 1.0f;
	speed = 25.0f;
	position = _pos;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(1.0f, 0.8f, 0.4f));
	SetPosition(position);
	SetRotation(owner->GetRotation());
}

PlayerAttackHitEffect::~PlayerAttackHitEffect()
{
}

void PlayerAttackHitEffect::UpdateGameObject(float _deltaTime)
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

		SetRotation(owner->GetRotation());
	}

	// ���C�t�J�E���g��0�ȉ�
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}