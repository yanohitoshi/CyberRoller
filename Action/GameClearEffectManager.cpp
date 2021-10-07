//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameClearEffectManager.h"
#include "GameClearEffect.h"

/*
@fn �R���X�g���N�^
@param	_owner �e�N���X�̃|�C���^
*/
GameClearEffectManager::GameClearEffectManager(GameObject* _owner)
	:GameObject(false, Tag::PARTICLE)
	, SecondCorrectionValue(5.0f)
	, CorrectionRandValue(10.0f)
	, RandValue(300)
	, MaxEffects(10)
	, MaxGenerateCount(8)
	, GenerateHeight(5500.0f)
	, GenerateFrequency(15)
	, LastCorrection(0.1f)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateCount = 0;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
GameClearEffectManager::~GameClearEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void GameClearEffectManager::UpdateGameObject(float _deltaTime)
{
	// owner�̑��x������Z����œ����Ă��Ă���owner�̍��������l�ȏ�ɂȂ�����ACTIVE�ɂ���
	if (owner->GetVelocity().z != 0 && owner->GetPosition().z >= GenerateHeight)
	{
		// particle��L����
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particle�𖳌���
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

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
*/
void GameClearEffectManager::ActiveEffectProcess()
{
	// �t���[���J�E���g�𐔂���
	++frameCount;
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();

	// �t���[���J�E���g��15�̔{���̎��������J�E���g��8�ȉ��̎�
	if (frameCount % GenerateFrequency == 0 && generateCount <= MaxGenerateCount)
	{
		// �G�t�F�N�g�̐��Y����
		GenerateEffectProcess();

		// 1���[�v�I����Ă���J�E���g�ǉ�
		++generateCount;
	}
}

/*
@fn �G�t�F�N�g���Y�����֐�
*/
void GameClearEffectManager::GenerateEffectProcess()
{
	// 10�̃G�t�F�N�g�𐶐�
	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{
		// �����_���Ȓl�𐶐�
		Vector3 randV((rand() % RandValue) / CorrectionRandValue - SecondCorrectionValue, (rand() % RandValue) / CorrectionRandValue - SecondCorrectionValue, 0);
		// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
		velocity = randV * LastCorrection;
		// ���x���ꎞ�ۑ��ݒ�
		Vector3 vel = velocity;

		//�����_���Ȓl��n��
		vel = vel + randV;
		// �U�����㉺�ɗ��Ƃ������̂Ń}�C�i�X���|����
		vel.z *= -1.0f;

		CalculatingDirectionProcess(efectCount, vel);

		//particle�𐶐�
		new GameClearEffect(position, vel);
	}

}

/*
@fn �G�t�F�N�g���΂������v�Z�����֐�
@param _index���ڂ̃G�t�F�N�g��
@param _velocity ���x
*/
void GameClearEffectManager::CalculatingDirectionProcess(int _index, Vector3& _velocity)
{
	// ���낢��ȕ����ɔ�΂���������
	// 2�E3�̔{���̍ۑ��x�x�N�g�������ꂼ�ꂘ�������͂����t�����ɕϊ�
	// 2�̔{���̎��͂��A3�̔{���̎��͂�
	if (_index % 2 == 0)
	{
		_velocity.x *= -1.0f;
	}
	else if (_index % 3 == 0)
	{
		_velocity.y *= -1.0f;
	}

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