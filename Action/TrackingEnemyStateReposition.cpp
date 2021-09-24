#include "TrackingEnemyStateReposition.h"

TrackingEnemyStateReposition::TrackingEnemyStateReposition()
{
}

TrackingEnemyStateReposition::~TrackingEnemyStateReposition()
{
}

EnemyState TrackingEnemyStateReposition::Update(EnemyObjectBase* _owner, float _deltaTime)
{

	if (!_owner->GetIsTracking())
	{
		Vector3 tmpPosition;
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), firstPosition, _deltaTime * 1.0);
		_owner->SetPosition(tmpPosition);
	}
	else
	{
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	repositionRotationVec = firstPosition - _owner->GetPosition();
	repositionRotationVec.Normalize();
	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());

	Vector3 chackReposition = firstPosition - _owner->GetPosition();

	float Length = chackReposition.Length();

	if (Length <= 2.0f)
	{
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

void TrackingEnemyStateReposition::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_REPOSITION;
	_owner->SetState(State::Active);

	moveSpeed = _owner->GetMoveSpeed();
	firstPosition = _owner->GetFirstPosition();
	repositionRotationVec = firstPosition - _owner->GetPosition();
	repositionRotationVec.Normalize();

	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());

}
