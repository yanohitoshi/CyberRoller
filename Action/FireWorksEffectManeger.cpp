#include "FireWorksEffectManeger.h"
#include "FierWorksEffect.h"
FireWorksEffectManeger::FireWorksEffectManeger(GameObject* _owner)
	:GameObject(false, Tag::PARTICLE)
	, CorrectionRandValue(10.0f)
	, RandValue(100)
	, MaxEffects(24)
	, LastCorrection(0.1f)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	crystalColor = CrystalColor::WHITE;
}

FireWorksEffectManeger::~FireWorksEffectManeger()
{
}

void FireWorksEffectManeger::UpdateGameObject(float _deltaTime)
{
	// owner�̃X�e�[�^�X��dead�ɂȂ�����
	if (owner->GetState() == State::Dead)
	{
		// particleState��L������
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particleState�𖳌�����
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

		// �G�t�F�N�g�̐���
		ActiveEffectProcess();

		break;

	}

}

void FireWorksEffectManeger::ActiveEffectProcess()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();

	// �����t���O��true��������
	if (generateFlag == true)
	{
		// �G�t�F�N�g���Y�֐�
		GenerateEffectProcess();

		// �����t���O��false��
		generateFlag = false;
	}

}

void FireWorksEffectManeger::GenerateEffectProcess()
{
	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{

		// �����_���Ȓl�𐶐�
		Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue);
		// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
		velocity = randV * LastCorrection;

		// ���x���ꎞ�ۑ��ݒ�
		Vector3 vel = velocity;

		//�����_���Ȓl��n��
		vel = vel + randV;
		// ���ɗ��Ƃ������̂�Z���̓}�C�i�X��
		vel.z *= -1.0f;

		// �G�t�F�N�g�̐F�̐ݒ�ƌ����𒲐�
		SelectEffectColorProcess(efectCount, vel);

		//particle�𐶐�
		new FierWorksEffect(position, vel, crystalColor);
	}
}

void FireWorksEffectManeger::SelectEffectColorProcess(int _index,Vector3& _velocity)
{
	// ���낢��ȕ����ɂ��낢��ȐF�Ŕ�΂������̂�
	// 2�̔{���̎��͂��������Ƀ}�C�i�X���|���ĐF��Ԃɐݒ�
	if (_index % 2 == 0)
	{
		_velocity.x *= -1.0f;
		crystalColor = CrystalColor::RED;
	}

	// 4�̔{���̎���y�������Ƀ}�C�i�X���|���ĐF��ɐݒ�
	if (_index % 4 == 0)
	{
		_velocity.y *= -1.0f;
		crystalColor = CrystalColor::BLUE;
	}

	// 6�̔{���̎���y�������Ƀ}�C�i�X���|���ĐF��΂ɐݒ�
	if (_index % 6 == 0)
	{
		_velocity.y *= -1.0f;
		crystalColor = CrystalColor::GREEN;
	}

	// 8�̔{���̎��͂��������Ƀ}�C�i�X���|���ĐF�𔒂ɐݒ�
	if (_index % 8 == 0)
	{
		_velocity.x *= -1.0f;
		crystalColor = CrystalColor::WHITE;
	}

}
