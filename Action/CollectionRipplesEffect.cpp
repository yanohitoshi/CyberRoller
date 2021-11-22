//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CollectionRipplesEffect.h"

/*
@fn �R���X�g���N�^
@param	�e�ƂȂ�N���X�̃|�C���^
@param	�|�W�V����
@param	�ړ����x
*/
CollectionRipplesEffect::CollectionRipplesEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 20, "Assets/Effect/Collection/Ripple.png", true)
	, AddScale(32.0f)
	, SubAlpha(0.01f)
	, InitAlpha(1.0f)
	, InitScale(0.0f)
	, MoveSpeed(25.0f)
{
	// �����o�[�ϐ��̏�����
	owner = _owner;
	scale = InitScale;
	alpha = InitAlpha;
	speed = MoveSpeed;
	position = _pos;
	velocity = _velocity;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(0.9f, 0.9f, 0.5f));
	SetPosition(position);

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CollectionRipplesEffect::~CollectionRipplesEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectionRipplesEffect::UpdateGameObject(float _deltaTime)
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