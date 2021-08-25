//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerSandSmokeMakeManeger.h"
#include "PlayerSandSmokeEffect.h"


PlayerSandSmokeMakeManeger::PlayerSandSmokeMakeManeger(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, GenerateSpeedValue(600.0f)
	, ShiftPositionValue(30.0f)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateCount = 0;
	effectPosition = Vector3::Zero;
}

PlayerSandSmokeMakeManeger::~PlayerSandSmokeMakeManeger()
{
}

void PlayerSandSmokeMakeManeger::UpdateGameObject(float _deltaTime)
{
	// owner�̑��x���Q�Ƃ��ėL���������𔻒�
	// �n�ʂɐڒn���ł��������͂��̑��x��0�łȂ����
	if (owner->GetVelocity().x != 0.0f && owner->GetVelocity().z == 0.0f || 
		owner->GetVelocity().y != 0.0f && owner->GetVelocity().z == 0.0f)
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
		// ������
		generateCount = 0;
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		ActiveEffectProcess();

		break;
	}

}

void PlayerSandSmokeMakeManeger::ActiveEffectProcess()
{
	// owner�̃|�W�V�����𓾂�
	position = owner->GetPosition();

	// �t���[���J�E���g�𐔂���
	++frameCount;

	// 10�t���[����1�x�v���C���[�̈ړ����x�����ȏゾ������
	if (frameCount % 10 == 0 && owner->GetVelocity().x > GenerateSpeedValue ||
		frameCount % 10 == 0 && owner->GetVelocity().y > GenerateSpeedValue ||
		frameCount % 10 == 0 && owner->GetVelocity().x < -GenerateSpeedValue||
		frameCount % 10 == 0 && owner->GetVelocity().y < -GenerateSpeedValue )
	{
		GenerateEffectProcess();
	}


}

void PlayerSandSmokeMakeManeger::GenerateEffectProcess()
{
	// �����������𐔂���
	++generateCount;

	// �J�E���g��2�̔{���̎��͉E����
	if (generateCount % 2 == 0)
	{
		ShiftRightEffectPosition();
	}
	else
	{
		ShiftLeftEffectPosition();
	}

	// �I�[�i�[�̑��x�����炤
	Vector3 vel = owner->GetVelocity();

	// ���K��
	vel.Normalize();

	// ���x���t�����ɂ���
	vel = vel * -1.0f;

	// particle�𐶐�
	new PlayerSandSmokeEffect(effectPosition, vel, true);
}

void PlayerSandSmokeMakeManeger::ShiftRightEffectPosition()
{
	// ��xposition��ۑ�
	effectPosition = position;

	// �G�t�F�N�g�̃|�W�V���������炵������o�Ă���悤�Ɍ�����
	if (owner->GetVelocity().x > 1.0f)
	{
		effectPosition.y += ShiftPositionValue;
	}
	else if (owner->GetVelocity().x < -1.0f)
	{
		effectPosition.y -= ShiftPositionValue;
	}
	else if (owner->GetVelocity().y > 1.0f)
	{
		effectPosition.x += ShiftPositionValue;
	}
	else if (owner->GetVelocity().y < -1.0f)
	{
		effectPosition.x -= ShiftPositionValue;
	}

}

void PlayerSandSmokeMakeManeger::ShiftLeftEffectPosition()
{
	// ��xposition��ۑ�
	effectPosition = position;

	// �G�t�F�N�g�̃|�W�V���������炵������o�Ă���悤�Ɍ�����
	if (owner->GetVelocity().x > 1.0f)
	{
		effectPosition.y -= ShiftPositionValue;
	}
	else if (owner->GetVelocity().x < -1.0f)
	{
		effectPosition.y += ShiftPositionValue;
	}
	else if (owner->GetVelocity().y > 1.0f)
	{
		effectPosition.x -= ShiftPositionValue;
	}
	else if (owner->GetVelocity().y < -1.0f)
	{
		effectPosition.x += ShiftPositionValue;
	}
}
