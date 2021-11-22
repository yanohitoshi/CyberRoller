//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionEffect.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�ړ����x
*/
ExplosionEffect::ExplosionEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 20, "Assets/Effect/Bomb/Explosion.png", true)
	, AddScale(64.0f)
	, SubAlpha(0.01f)
	, EffectColor(Color::LightBlue)
	, InitAlpha(1.0f)
	, InitScale(32.0f)
{
	// �����o�[�ϐ��̏�����
	scale = InitScale;
	alpha = InitAlpha;
	position = _pos;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ExplosionEffect::~ExplosionEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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

	}

	// ���C�t�J�E���g��0�ȉ��ɂȂ�����
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}
