//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CrystalDefaultEffect.h"
#include "CrystalEffectManager.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�ړ����x
@param	���F������pTag
*/
CrystalDefaultEffect::CrystalDefaultEffect(const Vector3& _pos, const Vector3& _velocity, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, _velocity, 100, "Assets/Effect/Particle_Soft.png", true)
	, AddScale(2.0f)
	, AddAlpha(0.005f)
	, SubAlpha(0.002f)
	, MaxAlphaValue(0.6f)
{
	// �����o�[�ϐ��̏�����
	scale = 0.0f;
	alpha = 0.0f;
	speed = 20.0f;
	inFlag = true;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);

	// �}�l�[�W���[�N���X����󂯎�����F�����Q�Ƃ��ĐF�̐ݒ�
	if (_crystalColor == CrystalColor::WHITE)
	{
		particleComponent->SetColor(Vector3(0.9f, 0.9f, 0.9f));
	}
	else if (_crystalColor == CrystalColor::RED)
	{
		particleComponent->SetColor(Vector3(1.0f, 0.5f, 0.5f));
	}
	else if (_crystalColor == CrystalColor::BLUE)
	{
		particleComponent->SetColor(Vector3(0.5f, 0.5f, 1.0f));
	}
	else if (_crystalColor == CrystalColor::GREEN)
	{
		particleComponent->SetColor(Vector3(0.5f, 1.0f, 0.5f));
	}
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CrystalDefaultEffect::~CrystalDefaultEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CrystalDefaultEffect::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ̃J�E���g�_�E��
	ParticleEffectBase::LifeCountDown();

	// ���C�t�J�E���g��0�ȏ�ɂȂ�����
	if (lifeCount > 0)
	{
		// �t�F�[�h�C������
		FadeInProcess();

		// �萔�𑫂��Ċg��
		scale += AddScale;
		// �萔�������ē���
		alpha -= SubAlpha;

		// scale�l���Z�b�g
		particleComponent->SetScale(scale);
		// alpha�l���Z�b�g
		particleComponent->SetAlpha(alpha);

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
void CrystalDefaultEffect::FadeInProcess()
{
	// �t�F�[�h�C���t���O��true��������
	if (inFlag == true)
	{
		// alpha�l�ɒ萔�𑫂�
		alpha += AddAlpha;
		// alpha�l�̍ő�萔�ɓ��B������
		if (alpha >= MaxAlphaValue)
		{
			// �t�F�[�h�C���t���O��false��
			inFlag = false;
		}
	}
}