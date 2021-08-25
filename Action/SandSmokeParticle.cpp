//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SandSmokeParticle.h"

SandSmokeParticle::SandSmokeParticle(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 25, "Assets/Effect/Particle_Soft.png")
	, AddScale(5.0f)
	, SubAlpha(0.05f)
{
	// �����o�[�ϐ��̏�����
	scale = 16.0f;
	alpha = 1.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	// �摜�ɕt�^����F���w��
	particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
}

SandSmokeParticle::~SandSmokeParticle()
{
}

void SandSmokeParticle::UpdateGameObject(float _deltaTime)
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
		position += velocity * _deltaTime;
		// �|�W�V�������X�V
		SetPosition(position);
	}

	// ���C�t�J�E���g��0�ȉ��ɂȂ�����
	if (lifeCount < 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}
