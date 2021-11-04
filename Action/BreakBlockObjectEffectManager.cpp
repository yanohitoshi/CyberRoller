#include "BreakBlockObjectEffectManager.h"
#include "BreakBlockObject.h"
#include "DustEffect.h"
#include "DebrisEffectObject.h"

BreakBlockObjectEffectManager::BreakBlockObjectEffectManager(BreakBlockObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, DustEffectRandValue(250)
	, CorrectionRandValue(10.0f)
	, LastCorrection(0.1f)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	activeCount = 0;
}

BreakBlockObjectEffectManager::~BreakBlockObjectEffectManager()
{
}

void BreakBlockObjectEffectManager::UpdateGameObject(float _deltaTime)
{
	// ���S��Ԃ�������L����
	if (owner->GetState() == State::Disabling)
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
		activeCount = 0;
		generateExplosionEffectsFlag = true;
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g�̐���
		ActiveEffectProcess();
		break;
	}
}

void BreakBlockObjectEffectManager::ActiveEffectProcess()
{

	if (generateExplosionEffectsFlag)
	{
		effectPosition = owner->GetPosition();
		GenerateDustEffectProcess();
		GenerateDebrisEffectProcess();
		generateExplosionEffectsFlag = false;
	}
}

void BreakBlockObjectEffectManager::GenerateDustEffectProcess()
{
	for (int dustEfectCount = 0; dustEfectCount < 20; dustEfectCount++)
	{
		// �����_���Ȓl�𐶐�
		Vector3 randV((rand() % DustEffectRandValue) / CorrectionRandValue, (rand() % DustEffectRandValue) / CorrectionRandValue, (rand() % DustEffectRandValue) / CorrectionRandValue);

		// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
		effectVelocity = randV * LastCorrection;
		effectVelocity.Normalize();

		if (dustEfectCount % 2 == 0)
		{
			effectVelocity.x *= -1.0f;
			effectVelocity.z *= -1.0f;
		}

		if (dustEfectCount % 3 == 0)
		{
			effectVelocity.y *= -1.0f;
		}

		//�G�t�F�N�g�𐶐�
		new DustEffect(this, effectPosition, effectVelocity);
	}
}

void BreakBlockObjectEffectManager::GenerateDebrisEffectProcess()
{
	for (int i = 0; i < 20; i++)
	{
		// �����_���Ȓl�𐶐�
		Vector3 randDir((float)(rand() % 50), (float)(rand() % 50), 1.0f);
		randDir.Normalize();

		if (i % 2 == 0)
		{
			randDir.x *= -1.0f;
		}

		if (i % 3 == 0)
		{
			randDir.y *= -1.0f;
		}

		randDir.z = 1.0f;

		new DebrisEffectObject(effectPosition, randDir);
	}
}
