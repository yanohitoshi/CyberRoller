//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateTracking.h"

/*
@fn �R���X�g���N�^
*/
EnemyObjectStateTracking::EnemyObjectStateTracking()
	:TrackingLengthValue(50.0f)
{
}

/*
@fn �f�X�g���N�^
*/
EnemyObjectStateTracking::~EnemyObjectStateTracking()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState EnemyObjectStateTracking::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// �ǐՑΏۂ��珉���|�W�V�����ւƌ������x�N�g�����v�Z
	Vector3 trackingObjectToFirstPos = firstPosition - _owner->GetAttackObjectPosition();
	// �I�[�i�[�̃|�W�V�������珉���|�W�V�����ւƌ������x�N�g�����v�Z
	Vector3 ownerObjectToFirstPos = firstPosition - _owner->GetPosition();

	// �ǐՑΏۂ��珉���|�W�V�����ւ̃x�N�g���̒���
	float trackingObjectToFirstPosLength = trackingObjectToFirstPos.LengthSq();
	// �I�[�i�[�̃|�W�V�������珉���|�W�V�����ւ̃x�N�g���̒���
	float ownerObjectToFirstPosLength = ownerObjectToFirstPos.LengthSq();

	// �ǐՃ^�[�Q�b�g������Ƃ�
	if (_owner->GetIsTracking())
	{
		// �I�[�i�[����ǐՑΏۂ֌������x�N�g��
		trackingRotationVec = _owner->GetAttackObjectPosition() - _owner->GetPosition();
		trackingRotationVec.z = 0.0f;
		float ownerPosToTrackingObjectLength = trackingRotationVec.Length();

		// �K��l�܂ŋ߂Â��܂Œǐ�
		if (ownerPosToTrackingObjectLength >= TrackingLengthValue)
		{
			if (!Math::NearZero(trackingRotationVec.Length()))
			{
				trackingRotationVec.Normalize();
			}

			velocity = trackingRotationVec * moveSpeed;

			// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
			_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

			RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
		}
		else
		{
			velocity = Vector3::Zero;
			// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
			_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
		}
	}
	else if (!_owner->GetIsTracking()) // �ǐՃ^�[�Q�b�g�����Ȃ��Ȃ����Ƃ�
	{
		// �����x�N�g���̒�������߂�ۂɃ^�[�����[�V�������͂��ނ�����
		if (ownerObjectToFirstPosLength > trackingObjectToFirstPosLength)
		{
			state = EnemyState::ENEMY_STATE_REPOSITION;
		}
		else
		{
			state = EnemyState::ENEMY_STATE_TURN;
		}
	}
	else
	{
		velocity = Vector3::Zero;
		// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void EnemyObjectStateTracking::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_TRACKING;
	_owner->SetState(State::Active);

	// �����|�W�V�����𓾂�
	firstPosition = _owner->GetFirstPosition();

	// �ړ����x�𓾂�
	moveSpeed = _owner->GetMoveSpeed();

	// �ǐՕ������v�Z
	trackingRotationVec = _owner->GetAttackObjectPosition() - _owner->GetPosition();
	// �㉺�ړ��͂����Ȃ��̂�0�ŌŒ�
	trackingRotationVec.z = 0.0f;

	if (!Math::NearZero(trackingRotationVec.Length()))
	{
		// ���K��
		trackingRotationVec.Normalize();
	}

	// ��]����
	RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
}
