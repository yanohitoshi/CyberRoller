#include "PlayerDeadEffectManager.h"
#include "PlayerDeadEffect.h"
#include "PlayerObject.h"

PlayerDeadEffectManager::PlayerDeadEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, PositionOffset(50.0f)
	, ShiftPositionZ(40.0f)
	, GenerationTime(30)
	, DistanceOffset(30.0f)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	effectFrameCount = 0;
}

PlayerDeadEffectManager::~PlayerDeadEffectManager()
{
}

void PlayerDeadEffectManager::UpdateGameObject(float _deltaTime)
{
	// ���݂̃X�e�[�^�X�����S��Ԃ�������G�t�F�N�g��L����
	if (owner->GetNowState() == PlayerState::PLAYER_STATE_DEAD)
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
		generationCount = 0;
		break;
		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g�̐���
		ActiveEffectProcess();
		break;
	}
}

void PlayerDeadEffectManager::ActiveEffectProcess()
{
	// �����܂ł̎��Ԃ𐔂���
	++generationCount;

	// ���Ԃ������甭���J�n
	if (generationCount >= GenerationTime)
	{
		// �G�t�F�N�g�����J�n��̃J�E���g�𐔂���
		++effectFrameCount;
		if (effectFrameCount % 5 == 0)
		{
			// ��������
			GenerateEffectProcess();
		}
	}
}

void PlayerDeadEffectManager::GenerateEffectProcess()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();
	// �I�[�i�[�̑O���x�N�g���̋t�����̃x�N�g�����v�Z
	Vector3 direction = owner->GetCharaForwardVec() * -1.0f;
	// �v�Z�����x�N�g���ɃI�t�Z�b�g��������
	position += direction * PositionOffset;
	// ���������炷
	position.z += ShiftPositionZ;
	// �I�[�i�[�̑��x�𓾂�
	distance = owner->GetVelocity();
	// ���K��
	distance.Normalize();
	// ���x�𐳋K���������̂ɒ萔���|����
	distance *= DistanceOffset;
	//particle�𐶐�
	new PlayerDeadEffect(owner, position, distance);
}