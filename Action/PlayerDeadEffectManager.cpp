//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerDeadEffectManager.h"
#include "PlayerDeadEffect.h"
#include "PlayerObject.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
PlayerDeadEffectManager::PlayerDeadEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, PositionOffset(50.0f)
	, ShiftPositionZ(40.0f)
	, GenerationTime(30)
	, KnockBackOffset(30.0f)
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
PlayerDeadEffectManager::~PlayerDeadEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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
		ActiveEffect();
		break;
	}
}

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
void PlayerDeadEffectManager::ActiveEffect()
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
			GenerateEffect();
		}
	}
}

/*
@fn �G�t�F�N�g���Y�����֐�
*/
void PlayerDeadEffectManager::GenerateEffect()
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
	distance *= KnockBackOffset;
	//particle�𐶐�
	new PlayerDeadEffect(owner, position, distance);
}