//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "JumpAttackEffect.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�ړ����x
*/
JumpAttackEffect::JumpAttackEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 45, "Assets/Effect/Player/JumpAttack/Attack.png", true)
	, AddScale(1.0f)
	, SubAlpha(0.05f)
	, InitAlpha(1.0f)
	, InitScale(128.0f)
{
	// �����o�[�ϐ��̏�����
	scale = InitScale;
	alpha = InitAlpha;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(0.3f, 0.3f, 1.0f));
	// Particle�̃u�����h���[�h���Z�b�g
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
JumpAttackEffect::~JumpAttackEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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