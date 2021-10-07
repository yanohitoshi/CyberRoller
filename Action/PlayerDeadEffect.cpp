#include "PlayerDeadEffect.h"

PlayerDeadEffect::PlayerDeadEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _distance)
	: ParticleEffectBase(_pos, Vector3::Zero, 15, "Assets/Effect/Thunder_Thin.png", false)
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

PlayerDeadEffect::~PlayerDeadEffect()
{
}

void PlayerDeadEffect::UpdateGameObject(float _deltaTime)
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

// @fix
void PlayerDeadEffect::RotateEffect()
{
	float radian;
	Quaternion rot;
	Quaternion target;

	//X���������_���Ȓl��]������
	radian = Math::ToRadians((float)(rand() % RandValue));
	rot = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radian);
	target = Quaternion::Concatenate(rot, incX);
	SetRotation(target);

	//Y���������_���Ȓl��]������
	radian = Math::ToRadians((float)(rand() % RandValue));
	rot = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radian);
	target = Quaternion::Concatenate(rot, incY);
	SetRotation(target);

	//Z���������_���Ȓl��]������
	radian = Math::ToRadians((float)(rand() % RandValue));
	rot = this->GetRotation();
	Quaternion incZ(Vector3::UnitZ, radian);
	target = Quaternion::Concatenate(rot, incZ);
	SetRotation(target);

	// ��]�l����ړ��������v�Z
	Matrix4 mat = Matrix4::CreateFromQuaternion(this->GetRotation());
	velocity.x += mat.GetXAxis().x;
	velocity.y += mat.GetYAxis().y;
	velocity.z += mat.GetZAxis().z;
	velocity.Normalize();

}
