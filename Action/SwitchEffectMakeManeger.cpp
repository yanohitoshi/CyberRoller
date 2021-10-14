//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SwitchEffectMakeManeger.h"
#include "SwitchParticleEffect.h"

/*
@fn �R���X�g���N�^
@param	�e�N���X�̃|�C���^
*/
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
	checkOnFlag = false;
	tmpCheckOnFlag = false;
	generateFlag = false;

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
SwitchEffectMakeManeger::~SwitchEffectMakeManeger()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void SwitchEffectMakeManeger::UpdateGameObject(float _deltaTime)
{
	// owner�̃t���O��ۑ�
	checkOnFlag = owner->GetSwitchFlag();

	// �O�t���[���̃t���O�ƍ��̃t���O������Ă�����
	if (checkOnFlag != tmpCheckOnFlag)
	{
		// �p�[�e�B�N����L����
		particleState = ParticleState::PARTICLE_ACTIVE;
		// �����t���O��true��
		generateFlag = true;
	}
	
	// �X�e�[�^�X��Ԃ�����
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
			ActiveEffectProcess();

			// �����t���O��false��
			generateFlag = false;
		}

		// particleState�𖳌�������break
		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}
	
	// �t���O��ۑ�
	tmpCheckOnFlag = checkOnFlag;

}

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
void SwitchEffectMakeManeger::ActiveEffectProcess()
{
	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{
		// �����_���Ȓl�𐶐�
		Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue + SecondCorrectionValue);

		// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
		velocity = randV * LastCorrection;

		// ���x���ꎞ�ۑ�
		Vector3 vel = velocity;

		//�����_���Ȓl��n��
		vel = vel + randV;

		CalculatingDirectionProcess(efectCount, vel);

		// owner�̃|�W�V��������
		position = owner->GetPosition();

		//particle�𐶐�
		new SwitchParticleEffect(position, vel);
	}

}

/*
@fn �G�t�F�N�g���΂������v�Z�����֐�
*/
void SwitchEffectMakeManeger::CalculatingDirectionProcess(int _index, Vector3& _velocity)
{
	// 2�E3�̔{���̍ۑ��x�x�N�g�������ꂼ�ꂘ��������y���t�����ɕϊ�
	// 2�̔{���̎��͂��A3�̔{���̎��͂�
	if (_index % 2 == 0)
	{
		_velocity.x *= -1.0f;
	}
	else if (_index % 3 == 0)
	{
		_velocity.y *= -1.0f;
	}

	// ���낢��ȕ����ɔ�΂���������
	// 4�E6�̔{���̍ۑ��x�x�N�g�������ꂼ�ꂘ��������y���t�����ɕϊ�
	// 6�̔{���̎��͂��A4�̔{���̎��͂�
	if (_index % 4 == 0)
	{
		_velocity.y *= -1.0f;
	}
	else if (_index % 6 == 0)
	{
		_velocity.x *= -1.0f;
	}

}