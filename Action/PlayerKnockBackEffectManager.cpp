#include "PlayerKnockBackEffectManager.h"
#include "PlayerKnockBackEffect.h"
#include "PlayerObject.h"

PlayerKnockBackEffectManager::PlayerKnockBackEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, PositionOffset(150.0f)
	, DistanceOffset(30.0f)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	effectFrameCount = 0;
}

PlayerKnockBackEffectManager::~PlayerKnockBackEffectManager()
{
}

void PlayerKnockBackEffectManager::UpdateGameObject(float _deltaTime)
{
	// ���݂̃X�e�[�^�X���m�b�N�o�b�N��Ԃ�������G�t�F�N�g��L����
	if (owner->GetNowState() == PlayerState::PLAYER_STATE_KNOCKBACK)
	{
		// �p�[�e�B�N����L����
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// �p�[�e�B�N���𖳌���
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// �X�e�[�^�X��Ԃ�����
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

void PlayerKnockBackEffectManager::ActiveEffectProcess()
{
	++effectFrameCount;
	if (effectFrameCount % 5 == 0)
	{
		GenerateEffectProcess();
	}
}

void PlayerKnockBackEffectManager::GenerateEffectProcess()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();
	position.z += PositionOffset;
	// �I�[�i�[�̑��x�𓾂�
	distance = owner->GetVelocity();
	// ���K��
	distance.Normalize();
	// ���x�𐳋K���������̂ɒ萔���|����
	distance *= DistanceOffset;
	//particle�𐶐�
	new PlayerKnockBackEffect(owner, position, distance);
}