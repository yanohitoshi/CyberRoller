#include "EnemyDeadEffectManager.h"
#include "EnemyDeadEffect.h"
#include "EnemyObjectBase.h"
#include "EnemyExplosionEffect.h"

EnemyDeadEffectManager::EnemyDeadEffectManager(EnemyObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
	, WaitingExplosionTime(120)
	, MaxExplosionEffects(10)
	, RandValue(250)
	, CorrectionRandValue(10.0f)
	, LastCorrection(0.1f)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	effectFrameCount = 0;
}

EnemyDeadEffectManager::~EnemyDeadEffectManager()
{
}

void EnemyDeadEffectManager::UpdateGameObject(float _deltaTime)
{
	// ���S��Ԃ�������L����
	if (owner->GetIsDeadFlag())
	{
		// �p�[�e�B�N����L����
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// �p�[�e�B�N���𖳌���
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// �p�[�e�B�N���̏�Ԃ�����
	switch (particleState)
	{
		// ������Ԃ�������break
	case (PARTICLE_DISABLE):
		effectFrameCount = 0;
		generateExplosionEffectsFlag = true;
		break;
		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g�̐���
		ActiveEffectProcess();
		break;
	}
}

void EnemyDeadEffectManager::ActiveEffectProcess()
{
	++effectFrameCount;

	if (effectFrameCount % 15 == 0)
	{
		GenerateEffectProcess();
	}
}

void EnemyDeadEffectManager::GenerateEffectProcess()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();

	if (generateExplosionEffectsFlag && effectFrameCount >= WaitingExplosionTime)
	{
		velocity = Vector3::Zero;

		for (int explosionEfectCount = 0; explosionEfectCount < MaxExplosionEffects; explosionEfectCount++)
		{
			// �����_���Ȓl�𐶐�
			Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue);

			// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
			velocity = randV * LastCorrection;
			velocity.Normalize();

			if (explosionEfectCount % 2 == 0)
			{
				velocity.x *= -1.0f;
				velocity.z *= -1.0f;
			}

			if (explosionEfectCount % 3 == 0)
			{
				velocity.y *= -1.0f;
			}

			//�G�t�F�N�g�𐶐�
			new EnemyExplosionEffect(owner, position, velocity);
		}

		generateExplosionEffectsFlag = false;
	}
	else
	{
		velocity = Vector3::UnitZ;
		//�G�t�F�N�g�𐶐�
		new EnemyDeadEffect(owner, position);
	}
}

