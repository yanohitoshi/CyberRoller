#include "ExplosionObjectEffectManager.h"
#include "ExplosionObjectBase.h"
#include "ExplosionEffect.h"
#include "ExplosionRipplesEffect.h"
#include "SplashExplosionEffect.h"

ExplosionObjectEffectManager::ExplosionObjectEffectManager(ExplosionObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
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
}

ExplosionObjectEffectManager::~ExplosionObjectEffectManager()
{
}

void ExplosionObjectEffectManager::UpdateGameObject(float _deltaTime)
{
	// ���S��Ԃ�������L����
	if (owner->GetIsExplode())
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
		//effectFrameCount = 0;
		generateExplosionEffectsFlag = true;
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g�̐���
		ActiveEffectProcess();
		break;
	}
}

void ExplosionObjectEffectManager::ActiveEffectProcess()
{
	
	if (generateExplosionEffectsFlag)
	{
		velocity = Vector3::Zero;
		effectPosition = owner->GetPosition();

		for (int i = 0; i < 2; i++)
		{
			new ExplosionRipplesEffect(this, effectPosition);
		}

		GenerateExplosionEffectProcess();

		generateExplosionEffectsFlag = false;
	}
}

void ExplosionObjectEffectManager::GenerateEffectProcess()
{
}

void ExplosionObjectEffectManager::GenerateExplosionEffectProcess()
{
	//�G�t�F�N�g�𐶐�
	new ExplosionEffect(effectPosition, effectVelocity);

	for (int explosionEfectCount = 0; explosionEfectCount < MaxExplosionEffects; explosionEfectCount++)
	{
		// �����_���Ȓl�𐶐�
		Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue);

		// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
		effectVelocity = randV * LastCorrection;
		effectVelocity.Normalize();

		if (explosionEfectCount % 2 == 0)
		{
			effectVelocity.x *= -1.0f;
			effectVelocity.z *= -1.0f;
		}

		if (explosionEfectCount % 3 == 0)
		{
			effectVelocity.y *= -1.0f;
		}

		new SplashExplosionEffect(effectPosition, effectVelocity);
	}
}
