#include "EnemyDeadEffectManager.h"
#include "EnemyDeadEffect.h"
#include "EnemyObjectBase.h"

EnemyDeadEffectManager::EnemyDeadEffectManager(EnemyObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(3)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateFlag = true;
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
		generateFlag = true;
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
	if (frameCount >= 10)
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
}

