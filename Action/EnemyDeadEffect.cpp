#include "EnemyDeadEffect.h"

EnemyDeadEffect::EnemyDeadEffect(GameObject* _owner,const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 10, "Assets/Effect/Thunder_Thin.png", false)
	, AddScale(4.0f)
	, SubAlpha(0.01f)
	, RandValue(361)
	, EffectColor(Vector3(0.65f, 0.65f, 1.0f))
{
	// �����o�[�ϐ��̏�����
	scale = 32;
	alpha = 1.0f;
	speed = 1.5f;
	position = _pos;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;

	RotateEffect();
}

EnemyDeadEffect::~EnemyDeadEffect()
{
}

void EnemyDeadEffect::UpdateGameObject(float _deltaTime)
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

void EnemyDeadEffect::RotateEffect()
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

	Matrix4 mat = Matrix4::CreateFromQuaternion(this->GetRotation());
	velocity.x += mat.GetXAxis().x;
	velocity.y += mat.GetYAxis().y;
	velocity.z += mat.GetZAxis().z;
	velocity.Normalize();

}
