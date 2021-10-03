//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "LandingEffectManager.h"
#include "LandingEffect.h"
#include "PlayerObject.h"

LandingEffectManager::LandingEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(8)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	tmpVelZ = 0.0f;
}

LandingEffectManager::~LandingEffectManager()
{
}

void LandingEffectManager::UpdateGameObject(float _deltaTime)
{
	// �O�̃t���[����Z���̑��x��0.0f�łȂ����̃t���[���ł�Z���̑��x0.0f�ł��W�����v�t���O��false��������
	if (owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPSTART || owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE ||
		owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPEND_TO_RUN)
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
		generateEffectsFlag = true;
		break;
		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g�̐���
		ActiveEffectProcess();
		break;
	}
}

void LandingEffectManager::ActiveEffectProcess()
{
	if (generateEffectsFlag)
	{
		// owner�̃|�W�V�����𓾂�
		position = owner->GetPosition();

		// 8����
		for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
		{
			// ���ꂼ��̃G�t�F�N�g�̕������v�Z���鏈��
			CalculatingDirectionProcess(efectCount, velocity);

			//particle�𐶐�
			new LandingEffect(position, velocity);
		}

		generateEffectsFlag = false;
	}
}

void LandingEffectManager::CalculatingDirectionProcess(int _index, Vector3& _velocity)
{
	// �������ɓ������̂ł��ꂼ��ɕ����x�N�g����n��
	if (_index == 0)
	{
		_velocity = Vector3::UnitX;
	}

	if (_index == 1)
	{
		_velocity = Vector3::UnitY;
	}

	if (_index == 2)
	{
		_velocity = Vector3::NegUnitX;
	}

	if (_index == 3)
	{
		_velocity = Vector3::NegUnitY;
	}

	if (_index == 4)
	{
		_velocity = Vector3::UnitX + Vector3::UnitY;
	}

	if (_index == 5)
	{
		_velocity = Vector3::UnitX + Vector3::NegUnitY;
	}

	if (_index == 6)
	{
		_velocity = Vector3::NegUnitX + Vector3::UnitY;
	}

	if (_index == 7)
	{
		_velocity = Vector3::NegUnitX + Vector3::NegUnitY;
	}
}
