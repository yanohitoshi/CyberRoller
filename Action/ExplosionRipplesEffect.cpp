//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionRipplesEffect.h"

/*
@fn �R���X�g���N�^
@param	�e�ƂȂ�N���X�̃|�C���^
@param	�|�W�V����
*/
ExplosionRipplesEffect::ExplosionRipplesEffect(GameObject* _owner, const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 20, "Assets/Effect/Bomb/Ripple.png", false)
	, AddScale(96.0f)
	, SubAlpha(0.03f)
	, EffectColor(Vector3(1.0f, 1.0f, 1.0f))
	, RandValue(271)
	, InitAlpha(1.0f)
	, InitScale(24.0f)
	, RotateLowestValue(90)
	, AxisYAngle(45.0f)
{
	// �����o�[�ϐ��̏�����
	scale = InitScale;
	alpha = InitAlpha;
	position = _pos;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);

	RotateEffect();
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ExplosionRipplesEffect::~ExplosionRipplesEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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
	angle = (float)(rand() % RandValue + RotateLowestValue);
	Rotation(this, angle, Vector3::UnitX);
	angle = AxisYAngle;
	Rotation(this, angle, Vector3::UnitY);
	angle = (float)(rand() % RandValue + RotateLowestValue);
	Rotation(this, angle, Vector3::UnitZ);
}