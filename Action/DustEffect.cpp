#include "DustEffect.h"

/*
@fn �R���X�g���N�^
@param	�e�ƂȂ�N���X�̃|�C���^
@param	�|�W�V����
@param	�ړ����x
*/
DustEffect::DustEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, Vector3::Zero, 45, "Assets/Effect/BreakBlock/Dust.png", true)
	, AddScale(12.0f)
	, SubAlpha(0.02f)
	, EffectColor(Vector3(0.93f, 0.93f, 0.93f))
	, SpeedRandValue(50)
	, SpeedLowestValue(10)
{
	// �����o�[�ϐ��̏�����
	scale = 0.0f;
	alpha = 1.0f;
	position = _pos;
	velocity = _velocity;
	speed = (float)(rand() % SpeedRandValue / SpeedLowestValue);
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
DustEffect::~DustEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void DustEffect::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ̃J�E���g�_�E��
	ParticleEffectBase::LifeCountDown();

	// ���C�t�J�E���g��0�ȏ�ɂ�������
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
