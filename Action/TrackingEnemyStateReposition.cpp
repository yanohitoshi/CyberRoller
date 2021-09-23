#include "TrackingEnemyStateReposition.h"

TrackingEnemyStateReposition::TrackingEnemyStateReposition()
{
}

TrackingEnemyStateReposition::~TrackingEnemyStateReposition()
{
}

EnemyState TrackingEnemyStateReposition::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	//repositionRotationVec = _owner->GetPosition() - firstPosition;
	//repositionRotationVec.Normalize();

	if (!_owner->GetIsTracking())
	{
		velocity = repositionRotationVec * moveSpeed;
		// positionに速度を足してキャラクターを動かす
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}
	else
	{
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	return state;
	//RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());
}

void TrackingEnemyStateReposition::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_TRACKING;
	_owner->SetState(State::Active);

	moveSpeed = _owner->GetMoveSpeed();
	firstPosition = _owner->GetFirstPosition();
	repositionRotationVec = _owner->GetPosition() - firstPosition;
	repositionRotationVec.Normalize();

	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());
}
