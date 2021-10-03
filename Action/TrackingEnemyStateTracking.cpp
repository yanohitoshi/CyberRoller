#include "TrackingEnemyStateTracking.h"

TrackingEnemyStateTracking::TrackingEnemyStateTracking()
{
}

TrackingEnemyStateTracking::~TrackingEnemyStateTracking()
{
}

EnemyState TrackingEnemyStateTracking::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// 追跡対象から初期ポジションへと向かうベクトルを計算
	Vector3 trackingObjectToFirstPos = firstPosition - trackingObject->GetPosition();
	// オーナーのポジションから初期ポジションへと向かうベクトルを計算
	Vector3 ownerObjectToFirstPos = firstPosition - _owner->GetPosition();

	// 追跡対象から初期ポジションへのベクトルの長さ
	float trackingObjectToFirstPosLength = trackingObjectToFirstPos.LengthSq();
	// オーナーのポジションから初期ポジションへのベクトルの長さ
	float ownerObjectToFirstPosLength = ownerObjectToFirstPos.LengthSq();

	if (_owner->GetIsTracking())
	{
		// オーナーから追跡対象へ向かうベクトル
		trackingRotationVec =  trackingObject->GetPosition() - _owner->GetPosition();
		trackingRotationVec.z = 0.0f;
		float ownerPosToTrackingObjectLength = trackingRotationVec.Length();

		if (ownerPosToTrackingObjectLength >= 50.0f)
		{
			trackingRotationVec.Normalize();
			velocity = trackingRotationVec * moveSpeed;
			// positionに速度を足してキャラクターを動かす
			_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

			RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
		}
		else
		{
			velocity = Vector3::Zero;
			// positionに速度を足してキャラクターを動かす
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
		// positionに速度を足してキャラクターを動かす
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}

	return state;
}

void TrackingEnemyStateTracking::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
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
