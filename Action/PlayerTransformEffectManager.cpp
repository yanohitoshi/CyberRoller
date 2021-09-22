#include "PlayerTransformEffectManager.h"
#include "PlayerTransformEffect.h"
#include "PlayerObject.h"

PlayerTransformEffectManager::PlayerTransformEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(20)
	, RandValue(100)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	velocity = Vector3::Zero;
	effectPosition = Vector3::Zero;
	frameCount = 0;
	effectCount = 0;
}

PlayerTransformEffectManager::~PlayerTransformEffectManager()
{
}

void PlayerTransformEffectManager::UpdateGameObject(float _deltaTime)
{
	// �e�N���X�̃X�e�[�^�X��Active��������
	if (owner->GetNowState() == PlayerState::PLAYER_STATE_JUMP_ATTACK)
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

void PlayerTransformEffectManager::ActiveEffectProcess()
{

	// �����t���O��true��������
	if (generateFlag == true)
	{
		++frameCount;
		if (frameCount % 2 == 0)
		{
			// �G�t�F�N�g���Y�֐�
			GenerateEffectProcess();
		}

		if (effectCount >= 3)
		{
			effectCount = 0;
			frameCount = 0;
			// �����t���O��false��
			generateFlag = false;
		}
	}

}

void PlayerTransformEffectManager::GenerateEffectProcess()
{
	
	// owner�̃|�W�V�����𓾂�
	effectPosition = owner->GetPosition();
	effectPosition.z += 100.0f;
	new PlayerTransformEffect(effectPosition, velocity);
	++effectCount;
}
