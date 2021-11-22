#include "CollectionLightEffect.h"
#include "CrystalEffectManager.h"

CollectionLightEffect::CollectionLightEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _direction, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, Vector3::Zero, 60, "Assets/Effect/Collection/Light.png", true)
	, AddScale(2.0f)
	, SubAlpha(0.01f)
{
	// �����o�[�ϐ��̏�����
	owner = _owner;
	scale = 32.0f;
	alpha = 1.0f;
	position = _pos;
	direction = _direction;
	SetPosition(position);

	// �����_���ȑ��x�𓾂�
	speed = (float)(rand() % 400 + 200);
	// �����_���ȏ����̒l�𓾂�
	value = (float)(rand() % 180);
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

CollectionLightEffect::~CollectionLightEffect()
{
}

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
		
		value += 0.1f;
		sinV = Math::Sin(value);

		// sin�̒l�𑫂����߂̕ϐ�
		Vector3 dir = Vector3::Zero;
		dir = direction;
		dir.x += sinV;
		dir.y += sinV;
		//dir.Normalize();
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
