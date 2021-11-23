//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FallExplosionObjectStateRespawn.h"
#include "MeshComponent.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return ExplosionObjectState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
ExplosionObjectState FallExplosionObjectStateRespawn::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ���Ԍv��
	++respawnCount;

	// ���Ԃ�������
	if (respawnCount > RespownTime)
	{
		// ������
		_owner->SetIsHitExplosionObject(false);
		meshComponent->SetVisible(true);
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
		_owner->SetRotation(Quaternion::Identity);
		_owner->SetScaleZ(5.0f);
		state = ExplosionObjectState::IDLE;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void FallExplosionObjectStateRespawn::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	state = ExplosionObjectState::RESPAWN;
	firstPosition = _owner->GetFirstPosition();
	respawnCount = 0;
	meshComponent = _owner->GetMeshComponent();
	_owner->SetIsExplode(false);
	_owner->SetState(State::Disabling);

	// �����_���ȃ|�W�V�������Z�b�g
	SetRandPosition(_owner);
	// �����_���ȗ������x���Z�b�g
	SetRandFallSpeed(_owner);
}

/*
@fn �����_���ȃ|�W�V�������Z�b�g
@param	_owner �e�N���X�̃|�C���^
*/
void FallExplosionObjectStateRespawn::SetRandPosition(ExplosionObjectBase* _owner)
{
	Vector3 fallArea = Vector3::Zero;

	// �����G���A���Ń����_���̒l���擾
	fallArea = _owner->GetFallArea();
	float randValueX = (float)(rand() % (int)(fallArea.x / 2.0f));
	float randValueY = (float)(rand() % (int)(fallArea.y / 2.0f));

	// 0�`3�܂ł̃����_�����擾
	int plus_minus_value = rand() % 4;

	// ���|�W�V�����ϐ��ɏ����ʒu����
	Vector3 tmpPosition = firstPosition;

	// �����_���̒l������x��y���̃v���X�}�C�i�X��ݒ�
	switch (plus_minus_value)
	{
	case(0):
		tmpPosition.x += randValueX;
		tmpPosition.y += randValueY;
		break;
	case(1):
		tmpPosition.x += randValueX;
		tmpPosition.y -= randValueY;
		break;
	case(2):
		tmpPosition.x -= randValueX;
		tmpPosition.y += randValueY;
		break;
	case(3):
		tmpPosition.x -= randValueX;
		tmpPosition.y -= randValueY;
		break;
	}
	_owner->SetPosition(tmpPosition);
}

/*
@fn �����_���ȗ������x���Z�b�g
@param	_owner �e�N���X�̃|�C���^
*/
void FallExplosionObjectStateRespawn::SetRandFallSpeed(ExplosionObjectBase* _owner)
{
	_owner->SetFallSpeed((float)(rand() % (int)(MaxFallSpeed) +LowestFallSpeed));
}
