//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "JumpAttackEffectManager.h"
#include "JumpAttackEffect.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
JumpAttackEffectManager::JumpAttackEffectManager(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	effectPosition = Vector3::Zero;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
JumpAttackEffectManager::~JumpAttackEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void JumpAttackEffectManager::UpdateGameObject(float _deltaTime)
{
	// �e�N���X�̃X�e�[�^�X��Active��������
	if (owner->GetState() == State::Active)
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
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		ActiveEffect();
		break;
	}

}

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
void JumpAttackEffectManager::ActiveEffect()
{
	GenerateEffect();
}

/*
@fn �G�t�F�N�g���Y�����֐�
*/
void JumpAttackEffectManager::GenerateEffect()
{
	// owner�̃|�W�V�����𓾂�
	effectPosition = owner->GetPosition();
	// particle�𐶐�
	new JumpAttackEffect(effectPosition, Vector3::Zero);
}
