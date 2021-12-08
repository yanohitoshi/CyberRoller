//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyFlinchEffectManager.h"
#include "EnemyElectricShockEffect.h"
#include "EnemyObjectBase.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
EnemyFlinchEffectManager::EnemyFlinchEffectManager(EnemyObjectBase* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxExplosionEffects(10)
	, RandValue(250)
	, CorrectionRandValue(10.0f)
	, LastCorrection(0.1f)
	, FiveFrequency(5)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	effectFrameCount = 0;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
EnemyFlinchEffectManager::~EnemyFlinchEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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
		ActiveEffect();
		break;
	}
}

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
void EnemyFlinchEffectManager::ActiveEffect()
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
void EnemyFlinchEffectManager::GenerateEffect()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();
	//�G�t�F�N�g�𐶐�
	new EnemyElectricShockEffect(owner, position);
}
