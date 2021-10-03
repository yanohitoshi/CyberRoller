#include "TrackingEnemyStateTracking.h"

TrackingEnemyStateTracking::TrackingEnemyStateTracking()
{
}

TrackingEnemyStateTracking::~TrackingEnemyStateTracking()
{
}

EnemyState TrackingEnemyStateTracking::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	Vector3 firstPosToTrackingObject = firstPosition - trackingObject->GetPosition();
	Vector3 firstPosToOwnerObject = firstPosition - _owner->GetPosition();

	float firstPosToTrackingObjectLength = firstPosToTrackingObject.LengthSq();
	float firstPosToOwnerObjectLength = firstPosToOwnerObject.LengthSq();

	if (_owner->GetIsTracking() && !_owner->GetIsOtherEnemyHit())
	{
		trackingRotationVec =  trackingObject->GetPosition() - _owner->GetPosition();
		trackingRotationVec.z = 0.0f;
		trackingRotationVec.Normalize();
		velocity = trackingRotationVec * moveSpeed;
		// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

		RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
	}
	else if (!_owner->GetIsTracking())
	{
		if (firstPosToOwnerObjectLength > firstPosToTrackingObjectLength)
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
