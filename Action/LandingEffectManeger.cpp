#include "LandingEffectManeger.h"
#include "LandingEffect.h"
#include "PlayerObject.h"

LandingEffectManeger::LandingEffectManeger(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(8)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	tmpVelZ = 0.0f;
	generateFlag = false;
}

LandingEffectManeger::~LandingEffectManeger()
{
}

void LandingEffectManeger::UpdateGameObject(float _deltaTime)
{
	// �O�̃t���[����Z���̑��x��0.0f�łȂ����̃t���[���ł�Z���̑��x0.0f�ł��W�����v�t���O��false��������
	if (owner->GetVelocity().z == 0.0f && tmpVelZ != 0.0f && PlayerObject::GetChackJumpFlag() == false)
	{
		// �p�[�e�B�N����L����
		particleState = ParticleState::PARTICLE_ACTIVE;
		// �����t���O��true��
		generateFlag = true;
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
		break;
		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �����t���O��true�̎�
		if (generateFlag == true)
		{
			// owner�̃|�W�V�����𓾂�
			position = owner->GetPosition();

			// 8����
			for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
			{
				// �������ɓ������̂ł��ꂼ��ɕ����x�N�g����n��
				if (efectCount == 0)
				{
					velocity = Vector3(1.0f,0.0f,0.0f);
				}
				if (efectCount == 1)
				{
					velocity = Vector3(0.0f,1.0f,0.0f);
				}
				if (efectCount == 2)
				{
					velocity = Vector3(-1.0f, 0.0f, 0.0f);
				}
				if (efectCount == 3)
				{
					velocity = Vector3(0.0f, -1.0f, 0.0f);
				}
				if (efectCount == 4)
				{
					velocity = Vector3(1.0f, 1.0f, 0.0f);
				}
				if (efectCount == 5)
				{
					velocity = Vector3(1.0f, -1.0f, 0.0f);
				}
				if (efectCount == 6)
				{
					velocity = Vector3(-1.0f, 1.0f, 0.0f);
				}
				if (efectCount == 7)
				{
					velocity = Vector3(-1.0f, -1.0f, 0.0f);
				}

				//particle�𐶐�
				new LandingEffect(position, velocity);
			}
			// �����t���O��false��
			generateFlag = false;
		}

		// particleState������
		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}

	// owner��Z�����x��ۑ�
	tmpVelZ = owner->GetVelocity().z;

}
