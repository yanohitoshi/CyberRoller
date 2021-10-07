//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerTransformEffectManager.h"
#include "PlayerTransformEffect.h"
#include "PlayerObject.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
PlayerTransformEffectManager::PlayerTransformEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
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

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
PlayerTransformEffectManager::~PlayerTransformEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
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

/*
@fn �G�t�F�N�g���Y�����֐�
*/
void PlayerTransformEffectManager::GenerateEffectProcess()
{
	
	// owner�̃|�W�V�����𓾂�
	effectPosition = owner->GetPosition();
	effectPosition.z += 100.0f;
	new PlayerTransformEffect(owner,effectPosition, velocity);
	++effectCount;
}