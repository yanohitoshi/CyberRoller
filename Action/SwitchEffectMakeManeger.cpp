#include "SwitchEffectMakeManeger.h"
#include "SwitchParticleEffect.h"

SwitchEffectMakeManeger::SwitchEffectMakeManeger(GameObject* _owner)
	: GameObject(false,Tag::PARTICLE)
	, SecondCorrectionValue(2.0f)
	, CorrectionRandValue(10.0f)
	, RandValue(100)
	, MaxEffects(15)
	, LastCorrection(0.1f)
{
	// �����o�[�ϐ��̏�����	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = owner->GetPosition();
	ChackOnFlag = false;
	tmpChackOnFlag = false;
	generateFlag = false;

}

SwitchEffectMakeManeger::~SwitchEffectMakeManeger()
{
}

void SwitchEffectMakeManeger::UpdateGameObject(float _deltaTime)
{
	// owner�̃t���O��ۑ�
	ChackOnFlag = owner->GetSwitchFlag();

	// �O�t���[���̃t���O�ƍ��̃t���O������Ă�����
	if (ChackOnFlag != tmpChackOnFlag)
	{
		// �p�[�e�B�N����L����
		particleState = ParticleState::PARTICLE_ACTIVE;
		// �����t���O��true��
		generateFlag = true;
	}
	
	// �p�[�e�B�N���̏�Ԃ�����
	switch (particleState)
	{
		// ������Ԃ�������break
	case (PARTICLE_DISABLE):
		break;
		// �L����Ԃ�������
	case PARTICLE_ACTIVE:


		//particle����������t���[���̏�����������
		if (generateFlag == true)
		{
			for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
			{
				// �����_���Ȓl�𐶐�
				Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue)/ CorrectionRandValue + SecondCorrectionValue);
				
				// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
				velocity = randV * LastCorrection;

				// ���x���ꎞ�ۑ�
				Vector3 vel = velocity;

				//�����_���Ȓl��n��
				vel = vel + randV;

				// 2�E3�̔{���̍ۑ��x�x�N�g�������ꂼ�ꂘ��������y���t�����ɕϊ�
				// 2�̔{���̎��͂��A3�̔{���̎��͂�
				if (efectCount % 2 == 0)
				{
					vel.x *= -1.0f;
				}
				else if (efectCount % 3 == 0)
				{
					vel.y *= -1.0f;
				}
				
				// ���낢��ȕ����ɔ�΂���������
				// 4�E6�̔{���̍ۑ��x�x�N�g�������ꂼ�ꂘ��������y���t�����ɕϊ�
				// 6�̔{���̎��͂��A4�̔{���̎��͂�
				if (efectCount % 4 == 0)
				{
					vel.y *= -1.0f;
				}
				else if (efectCount % 6 == 0)
				{
					vel.x *= -1.0f;
				}

				// owner�̃|�W�V��������
				position = owner->GetPosition();
				//particle�𐶐�
				new SwitchParticleEffect(position, vel);
			}

			// �����t���O��false��
			generateFlag = false;
		}

		// particleState�𖳌�������break
		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}
	
	// �t���O��ۑ�
	tmpChackOnFlag = ChackOnFlag;

}

