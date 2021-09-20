//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "LandingEffectManager.h"
#include "LandingEffect.h"
#include "PlayerObject.h"

LandingEffectManager::LandingEffectManager(GameObject* _owner)
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
	if (owner->GetVelocity().z == 0.0f && tmpVelZ != 0.0f && PlayerObject::GetChackJumpFlag() == false)
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
		break;
		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g�̐���
		ActiveEffectProcess();

		// particleState������
		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}

	// owner��Z�����x��ۑ�
	tmpVelZ = owner->GetVelocity().z;

}

void LandingEffectManager::ActiveEffectProcess()
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
