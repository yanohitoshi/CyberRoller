//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FierWorksEffect.h"
#include "ParticleComponent.h"
#include "CrystalEffectManager.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�ړ����x
@param	���F������pTag
*/
FierWorksEffect::FierWorksEffect(const Vector3& _pos, const Vector3& _velocity, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, _velocity, 210, "Assets/Effect/Particle_Soft.png",true, true)
	, FadeInAddScale(2.0f)
	, FadeOutAddScale(5.0f)
	, MaxAlpha(0.9f)
	, AddAlpha(0.05f)
	, SubAlpha(0.001f)
	, SubSpeed(1.0f)
	, VelocityAtFadeOut(40.0f)
	, ChangeFadeOutTime(190)
	, WhiteValue(Vector3(0.9f, 0.9f, 0.9f))
	, RedValue(Vector3(1.0f, 0.5f, 0.5f))
	, BlueValue(Vector3(0.5f, 0.5f, 1.0f))
	, GreenValue(Vector3(0.5f, 1.0f, 0.5f))
{
	// �����o�[�ϐ��̏�����
	scale = 2.0f;
	alpha = 0.1f;
	speed = 200.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
	// �ŏ��̓t�F�[�h�C����Ԃɏ�����
	inFlag = true;

	// �}�l�[�W���[�N���X�̐F�����Q�Ƃ��ĐF��ݒ�
	if (_crystalColor == CrystalColor::WHITE)
	{
		particleComponent->SetColor(WhiteValue);
	}
	else if (_crystalColor == CrystalColor::RED)
	{
		particleComponent->SetColor(RedValue);
	}
	else if (_crystalColor == CrystalColor::BLUE)
	{
		particleComponent->SetColor(BlueValue);
	}
	else if (_crystalColor == CrystalColor::GREEN)
	{
		particleComponent->SetColor(GreenValue);
	}
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
FierWorksEffect::~FierWorksEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void FierWorksEffect::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ̃J�E���g�_�E��
	ParticleEffectBase::LifeCountDown();

	// ���C�t�J�E���g���t�F�[�h�C���E�A�E�g�̐؂�ւ��^�C�~���O�ɓ��B���Ă��Ȃ�������
	if (lifeCount > ChangeFadeOutTime)
	{
		FadeInProcess();

		// �萔�𑫂��Ċg��
		scale += FadeInAddScale;

		// scale�l���Z�b�g
		particleComponent->SetScale(scale);
		// alpha�l���Z�b�g
		particleComponent->SetAlpha(alpha);

		// �|�W�V�����ɑ��x��ǉ�
		position += velocity * speed * _deltaTime;
		// �|�W�V�������X�V
		SetPosition(position);

	}
	else if (lifeCount <= ChangeFadeOutTime) // �؂�ւ���l�ɓ��B���Ă�����
	{
		// �t�F�[�h�A�E�g�p�萔�𑫂��Ċg��
		scale += FadeOutAddScale;
		// �萔�������ē���
		alpha -= SubAlpha;

		// x,y����0.0f�ɌŒ�
		velocity.x = 0.0f;
		velocity.y = 0.0f;

		// ���x���`�F�b�N
		ChackSpeedProcess();

		// scale�l���Z�b�g
		particleComponent->SetAlpha(alpha);
		// alpha�l���Z�b�g
		particleComponent->SetScale(scale);

		// �|�W�V�����ɑ��x��ǉ�
		position += velocity * speed * _deltaTime;
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

/*
@fn �t�F�[�h�C���֐�
*/
void FierWorksEffect::FadeInProcess()
{
	// �t�F�[�h�C����Ԃ�������
	if (inFlag == true)
	{
		// alpha�l�ɒ萔�𑫂�
		alpha += AddAlpha;

		// alpha�l���ő�l�ɓ��B������
		if (alpha >= MaxAlpha)
		{
			// �t�F�[�h�C���t���O��false��
			inFlag = false;
		}
	}

}

/*
@fn ���x�}���֐�
*/
void FierWorksEffect::ChackSpeedProcess()
{
	// ���x���萔���傫�������炾������
	if (speed > VelocityAtFadeOut)
	{
		// ����
		speed -= SubSpeed;

		// ���x���萔�ȉ���������
		if (speed <= VelocityAtFadeOut)
		{
			// �萔����
			speed = VelocityAtFadeOut;
		}
	}

}
