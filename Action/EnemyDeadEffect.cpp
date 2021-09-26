#include "EnemyDeadEffect.h"

EnemyDeadEffect::EnemyDeadEffect(GameObject* _owner,const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 30, "Assets/Effect/Thunder_Thin.png", false)
	, AddScale(4.0f)
	, SubAlpha(0.01f)
{
	// �����o�[�ϐ��̏�����
	scale = 64.0f;
	alpha = 1.0f;
	position = _pos;
	position.z += 20.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(0.65f, 0.65f, 1.0f));
	owner = _owner;

	Vector3 forward = owner->GetForwardVec();
	if (forward.x > 0.0f)
	{
		position.x += 50.0f;
	}
	else if (forward.x < 0.0f)
	{
		position.x -= 50.0f;
	}
	else if (forward.y > 0.0f)
	{
		position.y += 50.0f;
	}
	else if (forward.y < 0.0f)
	{
		position.y -= 50.0f;
	}
	//Z����10�x��]������
	float radianX = Math::ToRadians((float)(rand() % 361));
	Quaternion rotX = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radianX);
	Quaternion targetX = Quaternion::Concatenate(rotX, incX);
	SetRotation(targetX);

	//Z����10�x��]������
	float radianY = Math::ToRadians((float)(rand() % 361));
	Quaternion rotY = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radianY);
	Quaternion targetY = Quaternion::Concatenate(rotY, incY);
	SetRotation(targetY);

	//Z����10�x��]������
	float radianZ = Math::ToRadians((float)(rand() % 361));
	Quaternion rotZ = this->GetRotation();
	Quaternion incZ(Vector3::UnitZ, radianZ);
	Quaternion targetZ = Quaternion::Concatenate(rotZ, incZ);
	SetRotation(targetZ);
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