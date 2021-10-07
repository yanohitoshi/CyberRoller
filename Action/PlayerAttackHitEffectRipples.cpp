//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerAttackHitEffectRipples.h"

/*
@fn �R���X�g���N�^
@param	�e�ƂȂ�N���X�̃|�C���^
@param	�|�W�V����
@param	�ړ����x
*/
PlayerAttackHitEffectRipples::PlayerAttackHitEffectRipples(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 5, "Assets/Effect/Shockwave.png", false)
	, AddScale(128.0f)
	, SubAlpha(0.01f)
{
	// �����o�[�ϐ��̏�����
	owner = _owner;
	scale = 0.0f;
	alpha = 1.0f;
	speed = 25.0f;
	position = _pos;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(1.0f, 0.8f, 0.4f));
	SetPosition(position);
	SetRotation(owner->GetRotation());
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
PlayerAttackHitEffectRipples::~PlayerAttackHitEffectRipples()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void PlayerAttackHitEffectRipples::UpdateGameObject(float _deltaTime)
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

		SetRotation(owner->GetRotation());
	}

	// ���C�t�J�E���g��0�ȉ�
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}