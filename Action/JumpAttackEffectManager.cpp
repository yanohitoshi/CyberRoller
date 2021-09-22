#include "JumpAttackEffectManager.h"
#include "JumpAttackEffect.h"

JumpAttackEffectManager::JumpAttackEffectManager(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateCount = 0;
	effectPosition = Vector3::Zero;
}

JumpAttackEffectManager::~JumpAttackEffectManager()
{
}

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
		frameCount = 0;
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		ActiveEffectProcess();
		break;
	}

}

void JumpAttackEffectManager::ActiveEffectProcess()
{
	GenerateEffectProcess();
}

void JumpAttackEffectManager::GenerateEffectProcess()
{
	++frameCount;
	if (frameCount % 2 == 0)
	{
		//// owner�̃|�W�V�����𓾂�
		//effectPosition = owner->GetPosition();
		//// particle�𐶐�
		//new JumpAttackEffect(effectPosition, Vector3::Zero);
	}
	// owner�̃|�W�V�����𓾂�
	effectPosition = owner->GetPosition();
	// particle�𐶐�
	new JumpAttackEffect(effectPosition, Vector3::Zero);
}
