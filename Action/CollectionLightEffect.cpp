//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CollectionLightEffect.h"
#include "CrystalEffectManager.h"

/*
@fn �R���X�g���N�^
@param	�e�ƂȂ�N���X�̃|�C���^
@param	�|�W�V����
@param	�ړ����x
*/
CollectionLightEffect::CollectionLightEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _direction, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, Vector3::Zero, 60, "Assets/Effect/Collection/Light.png", true)
	, AddScale(2.0f)
	, SubAlpha(0.01f)
	, InitAlpha(1.0f)
	, InitScale(32.0f)
	, AddValue(0.1f)
	, SpeedRandValue(400)
	, SpeedLowestValue(200)
	, SinRandValue(180)
{
	// �����o�[�ϐ��̏�����
	owner = _owner;
	scale = InitScale;
	alpha = InitAlpha;
	position = _pos;
	direction = _direction;
	SetPosition(position);

	// �����_���ȑ��x�𓾂�
	speed = (float)(rand() % SpeedRandValue + SpeedLowestValue);
	// �����_���ȏ����̒l�𓾂�
	value = (float)(rand() % SinRandValue);
	sinV = Math::Sin(value);

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
CollectionLightEffect::~CollectionLightEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectionLightEffect::UpdateGameObject(float _deltaTime)
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
		
		value += AddValue;
		sinV = Math::Sin(value);

		// sin�̒l�𑫂����߂̕ϐ�
		Vector3 dir = Vector3::Zero;
		dir = direction;
		dir.x += sinV;
		dir.y += sinV;
		velocity = dir * speed;

		SetPosition(position + velocity * _deltaTime);
	}

	// ���C�t�J�E���g��0�ȉ�
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}
