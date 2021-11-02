#include "ExplosionObjectEffectManager.h"
#include "ExplosionObject.h"

ExplosionObjectEffectManager::ExplosionObjectEffectManager(ExplosionObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	//, WaitingExplosionTime(49)
	//, MaxExplosionEffects(10)
	//, RandValue(250)
	//, CorrectionRandValue(10.0f)
	//, LastCorrection(0.1f)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	//generateExplosionEffectsFlag = true;
	//effectFrameCount = 0;
}
ExplosionObjectEffectManager::~ExplosionObjectEffectManager()
{
}

void ExplosionObjectEffectManager::UpdateGameObject(float _deltaTime)
{
	// ���S��Ԃ�������L����
	if (owner->GetIsStartExplosion())
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
		//generateExplosionEffectsFlag = true;
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
}

void ExplosionObjectEffectManager::GenerateEffectProcess()
{
}

void ExplosionObjectEffectManager::GenerateExplosionEffectProcess()
{
}
