#include "EnemyFlinchEffectManager.h"
#include "EnemyElectricShockEffect.h"
#include "EnemyObjectBase.h"

EnemyFlinchEffectManager::EnemyFlinchEffectManager(EnemyObjectBase* _owner)
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
	effectFrameCount = 0;
}

EnemyFlinchEffectManager::~EnemyFlinchEffectManager()
{
}

void EnemyFlinchEffectManager::UpdateGameObject(float _deltaTime)
{
	// ���S��Ԃ�������L����
	if (owner->GetIsFlinch())
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
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g�̐���
		ActiveEffectProcess();
		break;
	}
}

void EnemyFlinchEffectManager::ActiveEffectProcess()
{
	++effectFrameCount;

	if (effectFrameCount % 5 == 0)
	{
		GenerateEffectProcess();
	}
}

void EnemyFlinchEffectManager::GenerateEffectProcess()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();
	//�G�t�F�N�g�𐶐�
	new EnemyElectricShockEffect(owner, position);
}
