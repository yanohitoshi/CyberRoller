//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CrystalEffectManager.h"
#include "CrystalDefaultEffect.h"
#include "PlayerObject.h"
#include "MoveWallBlock.h"

/*
@fn �R���X�g���N�^
@param	�e�N���X�̃|�C���^
@param	���F������pTag
@param �V�[���Ō�̓����ǂ̃|�C���^
*/
CrystalEffectManager::CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor, MoveWallBlock* _lastMoveWall)
	:GameObject(false, Tag::PARTICLE)
	, ShiftPositionZ(100.0f)
	, Radius(150.0f)
	, YawSpeed(0.06f)
	, SecondCorrectionValue(2.0f)
	, CorrectionRandValue(10.0f)
	, RandValue(100)
	, DeltaTimeCorrectionValue(10.0f)
	, LastCorrection(0.1f)
	, lastMoveWallBlock(_lastMoveWall)
{
	// �����o�[�ϐ��̏�����	
	crystalColor = _crystalColor;
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = owner->GetPosition();
	position.z -= ShiftPositionZ;
	frameCount = 0;
	activeFrameCount = 0;
	tmpMovePos = Vector3::Zero;
	isEffectActive = false;

	// �F���ƂɃ}�l�[�W���[�N���X�𐶐����邽�߂��ꂼ��ɏꍇ������������
	if (crystalColor == CrystalColor::WHITE)
	{
		// �����p�x��ݒ�
		yaw = Math::ToRadians(0);
	}
	else if (crystalColor == CrystalColor::RED)
	{
		// �����p�x��ݒ�
		yaw = Math::ToRadians(90);
	}
	else if (crystalColor == CrystalColor::BLUE)
	{
		// �����p�x��ݒ�
		yaw = Math::ToRadians(180);
	}
	else if (crystalColor == CrystalColor::GREEN)
	{
		// �����p�x��ݒ�
		yaw = Math::ToRadians(270);
	}
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CrystalEffectManager::~CrystalEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CrystalEffectManager::UpdateGameObject(float _deltaTime)
{
	// �G�t�F�N�g�𔭐������Ȃ���Ԃ̎�
	if (!isEffectActive)
	{
		// �Ō�̕ǂ��J���Ă��邩�̃t���O�����炤
		//isEffectActive = lastMoveWallBlock->GetOpenFlag();
		isEffectActive = true;
	}


	// activeFrameCount��8�ȏ�ɂȂ�����
	if (isEffectActive)
	{
		// particleState��L����
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particleState�𖳌���
		particleState = ParticleState::PARTICLE_DISABLE;
		// activeFrameCount��������
		activeFrameCount = 0;
	}

	// �p�[�e�B�N���̏�Ԃ�����
	switch (particleState)
	{
		// ������Ԃ�������break
	case (PARTICLE_DISABLE):
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		// �G�t�F�N�g����
		ActiveEffectProcess(_deltaTime);
		break;
	}
}

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CrystalEffectManager::ActiveEffectProcess(float _deltaTime)
{
	// �����ꏊ�̉�]����
	RotationProcess(_deltaTime);

	// �A�N�e�B�u�𐧌䂷��J�E���g�𐔂���
	++activeFrameCount;

	if (activeFrameCount % 8 == 0)
	{
		GenerateEffectProcess();
	}
}

/*
@fn �G�t�F�N�g���Y�����֐�
*/
void CrystalEffectManager::GenerateEffectProcess()
{
	// ���x���ꎞ�ۑ�����ϐ�
	Vector3 vel;
	// ���x�p�̃����_���Ȓl�𐶐���x����y���̑��x��0.0f�ɌŒ�
	Vector3 randV(0.0f, 0.0f, (rand() % RandValue) / CorrectionRandValue + SecondCorrectionValue);
	// �l���傫������̂ōŌ�̕␳�������đ��x�ɑ��
	velocity = randV * LastCorrection;
	//���x��ݒ�
	vel = velocity + randV;

	// �|�W�V�����p�̃����_���Ȓl�����
	Vector3 randPos((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue + SecondCorrectionValue);
	// �l���傫������̂ōŌ�̕␳��������
	Vector3 pos = randPos * LastCorrection;
	//�����_���Ȓl��n��
	pos = pos + position;

	//particle�𐶐�
	new CrystalDefaultEffect(pos, vel, crystalColor);
}

/*
@fn �|�W�V�����̉�]�����֐�
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CrystalEffectManager::RotationProcess(float _deltaTime)
{
	// ��]���x��ǉ�
	yaw += YawSpeed;

	// ��]�p��x��y�|�W�V������ݒ�
	tmpMovePos.x = Radius * cosf(yaw) + owner->GetPosition().x;
	tmpMovePos.y = Radius * sinf(yaw) + owner->GetPosition().y;
	// z���͌Œ�
	tmpMovePos.z = owner->GetPosition().z - ShiftPositionZ;
	// �v�Z�����|�W�V�����ƍ��̃|�W�V�����Ő��`�ۊǂ����|�W�V�����ɑ��
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaTimeCorrectionValue);
	// �|�W�V�������X�V
	SetPosition(position);
}