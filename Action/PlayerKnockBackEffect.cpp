//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerKnockBackEffect.h"

/*
@fn �R���X�g���N�^
@param	�e�N���X�̃|�C���^
@param	�ړ����x
@param	�v���C���[�̑̂Ɉʒu�����킹�邽�߂̊Ԋu
*/
PlayerKnockBackEffect::PlayerKnockBackEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _distance)
	: ParticleEffectBase(_pos, Vector3::Zero, 15, "Assets/Effect/Player/KnockBack/KnockBack.png", false)
	, AddScale(4.0f)
	, SubAlpha(0.1f)
	, RandValue(361)
	, EffectColor(Vector3(0.65f, 0.65f, 1.0f))
{
	// �����o�[�ϐ��̏�����
	scale = 32;
	alpha = 1.0f;
	speed = 1.0f;
	position = _pos + _distance;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
	RotateEffect();
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
PlayerKnockBackEffect::~PlayerKnockBackEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void PlayerKnockBackEffect::UpdateGameObject(float _deltaTime)
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

/*
@fn ��]�����֐�
@brief	�G�t�F�N�g�̉�]���s��
*/
void PlayerKnockBackEffect::RotateEffect()
{
	// X������]
	Rotation(Vector3::UnitX);
	// Y������]
	Rotation(Vector3::UnitY);
	// Z������]
	Rotation(Vector3::UnitZ);

	// ��]�l����ړ��������v�Z
	Matrix4 mat = Matrix4::CreateFromQuaternion(this->GetRotation());
	velocity.x += mat.GetXAxis().x;
	velocity.y += mat.GetYAxis().y;
	velocity.z += mat.GetZAxis().z;
	velocity.Normalize();

}

/*
@fn ��]�v�Z����
@param _axis ��]��
*/
void PlayerKnockBackEffect::Rotation(const Vector3 _axis)
{
	//�����_���Ȓl��]������
	float radian = Math::ToRadians((float)(rand() % RandValue));
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}
