//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BreakBlockObjectEffectManager.h"
#include "BreakBlockObject.h"
#include "DustEffect.h"
#include "DebrisEffectObject.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
BreakBlockObjectEffectManager::BreakBlockObjectEffectManager(BreakBlockObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, DustEffectRandValue(250)
	, CorrectionRandValue(10.0f)
	, DustMaxEffect(20)
	, DebrisEffectRandValue(50)
	, DebrisMaxEffect(20)
	, LastCorrection(0.1f)
	, TowFrequency(2)
	, ThreeFrequency(3)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	activeCount = 0;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
BreakBlockObjectEffectManager::~BreakBlockObjectEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void BreakBlockObjectEffectManager::UpdateGameObject(float _deltaTime)
{
	// ���S��Ԃ�������L����
	if (owner->GetState() == State::Disabling)
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
		activeCount = 0;
		generateExplosionEffectsFlag = true;
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g�̐���
		ActiveEffectProcess();
		break;
	}
}

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
void BreakBlockObjectEffectManager::ActiveEffectProcess()
{
	// �܂���������Ă��Ȃ�������
	if (generateExplosionEffectsFlag)
	{
		effectPosition = owner->GetPosition();
		GenerateDustEffectProcess();
		GenerateDebrisEffectProcess();
		generateExplosionEffectsFlag = false;
	}
}

/*
@fn �y���G�t�F�N�g���Y�����֐�
*/
void BreakBlockObjectEffectManager::GenerateDustEffectProcess()
{
	for (int dustEfectCount = 0; dustEfectCount < DustMaxEffect; dustEfectCount++)
	{
		// �����_���Ȓl�𐶐�
		Vector3 randV((rand() % DustEffectRandValue) / CorrectionRandValue, (rand() % DustEffectRandValue) / CorrectionRandValue, (rand() % DustEffectRandValue) / CorrectionRandValue);

		// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
		effectVelocity = randV * LastCorrection;
		effectVelocity.Normalize();

		if (dustEfectCount % TowFrequency == 0)
		{
			effectVelocity.x *= -1.0f;
			effectVelocity.z *= -1.0f;
		}

		if (dustEfectCount % ThreeFrequency == 0)
		{
			effectVelocity.y *= -1.0f;
		}

		//�G�t�F�N�g�𐶐�
		new DustEffect(this, effectPosition, effectVelocity);
	}
}

/*
@fn �j�ЃG�t�F�N�g���Y�����֐�
*/
void BreakBlockObjectEffectManager::GenerateDebrisEffectProcess()
{
	for (int i = 0; i < DebrisMaxEffect; i++)
	{
		// �����_���Ȓl�𐶐�
		Vector3 randDir((float)(rand() % DebrisEffectRandValue), (float)(rand() % DebrisEffectRandValue), 1.0f);
		randDir.Normalize();

		if (i % TowFrequency == 0)
		{
			randDir.x *= -1.0f;
		}

		if (i % ThreeFrequency == 0)
		{
			randDir.y *= -1.0f;
		}

		randDir.z = 1.0f;

		new DebrisEffectObject(effectPosition, randDir);
	}
}
