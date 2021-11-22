//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SwitchParticleEffect.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�ړ����x
*/
SwitchParticleEffect::SwitchParticleEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 20, "Assets/Effect/Switch/Star.png",true)
	, AddScale(1.0f)
	, SubAlpha(0.02f)
	, InitAlpha(1.0f)
	, InitScale(96.0f)
	, MoveSpeed(20.0f)
{
	// �����o�[�ϐ��̏�����
	scale = InitScale;
	alpha = InitAlpha;
	speed = MoveSpeed;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 0.0f));
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
SwitchParticleEffect::~SwitchParticleEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void SwitchParticleEffect::UpdateGameObject(float _deltaTime)
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
		// ���x�𐳋K��
		velocity.Normalize();
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