//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerSandSmokeMakeManager.h"
#include "PlayerSandSmokeEffect.h"
#include "PlayerObject.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
PlayerSandSmokeMakeManager::PlayerSandSmokeMakeManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, GenerateSpeedValue(600.0f)
	, ShiftPositionValue(30.0f)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateCount = 0;
	effectPosition = Vector3::Zero;
	ownerState = owner->GetNowState();
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
PlayerSandSmokeMakeManager::~PlayerSandSmokeMakeManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void PlayerSandSmokeMakeManager::UpdateGameObject(float _deltaTime)
{
	ownerState = owner->GetNowState();

	// owner�̑��x���Q�Ƃ��ėL���������𔻒�
	// �n�ʂɐڒn���ł��������͂��̑��x��0�łȂ����
	if (ownerState == PlayerState::PLAYER_STATE_RUN || ownerState == PlayerState::PLAYER_STATE_RUN_START)
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
		// ������Ԃ������琶���J�E���g��0�ɂ���break
	case (PARTICLE_DISABLE):
		// ������
		generateCount = 0;
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
void PlayerSandSmokeMakeManager::ActiveEffectProcess()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();

	// �t���[���J�E���g�𐔂���
	++frameCount;

	// 10�t���[����1�x�v���C���[�̈ړ����x�����ȏゾ������
	if (frameCount % 10 == 0 && owner->GetVelocity().x > GenerateSpeedValue ||
		frameCount % 10 == 0 && owner->GetVelocity().y > GenerateSpeedValue ||
		frameCount % 10 == 0 && owner->GetVelocity().x < -GenerateSpeedValue||
		frameCount % 10 == 0 && owner->GetVelocity().y < -GenerateSpeedValue )
	{
		GenerateEffectProcess();
	}


}

/*
@fn �G�t�F�N�g���Y�����֐�
*/
void PlayerSandSmokeMakeManager::GenerateEffectProcess()
{
	// �����������𐔂���
	++generateCount;

	// �J�E���g��2�̔{���̎��͉E����
	if (generateCount % 2 == 0)
	{
		ShiftRightEffectPosition();
	}
	else
	{
		ShiftLeftEffectPosition();
	}

	// �I�[�i�[�̑��x�����炤
	Vector3 vel = owner->GetVelocity();

	// ���K��
	vel.Normalize();

	// ���x���t�����ɂ���
	vel = vel * -1.0f;

	// particle�𐶐�
	new PlayerSandSmokeEffect(effectPosition, vel);
}

/*
@fn �G�t�F�N�g�̃|�W�V�������E�ɂ��炷�֐�
*/
void PlayerSandSmokeMakeManager::ShiftRightEffectPosition()
{
	// ��xposition��ۑ�
	effectPosition = position;

	// �G�t�F�N�g�̃|�W�V���������炵������o�Ă���悤�Ɍ�����
	if (owner->GetVelocity().x > 1.0f)
	{
		effectPosition.y += ShiftPositionValue;
	}
	else if (owner->GetVelocity().x < -1.0f)
	{
		effectPosition.y -= ShiftPositionValue;
	}
	else if (owner->GetVelocity().y > 1.0f)
	{
		effectPosition.x += ShiftPositionValue;
	}
	else if (owner->GetVelocity().y < -1.0f)
	{
		effectPosition.x -= ShiftPositionValue;
	}

}

/*
@fn �G�t�F�N�g�̃|�W�V���������ɂ��炷�֐�
*/
void PlayerSandSmokeMakeManager::ShiftLeftEffectPosition()
{
	// ��xposition��ۑ�
	effectPosition = position;

	// �G�t�F�N�g�̃|�W�V���������炵������o�Ă���悤�Ɍ�����
	if (owner->GetVelocity().x > 1.0f)
	{
		effectPosition.y -= ShiftPositionValue;
	}
	else if (owner->GetVelocity().x < -1.0f)
	{
		effectPosition.y += ShiftPositionValue;
	}
	else if (owner->GetVelocity().y > 1.0f)
	{
		effectPosition.x -= ShiftPositionValue;
	}
	else if (owner->GetVelocity().y < -1.0f)
	{
		effectPosition.x += ShiftPositionValue;
	}
}