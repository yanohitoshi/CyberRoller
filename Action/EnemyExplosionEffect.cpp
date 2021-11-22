//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyExplosionEffect.h"

/*
@fn �R���X�g���N�^
@param	�e�ƂȂ�N���X�̃|�C���^
@param	�|�W�V����
@param	�ړ����x
*/
EnemyExplosionEffect::EnemyExplosionEffect(GameObject* _owner, const Vector3& _pos,const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 30, "Assets/Effect/Enemy/Explosion.png", true)
	, AddScale(8.0f)
	, SubAlpha(0.02f)
	, EffectColor(Vector3(0.65f, 0.65f, 1.0f))
	, SpeedRandValue(50)
	, SpeedCorrection(10.0f)
{
	// �����o�[�ϐ��̏�����
	scale = 0.0f;
	alpha = 1.0f;
	position = _pos;
	velocity = _velocity;
	speed = (float)(rand() % SpeedRandValue / SpeedCorrection);
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
EnemyExplosionEffect::~EnemyExplosionEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void EnemyExplosionEffect::UpdateGameObject(float _deltaTime)
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