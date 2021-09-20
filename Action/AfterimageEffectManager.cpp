#include "AfterimageEffectManager.h"
#include "AfterimageEffect.h"

AfterimageEffectManager::AfterimageEffectManager(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(50)
	, RandValue(100)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	velocity = Vector3::Zero;
	effectPosition = Vector3::Zero;
}

AfterimageEffectManager::~AfterimageEffectManager()
{
}

void AfterimageEffectManager::UpdateGameObject(float _deltaTime)
{
	//// �e�N���X�̃X�e�[�^�X��Active��������
	//if (owner->GetNowState() == PlayerState::PLAYER_STATE_JUMP_ATTACK)
	//{
	//	// particleState��L����
	//	particleState = ParticleState::PARTICLE_ACTIVE;
	//}
	//else
	//{
	//	// particleState�𖳌���
	//	particleState = ParticleState::PARTICLE_DISABLE;
	//}

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

void AfterimageEffectManager::ActiveEffectProcess()
{
	// owner�̃|�W�V�����𓾂�
	effectPosition = owner->GetPosition();

	// �����t���O��true��������
	if (generateFlag == true)
	{
		// �G�t�F�N�g���Y�֐�
		GenerateEffectProcess();

		// �����t���O��false��
		generateFlag = false;
	}

}

void AfterimageEffectManager::GenerateEffectProcess()
{

	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{

		// �����_���Ȓl�𐶐�
		Vector3 randV((rand() % RandValue), (rand() % RandValue), (rand() % RandValue));
		// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
		velocity = randV /** LastCorrection*/;
		velocity.Normalize();

		//// ���x���ꎞ�ۑ��ݒ�
		//Vector3 vel = velocity;

		////�����_���Ȓl��n��
		//vel = vel + randV;
		//// ���ɗ��Ƃ������̂�Z���̓}�C�i�X��
		//vel.z *= -1.0f;

		if (MaxEffects % 2 == 0)
		{
			velocity.x *= -1.0f;
		}
		else if (MaxEffects % 3 == 0)
		{
			velocity.y *= -1.0f;
		}

		new AfterimageEffect(effectPosition, velocity);
	}

}