//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyDeadEffectManager.h"
#include "EnemyElectricShockEffect.h"
#include "EnemyObjectBase.h"
#include "EnemyExplosionEffect.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
EnemyDeadEffectManager::EnemyDeadEffectManager(EnemyObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
	, WaitingExplosionTime(49)
	, MaxExplosionEffects(10)
	, RandValue(250)
	, CorrectionRandValue(10.0f)
	, LastCorrection(0.1f)
	, TowFrequency(2)
	, ThreeFrequency(3)
	, FiveFrequency(5)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	generateExplosionEffectsFlag = true;
	effectFrameCount = 0;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
EnemyDeadEffectManager::~EnemyDeadEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void EnemyDeadEffectManager::UpdateGameObject(float _deltaTime)
{

	// ���S��Ԃ�������L����
	if (owner->GetIsDead() && owner->GetIsVisible())
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
		generateExplosionEffectsFlag = true;
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g�̐���
		ActiveEffect();
		break;
	}
}

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
void EnemyDeadEffectManager::ActiveEffect()
{
	++effectFrameCount;

	if (effectFrameCount % FiveFrequency == 0)
	{
		GenerateEffect();
	}
}

/*
@fn �G�t�F�N�g���Y�����֐�
*/
void EnemyDeadEffectManager::GenerateEffect()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();

	if (generateExplosionEffectsFlag && effectFrameCount >= WaitingExplosionTime)
	{
		GenerateExplosionEffectProcess();

		generateExplosionEffectsFlag = false;
	}
	else
	{
		velocity = Vector3::UnitZ;
		//�G�t�F�N�g�𐶐�
		new EnemyElectricShockEffect(owner, position);
	}
}

/*
@fn �����G�t�F�N�g���Y�����֐�
*/
void EnemyDeadEffectManager::GenerateExplosionEffectProcess()
{
	velocity = Vector3::Zero;

	for (int explosionEfectCount = 0; explosionEfectCount < MaxExplosionEffects; explosionEfectCount++)
	{
		// �����_���Ȓl�𐶐�
		Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue);

		// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
		velocity = randV * LastCorrection;
		velocity.Normalize();

		if (explosionEfectCount % TowFrequency == 0)
		{
			velocity.x *= -1.0f;
			velocity.z *= -1.0f;
		}

		if (explosionEfectCount % ThreeFrequency == 0)
		{
			velocity.y *= -1.0f;
		}

		//�G�t�F�N�g�𐶐�
		new EnemyExplosionEffect(owner, position, velocity);
	}
}