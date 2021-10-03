#include "PlayerAttackHitEffectManager.h"
#include "PlayerAttackHitEffect.h"
#include "PlayerObject.h"

PlayerAttackHitEffectManager::PlayerAttackHitEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, CorrectionPosition(100.0f)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	velocity = Vector3::Zero;
	effectPosition = Vector3::Zero;
}

PlayerAttackHitEffectManager::~PlayerAttackHitEffectManager()
{
}

void PlayerAttackHitEffectManager::UpdateGameObject(float _deltaTime)
{
	// �e�N���X�̃X�e�[�^�X��Active��������
	if (owner->GetIsJumpAttackSuccess())
	{
		// particleState��L����
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particleState�𖳌���
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// �p�[�e�B�N���̏�Ԃ�����
	switch (particleState)
	{
	case (PARTICLE_DISABLE):
		// ������
		generateFlag = true;
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		ActiveEffectProcess();

		break;
	}
}

void PlayerAttackHitEffectManager::ActiveEffectProcess()
{
	// �����t���O��true��������
	if (generateFlag == true)
	{
		// �G�t�F�N�g���Y�֐�
		GenerateEffectProcess();
		generateFlag = false;
	}
}

void PlayerAttackHitEffectManager::GenerateEffectProcess()
{
	// �|�W�V�����v�Z
	effectPosition = owner->GetPosition() + owner->GetForwardVec() * CorrectionPosition;
	// �G�t�F�N�g����
	new PlayerAttackHitEffect(owner, effectPosition, velocity);
}