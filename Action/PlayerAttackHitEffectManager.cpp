//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerAttackHitEffectManager.h"
#include "PlayerAttackHitEffect.h"
#include "PlayerObject.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
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

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
PlayerAttackHitEffectManager::~PlayerAttackHitEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
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

/*
@fn �G�t�F�N�g���Y�����֐�
*/
void PlayerAttackHitEffectManager::GenerateEffectProcess()
{
	// �|�W�V�����v�Z
	effectPosition = owner->GetPosition() + owner->GetForwardVec() * CorrectionPosition;
	// �G�t�F�N�g����
	new PlayerAttackHitEffect(owner, effectPosition, velocity);
}