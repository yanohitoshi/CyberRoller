#include "TrackingEnemyStateTracking.h"

TrackingEnemyStateTracking::TrackingEnemyStateTracking()
{
}

TrackingEnemyStateTracking::~TrackingEnemyStateTracking()
{
}

EnemyState TrackingEnemyStateTracking::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	if (_owner->GetIsTracking())
	{
		trackingRotationVec = _owner->GetPosition() - trackingObject->GetPosition();
		trackingRotationVec.Normalize();

		velocity = trackingRotationVec * moveSpeed;
		// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

		RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
	}
	else
	{
		state = EnemyState::ENEMY_STATE_TURN;
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

	trackingObject = _owner->GetTrackingObject();
	moveSpeed = _owner->GetMoveSpeed();
	trackingRotationVec = _owner->GetPosition() - trackingObject->GetPosition();
	trackingRotationVec.Normalize();

	RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
}
