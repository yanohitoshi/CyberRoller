#include "SandSmokeMakeManeger.h"
#include "ParticleEffectBase.h"
#include "SandSmokeParticle.h"

SandSmokeMakeManeger::SandSmokeMakeManeger(GameObject* _owner)
	:GameObject(false,Tag::PARTICLE)
	, ShiftPositionX(40.0f)
	, MaxShiftPositionY(1500.0f)
	, MinShiftPositionY(900.0f)
	, BigWallSize(1500.0f)
	, SmallWallSize(1100.0f)
	, RandValueX(500)
	, BigRandValueY(40000)
	, SmallRandValueY(20000)
	, RandValueZ(100)
	, CorrectionRandValue(10.0f)
	, GenerateFrequency(3)
	, SmallWallMaxEffect(10)
	, BigWallMaxEffect(20)
	, LastCorrection(0.1f)
	, LowestVelValue(Vector3(-2.0f,0.0f,1.0f))
{
	// �����o�[�ϐ��̏�����
	owner = _owner;
	position = owner->GetPosition();
	ownerSize = owner->GetScaleVec();
	frameCount = 0;
	isBigWall = false;

	// ���S�ɐݒu���邽�߂ɏ������炷
	position.x -= ShiftPositionX;

	// owner�̑傫�������Ă��ꂼ��̐��l�����炵�Ē��S�ɐݒu�i������2��Ȃ̂ł������Ă邪���ǂ̗]�n����j
	// �������T�C�Y�̎�
	if (ownerSize.y == SmallWallSize)
	{
		position.y -= MinShiftPositionY;
	}
	// �傫���T�C�Y�̎�
	if (ownerSize.y == BigWallSize)
	{
		position.y -= MaxShiftPositionY;
		isBigWall = true;
	}
}

SandSmokeMakeManeger::~SandSmokeMakeManeger()
{
}

void SandSmokeMakeManeger::UpdateGameObject(float _deltaTime)
{
	// owner�̑��x�����ē����Ă��鎞
	if (owner->GetVelocity().z != 0)
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
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �t���[���J�E���g�𐔂���
		++frameCount;

		// �������T�C�Y�̎�
		if (isBigWall)
		{
			CreateBigWallEffect();
		}
		else
		{
			CreateSmallWallEffect();
		}

		break;
	}


}

void SandSmokeMakeManeger::CreateBigWallEffect()
{
	// 3�t���[���Ɉ�x
	if (frameCount % GenerateFrequency == 0)
	{
		// �G�t�F�N�g��20����
		for (int efectCount = 0; efectCount < BigWallMaxEffect; efectCount++)
		{
			// �����_���Ȓl�𐶐�
			Vector3 randV((rand() % RandValueX) / CorrectionRandValue, (rand() % BigRandValueY) / CorrectionRandValue, (rand() % RandValueZ) / CorrectionRandValue);

			// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
			velocity = randV * LastCorrection;

			// �����_���̒l�ɑ��x�̍Œ�l��ǉ�
			velocity.x += LowestVelValue.x;
			velocity.y += LowestVelValue.y;
			velocity.z += LowestVelValue.z;

			//�����ʒu��ݒ�
			Vector3 pos = position;
			//�����_���Ȓl��n��
			pos = pos + randV;
			//particle�𐶐�
			new SandSmokeParticle(pos, velocity);

		}
	}

}

void SandSmokeMakeManeger::CreateSmallWallEffect()
{
	// 3�t���[���Ɉ�x
	if (frameCount % GenerateFrequency == 0)
	{
		// �G�t�F�N�g��10����
		for (int efectCount = 0; efectCount < SmallWallMaxEffect; efectCount++)
		{
			// �����_���Ȓl�𐶐�
			Vector3 randV((rand() % RandValueX) / CorrectionRandValue, (rand() % SmallRandValueY) / CorrectionRandValue, (rand() % RandValueZ) / CorrectionRandValue);

			// �����_���ŏo���l�ɕ␳��������
			velocity = randV * LastCorrection;

			// �����_���̒l�ɑ��x�̍Œ�l��ǉ�
			velocity.x += LowestVelValue.x;
			velocity.y += LowestVelValue.y;
			velocity.z += LowestVelValue.z;

			//�����ʒu��ݒ�
			Vector3 pos = position;
			//�����_���Ȓl��n��
			pos = pos + randV;
			//particle�𐶐�
			new SandSmokeParticle(pos, velocity);

		}
	}
}


