#include "TrackingEnemyStateIdle.h"

TrackingEnemyStateIdle::TrackingEnemyStateIdle()
	: StayTime(60)
{
}

TrackingEnemyStateIdle::~TrackingEnemyStateIdle()
{
}

EnemyState TrackingEnemyStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	if (_owner->GetIsTracking() && !_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

void TrackingEnemyStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_IDLE;
	_owner->SetState(State::Active);
	RotationProcess(_owner, Vector3::NegUnitX, _owner->GetCharaForwardVec());
}
