#include "CrystalEffectManager.h"
#include "CrystalDefaultEffect.h"


CrystalEffectManager::CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor)
	:GameObject(false, Tag::PARTICLE)
	, ShiftPositionZ(100.0f)
	, Radius(150.0f)
	, YawSpeed(0.06f)
	, SecondCorrectionValue(2.0f)
	, CorrectionRandValue(10.0f)
	, RandValue(100)
	, DeltaTimeCorrectionValue(10.0f)
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

CrystalEffectManager::~CrystalEffectManager()
{
}

void CrystalEffectManager::UpdateGameObject(float _deltaTime)
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

	// �A�N�e�B�u�𐧌䂷��J�E���g�𐔂���
	++activeFrameCount;

	// activeFrameCount��8�ȏ�ɂȂ�����
	if (activeFrameCount  >= 8)
	{
		// particleState��L����
		particleState = ParticleState::PARTICLE_ACTIVE;
		// activeFrameCount��������
		activeFrameCount = 0;
	}
	else
	{
		// particleState�𖳌���
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

		// ���x���ꎞ�ۑ�����ϐ�
		Vector3 vel;
		// ���x�p�̃����_���Ȓl�𐶐�
		Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue + SecondCorrectionValue);
		velocity = randV * 0.1f;
		//�����ʒu��ݒ�
		vel = velocity;
		//�����_���Ȓl��n��
		vel = vel + randV;
		vel.x = 0.0f;
		vel.y = 0.0f;

		// �|�W�V�����p�̃����_���Ȓl�����
		Vector3 randPos((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue + SecondCorrectionValue);
		Vector3 pos = randPos * 0.1f;
		pos = pos + position;


		//particle�𐶐�
		new CrystalDefaultEffect(pos, vel,crystalColor);

		break;

	}

}
