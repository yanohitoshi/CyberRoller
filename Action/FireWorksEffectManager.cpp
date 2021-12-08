//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FireWorksEffectManager.h"
#include "FierWorksEffect.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
FireWorksEffectManager::FireWorksEffectManager(GameObject* _owner)
	:GameObject(false, Tag::PARTICLE)
	, CorrectionRandValue(10.0f)
	, RandValue(100)
	, MaxEffects(24)
	, LastCorrection(0.1f)
	, TowFrequency(2)
	, FourFrequency(4)
	, SixFrequency(6)
	, EightFrequency(8)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	crystalColor = CrystalColor::WHITE;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
FireWorksEffectManager::~FireWorksEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void FireWorksEffectManager::UpdateGameObject(float _deltaTime)
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
		ActiveEffect();
		break;
	}
}

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
void FireWorksEffectManager::ActiveEffect()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();

	// �����t���O��true��������
	if (generateFlag == true)
	{
		// �G�t�F�N�g���Y�֐�
		GenerateEffect();

		// �����t���O��false��
		generateFlag = false;
	}

}

/*
@fn �G�t�F�N�g���Y�����֐�
*/
void FireWorksEffectManager::GenerateEffect()
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
		SelectEffectColor(efectCount, vel);

		//particle�𐶐�
		new FierWorksEffect(position, vel, crystalColor);
	}
}

/*
@fn �G�t�F�N�g�̐F�ƌ�����ݒ肷��֐�
*/
void FireWorksEffectManager::SelectEffectColor(int _index,Vector3& _velocity)
{
	// ���낢��ȕ����ɂ��낢��ȐF�Ŕ�΂������̂�
	// 2�̔{���̎��͂��������Ƀ}�C�i�X���|���ĐF��Ԃɐݒ�
	if (_index % TowFrequency == 0)
	{
		_velocity.x *= -1.0f;
		crystalColor = CrystalColor::RED;
	}

	// 4�̔{���̎���y�������Ƀ}�C�i�X���|���ĐF��ɐݒ�
	if (_index % FourFrequency == 0)
	{
		_velocity.y *= -1.0f;
		crystalColor = CrystalColor::BLUE;
	}

	// 6�̔{���̎���y�������Ƀ}�C�i�X���|���ĐF��΂ɐݒ�
	if (_index % SixFrequency == 0)
	{
		_velocity.y *= -1.0f;
		crystalColor = CrystalColor::GREEN;
	}

	// 8�̔{���̎��͂��������Ƀ}�C�i�X���|���ĐF�𔒂ɐݒ�
	if (_index % EightFrequency == 0)
	{
		_velocity.x *= -1.0f;
		crystalColor = CrystalColor::WHITE;
	}
}
