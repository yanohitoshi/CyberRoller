#include "TrackingEnemyStateTracking.h"

TrackingEnemyStateTracking::TrackingEnemyStateTracking()
{
}

TrackingEnemyStateTracking::~TrackingEnemyStateTracking()
{
}

EnemyState TrackingEnemyStateTracking::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// �ǐՑΏۂ��珉���|�W�V�����ւƌ������x�N�g�����v�Z
	Vector3 trackingObjectToFirstPos = firstPosition - trackingObject->GetPosition();
	// �I�[�i�[�̃|�W�V�������珉���|�W�V�����ւƌ������x�N�g�����v�Z
	Vector3 ownerObjectToFirstPos = firstPosition - _owner->GetPosition();

	// �ǐՑΏۂ��珉���|�W�V�����ւ̃x�N�g���̒���
	float trackingObjectToFirstPosLength = trackingObjectToFirstPos.LengthSq();
	// �I�[�i�[�̃|�W�V�������珉���|�W�V�����ւ̃x�N�g���̒���
	float ownerObjectToFirstPosLength = ownerObjectToFirstPos.LengthSq();

	if (_owner->GetIsTracking())
	{
		// �I�[�i�[����ǐՑΏۂ֌������x�N�g��
		trackingRotationVec =  trackingObject->GetPosition() - _owner->GetPosition();
		trackingRotationVec.z = 0.0f;
		float ownerPosToTrackingObjectLength = trackingRotationVec.Length();

		if (ownerPosToTrackingObjectLength >= 50.0f)
		{
			trackingRotationVec.Normalize();
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
	else if (!_owner->GetIsTracking())
	{
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

void TrackingEnemyStateTracking::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_TRACKING;
	_owner->SetState(State::Active);

	firstPosition = _owner->GetFirstPosition();

	trackingObject = _owner->GetTrackingObject();
	moveSpeed = _owner->GetMoveSpeed();
	trackingRotationVec = trackingObject->GetPosition() - _owner->GetPosition();
	trackingRotationVec.z = 0.0f;
	trackingRotationVec.Normalize();

	RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
}
