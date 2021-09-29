#include "EnemyDeadEffectManager.h"
#include "EnemyDeadEffect.h"
#include "EnemyObjectBase.h"
#include "EnemyExplosionEffect.h"

EnemyDeadEffectManager::EnemyDeadEffectManager(EnemyObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(1)
	, MaxExplosionEffects(50)
	, RandValueX(250)
	, RandValueY(250)
	, RandValueZ(250)
	, CorrectionRandValue(10.0f)
	, LastCorrection(0.1f)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	frameCount = 0;
}

EnemyDeadEffectManager::~EnemyDeadEffectManager()
{
}

void EnemyDeadEffectManager::UpdateGameObject(float _deltaTime)
{
	// �O�̃t���[����Z���̑��x��0.0f�łȂ����̃t���[���ł�Z���̑��x0.0f�ł��W�����v�t���O��false��������
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

	++frameCount;
	if (frameCount >= 15)
	{
		GenerateEffectProcess();
		frameCount = 0;
	}
}

void EnemyDeadEffectManager::GenerateEffectProcess()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();

	velocity = Vector3::UnitZ;

	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{
		//particle�𐶐�
		new EnemyDeadEffect(owner,position);
	}

	if (generateExplosionEffectsFlag)
	{
		for (int explosionEfectCount = 0; explosionEfectCount < MaxExplosionEffects; explosionEfectCount++)
		{
			// �����_���Ȓl�𐶐�
			Vector3 randV((rand() % RandValueX) / CorrectionRandValue, (rand() % RandValueY) / CorrectionRandValue, (rand() % RandValueZ) / CorrectionRandValue);

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

			//particle�𐶐�
			new EnemyExplosionEffect(owner, position, velocity);
		}
		generateExplosionEffectsFlag = false;
	}
}

